# 🔨 Resumo de Métodos de Build - Calculadora Qt C++

## 🚀 Scripts de Build Disponíveis

| Script | Descrição | Quando Usar |
|--------|-----------|-------------|
| `setup-complete.sh` | **Setup completo** - Verifica deps, instala se necessário, faz build e testa | ✅ **Primeira vez** ou setup limpo |
| `build-local.sh` | **Build completo** - Limpeza, configuração CMake e compilação com verificações | ✅ **Build limpo** ou após mudanças grandes |
| `build-quick.sh` | **Build rápido** - Apenas recompila (assume que CMake já foi configurado) | ✅ **Mudanças pequenas** no código |
| `test-functional.sh` | **Teste funcional** - Verifica se executável foi criado e funciona | ✅ **Validar build** |

## 🎯 Fluxos Recomendados

### 🆕 Primeira vez / Setup inicial
```bash
./setup-complete.sh
```
- ✅ Verifica todas dependências
- ✅ Instala deps se necessário (Ubuntu/Debian)
- ✅ Faz build completo
- ✅ Executa testes

### 🔄 Build após mudanças no código
```bash
./build-quick.sh
```
- ✅ Recompila rapidamente
- ✅ Apenas 5-15 segundos

### 🧹 Build limpo (resolver problemas)
```bash
./build-local.sh
```
- ✅ Limpa build anterior
- ✅ Reconfigura CMake
- ✅ Recompila tudo

### 🧪 Apenas testar
```bash
./test-functional.sh
```
- ✅ Verifica se executável existe
- ✅ Testa dependências
- ✅ Teste básico de funcionamento

## 📋 Dependências Necessárias

### Ubuntu/Debian
```bash
sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev
```

### Fedora/RHEL
```bash
sudo dnf install gcc-c++ cmake qt6-qtbase-devel qt6-qttools-devel
```

### Arch Linux
```bash
sudo pacman -S base-devel cmake qt6-base qt6-tools
```

## 🏃 Quick Start

```bash
# 1. Clone do repositório (se necessário)
git clone https://github.com/Eveneto/calculadora.git
cd calculadora

# 2. Setup completo
./setup-complete.sh

# 3. Executar
./build/calculadora
```

## 📊 Comparação de Métodos

| Aspecto | setup-complete.sh | build-local.sh | build-quick.sh |
|---------|------------------|----------------|----------------|
| **Tempo** | 60-120s (primeira vez) | 30-60s | 5-15s |
| **Verifica deps** | ✅ | ✅ | ❌ |
| **Instala deps** | ✅ (Ubuntu) | ❌ | ❌ |
| **Limpa build** | ✅ | ✅ | ❌ |
| **Configura CMake** | ✅ | ✅ | ❌ |
| **Compila** | ✅ | ✅ | ✅ |
| **Testa** | ✅ | Opcional | ❌ |

## 🎨 Output dos Scripts

Todos os scripts fornecem output colorido e informativo:
- 🔵 **[INFO]** - Informações gerais
- 🟢 **[SUCESSO]** - Operações bem-sucedidas  
- 🟡 **[AVISO]** - Avisos importantes
- 🔴 **[ERRO]** - Erros que impedem continuação

## 🔧 Opções Avançadas

### Build com Testes
```bash
cd build
cmake .. -DBUILD_TESTS=ON
make
./functional_test
```

### Build Debug
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

### Build específico (apenas executável)
```bash
cd build
make calculadora  # Apenas o executável principal
```

## 📂 Estrutura após Build

```
calculadora/
├── build/
│   ├── calculadora           # ← Executável principal
│   ├── CMakeCache.txt        # Cache do CMake
│   ├── Makefile              # Makefile gerado
│   └── CMakeFiles/           # Arquivos internos CMake
├── src/                      # Código fonte
├── include/                  # Headers
├── build-local.sh           # Scripts de build
├── build-quick.sh
├── setup-complete.sh
└── test-functional.sh
```

## 🚨 Solução de Problemas

### Build falha
1. Execute `./setup-complete.sh` para verificar deps
2. Se persistir, tente `./build-local.sh` para build limpo
3. Verifique logs de erro no terminal

### Qt6 não encontrado
```bash
# Ubuntu/Debian
sudo apt install qt6-base-dev qt6-tools-dev

# Verificar instalação
qmake6 --version
```

### Permissões de script
```bash
chmod +x *.sh
```

### Espaço em disco
- Build completo: ~20MB
- Limpar: `rm -rf build/`

## 🌐 Distribuição

Para distribuir para usuários finais, consulte:
- [`DISTRIBUICAO_COMPLETA.md`](DISTRIBUICAO_COMPLETA.md) - Todas opções
- [`DOWNLOAD.md`](DOWNLOAD.md) - Para usuários finais
- [`BUILD_WINDOWS_LOCAL.md`](BUILD_WINDOWS_LOCAL.md) - Build Windows
