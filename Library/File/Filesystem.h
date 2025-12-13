#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>

class Item;
class User;
class Loan;

class Filesystem {
public:
    // Carga desde CSV
    static bool loadItems(const std::string& filename, std::vector<Item*>& catalog);
    static bool loadUsers(const std::string& filename, std::vector<User*>& users);
    static bool loadLoans(const std::string& filename,
                          std::vector<Loan*>& loans,
                          const std::vector<User*>& users,
                          const std::vector<Item*>& catalog);

    // Guardado a CSV
    static bool saveItems(const std::string& filename, const std::vector<Item*>& catalog);
    static bool saveUsers(const std::string& filename, const std::vector<User*>& users);
    static bool saveLoans(const std::string& filename, const std::vector<Loan*>& loans);
    
    // Eliminación por ID
    static bool deleteItemById(int id, std::vector<Item*>& catalog);
    static bool deleteUserById(int id, std::vector<User*>& users);
    static bool deleteLoanByIndex(size_t index, std::vector<Loan*>& loans);
};

#endif // FILESYSTEM_H
