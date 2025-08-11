#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include "Calculator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Configurações da aplicação
    app.setApplicationName("Calculadora Qt");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Dev Learning");
    
    // Configurar estilo da aplicação
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // Criar e exibir a calculadora
    Calculator calculator;
    calculator.show();
    
    return app.exec();
}
