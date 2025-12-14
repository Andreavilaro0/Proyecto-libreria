#include <iostream>
#include <vector>

// Forward declarations
class Item;
class User;
class Loan;
class Book;
class Journal;
class Ebook;
class Filesystem;

// Item.h tiene un error: le falta }; al final
// Este workaround lo soluciona para test.cpp
#define ITEM_H
#include <string>
#include <algorithm>
#include <chrono>

class Item {
private:
  int id;
  std::string title, author, category;
  bool status = false;

public:
  Item() {};
  Item(int, std::string, std::string, std::string, bool);
  virtual std::string info() = 0;

  int getId()const;
  std::string getTitle()const;
  std::string getAuthor()const;
  std::string getCategory()const;
  bool getStatus()const;

  void setStatus(bool _status);
  void setTitle(std::string _title);
  void setAuthor(std::string _author);
  void setCategory(std::string _category);
};

#include "Filesystem.h"
#include "../Item/Book.h"
#include "../Item/Journal.h"
#include "../Item/E-book.h"
#include "../User/User.h"
#include "../Loan/Loan.h"

using namespace std;

int main() {
    vector<Item*> catalog;
    vector<User*> users;
    vector<Loan*> loans;

    // Cambia las rutas si tus CSV están en otra carpeta
    string itemsFile = "Data/items.csv";
    string usersFile = "Data/users.csv";
    string loansFile = "Data/loans.csv";

    cout << "=== TEST DE LECTURA DE ARCHIVOS ===" << endl;

    cout << "\nCargando Items..." << endl;
    if (!Filesystem::loadItems(itemsFile, catalog)) {
        cout << "Error cargando items." << endl;
        return 1;
    }
    cout << "Items cargados: " << catalog.size() << endl;

    cout << "\nCargando Usuarios..." << endl;
    if (!Filesystem::loadUsers(usersFile, users)) {
        cout << "Error cargando usuarios." << endl;
        return 1;
    }
    cout << "Usuarios cargados: " << users.size() << endl;

    cout << "\nCargando Préstamos..." << endl;
    if (!Filesystem::loadLoans(loansFile, loans, users, catalog)) {
        cout << "Error cargando préstamos." << endl;
        return 1;
    }
    cout << "Prestamos cargados: " << loans.size() << endl;


    cout << "\n=== MOSTRANDO OBJETOS CREADOS ===" << endl;

    // Items
    cout << "\n--- ITEMS ---" << endl;
    for (auto* item : catalog) {
        cout << "ID: " << item->getId()
             << " | Titulo: " << item->getTitle()
             << " | Autor: " << item->getAuthor()
             << " | Categoria: " << item->getCategory()
             << " | Estado: " << (item->getStatus() ? "Prestado" : "Disponible")
             << endl;

        // Mostrar atributos específicos según tipo
        Book* b = dynamic_cast<Book*>(item);
        if (b) {
            cout << "   Tipo: Libro" << endl;
        } 
        else {
            Journal* j = dynamic_cast<Journal*>(item);
            if (j) {
                cout << "   Tipo: Revista" << endl;
            }
            else {
                Ebook* e = dynamic_cast<Ebook*>(item);
                if (e) {
                    cout << "   Tipo: E-book"
                         << " | Licencia: " << e->getLicense()
                         << endl;
                }
            }
        }
    }

    // Usuarios
    cout << "\n--- USUARIOS ---" << endl;
    for (auto* u : users) {
        cout << "ID: " << u->getId()
             << " | Nombre: " << u->getName()
             << " | Rol: " << u->getRol()
             << endl;
    }

    // Préstamos
    cout << "\n--- PRESTAMOS ---" << endl;
    for (auto* l : loans) {
        cout << "Item: " << l->getItem()->getTitle()
             << " | Autor: " << l->getItem()->getAuthor()
             << endl;
    }

    // Liberar memoria
    for (auto* item : catalog) delete item;
    for (auto* u : users) delete u;
    for (auto* l : loans) delete l;

    cout << "\n=== TEST COMPLETADO ===" << endl;
    return 0;
}
