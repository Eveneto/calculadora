# Build Local - Calculadora Qt C++

Este guia explica como fazer o build local da calculadora no Linux.

## Dependências Necessárias

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev
```

### Fedora/CentOS/RHEL
```bash
sudo dnf install gcc-c++ cmake qt6-qtbase-devel qt6-qttools-devel
```

### Arch Linux
```bash
sudo pacman -S base-devel cmake qt6-base qt6-tools
```

## Como Fazer o Build

### Método 1: Script Automático (Recomendado)
```bash
# Clone o repositório (se ainda não tiver)
git clone https://github.com/Eveneto/calculadora.git
cd calculadora

# Execute o script de build
./build-local.sh
```

### Método 2: Manual
```bash
# Criar diretório de build
mkdir -p build
cd build

# Configurar com CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Compilar
make -j$(nproc)

# Executar
./calculadora
```

### Método 3: Build Rápido (após primeiro build)
```bash
# Para recompilar após mudanças
./build-quick.sh
```

## Scripts Disponíveis

| Script | Descrição |
|--------|-----------|
| `build-local.sh` | Build completo com verificações e limpeza |
| `build-quick.sh` | Build rápido (apenas recompila) |

## Opções de Build

### Build com Testes
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON
make
./functional_test  # Executar testes
```

### Build Debug
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

### Build Release (Otimizado)
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Verificação da Instalação

### Verificar Qt6
```bash
qmake6 --version
```

### Verificar CMake
```bash
cmake --version
```

### Verificar Compilador
```bash
g++ --version
```

## Estrutura de Arquivos após Build

```
calculadora/
├── build/
│   ├── calculadora          # ← Executável principal
│   ├── functional_test      # ← Testes (se BUILD_TESTS=ON)
│   └── ...                  # Arquivos de build CMake
├── src/                     # Código fonte
├── include/                 # Headers
└── build-local.sh          # Script de build
```

## Executar a Aplicação

```bash
# Opção 1: Do diretório raiz
./build/calculadora

# Opção 2: Do diretório build
cd build
./calculadora
```

## Solução de Problemas

### Qt6 não encontrado
```bash
# Ubuntu/Debian
sudo apt install qt6-base-dev qt6-tools-dev

# Verificar instalação
dpkg -l | grep qt6
```

### CMake muito antigo
```bash
# Ubuntu 20.04 ou mais antigo
sudo apt install cmake=3.16* # ou superior
```

### Erro de permissão no script
```bash
chmod +x build-local.sh
chmod +x build-quick.sh
```

### Build falha por dependências
```bash
# Instalar dependências de desenvolvimento
sudo apt install build-essential

# Verificar se todas estão instaladas
sudo apt install cmake qt6-base-dev qt6-tools-dev build-essential
```

## Distribuição do Executável

O executável compilado (`build/calculadora`) pode ser distribuído, mas requer que o Qt6 esteja instalado no sistema de destino.

Para criar um pacote independente, consulte `DISTRIBUICAO_COMPLETA.md`.

## Performance

- **Build completo**: ~30-60 segundos
- **Build incremental**: ~5-15 segundos
- **Tamanho do executável**: ~50KB (sem Qt incluído)
- **RAM necessária para build**: ~500MB
- **Espaço em disco**: ~20MB (diretório build)

## Recursos do Build

- ✅ Compilação otimizada (Release)
- ✅ Suporte a múltiplos cores (`-j$(nproc)`)
- ✅ Verificação automática de dependências
- ✅ Limpeza automática de builds anteriores
- ✅ Verificação de integridade do executável
- ✅ Testes opcionais
- ✅ Output colorido e informativo
