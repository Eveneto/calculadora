#include <QApplication>
#include <QTimer>
#include <QTest>
#include <iostream>
#include "Calculator.h"

class SimpleTest : public QObject
{
    Q_OBJECT

public slots:
    void runTests();

private:
    void simulateCalculation(Calculator* calc, const QString& expression, const QString& expected);
    void simulateButtonSequence(Calculator* calc, const QStringList& buttons);
    QPushButton* findButton(Calculator* calc, const QString& text);
};

QPushButton* SimpleTest::findButton(Calculator* calc, const QString& text)
{
    // Buscar botão por texto
    QList<QPushButton*> buttons = calc->findChildren<QPushButton*>();
    for (QPushButton* button : buttons) {
        if (button->text() == text) {
            return button;
        }
    }
    return nullptr;
}

void SimpleTest::simulateButtonSequence(Calculator* calc, const QStringList& buttons)
{
    for (const QString& buttonText : buttons) {
        QPushButton* button = findButton(calc, buttonText);
        if (button) {
            button->click();
            QTest::qWait(50); // Pequena pausa entre cliques
        } else {
            std::cout << "Botão não encontrado: " << buttonText.toStdString() << std::endl;
        }
    }
}

void SimpleTest::simulateCalculation(Calculator* calc, const QString& expression, const QString& expected)
{
    std::cout << "\n=== Testando: " << expression.toStdString() << " ===\n";
    
    // Limpar calculadora
    QPushButton* clearBtn = findButton(calc, "C");
    if (clearBtn) clearBtn->click();
    
    QStringList sequence;
    
    // Converter expressão em sequência de botões
    if (expression == "2/10") {
        sequence = {"2", "/", "1", "0", "="};
    } else if (expression == "3.14") {
        sequence = {"3", ".", "1", "4"};
    } else if (expression == "1.5+2.5") {
        sequence = {"1", ".", "5", "+", "2", ".", "5", "="};
    } else if (expression == "10.5/2") {
        sequence = {"1", "0", ".", "5", "/", "2", "="};
    } else if (expression == "0.1+0.2") {
        sequence = {"0", ".", "1", "+", "0", ".", "2", "="};
    } else if (expression == "1000") {
        sequence = {"1", "0", "0", "0"};
    }
    
    simulateButtonSequence(calc, sequence);
    
    // Obter resultado do display
    QLineEdit* display = calc->findChild<QLineEdit*>();
    if (display) {
        QString result = display->text();
        std::cout << "Resultado: " << result.toStdString() << std::endl;
        std::cout << "Esperado:  " << expected.toStdString() << std::endl;
        
        if (result == expected) {
            std::cout << "✓ PASSOU" << std::endl;
        } else {
            std::cout << "✗ FALHOU" << std::endl;
        }
    }
}

void SimpleTest::runTests()
{
    Calculator calc;
    calc.show();
    QTest::qWait(100);
    
    std::cout << "=== BATERIA DE TESTES AUTOMATIZADA ===" << std::endl;
    
    // Teste 1: Divisão 2/10 = 0,2
    simulateCalculation(&calc, "2/10", "0,2");
    
    // Teste 2: Entrada decimal 3.14
    simulateCalculation(&calc, "3.14", "3,14");
    
    // Teste 3: Soma decimal 1.5 + 2.5 = 4
    simulateCalculation(&calc, "1.5+2.5", "4");
    
    // Teste 4: Divisão decimal 10.5 / 2 = 5,25
    simulateCalculation(&calc, "10.5/2", "5,25");
    
    // Teste 5: Soma pequenos decimais 0.1 + 0.2 = 0,3
    simulateCalculation(&calc, "0.1+0.2", "0,3");
    
    // Teste 6: Formatação de número grande 1000
    simulateCalculation(&calc, "1000", "1.000");
    
    std::cout << "\n=== FIM DOS TESTES ===" << std::endl;
    
    // Verificar símbolo de divisão
    QPushButton* divButton = findButton(&calc, "/");
    if (divButton) {
        std::cout << "✓ Símbolo de divisão correto: /" << std::endl;
    } else {
        std::cout << "✗ Símbolo de divisão não encontrado ou incorreto" << std::endl;
    }
    
    QApplication::quit();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    SimpleTest test;
    QTimer::singleShot(500, &test, &SimpleTest::runTests);
    
    return app.exec();
}

#include "simple_test.moc"
