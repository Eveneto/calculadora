#!/bin/bash

echo "================================================="
echo "  BATERIA DE TESTES MANUAL - CALCULADORA QT"
echo "================================================="

cd /home/dev_pc/Documentos/calculadora/build

echo ""
echo "🧮 Teste 1: Operações básicas"
echo "   2 + 3 = 5"
echo "   10 - 4 = 6" 
echo "   5 × 6 = 30"
echo "   15 / 3 = 5"
echo ""

echo "🔢 Teste 2: Operações decimais críticas"
echo "   2 / 10 = 0.2 (problema identificado)"
echo "   1 / 3 = 0.33333..."
echo "   0.5 + 0.3 = 0.8"
echo "   2.5 × 4 = 10"
echo ""

echo "📊 Teste 3: Formatação de números"
echo "   1234567 → 1.234.567"
echo "   1234.56 → 1.234,56"
echo "   0.123 → 0,123"
echo ""

echo "⚠️  Teste 4: Casos especiais"
echo "   5 / 0 → Erro (divisão por zero)"
echo "   999999999999999 + 1 → Número grande"
echo ""

echo "⌨️  Teste 5: Entrada por teclado"
echo "   Números: 0-9"
echo "   Operações: +, -, *, /"
echo "   Decimal: . ou ,"
echo "   Igual: Enter ou ="
echo "   Limpar: Esc, Del ou C"
echo "   Backspace: apagar último dígito"
echo ""

echo "📋 Teste 6: Histórico"
echo "   Adicionar operações"
echo "   Limpar histórico"
echo "   Reutilizar resultados"
echo ""

echo "🚀 Executando calculadora para teste manual..."
echo "   Por favor, teste os cenários acima!"
echo ""

./calculadora
