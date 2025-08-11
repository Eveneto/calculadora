<!-- Use this file to provide workspace-specific custom instructions to Copilot. For more details, visit https://code.visualstudio.com/docs/copilot/copilot-customization#_use-a-githubcopilotinstructionsmd-file -->

# Calculadora Qt C++ - Instruções para o Copilot

Este projeto é uma calculadora desenvolvida em C++ usando o framework Qt, com as seguintes características:

## Tecnologias
- **Linguagem**: C++17 ou superior
- **Framework**: Qt 6.x
- **Build System**: CMake
- **IDE**: VS Code com extensões C++/Qt

## Funcionalidades
- Calculadora básica (+, -, *, /)
- Histórico de operações
- Interface gráfica moderna
- Validação de entrada
- Tratamento de erros

## Estrutura do Projeto
- `src/` - Código fonte principal
- `include/` - Headers
- `ui/` - Arquivos de interface Qt
- `CMakeLists.txt` - Configuração do build

## Padrões de Código
- Use nomenclatura camelCase para métodos
- Use PascalCase para classes
- Prefixo `m_` para membros privados
- Documentação em comentários para métodos públicos
- Siga as convenções Qt (signals/slots)

## Boas Práticas Qt
- Use `Q_OBJECT` macro em classes com signals/slots
- Implemente destruidores virtuais quando necessário
- Use smart pointers quando apropriado
- Prefira signals/slots ao invés de callbacks diretos
