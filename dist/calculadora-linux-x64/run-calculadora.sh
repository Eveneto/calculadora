#!/bin/bash

# Script de execução da Calculadora Qt C++
# Configura o ambiente e executa a aplicação

# Obter diretório do script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Configurar biblioteca Qt
export LD_LIBRARY_PATH="$DIR:$LD_LIBRARY_PATH"
export QT_PLUGIN_PATH="$DIR"

# Executar calculadora
cd "$DIR"
./calculadora "$@"
