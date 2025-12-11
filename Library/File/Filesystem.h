#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>

// Declaraciones adelantadas (solo punteros/referencias)
class Item;
class User;
class Loan;

// OJO: nombre de clase = Filesystem (con s minúscula)
class Filesystem {
public:
  // Carga desde CSV
  static bool loadItems(const std::string &filename,
                        std::vector<Item *> &catalog);
  static bool loadUsers(const std::string &filename,
                        std::vector<User *> &users);
  static bool loadLoans(const std::string &filename, std::vector<Loan *> &loans,
                        const std::vector<User *> &users,
                        const std::vector<Item *> &catalog);

  // Guardado a CSV
  static bool saveItems(const std::string &filename,
                        const std::vector<Item *> &catalog);
  static bool saveUsers(const std::string &filename,
                        const std::vector<User *> &users);
  static bool saveLoans(const std::string &filename,
                        const std::vector<Loan *> &loans);
};

#endif // FILESYSTEM_H
