# Library management system (C++17)

**English** · [Español](README.es.md)

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.16%2B-brightgreen)
![Platforms](https://img.shields.io/badge/Platforms-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey)

A terminal application to manage a university library. It handles **items** (books, e-books and
journals), **users** and **loans**, and it saves all the data in **CSV files**.

University project for the **Object-Oriented Programming** course at UDIT (Madrid), 2025–2026.
**Authors:** Andrea Ávila and Lucas Henrique Silva de Carvalho.

---

## Features

- Add, edit and remove items and users.
- Lend and return items, with deadlines and penalties for late returns.
- Search by title, author, category or date, and list all records.
- A report of active loans by user role.
- Data is loaded from CSV files at start-up and saved again when you exit.

## Design

- **Inheritance and polymorphism:** `Item` is the base class. `Book`, `Ebook` and `Journal` extend
  it. The catalog stores all of them together as `std::vector<Item*>`.
- **Separate classes by responsibility:** `User`, `Loan`, `Library` (the menus and the business
  rules) and `Filesystem` (reading and writing the CSV files).
- **Portable build with CMake:** the same project builds on Windows (MSVC or MinGW), macOS (Clang)
  and Linux (GCC or Clang). It compiles with `-Wall -Wextra -Wpedantic`, and CMake copies the CSV
  files next to the executable after each build.

## Project structure

```text
.
├── CMakeLists.txt
├── main.cpp            # main menu and program loop
├── Library.cpp/.h      # menus and library operations
└── Library
    ├── File            # Filesystem (CSV read/write) and the CSV data files
    ├── Item            # Item, Book, E-book, Journal
    ├── User            # User
    └── Loan            # Loan
```

## Build and run

You need **CMake 3.16+** and a **C++17** compiler.

macOS / Linux:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/ProyectoLibreria
```

Windows:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\ProyectoLibreria.exe
```

## CSV files

The program uses relative paths:

- `Library/File/items.csv`
- `Library/File/user.csv`
- `Library/File/loan.csv`

If you see *"No se pudo abrir el fichero"* ("could not open the file"), run the program from a
folder that contains `Library/File/` with the three CSV files. The build already copies them next
to the executable.

## Known issues

- In the main menu, option **3 (Handle Loans)** opens the user menu instead of the loan menu.
- The project has no automated tests yet.

## What I learned

- How to design a class hierarchy and use polymorphism with a shared base class.
- Manual memory management with `new` and `delete` for the collections. A next step would be to
  use smart pointers (`std::unique_ptr`).
- How to structure a C++ project with CMake so it builds on three operating systems.

## Authorship

This is original work by Andrea Ávila and Lucas Henrique Silva de Carvalho for the Object-Oriented
Programming course (2025/2026). ChatGPT was used to help write this README and the `CMakeLists.txt`.
The full authorship statement (in Spanish) is in [README.es.md](README.es.md#declaración-de-autoría).

## License

Academic / educational project.
