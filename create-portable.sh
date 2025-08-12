#!/bin/bash

# Criador de Pacote Portátil - Calculadora Qt C++
# Cria um pacote ZIP com executável e dependências Qt

echo "📦 CRIADOR DE PACOTE PORTÁTIL"
echo "============================="

# Verificar se executável existe
if [ ! -f "build/calculadora" ]; then
    echo "❌ Executável não encontrado!"
    echo "Execute ./build-local.sh primeiro"
    exit 1
fi

# Configurações
PACKAGE_NAME="calculadora-linux-x64"
PACKAGE_DIR="dist/$PACKAGE_NAME"
ZIP_FILE="$PACKAGE_NAME.zip"

echo "📋 Configurações:"
echo "   Nome do pacote: $PACKAGE_NAME"
echo "   Diretório: $PACKAGE_DIR"
echo "   Arquivo final: $ZIP_FILE"
echo

# Limpar e criar diretório de distribuição
echo "🧹 Preparando diretório..."
rm -rf dist/
mkdir -p "$PACKAGE_DIR"

# Copiar executável
echo "📋 Copiando executável..."
cp build/calculadora "$PACKAGE_DIR/"
chmod +x "$PACKAGE_DIR/calculadora"

# Encontrar dependências Qt
echo "🔍 Identificando dependências Qt..."
QT_LIBS=$(ldd build/calculadora | grep libQt | awk '{print $3}')

if [ -z "$QT_LIBS" ]; then
    echo "❌ Não foi possível encontrar dependências Qt!"
    exit 1
fi

echo "📦 Copiando bibliotecas Qt..."
for lib in $QT_LIBS; do
    if [ -f "$lib" ]; then
        cp "$lib" "$PACKAGE_DIR/"
        echo "  ✓ $(basename $lib)"
    fi
done

# Copiar outras dependências importantes
echo "🔗 Copiando dependências sistema..."
OTHER_LIBS=$(ldd build/calculadora | grep -E "(libstdc\+\+|libgcc_s)" | awk '{print $3}')
for lib in $OTHER_LIBS; do
    if [ -f "$lib" ]; then
        cp "$lib" "$PACKAGE_DIR/"
        echo "  ✓ $(basename $lib)"
    fi
done

# Encontrar e copiar plugins Qt necessários
echo "🔌 Copiando plugins Qt..."
QT_PLUGIN_PATH="/usr/lib/x86_64-linux-gnu/qt6/plugins"
if [ -d "$QT_PLUGIN_PATH" ]; then
    # Plataformas (necessário para interface gráfica)
    mkdir -p "$PACKAGE_DIR/platforms"
    if [ -f "$QT_PLUGIN_PATH/platforms/libqxcb.so" ]; then
        cp "$QT_PLUGIN_PATH/platforms/libqxcb.so" "$PACKAGE_DIR/platforms/"
        echo "  ✓ platforms/libqxcb.so"
    fi
    
    # Imageformats (opcional, para ícones)
    if [ -d "$QT_PLUGIN_PATH/imageformats" ]; then
        mkdir -p "$PACKAGE_DIR/imageformats"
        cp "$QT_PLUGIN_PATH/imageformats"/*.so "$PACKAGE_DIR/imageformats/" 2>/dev/null || true
        echo "  ✓ imageformats/"
    fi
fi

# Criar script de execução
echo "📜 Criando script de execução..."
cat > "$PACKAGE_DIR/run-calculadora.sh" << 'EOF'
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
EOF

chmod +x "$PACKAGE_DIR/run-calculadora.sh"

# Criar README para o usuário
echo "📄 Criando documentação..."
cat > "$PACKAGE_DIR/README.txt" << EOF
🧮 CALCULADORA QT C++ - VERSÃO PORTÁTIL
=====================================

📋 COMO USAR:
1. Extraia este arquivo ZIP em qualquer pasta
2. Execute: ./run-calculadora.sh
   OU clique duplo em: calculadora

🔧 FUNCIONALIDADES:
✓ Operações básicas: +, -, *, /
✓ Histórico de operações
✓ Interface gráfica moderna
✓ Suporte a números decimais
✓ Suporte completo a teclado

⚙️ REQUISITOS SISTEMA:
- Linux 64-bit
- Bibliotecas gráficas básicas (X11/Wayland)
- Não requer instalação do Qt

📱 CONTROLES:
- Números: 0-9, ponto decimal
- Operações: +, -, *, /
- Resultado: Enter ou =
- Limpar: C ou Delete
- Histórico: Clique em operações anteriores

🐛 PROBLEMAS?
Se não executar, tente no terminal:
  cd pasta-da-calculadora
  ./run-calculadora.sh

📧 SUPORTE:
GitHub: https://github.com/Eveneto/calculadora

Versão: 1.0.0
Data: $(date '+%d/%m/%Y')
EOF

# Criar arquivo de informações técnicas
cat > "$PACKAGE_DIR/TECNICO.txt" << EOF
INFORMAÇÕES TÉCNICAS - Calculadora Qt C++
=========================================

📦 CONTEÚDO DO PACOTE:
- calculadora           # Executável principal
- libQt6*.so            # Bibliotecas Qt runtime
- platforms/            # Plugins de plataforma Qt
- imageformats/         # Plugins de imagem Qt (opcional)
- run-calculadora.sh    # Script de execução
- *.so                  # Outras dependências

🔧 ESTRUTURA:
Este é um pacote "portátil" que inclui todas as dependências
necessárias para executar a calculadora sem instalação do Qt.

📋 DEPENDÊNCIAS INCLUÍDAS:
$(ldd build/calculadora | grep "=>" | head -10)

💾 TAMANHO TOTAL: ~$(du -sh "$PACKAGE_DIR" | cut -f1)

🖥️ TESTADO EM:
- Ubuntu 22.04/24.04
- Sistema $(uname -s) $(uname -m)
- Qt $(qmake6 --version | grep "Qt version" | cut -d' ' -f4)
EOF

# Verificar tamanho do pacote
PACKAGE_SIZE=$(du -sh "$PACKAGE_DIR" | cut -f1)
echo "📊 Tamanho do pacote: $PACKAGE_SIZE"

# Criar ZIP
echo "🗜️ Criando arquivo ZIP..."
cd dist/
if command -v zip &> /dev/null; then
    zip -r "../$ZIP_FILE" "$PACKAGE_NAME/" > /dev/null
    cd ..
    ZIP_SIZE=$(du -sh "$ZIP_FILE" | cut -f1)
    echo "✅ Arquivo criado: $ZIP_FILE ($ZIP_SIZE)"
else
    cd ..
    tar -czf "${PACKAGE_NAME}.tar.gz" -C dist "$PACKAGE_NAME"
    TAR_SIZE=$(du -sh "${PACKAGE_NAME}.tar.gz" | cut -f1)
    echo "✅ Arquivo criado: ${PACKAGE_NAME}.tar.gz ($TAR_SIZE)"
fi

# Teste rápido
echo "🧪 Testando pacote..."
if [ -f "$PACKAGE_DIR/calculadora" ] && [ -x "$PACKAGE_DIR/run-calculadora.sh" ]; then
    echo "✅ Pacote criado com sucesso!"
else
    echo "❌ Erro na criação do pacote!"
    exit 1
fi

# Resumo final
echo
echo "🎉 PACOTE PORTÁTIL CRIADO!"
echo "=========================="
echo "📦 Arquivo: $ZIP_FILE (se zip disponível) ou ${PACKAGE_NAME}.tar.gz"
echo "📂 Pasta: $PACKAGE_DIR"
echo "💾 Tamanho: $PACKAGE_SIZE"
echo
echo "📋 Para testar localmente:"
echo "   cd $PACKAGE_DIR"
echo "   ./run-calculadora.sh"
echo
echo "📤 Para enviar ao amigo:"
echo "   Envie o arquivo $ZIP_FILE ou ${PACKAGE_NAME}.tar.gz"
echo "   Instrua para extrair e executar run-calculadora.sh"
echo
echo "💡 O pacote é independente e não precisa de Qt instalado!"
