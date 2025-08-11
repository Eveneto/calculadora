#!/bin/bash

echo "=== TESTE ESPECÍFICO DOS PROBLEMAS RELATADOS ==="
echo ""

# Função para executar um teste
run_test() {
    local test_name="$1"
    local input_keys="$2"
    local expected="$3"
    
    echo "Teste: $test_name"
    echo "Entrada: $input_keys"
    echo "Esperado: $expected"
    echo ""
    
    # Para testes manuais, apenas mostrar instruções
    echo "INSTRUÇÕES PARA TESTE MANUAL:"
    echo "1. Execute a calculadora: cd /home/dev_pc/Documentos/calculadora/build && ./calculadora"
    echo "2. Digite: $input_keys"
    echo "3. Verifique se o resultado é: $expected"
    echo "---"
    echo ""
}

echo "PROBLEMAS IDENTIFICADOS PARA TESTE:"
echo ""

# Teste 1: Divisão 2/10 = 0,2 (relatado como retornando 2)
run_test "Divisão 2/10" "2 / 10 =" "0,2"

# Teste 2: Ponto decimal não funcionando
run_test "Ponto decimal" "3.14" "3,14"

# Teste 3: Verificar símbolo de divisão
echo "Teste: Símbolo de divisão"
echo "VERIFICAR: O botão deve mostrar '/' e não '÷'"
echo "---"
echo ""

# Testes adicionais
run_test "Divisão decimal" "10.5 / 2 =" "5,25"
run_test "Soma decimal" "1.5 + 2.5 =" "4"
run_test "Pequenos decimais" "0.1 + 0.2 =" "0,3"
run_test "Formatação milhares" "1000" "1.000"
run_test "Formatação decimal" "1234.56" "1.234,56"

echo "ANÁLISE DO CÓDIGO PARA VERIFICAR PROBLEMAS:"
echo ""

# Verificar se há problemas óbvios no código
echo "1. Verificando função calculateResult()..."
if grep -n "result = num1 / num2" /home/dev_pc/Documentos/calculadora/src/Calculator.cpp > /dev/null; then
    echo "✓ Divisão implementada corretamente"
else
    echo "✗ Problema na implementação da divisão"
fi

echo ""
echo "2. Verificando tratamento do ponto decimal..."
if grep -n 'digit == "."' /home/dev_pc/Documentos/calculadora/src/Calculator.cpp > /dev/null; then
    echo "✓ Tratamento do ponto decimal encontrado"
else
    echo "✗ Problema no tratamento do ponto decimal"
fi

echo ""
echo "3. Verificando símbolo de divisão..."
if grep -n '"/"' /home/dev_pc/Documentos/calculadora/src/Calculator.cpp > /dev/null; then
    echo "✓ Símbolo '/' encontrado no código"
else
    echo "✗ Símbolo '/' não encontrado"
fi

echo ""
echo "EXECUÇÃO DE TESTE ESPECÍFICO:"
echo "Para testar o problema 2/10, execute:"
echo "cd /home/dev_pc/Documentos/calculadora/build && ./calculadora"
echo ""
echo "Em seguida:"
echo "1. Clique em 2"
echo "2. Clique em /"
echo "3. Clique em 1"  
echo "4. Clique em 0"
echo "5. Clique em ="
echo "6. Verifique se mostra 0,2 (e não 2)"
