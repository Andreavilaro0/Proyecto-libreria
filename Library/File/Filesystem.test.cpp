#include "Filesystem.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {
std::string readFirstLine(const fs::path &path) {
  std::ifstream file(path);
  std::string line;
  std::getline(file, line);
  return line;
}
} // namespace

int main() {
  std::vector<Item *> catalog;
  std::vector<User *> users;
  std::vector<Loan *> loans;

  // Smoke tests: solo verificamos que los CSV se leen correctamente.
  assert(Filesystem::loadItems("Library/File/items.csv", catalog));
  assert(Filesystem::loadUsers("Library/File/user.csv", users));
  assert(Filesystem::loadLoans("Library/File/loan.csv", loans, users, catalog));

  // Comprobamos que los guardados generan archivos accesibles con la cabecera
  // esperada.
  const fs::path tempDir = fs::path("Library/File/.tmp_tests");
  fs::create_directories(tempDir);

  const fs::path itemsOut = tempDir / "items_out.csv";
  assert(Filesystem::saveItems(itemsOut.string(), catalog));
  assert(readFirstLine(itemsOut) == "id,title,author,category,status");

  const fs::path usersOut = tempDir / "users_out.csv";
  assert(Filesystem::saveUsers(usersOut.string(), users));
  assert(readFirstLine(usersOut) == "id,name,rol,count");

  const fs::path loansOut = tempDir / "loans_out.csv";
  assert(Filesystem::saveLoans(loansOut.string(), loans));
  assert(readFirstLine(loansOut) == "userId,itemId,startDay,deadline,returnDay");

  fs::remove_all(tempDir);

  std::cout << "Filesystem tests passed" << std::endl;
  return 0;
}

