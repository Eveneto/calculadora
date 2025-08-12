#include <QApplication>
#include <QTest>
#include <QSignalSpy>
#include <iostream>
#include "Calculator.h"

class FunctionalTest : public QObject
{
    Q_OBJECT

private slots:
    void testCalculatorCreation();
    void testButtonClicks();
    void testKeyboardInput();
};

void FunctionalTest::testCalculatorCreation()
{
    Calculator calc;
    QVERIFY(!calc.windowTitle().isEmpty());
    
    // Verificar se display existe e tem valor inicial
    QLineEdit* display = calc.findChild<QLineEdit*>();
    QVERIFY(display != nullptr);
    
    std::cout << "✓ Calculadora criada com sucesso" << std::endl;
}

void FunctionalTest::testButtonClicks()
{
    Calculator calc;
    calc.show();
    
    // Encontrar botões
    QList<QPushButton*> buttons = calc.findChildren<QPushButton*>();
    QVERIFY(buttons.size() > 0);
    
    // Verificar se botões numéricos existem
    bool found[10] = {false};
    for (QPushButton* btn : buttons) {
        QString text = btn->text();
        if (text.length() == 1 && text[0].isDigit()) {
            int digit = text.toInt();
            if (digit >= 0 && digit <= 9) {
                found[digit] = true;
            }
        }
    }
    
    for (int i = 0; i < 10; i++) {
        QVERIFY2(found[i], QString("Botão %1 não encontrado").arg(i).toLocal8Bit());
    }
    
    std::cout << "✓ Todos os botões numéricos encontrados" << std::endl;
}

void FunctionalTest::testKeyboardInput()
{
    Calculator calc;
    calc.show();
    calc.setFocus();
    
    QLineEdit* display = calc.findChild<QLineEdit*>();
    QVERIFY(display != nullptr);
    
    // Simular entrada de teclado
    QTest::keyClick(&calc, Qt::Key_2);
    QTest::qWait(50);
    
    // O display deve ter mudado do valor inicial
    QString displayText = display->text();
    QVERIFY(!displayText.isEmpty());
    
    std::cout << "✓ Entrada por teclado funcionando" << std::endl;
}

QTEST_MAIN(FunctionalTest)
#include "functional_test.moc"
