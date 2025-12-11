#include <iostream>
#include <vector>
#include "Filesystem.h"
#include "../Item/Item.h"
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
             << " | Tipo: " << item->getType()
             << " | Titulo: " << item->getTitle()
             << " | Categoria: " << item->getCategory()
             << " | Estado: " << (item->isAvailable() ? "Disponible" : "Prestado")
             << endl;

        // Mostrar atributos específicos según tipo
        if (auto* b = dynamic_cast<Book*>(item)) {
            cout << "   Autor: " << b->getAuthor() << endl;
        } 
        else if (auto* j = dynamic_cast<Journal*>(item)) {
            cout << "   Autor: " << j->getAuthor() << endl;
        }
        else if (auto* e = dynamic_cast<EBook*>(item)) {
            cout << "   Autor: " << e->getAuthor()
                 << " | Licencia: " << e->getLicense()
                 << endl;
        }
    }

    // Usuarios
    cout << "\n--- USUARIOS ---" << endl;
    for (auto* u : users) {
        cout << "ID: " << u->getId()
             << " | Nombre: " << u->getName()
             << " | Rol: " << static_cast<int>(u->getRole())
             << endl;
    }

    // Préstamos
    cout << "\n--- PRESTAMOS ---" << endl;
    for (auto* l : loans) {
        cout << "Loan ID: " << l->getLoanId()
             << " | Usuario: " << l->getUser()->getName()
             << " | Item: " << l->getItem()->getTitle()
             << " | Fecha prestamo: " << l->getStartDate().toString()
             << " | Fecha devolución: " << l->getEndDate().toString()
             << endl;
    }

    // Liberar memoria
    for (auto* item : catalog) delete item;
    for (auto* u : users) delete u;
    for (auto* l : loans) delete l;

    cout << "\n=== TEST COMPLETADO ===" << endl;
    return 0;
}
