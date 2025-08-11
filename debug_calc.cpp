#include <iostream>
#include <QString>
#include <QCoreApplication>

// Função para simular unformatNumber
QString unformatNumber(const QString& formattedNumber)
{
    QString result = formattedNumber;
    
    // Remover separadores de milhares (pontos), mas preservar ponto decimal se for o único
    if (result.count('.') > 1) {
        // Se há múltiplos pontos, remover os separadores de milhares
        // O ponto decimal seria o último
        int lastDot = result.lastIndexOf('.');
        QString integerPart = result.left(lastDot);
        QString decimalPart = result.mid(lastDot);
        
        // Remover pontos da parte inteira
        integerPart.remove('.');
        result = integerPart + decimalPart;
    }
    
    // Converter vírgula decimal para ponto (padrão internacional)
    result.replace(',', '.');
    
    return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    std::cout << "=== TESTE ESPECÍFICO DE CÁLCULO ===" << std::endl;
    
    // Teste 1: 2/10
    QString num1 = "2";
    QString num2 = "10";
    QString operation = "/";
    
    bool ok1, ok2;
    double n1 = unformatNumber(num1).toDouble(&ok1);
    double n2 = unformatNumber(num2).toDouble(&ok2);
    
    std::cout << "Teste: " << num1.toStdString() << " " << operation.toStdString() << " " << num2.toStdString() << std::endl;
    std::cout << "n1 = " << n1 << " (ok=" << ok1 << ")" << std::endl;
    std::cout << "n2 = " << n2 << " (ok=" << ok2 << ")" << std::endl;
    
    if (ok1 && ok2 && operation == "/") {
        double result = n1 / n2;
        std::cout << "Resultado: " << result << std::endl;
        std::cout << "Esperado: 0.2" << std::endl;
    }
    
    // Teste 2: ponto decimal
    QString decimal = "3.14";
    double decimalNum = unformatNumber(decimal).toDouble(&ok1);
    std::cout << "\nTeste decimal: " << decimal.toStdString() << std::endl;
    std::cout << "Unformat: " << unformatNumber(decimal).toStdString() << std::endl;
    std::cout << "Double: " << decimalNum << " (ok=" << ok1 << ")" << std::endl;
    
    return 0;
}
