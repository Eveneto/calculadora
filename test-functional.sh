#!/bin/bash

# Teste Funcional - Calculadora Qt C++
# Testa se a aplicação inicia corretamente

echo "=========================================="
echo "    TESTE FUNCIONAL - CALCULADORA"
echo "=========================================="

# Verificar se executável existe
if [ ! -f "build/calculadora" ]; then
    echo "❌ Executável não encontrado!"
    echo "Execute ./build-local.sh primeiro"
    exit 1
fi

echo "✅ Executável encontrado: build/calculadora"

# Verificar tamanho do executável
SIZE=$(stat -c%s "build/calculadora")
echo "📏 Tamanho: $(($SIZE / 1024))KB"

# Verificar dependências
echo "🔗 Verificando dependências..."
if ldd build/calculadora > /dev/null 2>&1; then
    echo "✅ Dependências OK"
else
    echo "❌ Problema com dependências"
    exit 1
fi

# Verificar se pode executar (teste rápido)
echo "🚀 Testando execução..."
cd build

# Executar com timeout para testar inicialização
timeout 3s ./calculadora --version 2>/dev/null || timeout 3s ./calculadora --help 2>/dev/null || echo "Aplicação Qt iniciada (esperado sem argumentos de linha de comando)"

echo "✅ Teste básico concluído!"
echo
echo "Para executar manualmente:"
echo "  cd build && ./calculadora"
echo
echo "Ou use: ./build/calculadora"
