
#include "Filesystem.h"

// Rutas relativas desde Library/File
#include "Item/Item.h"
#include "Loan/Loan.h"
#include "User/User.h"

#include <fstream>
#include <iostream>

// ========== ITEMS ==========

bool Filesystem::loadItems(const std::string &filename,
                           std::vector<Item *> &catalog) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "[ERROR] No se pudo abrir el fichero de items: " << filename
              << std::endl;
    return false;
  }

  // Aquí podrías limpiar el catálogo si quieres:
  // for (Item* it : catalog) delete it;
  // catalog.clear();

  // De momento solo leemos y descartamos para demostrar E/S correcta
  std::string line;
  while (std::getline(file, line)) {
    // En una versión más completa, aquí parseas la línea y creas Items
  }

  if (!file.good() && !file.eof()) {
    std::cerr << "[ERROR] Error leyendo el fichero de items: " << filename
              << std::endl;
    return false;
  }

  return true;
}

bool Filesystem::saveItems(const std::string &filename,
                           const std::vector<Item *> &catalog) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "[ERROR] No se pudo abrir el fichero de salida de items: "
              << filename << std::endl;
    return false;
  }

  // Cabecera de ejemplo
  file << "id,title,author,category,status\n";

  // Aquí podrías recorrer catalog y escribir realmente los datos
  // Ahora mismo solo demostramos que se escribe sin error.

  if (!file.good()) {
    std::cerr << "[ERROR] Error de escritura al guardar items en " << filename
              << std::endl;
    return false;
  }

  return true;
}

// ========== USERS ==========

bool Filesystem::loadUsers(const std::string &filename,
                           std::vector<User *> &users) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "[ERROR] No se pudo abrir el fichero de usuarios: " << filename
              << std::endl;
    return false;
  }

  // for (User* u : users) delete u;
  // users.clear();

  std::string line;
  while (std::getline(file, line)) {
    // Aquí en la versión completa crearás objetos User a partir del CSV
  }

  if (!file.good() && !file.eof()) {
    std::cerr << "[ERROR] Error leyendo el fichero de usuarios: " << filename
              << std::endl;
    return false;
  }

  return true;
}

bool Filesystem::saveUsers(const std::string &filename,
                           const std::vector<User *> &users) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "[ERROR] No se pudo abrir el fichero de salida de usuarios: "
              << filename << std::endl;
    return false;
  }

  file << "id,name,rol,count\n";

  // Aquí escribirías realmente la info de cada User

  if (!file.good()) {
    std::cerr << "[ERROR] Error de escritura al guardar usuarios en "
              << filename << std::endl;
    return false;
  }

  return true;
}

// ========== LOANS ==========

bool Filesystem::loadLoans(const std::string &filename,
                           std::vector<Loan *> &loans,
                           const std::vector<User *> &users,
                           const std::vector<Item *> &catalog) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "[ERROR] No se pudo abrir el fichero de préstamos: "
              << filename << std::endl;
    return false;
  }

  // for (Loan* l : loans) delete l;
  // loans.clear();

  std::string line;
  while (std::getline(file, line)) {
    // Aquí parsearías la línea y crearías Loan enlazando user/item
  }

  if (!file.good() && !file.eof()) {
    std::cerr << "[ERROR] Error leyendo el fichero de préstamos: " << filename
              << std::endl;
    return false;
  }

  return true;
}

bool Filesystem::saveLoans(const std::string &filename,
                           const std::vector<Loan *> &loans) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "[ERROR] No se pudo abrir el fichero de salida de préstamos: "
              << filename << std::endl;
    return false;
  }

  file << "userId,itemId,startDay,deadline,returnDay\n";

  // Aquí escribirías realmente la info de cada Loan

  if (!file.good()) {
    std::cerr << "[ERROR] Error de escritura al guardar préstamos en "
              << filename << std::endl;
    return false;
  }

  return true;
}
