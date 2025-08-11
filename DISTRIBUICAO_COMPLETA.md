# 📦 Guia Completo de Distribuição - Calculadora Qt C++

## 🎯 **Meta: Criar executável Windows que "só baixa e executa"**

---

## 🚀 **MÉTODO 1: GitHub Actions (Automático) - RECOMENDADO**

### ✅ **Vantagens:**
- Compilação automática para Windows e Linux
- Releases automáticos com downloads
- Funciona sem ter Windows

### 📋 **Como fazer:**

1. **Enviar arquivos para GitHub:**
```bash
git add .
git commit -m "📦 Adicionar scripts de distribuição Windows"
git push
```

2. **Criar release:**
```bash
git tag v1.0.0
git push origin v1.0.0
```

3. **GitHub Actions irá:**
   - ✅ Compilar para Windows automaticamente
   - ✅ Criar `calculadora-windows-portable.zip`
   - ✅ Disponibilizar para download em "Releases"

### 🔗 **Resultado:**
- **URL de download:** `https://github.com/Eveneto/calculadora/releases/latest`
- **Arquivo:** `calculadora-windows-portable.zip`
- **Uso:** Usuário baixa, extrai e executa `calculadora.exe`

---

## 🖥️ **MÉTODO 2: Compilação Windows Local**

### 📋 **Pré-requisitos:**
1. **Qt 6.x para Windows** - https://www.qt.io/download-qt-installer
2. **CMake** - https://cmake.org/download/
3. **Git** - https://git-scm.com/download/win

### 🛠️ **Passos:**

1. **Clonar repositório:**
```cmd
git clone https://github.com/Eveneto/calculadora.git
cd calculadora
```

2. **Executar script de build:**
```cmd
build-windows.bat
```

3. **Resultado:**
   - Pasta `dist/` com executável e DLLs
   - Pronto para distribuição

### 📦 **Criar instalador (opcional):**
1. Instalar NSIS - https://nsis.sourceforge.io/
2. Executar: `makensis installer.nsi`
3. Resultado: `calculadora-setup.exe`

---

## 📱 **MÉTODO 3: Distribuição Online**

### 🌐 **Opções de hospedagem:**

#### **A) GitHub Releases (Grátis)**
- ✅ Automático com GitHub Actions
- ✅ Histórico de versões
- ✅ Download direto
- URL: `github.com/Eveneto/calculadora/releases`

#### **B) Google Drive/OneDrive**
- ✅ Simples de usar
- ❌ Não tem versionamento
- Compartilhar link do arquivo ZIP

#### **C) Site próprio**
- ✅ Controle total
- ❌ Precisa de hospedagem
- Exemplo: `seusite.com/downloads/calculadora.zip`

---

## 📋 **Estrutura do Pacote Final**

```
calculadora-windows-v1.0.0.zip
├── calculadora.exe          # Executável principal
├── Qt6Core.dll             # Bibliotecas Qt necessárias
├── Qt6Gui.dll
├── Qt6Widgets.dll
├── platforms/
│   └── qwindows.dll
├── README.txt              # Instruções de uso
└── LICENSE.txt             # Licença (opcional)
```

---

## 🎯 **Fluxo Completo para o Usuário**

### **Experiência ideal:**
1. 🔍 Usuário encontra: "Baixar Calculadora"
2. 📥 Clica e baixa: `calculadora-windows.zip` (5-15 MB)
3. 📂 Extrai o ZIP em qualquer pasta
4. ▶️ Executa: `calculadora.exe`
5. ✨ **Funciona imediatamente!**

### **Sem necessidade de:**
- ❌ Instalação adicional
- ❌ Permissões de administrador  
- ❌ Registro do Windows
- ❌ Instalação do Qt

---

## 🚀 **Próximos Passos Recomendados**

### **Imediato:**
1. ✅ Push dos novos arquivos para GitHub
2. ✅ Criar tag `v1.0.0` 
3. ✅ GitHub Actions compila automaticamente
4. ✅ Download disponível em "Releases"

### **Futuro:**
- 📱 Criar ícone personalizado
- 🔐 Assinatura digital (certificado)
- 🌐 Site/landing page
- 📊 Analytics de download

---

## 💡 **Exemplo de Marketing**

### **Texto para divulgação:**
```
🧮 Calculadora Qt C++ v1.0.0

✨ Interface moderna e intuitiva
🔢 Histórico de operações
⌨️ Suporte completo a teclado
🇧🇷 Formatação brasileira

📥 Download: github.com/Eveneto/calculadora/releases
💻 Windows 10/11 | Sem instalação
📦 Apenas 10MB | Funcionamento instantâneo
```

---

## ❓ **FAQ para Usuários**

**P: Preciso instalar algo?**  
R: Não! Apenas baixe, extraia e execute.

**P: É seguro?**  
R: Sim! Código aberto no GitHub.

**P: Funciona offline?**  
R: Sim! Não precisa de internet.

**P: Compatibilidade?**  
R: Windows 10/11, 32 e 64 bits.
