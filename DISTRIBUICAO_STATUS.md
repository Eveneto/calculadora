# 🚀 **Guia Completo de Distribuição - Calculadora Qt C++**

## 📦 **Status dos Builds Automáticos**

### ✅ **Linux Build**
- **Status**: ✅ Funcionando perfeitamente
- **Como usar**: Clone e compile localmente
- **Dependências**: Qt 6.x, CMake, GCC

### 🪟 **Windows Build**
- **Status**: 🔧 Em desenvolvimento
- **Problema atual**: Configuração do windeployqt
- **Soluções disponíveis**:

## 🛠️ **Opções para Download Windows**

### **1. Build Portátil (Disponível Agora)**
📁 **Arquivo**: `calculadora-windows-portable.zip`
- ✅ Executável compilado
- ⚠️ Requer Qt 6.x instalado no sistema
- 📥 Download via [GitHub Actions](https://github.com/Eveneto/calculadora/actions)

### **2. Build Completo (Em Progresso)**
📁 **Arquivo**: `calculadora-windows-x64.zip` 
- 🔧 Executável + todas as DLLs Qt
- ✅ Não requer instalação adicional
- 🎯 **Meta**: Funcionar igual programa normal

### **3. Instalador Windows (Futuro)**
📁 **Arquivo**: `calculadora-setup.exe`
- 🎯 Instalador profissional
- ✅ Menu Iniciar + Atalhos
- 🔧 Usa NSIS (script já criado)

## 💻 **Como Baixar Agora**

### **Opção 1: GitHub Actions (Automático)**
1. Vá em [Actions](https://github.com/Eveneto/calculadora/actions)
2. Clique no último build com ✅
3. Baixe `calculadora-windows-portable` ou `calculadora-windows-x64`
4. Extraia e execute!

### **Opção 2: Compilar Localmente**
```bash
# Windows (com Qt instalado)
git clone https://github.com/Eveneto/calculadora.git
cd calculadora
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Linux
sudo apt install qt6-base-dev cmake
git clone https://github.com/Eveneto/calculadora.git
cd calculadora
mkdir build && cd build
cmake .. && make
```

## 🔧 **Problemas Conhecidos e Soluções**

### **Problema**: Windows build falha no windeployqt
**Sintomas**: 
- Error: Process completed with exit code 1
- "Cannot open .: Access is denied"

**Soluções tentadas**:
- ✅ Configuração de paths do Qt
- ✅ Flags --no-translations 
- 🔧 Testando build sem windeployqt

**Status**: Corrigindo no próximo commit

### **Solução Temporária**
Para Windows, use a versão portátil que requer Qt instalado.

## 📈 **Roadmap de Distribuição**

### **Fase 1: ✅ Concluída**
- Repositório GitHub criado
- Código fonte completo
- Build Linux funcionando
- Documentação completa

### **Fase 2: 🔧 Em Progresso**
- Windows build automático
- Executável standalone
- GitHub Releases

### **Fase 3: 🎯 Planejada**
- Instalador Windows profissional
- Distribuição em Microsoft Store
- Versão macOS

## 🎯 **Para Usuários Finais**

**Quer apenas usar a calculadora?**

1. **Linux**: Clone e compile (5 minutos)
2. **Windows**: Baixe da seção Actions (1 minuto)
3. **Aguarde**: Build completo sendo finalizado

**Precisa de ajuda?**
- 💬 Abra uma [Issue](https://github.com/Eveneto/calculadora/issues)
- 📧 Entre em contato via GitHub

---
*Última atualização: Build Windows em correção final* 🚀
