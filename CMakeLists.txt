cmake_minimum_required(VERSION 3.16.0)
project(calculadora VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Test)

# Automaticamente gerar MOC, UIC e RCC quando necessário
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Incluir diretórios
include_directories(include)

# Arquivos fonte
set(SOURCES
    src/main.cpp
    src/Calculator.cpp
    src/CalculatorHistory.cpp
)

# Arquivos header
set(HEADERS
    include/Calculator.h
    include/CalculatorHistory.h
)

# Criar executável
add_executable(calculadora ${SOURCES} ${HEADERS})

# Linkar bibliotecas Qt
target_link_libraries(calculadora Qt6::Core Qt6::Widgets)

# Configurações específicas para Windows (se necessário)
if(WIN32)
    set_property(TARGET calculadora PROPERTY WIN32_EXECUTABLE TRUE)
endif()

# Testes
add_executable(test_calculator 
    test_calculator.cpp
    src/Calculator.cpp
    src/CalculatorHistory.cpp
)
target_link_libraries(test_calculator Qt6::Core Qt6::Widgets Qt6::Test)

# Teste simples
add_executable(simple_test
    simple_test.cpp
    src/Calculator.cpp
    src/CalculatorHistory.cpp
)
target_link_libraries(simple_test Qt6::Core Qt6::Widgets Qt6::Test)
