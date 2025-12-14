cmake_minimum_required(VERSION 3.16)

project(ProyectoLibreria VERSION 1.0.0 LANGUAGES CXX)

# ---- C++ Standard ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Executable ----
add_executable(ProyectoLibreria
    main.cpp
    Library.cpp
    Library/File/Filesystem.cpp
    Library/Item/Item.cpp
    Library/User/User.cpp
    Library/Loan/Loan.cpp
)

# ---- Include paths (por includes mixtos con/sin ruta) ----
target_include_directories(ProyectoLibreria PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Library
    ${CMAKE_CURRENT_SOURCE_DIR}/Library/File
    ${CMAKE_CURRENT_SOURCE_DIR}/Library/Item
    ${CMAKE_CURRENT_SOURCE_DIR}/Library/User
    ${CMAKE_CURRENT_SOURCE_DIR}/Library/Loan
)

# ---- Warnings ----
if (MSVC)
    target_compile_options(ProyectoLibreria PRIVATE /W4)
else()
    target_compile_options(ProyectoLibreria PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Copia de CSV al directorio de salida (para rutas relativas Library/File/*.csv) ----
add_custom_command(TARGET ProyectoLibreria POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:ProyectoLibreria>/Library/File"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/Library/File/items.csv"
            "$<TARGET_FILE_DIR:ProyectoLibreria>/Library/File/items.csv"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/Library/File/user.csv"
            "$<TARGET_FILE_DIR:ProyectoLibreria>/Library/File/user.csv"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/Library/File/loan.csv"
            "$<TARGET_FILE_DIR:ProyectoLibreria>/Library/File/loan.csv"
    VERBATIM
)

# ---- (Opcional) Install & packaging ----
include(GNUInstallDirs)
install(TARGETS ProyectoLibreria
    RUNTIME DESTINATION .
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Library/File"
    DESTINATION "Library"
    FILES_MATCHING PATTERN "*.csv"
)

include(CPack)