# Calculadora Qt C++ com Histórico

Uma calculadora moderna desenvolvida em C++ usando o framework Qt, com interface gráfica intuitiva e funcionalidade de histórico de operações.

## 🚀 Funcionalidades

- ✅ **Operações Básicas**: Adição (+), Subtração (-), Multiplicação (*), Divisão (/)
- 📊 **Histórico de Operações**: Visualiza todas as operações realizadas
- 🎨 **Interface Moderna**: Design limpo e responsivo
- 🔢 **Suporte a Decimais**: Trabalha com números decimais
- ⚠️ **Validação de Entrada**: Tratamento de erros e validações
- 🔄 **Reutilização do Histórico**: Clique em operações anteriores para reutilizar resultados

## 🛠️ Tecnologias Utilizadas

- **Linguagem**: C++17
- **Framework**: Qt 6.x
- **Build System**: CMake
- **Padrão de Design**: Model-View-Controller (MVC)

## 📋 Pré-requisitos

Antes de compilar o projeto, certifique-se de ter instalado:

- **Qt 6.x** (Qt Core e Qt Widgets)
- **CMake** (versão 3.16 ou superior)
- **Compilador C++17** (GCC, Clang, ou MSVC)

### Instalação no Ubuntu/Debian

```bash
sudo apt update
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential
```

### Instalação no Arch Linux

```bash
sudo pacman -S qt6-base qt6-tools cmake gcc
```

### Instalação no macOS (via Homebrew)

```bash
brew install qt@6 cmake
```

## 🔧 Compilação e Execução

### 1. Clone ou navegue até o diretório do projeto

```bash
cd /home/dev_pc/Documentos/calculadora
```

### 2. Crie o diretório de build

```bash
mkdir build
cd build
```

### 3. Configure com CMake

```bash
cmake ..
```

### 4. Compile o projeto

```bash
make -j$(nproc)
```

### 5. Execute a calculadora

```bash
./calculadora
```

## 🎯 Como Usar

1. **Números**: Clique nos botões numéricos (0-9) para inserir números
2. **Operações**: Clique em +, -, *, / para selecionar a operação
3. **Resultado**: Pressione = para calcular o resultado
4. **Decimal**: Use o botão . para números decimais
5. **Limpar**: Pressione C para limpar a entrada atual
6. **Histórico**: 
   - Visualize todas as operações no painel direito
   - Clique em uma operação anterior para reutilizar o resultado
   - Use "Limpar Histórico" para remover todas as operações

## 📁 Estrutura do Projeto

```
calculadora/
├── include/
│   ├── Calculator.h          # Classe principal da calculadora
│   └── CalculatorHistory.h   # Classe de gerenciamento do histórico
├── src/
│   ├── main.cpp             # Ponto de entrada da aplicação
│   ├── Calculator.cpp       # Implementação da calculadora
│   └── CalculatorHistory.cpp # Implementação do histórico
├── CMakeLists.txt           # Configuração do build
└── README.md               # Este arquivo
```

## 🎨 Interface

A interface da calculadora é dividida em duas partes principais:

- **Painel Esquerdo**: Calculadora com display e botões
- **Painel Direito**: Histórico de operações realizadas

A interface é responsiva e pode ser redimensionada conforme necessário.

## 🧪 Funcionalidades Técnicas

### Padrões de Código
- Nomenclatura camelCase para métodos
- PascalCase para classes
- Prefixo `m_` para membros privados
- Documentação completa nos headers

### Arquitetura
- **Separação de Responsabilidades**: Lógica de cálculo separada da interface
- **Signals e Slots Qt**: Comunicação eficiente entre componentes
- **Gerenciamento de Memória**: Uso de smart pointers
- **Tratamento de Erros**: Validações e mensagens de erro apropriadas

## 🚀 Desenvolvimento

Este projeto foi criado como uma ferramenta de aprendizado para C++ e Qt. 

### Próximas Funcionalidades (Ideias)
- [ ] Operações científicas (sin, cos, tan, log, etc.)
- [ ] Suporte a parênteses para operações complexas
- [ ] Salvamento do histórico em arquivo
- [ ] Temas personalizáveis
- [ ] Suporte a expressões matemáticas completas
- [ ] Atalhos de teclado

## 📄 Licença

Este projeto é livre para uso educacional e pessoal.

## 👨‍💻 Contribuição

Sinta-se à vontade para contribuir com melhorias, correções de bugs ou novas funcionalidades!

## 📞 Suporte

Em caso de dúvidas ou problemas:
1. Verifique se todas as dependências estão instaladas
2. Certifique-se de que o Qt 6.x está corretamente configurado
3. Verifique se o CMake consegue encontrar o Qt
