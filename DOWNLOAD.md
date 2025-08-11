# 🧮 Calculadora Qt C++ - Download Executável Windows

## 📥 **Download Direto (Sem Instalação)**

### **Opção 1: GitHub Releases (Automático)**
1. Vá para: https://github.com/Eveneto/calculadora/releases
2. Baixe `calculadora-windows-x64.zip`
3. Extraia o arquivo ZIP
4. Execute `calculadora.exe`

### **Opção 2: GitHub Actions (Build Automático)**
1. Vá para: https://github.com/Eveneto/calculadora/actions
2. Clique no último build com ✅
3. Baixe `calculadora-windows-x64`
4. Extraia e execute `calculadora.exe`

## 🪟 **Requisitos Windows**
- Windows 10/11 (64-bit)
- Não precisa instalar Qt nem Visual Studio
- Todos os arquivos necessários estão inclusos

## ✨ **Funcionalidades**
- ➕ Operações básicas (+, -, ×, ÷)
- 📊 Histórico de operações
- ⌨️ Suporte a teclado
- 🇧🇷 Formatação brasileira (1.000,50)
- ⚠️ Validação de erros

## 🔧 **Como Compilar Você Mesmo**

### **Windows com Visual Studio:**
```cmd
git clone https://github.com/Eveneto/calculadora.git
cd calculadora
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

### **Criar executável standalone:**
```cmd
windeployqt Release/calculadora.exe
```

## 📁 **Estrutura do Download**
```
calculadora-windows-x64/
├── calculadora.exe     # ← Executável principal
├── Qt6Core.dll         # Bibliotecas Qt
├── Qt6Gui.dll
├── Qt6Widgets.dll
├── platforms/          # Plugins Qt
└── README.txt          # Instruções
```

## 🆘 **Problemas Comuns**

**"Arquivo não encontrado":**
- Extraia TODOS os arquivos do ZIP
- Mantenha calculadora.exe junto com as DLLs

**"Windows Defender bloqueia":**
- Clique em "Mais informações" → "Executar assim mesmo"
- É normal para executáveis não assinados

**"Não abre":**
- Clique direito → "Executar como administrador"
- Verifique se é Windows 64-bit

## 📞 **Suporte**
- Issues: https://github.com/Eveneto/calculadora/issues
- Email: [seu-email]
