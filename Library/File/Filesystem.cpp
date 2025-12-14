// Filesystem.cpp
#include "Filesystem.h"

#include "../Item/Item.h"
#include "../Item/Book.h"
#include "../Item/Journal.h"
#include "../Item/E-book.h"
#include "../User/User.h"
#include "../Loan/Loan.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>   // std::put_time
#include <algorithm> // std::remove_if

// ---------------- FECHA: YYYY-MM-DD → time_point ------------------

static std::chrono::system_clock::time_point parseDate(const std::string& dateStr) {
    if (dateStr.size() != 10) {
        return std::chrono::system_clock::time_point{};
    }

    int y = std::stoi(dateStr.substr(0, 4));
    int m = std::stoi(dateStr.substr(5, 2));
    int d = std::stoi(dateStr.substr(8, 2));

    std::tm tm{};
    tm.tm_year = y - 1900;
    tm.tm_mon  = m - 1;
    tm.tm_mday = d;

    std::time_t tt = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(tt);
}

// ---------------- time_point → "YYYY-MM-DD" -----------------------

static std::string formatDate(const std::chrono::system_clock::time_point& tp) {
    if (tp == std::chrono::system_clock::time_point{}) {
        return ""; // sin fecha
    }

    std::time_t tt = std::chrono::system_clock::to_time_t(tp);
    std::tm tm{};
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &tt);
#else
    localtime_r(&tt, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

// -------------------------- ITEMS -------------------------------
//
// Formato esperado:
// id,type,title,author,category,status,license,expiration

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

        int id = std::stoi(idStr);
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

        int id    = std::stoi(idStr);
        int count = std::stoi(countStr);

        User* user = new User(id, name, role, count);
        users.push_back(user);
    }

    return true;
}

// read loans
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

        int userId = std::stoi(userIdStr);
        int itemId = std::stoi(itemIdStr);

        User* userPtr = nullptr;
        Item* itemPtr = nullptr;

        for (User* u : users) {
            if (u && u->getId() == userId) {
                userPtr = u;
                break;
            }
        }

        for (Item* it : catalog) {
            if (it && it->getId() == itemId) {
                itemPtr = it;
                break;
            }
        }

        if (!userPtr || !itemPtr) {
            std::cerr << "[WARN] No se encontró user o item en línea: " << line << "\n";
            continue;
        }

        auto startDay  = parseDate(startStr);
        auto deadline  = parseDate(deadlineStr);
        auto returnDay = parseDate(returnStr);

        Loan* loan = new Loan(userPtr, itemPtr, startDay, deadline, returnDay);
        loans.push_back(loan);
    }

    return true;
}

//  save items

bool Filesystem::saveItems(const std::string& filename,
                           const std::vector<Item*>& catalog) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir el fichero para guardar items: "
                  << filename << "\n";
        return false;
    }

    file << "id,type,title,author,category,status,license,expiration\n";

    for (const Item* it : catalog) {
        if (!it) continue;

        std::string type;
        std::string license;
        std::string expirationStr;

        if (dynamic_cast<const Book*>(it)) {
            type = "Book";
        } else if (dynamic_cast<const Journal*>(it)) {
            type = "Journal";
        } else if (auto eb = dynamic_cast<const Ebook*>(it)) {
            type         = "EBook";
            license      = eb->getLicense();
            expirationStr = formatDate(eb->getExpiration());
        } else {
            type = "Unknown";
        }

        file << it->getId() << ','
             << type << ','
             << it->getTitle() << ','
             << it->getAuthor() << ','
             << it->getCategory() << ','
             << (it->getStatus() ? "true" : "false") << ','
             << license << ','
             << expirationStr
             << '\n';
    }

    return true;
}

//  save users

bool Filesystem::saveUsers(const std::string& filename,
                           const std::vector<User*>& users) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir el fichero para guardar users: "
                  << filename << "\n";
        return false;
    }

    file << "id,name,role,count\n";

    for (const User* u : users) {
        if (!u) continue;

        file << u->getId() << ','
             << u->getName() << ','
             << u->getRol() << ','
             << u->getCount()
             << '\n';
    }

    return true;
}

//  save loans

bool Filesystem::saveLoans(const std::string& filename,
                           const std::vector<Loan*>& loans) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir el fichero para guardar loans: "
                  << filename << "\n";
        return false;
    }

    file << "userId,itemId,startDate,deadline,returnDate\n";

    for (const Loan* l : loans) {
        if (!l) continue;

        file << l->getUser()->getId() << ','
             << l->getItem()->getId() << ','
             << formatDate(l->getStartDay()) << ','
             << formatDate(l->getDeadline()) << ','
             << formatDate(l->getReturnDay())
             << '\n';
    }

    return true;
}

//  Delete items

bool Filesystem::deleteItemById(int id, std::vector<Item*>& catalog) {
    bool found = false;

    auto it = std::remove_if(catalog.begin(), catalog.end(),
                             [&](Item* item) {
                                 if (item && item->getId() == id) {
                                     delete item;
                                     found = true;
                                     return true;
                                 }
                                 return false;
                             });

    catalog.erase(it, catalog.end());
    return found;
}

//  Delete user

bool Filesystem::deleteUserById(int id, std::vector<User*>& users) {
    bool found = false;

    auto it = std::remove_if(users.begin(), users.end(),
                             [&](User* u) {
                                 if (u && u->getId() == id) {
                                     delete u;
                                     found = true;
                                     return true;
                                 }
                                 return false;
                             });

    users.erase(it, users.end());
    return found;
}

//  Delete loans

bool Filesystem::deleteLoanByIndex(size_t index, std::vector<Loan*>& loans) {
    if (index >= loans.size()) {
        return false;
    }

    delete loans[index];
    loans.erase(loans.begin() + index);
    return true;
}