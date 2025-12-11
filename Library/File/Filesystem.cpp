
#include "../Item/Item.h"
#include "../Item/Book.h"
#include "../Item/Journal.h"
#include "../Item/Ebook.h"
#include "../User/User.h"
#include "../Loan/Loan.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <ctime>



// ---------------- FECHA: YYYY-MM-DD → time_point ------------------

static std::chrono::system_clock::time_point parseDate(const std::string& dateStr) {
    if (dateStr.size() != 10) {
        return std::chrono::system_clock::time_point{};
    }

    int y = stoi(dateStr.substr(0, 4));
    int m = stoi(dateStr.substr(5, 2));
    int d = stoi(dateStr.substr(8, 2));

    std::tm tm{};
    tm.tm_year = y - 1900;
    tm.tm_mon = m - 1;
    tm.tm_mday = d;

    std::time_t tt = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(tt);
}

// -------------------------- ITEMS -------------------------------
//
// Formato esperado:


bool Filesystem::loadItems(const std::string& filename, std::vector<Item*>& catalog) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir el fichero de items.\n";
        return false;
    }

    std::string line;

    // Saltar cabecera
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);

        std::string idStr, type, title, author, category, statusStr, license, expirationStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, type, ',');
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, category, ',');
        std::getline(ss, statusStr, ',');
        std::getline(ss, license, ',');
        std::getline(ss, expirationStr, ',');

        int id = stoi(idStr);
        bool status = (statusStr == "true" || statusStr == "1");

        Item* item = nullptr;

        if (type == "Book") {
            item = new Book(id, title, author, category, status);

        } else if (type == "Journal") {
            item = new Journal(id, title, author, category, status);

        } else if (type == "Ebook" || type == "EBook") {
            auto exp = parseDate(expirationStr);
            item = new Ebook(id, title, author, category, status, license, exp);
        }

        if (item != nullptr) {
            catalog.push_back(item);
        }
    }

    return true;
}

// --------------------------- USERS ------------------------------
//
// Formato esperado:
// id,name,role,count


bool Filesystem::loadUsers(const std::string& filename, std::vector<User*>& users) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir usuarios.\n";
        return false;
    }

    std::string line;

    std::getline(file, line); // cabecera

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);

        std::string idStr, name, role, countStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, role, ',');
        std::getline(ss, countStr, ',');

        int id = stoi(idStr);
        int count = stoi(countStr);

        User* user = new User(id, name, role, count);
        users.push_back(user);
    }

    return true;
}

// --------------------------- LOANS -------------------------------
//
// Formato esperado:
// userId,itemId,startDate,deadline,returnDate
// 1,3,2025-01-10,2025-01-20,2025-01-18

bool Filesystem::loadLoans(const std::string& filename,
                           std::vector<Loan*>& loans,
                           const std::vector<User*>& users,
                           const std::vector<Item*>& catalog) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir préstamos.\n";
        return false;
    }

    std::string line;
    std::getline(file, line); // cabecera

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);

        std::string userIdStr, itemIdStr, startStr, deadlineStr, returnStr;

        std::getline(ss, userIdStr, ',');
        std::getline(ss, itemIdStr, ',');
        std::getline(ss, startStr, ',');
        std::getline(ss, deadlineStr, ',');
        std::getline(ss, returnStr, ',');

        int userId = stoi(userIdStr);
        int itemId = stoi(itemIdStr);

        User* userPtr = nullptr;
        Item* itemPtr = nullptr;

        // Buscar user sin break
        for (size_t i = 0; i < users.size(); i++) {
            if (users[i] && users[i]->getId() == userId) {
                userPtr = users[i];
            }
        }

        // Buscar item sin break
        for (size_t i = 0; i < catalog.size(); i++) {
            if (catalog[i] && catalog[i]->getId() == itemId) {
                itemPtr = catalog[i];
            }
        }

        if (!userPtr || !itemPtr) {
            std::cerr << "[WARN] No se encontró user o item en línea: " << line << "\n";
            continue;
        }

        auto startDay   = parseDate(startStr);
        auto deadline   = parseDate(deadlineStr);
        auto returnDay  = parseDate(returnStr);

        Loan* loan = new Loan(userPtr, itemPtr, startDay, deadline, returnDay);
        loans.push_back(loan);
    }

    return true;
}
