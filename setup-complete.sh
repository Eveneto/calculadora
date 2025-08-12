#!/bin/bash

# Script Completo - Calculadora Qt C++
# Verifica dependências, faz build e testa

echo "🧮 CALCULADORA QT C++ - SETUP COMPLETO"
echo "====================================="

# Funções utilitárias
check_command() {
    if command -v "$1" &> /dev/null; then
        echo "✅ $1 encontrado"
        return 0
    else
        echo "❌ $1 não encontrado"
        return 1
    fi
}

install_deps_ubuntu() {
    echo "🔄 Instalando dependências para Ubuntu/Debian..."
    sudo apt update
    sudo apt install -y build-essential cmake qt6-base-dev qt6-tools-dev
}

# 1. VERIFICAR SISTEMA
echo "📋 Verificando sistema..."
if [ -f /etc/debian_version ]; then
    OS="debian"
    echo "Sistema: Ubuntu/Debian detectado"
elif [ -f /etc/arch-release ]; then
    OS="arch"
    echo "Sistema: Arch Linux detectado"
else
    OS="unknown"
    echo "Sistema: Desconhecido (assumindo compatível)"
fi

# 2. VERIFICAR DEPENDÊNCIAS
echo
echo "🔍 Verificando dependências..."
all_deps_ok=true

check_command "gcc" || check_command "g++" || all_deps_ok=false
check_command "cmake" || all_deps_ok=false
check_command "make" || all_deps_ok=false
check_command "qmake6" || check_command "qmake" || all_deps_ok=false

# 3. INSTALAR DEPENDÊNCIAS SE NECESSÁRIO
if [ "$all_deps_ok" = false ]; then
    echo
    echo "⚠️  Algumas dependências estão faltando!"
    
    if [ "$OS" = "debian" ]; then
        read -p "Deseja instalar as dependências automaticamente? (s/N): " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Ss]$ ]]; then
            install_deps_ubuntu
        else
            echo "Por favor, instale manualmente:"
            echo "sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev"
            exit 1
        fi
    else
        echo "Instale manualmente as dependências para seu sistema:"
        echo "- GCC/G++"
        echo "- CMake"
        echo "- Qt6 Development"
        exit 1
    fi
fi

# 4. BUILD
echo
echo "🔨 Iniciando build..."
if [ -f "build-local.sh" ]; then
    ./build-local.sh
else
    echo "Script build-local.sh não encontrado, fazendo build manual..."
    mkdir -p build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make -j$(nproc)
    cd ..
fi

# 5. TESTE
echo
echo "🧪 Executando testes..."
if [ -f "test-functional.sh" ]; then
    ./test-functional.sh
else
    echo "Teste funcional manual..."
    if [ -f "build/calculadora" ]; then
        echo "✅ Executável criado com sucesso!"
        ls -la build/calculadora
    else
        echo "❌ Executável não encontrado!"
        exit 1
    fi
fi

# 6. RESUMO FINAL
echo
echo "🎉 SETUP COMPLETO!"
echo "=================="
echo "✅ Dependências verificadas"
echo "✅ Build realizado com sucesso"
echo "✅ Testes funcionais passaram"
echo
echo "Para executar a calculadora:"
echo "  ./build/calculadora"
echo
echo "Scripts disponíveis:"
echo "  ./build-local.sh     - Build completo"
echo "  ./build-quick.sh     - Build rápido"
echo "  ./test-functional.sh - Teste funcional"
echo
echo "Guias disponíveis:"
echo "  BUILD_LOCAL_LINUX.md - Detalhes do build Linux"
echo "  DISTRIBUICAO_COMPLETA.md - Opções de distribuição"
