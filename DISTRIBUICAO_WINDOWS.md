# Guia de Distribuição - Calculadora Qt C++ para Windows

## 🎯 Objetivo
Criar um executável .exe que funciona em qualquer Windows sem instalação adicional.

## 📋 Opções de Distribuição

### Opção 1: Cross-compilation (Linux → Windows)
### Opção 2: Compilação nativa no Windows  
### Opção 3: GitHub Actions (CI/CD automático)

---

## 🛠️ OPÇÃO 1: Cross-compilation (Recomendado)

### Pré-requisitos Linux:
```bash
# Instalar MinGW para cross-compilation
sudo apt install mingw-w64 wine

# Baixar Qt para Windows
# https://download.qt.io/official_releases/qt/6.5/
```

### Configurar CMake para Windows:
```cmake
# CMakeLists.txt - adicionar configuração Windows
if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/mingw_64")
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
endif()
```

---

## 🏗️ OPÇÃO 2: Compilação Windows Nativa

### Ferramentas necessárias:
1. **Qt 6.x para Windows** (com MinGW ou MSVC)
2. **CMake** 
3. **Git**

### Comandos no Windows:
```cmd
git clone https://github.com/Eveneto/calculadora.git
cd calculadora
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

---

## 📦 OPÇÃO 3: GitHub Actions (Automático)

Criar workflow que compila para múltiplas plataformas automaticamente.

---

## 🚀 Empacotamento Final

### Usar windeployqt para incluir DLLs Qt:
```cmd
windeployqt.exe calculadora.exe
```

### Criar instalador com NSIS ou Inno Setup

### Resultado: 
- calculadora-setup.exe (instalador)
- calculadora-portable.zip (versão portátil)
