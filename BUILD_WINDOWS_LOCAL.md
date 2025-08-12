# 🪟 Compilação Local Windows - Guia Passo a Passo

## 📋 **MÉTODO 1: Script Automático (Recomendado)**

### **Pré-requisitos:**
1. **Qt 6.x para Windows** - [Download aqui](https://www.qt.io/download-qt-installer)
2. **CMake** - [Download aqui](https://cmake.org/download/)
3. **Visual Studio Community** (grátis) - [Download aqui](https://visualstudio.microsoft.com/pt-br/vs/community/)

### **Passos Rápidos:**
1. Instale Qt 6.x (escolha MSVC 2019 64-bit)
2. Instale CMake (marque "Add to PATH")
3. Instale Visual Studio Community (com C++)
4. Execute o script `build-local-windows.bat`

---

## 📋 **MÉTODO 2: Passo a Passo Manual**

### **1. Preparar Ambiente:**
```cmd
# Abrir "Developer Command Prompt for VS 2019/2022"
# (Procurar no Menu Iniciar)

# Navegar para pasta do projeto
cd C:\caminho\para\calculadora
```

### **2. Configurar Paths:**
```cmd
# Definir caminho do Qt (ajuste conforme sua instalação)
set Qt6_DIR=C:\Qt\6.5.0\msvc2019_64\lib\cmake\Qt6
set PATH=%PATH%;C:\Qt\6.5.0\msvc2019_64\bin
```

### **3. Compilar:**
```cmd
# Criar pasta de build
mkdir build-windows
cd build-windows

# Configurar CMake
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -G "Visual Studio 16 2019" -A x64

# Compilar
cmake --build . --config Release --target calculadora
```

### **4. Preparar Distribuição:**
```cmd
# Criar pasta para arquivos finais
mkdir ..\dist
copy Release\calculadora.exe ..\dist\

# Copiar DLLs do Qt
windeployqt ..\dist\calculadora.exe --release --no-translations
```

---

## 🛠️ **MÉTODO 3: MinGW (Alternativo)**

Se não quiser instalar Visual Studio:

### **Pré-requisitos:**
1. Qt 6.x com MinGW
2. CMake

### **Comandos:**
```cmd
mkdir build-mingw
cd build-mingw

cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -G "MinGW Makefiles"
mingw32-make

mkdir ..\dist
copy calculadora.exe ..\dist\
windeployqt ..\dist\calculadora.exe --release --no-translations
```

---

## 📦 **Resultado Final**

Após qualquer método, você terá:
```
dist/
├── calculadora.exe
├── Qt6Core.dll
├── Qt6Gui.dll
├── Qt6Widgets.dll
├── platforms/
└── outros arquivos Qt necessários
```

**Total**: ~15-25 MB
**Funcionamento**: Standalone (não precisa Qt instalado)

---

## 🚀 **Distribuir o Executável**

### **Criar ZIP:**
1. Comprimir pasta `dist/` 
2. Renomear para `calculadora-windows-v1.0.zip`
3. Pronto para distribuir!

### **Testar:**
1. Copie a pasta `dist/` para outro PC
2. Execute `calculadora.exe`
3. Deve funcionar sem Qt instalado

---

## ❗ **Soluções para Problemas Comuns**

### **"Qt6Core.dll não encontrado"**
```cmd
# Verificar se windeployqt rodou corretamente
windeployqt --verbose ..\dist\calculadora.exe
```

### **"CMake não encontrado"**
```cmd
# Adicionar CMake ao PATH ou usar caminho completo
"C:\Program Files\CMake\bin\cmake.exe" ..
```

### **"Qt6_DIR não encontrado"**
```cmd
# Definir manualmente
set Qt6_DIR=C:\Qt\6.5.0\msvc2019_64\lib\cmake\Qt6
```

### **Erro do Visual Studio**
```cmd
# Usar Developer Command Prompt, não CMD normal
# Ou definir ambiente:
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
```

---

## 🎯 **Quer Apenas o Executável Pronto?**

Se não quiser compilar, posso te enviar o executável compilado ou você pode:

1. **Usar WSL/Linux** e compilar para Linux
2. **Aguardar** eu corrigir o GitHub Actions
3. **Pedir ajuda** com algum passo específico

Qual método prefere tentar primeiro?
