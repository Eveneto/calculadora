#!/bin/bash

echo "=== BATERIA DE TESTES ESPECÍFICOS ==="
echo "Testando as questões identificadas:"
echo ""

echo "1. Teste de divisão 2/10 (deve ser 0.2):"
echo "   - Digite: 2 ÷ 10 ="
echo "   - Resultado esperado: 0,2"
echo ""

echo "2. Teste do ponto decimal:"
echo "   - Digite: 3.14"
echo "   - Deve aceitar o ponto e mostrar 3,14"
echo ""

echo "3. Teste símbolo de divisão:"
echo "   - Verificar se o botão mostra '/' e não '÷'"
echo ""

echo "4. Testes de cálculo decimal:"
echo "   - 1.5 + 2.5 = 4"
echo "   - 10.5 ÷ 2 = 5,25"
echo "   - 0.1 + 0.2 = 0,3"
echo ""

echo "5. Testes de formatação:"
echo "   - 1000 = 1.000"
echo "   - 1234.56 = 1.234,56"
echo ""

echo "Executando calculadora para testes manuais..."
echo "Pressione Ctrl+C para sair quando terminar os testes."

cd /home/dev_pc/Documentos/calculadora/build
if [ -f calculadora ]; then
    ./calculadora
else
    echo "Erro: executável da calculadora não encontrado!"
    echo "Execute: cd build && cmake .. && make"
fi
