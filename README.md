# Proyecto Librería (C++17) — Gestión de Biblioteca

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.16%2B-brightgreen)
![Platforms](https://img.shields.io/badge/Platforms-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey)

Sistema de gestión de biblioteca por consola en **C++17** con **persistencia en CSV**.  
Permite administrar **ítems**, **usuarios** y **préstamos**, leyendo y guardando datos en archivos `.csv`.

---

## Contenido

- [Requisitos](#requisitos)
- [Estructura del proyecto](#estructura-del-proyecto)
- [Compilación](#compilación)
  - [macOS / Linux](#macos--linux)
  - [Windows](#windows)
- [Ejecución](#ejecución)
- [CSV y rutas](#csv-y-rutas)
- [Ejemplo de uso rápido](#ejemplo-de-uso-rápido)
- [Troubleshooting](#troubleshooting)
- [Notas de portabilidad](#notas-de-portabilidad)
- [Declaración de autoría](#declaración-de-autoría)
- [Licencia](#licencia)

---

## Requisitos

- **CMake 3.16+**
- Compilador con soporte **C++17**
  - **Windows:** Visual Studio (MSVC) / MinGW
  - **macOS:** Xcode Command Line Tools (Clang)
  - **Linux:** GCC o Clang

Comprobar versiones:
```bash
cmake --version
```

---

## Estructura del proyecto

Resumen de carpetas y archivos principales (referencia de organización):

```text
.
├── CMakeLists.txt
├── README.md
├── main.cpp
├── Library.cpp
├── Library.h
└── Library
    ├── File
    │   ├── Filesystem.cpp
    │   ├── Filesystem.h
    │   ├── items.csv
    │   ├── user.csv
    │   └── loan.csv
    ├── Item
    │   ├── Item.h
    │   └── Item.cpp
    ├── User
    │   ├── User.h
    │   └── User.cpp
    └── Loan
        ├── Loan.h
        └── Loan.cpp
```

---

## Compilación

### macOS / Linux
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

### Windows
```powershell
cmake -S . -B build
cmake --build build --config Release
```

---

## Ejecución

### macOS / Linux
```bash
./build/ProyectoLibreria
```

### Windows
```powershell
.\build\Release\ProyectoLibreria.exe
```

---

## CSV y rutas

El programa utiliza rutas relativas para los CSV:
- `Library/File/items.csv`
- `Library/File/user.csv`
- `Library/File/loan.csv`

Si ejecutas el binario desde otra carpeta, asegúrate de incluir también:
```
Library/File/
```
con los `.csv` dentro.

---

## Ejemplo de uso rápido

1) Compila con CMake (sección “Compilación”).  
2) Ejecuta el programa (sección “Ejecución”).  
3) Verifica que carga los CSV y realiza operaciones desde el menú.

---

## Troubleshooting

### “No se pudo abrir el fichero …”
Causa típica: el programa no encuentra los CSV por rutas relativas.

- Asegúrate de tener `Library/File/items.csv`, `Library/File/user.csv`, `Library/File/loan.csv`
- Ejecuta desde donde existan esas rutas:
  - macOS/Linux: `./build/ProyectoLibreria`
  - Windows: `.\build\Release\ProyectoLibreria.exe`

---

## Notas de portabilidad

No existe un único ejecutable que funcione igual en **Windows/macOS/Linux**.  
Lo portable es el **sistema de build con CMake**, que genera el ejecutable nativo en cada plataforma.

---

## Declaración de autoría

Nosotros, **Andrea Avila Rodriguez** y **Lucas Henrique Silva de Carvalho**, declaramos que el proyecto **“Gestión de Biblioteca”** (C++17), así como su documentación y ficheros asociados, es un trabajo **original** realizado por nosotros para la asignatura **Programación Orientada a Objetos** en el curso **2025/2026**.

Hemos utilizado únicamente recursos externos de carácter general (por ejemplo, documentación oficial de C++/CMake y material docente).TAambien chat gpt para realizar este README y CMAKE, Cuando corresponde, las ideas o fragmentos de referencia han sido consultados de forma legítima y sin plagio. **Nos responsabilizamos** del contenido y del funcionamiento del código entregado.

Fecha: **14/12/2026**  



## Licencia

Proyecto académico / educativo.