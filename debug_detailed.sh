#!/bin/bash

echo "=== DEBUG: Análise detalhada do problema 2/10 ==="
echo ""

echo "Verificando implementação detalhada..."
echo ""

echo "1. VERIFICANDO CONVERSÃO DE STRINGS PARA DOUBLE:"
echo "   - Código usa: unformatNumber(m_previousNumber).toDouble(&ok1)"
echo "   - Para '2' deve retornar: 2.0"
echo "   - Para '10' deve retornar: 10.0"
echo ""

echo "2. VERIFICANDO OPERAÇÃO DE DIVISÃO:"
echo "   - Código usa: result = num1 / num2"
echo "   - Para 2.0 / 10.0 deve retornar: 0.2"
echo ""

echo "3. VERIFICANDO FORMATAÇÃO DO RESULTADO:"
echo "   - 0.2 é decimal, então vai para QString::number(result, 'f', 8)"
echo "   - Depois remove zeros desnecessários"
echo "   - Resultado esperado: '0.2'"
echo ""

echo "4. VERIFICANDO FUNÇÃO formatNumber():"
echo "   - '0.2' deve virar '0,2' (vírgula decimal brasileira)"
echo ""

echo "POSSÍVEIS CAUSAS DO PROBLEMA:"
echo ""

# Verificar se há alguma condição que possa estar causando o problema
echo "Verificando condições específicas..."

# 1. Verificar se waitingForNewNumber está sendo usado corretamente
if grep -A5 -B5 "waitingForNewNumber.*false" /home/dev_pc/Documentos/calculadora/src/Calculator.cpp; then
    echo "Encontrado uso de waitingForNewNumber"
else
    echo "Não encontrado problema óbvio com waitingForNewNumber"
fi

echo ""
echo "TESTE RECOMENDADO:"
echo "Execute a calculadora e teste passo a passo:"
echo "1. Abra a calculadora"
echo "2. Digite '2' - verifique se aparece '2' no display"
echo "3. Clique '/' - verifique se aparece '2 /' na label de operação"
echo "4. Digite '1' - verifique se aparece '1' no display"
echo "5. Digite '0' - verifique se aparece '10' no display"
echo "6. Clique '=' - verifique o resultado final"
echo ""
echo "Se em algum passo o comportamento for diferente, isso indica onde está o problema."
