#include "Calculator.h"
#include "CalculatorHistory.h"
#include <QApplication>
#include <QTest>
#include <QSignalSpy>
#include <QtTest>
#include <QDebug>

class CalculatorTest : public QObject
{
    Q_OBJECT

private slots:
    void testBasicOperations();
    void testDecimalOperations();  
    void testFormattingNumbers();
    void testDivisionByZero();
    void testLargeNumbers();
    void testHistory();

private:
    Calculator* calculator;
    
public slots:
    void init() {
        calculator = new Calculator();
    }
    
    void cleanup() {
        delete calculator;
    }
};

void CalculatorTest::testBasicOperations()
{
    qDebug() << "\n=== TESTE: Operações Básicas ===";
    
    // Teste 1: 2 + 3 = 5
    calculator->m_currentNumber = "2";
    calculator->m_currentOperation = "+";
    calculator->m_previousNumber = "2";
    calculator->m_currentNumber = "3";
    calculator->m_waitingForNewNumber = false;
    QString result1 = calculator->calculateResult();
    qDebug() << "2 + 3 =" << result1 << "(esperado: 5)";
    QCOMPARE(result1, QString("5"));
    
    // Teste 2: 10 - 4 = 6
    calculator->m_currentNumber = "10";
    calculator->m_currentOperation = "-";
    calculator->m_previousNumber = "10";
    calculator->m_currentNumber = "4";
    QString result2 = calculator->calculateResult();
    qDebug() << "10 - 4 =" << result2 << "(esperado: 6)";
    QCOMPARE(result2, QString("6"));
    
    // Teste 3: 5 × 6 = 30
    calculator->m_currentNumber = "5";
    calculator->m_currentOperation = "×";
    calculator->m_previousNumber = "5";
    calculator->m_currentNumber = "6";
    QString result3 = calculator->calculateResult();
    qDebug() << "5 × 6 =" << result3 << "(esperado: 30)";
    QCOMPARE(result3, QString("30"));
    
    // Teste 4: 15 / 3 = 5
    calculator->m_currentNumber = "15";
    calculator->m_currentOperation = "/";
    calculator->m_previousNumber = "15";
    calculator->m_currentNumber = "3";
    QString result4 = calculator->calculateResult();
    qDebug() << "15 / 3 =" << result4 << "(esperado: 5)";
    QCOMPARE(result4, QString("5"));
}

void CalculatorTest::testDecimalOperations()
{
    qDebug() << "\n=== TESTE: Operações com Decimais ===";
    
    // Teste crítico: 2 / 10 = 0.2
    calculator->m_currentOperation = "/";
    calculator->m_previousNumber = "2";
    calculator->m_currentNumber = "10";
    calculator->m_waitingForNewNumber = false;
    QString result1 = calculator->calculateResult();
    qDebug() << "2 / 10 =" << result1 << "(esperado: 0.2)";
    QCOMPARE(result1, QString("0.2"));
    
    // Teste 2: 1 / 3 ≈ 0.33333333
    calculator->m_currentOperation = "/";
    calculator->m_previousNumber = "1";
    calculator->m_currentNumber = "3";
    QString result2 = calculator->calculateResult();
    qDebug() << "1 / 3 =" << result2 << "(esperado: aproximadamente 0.33333333)";
    QVERIFY(result2.startsWith("0.333"));
    
    // Teste 3: 0.5 + 0.3 = 0.8
    calculator->m_currentOperation = "+";
    calculator->m_previousNumber = "0.5";
    calculator->m_currentNumber = "0.3";
    QString result3 = calculator->calculateResult();
    qDebug() << "0.5 + 0.3 =" << result3 << "(esperado: 0.8)";
    QCOMPARE(result3, QString("0.8"));
    
    // Teste 4: 2.5 × 4 = 10
    calculator->m_currentOperation = "×";
    calculator->m_previousNumber = "2.5";
    calculator->m_currentNumber = "4";
    QString result4 = calculator->calculateResult();
    qDebug() << "2.5 × 4 =" << result4 << "(esperado: 10)";
    QCOMPARE(result4, QString("10"));
}

void CalculatorTest::testFormattingNumbers()
{
    qDebug() << "\n=== TESTE: Formatação de Números ===";
    
    // Teste 1: Número grande
    QString formatted1 = calculator->formatNumber("1234567");
    qDebug() << "Formatação de 1234567:" << formatted1 << "(esperado: 1.234.567)";
    QCOMPARE(formatted1, QString("1.234.567"));
    
    // Teste 2: Número decimal
    QString formatted2 = calculator->formatNumber("1234.56");
    qDebug() << "Formatação de 1234.56:" << formatted2 << "(esperado: 1.234,56)";
    QCOMPARE(formatted2, QString("1.234,56"));
    
    // Teste 3: Número pequeno
    QString formatted3 = calculator->formatNumber("0.123");
    qDebug() << "Formatação de 0.123:" << formatted3 << "(esperado: 0,123)";
    QCOMPARE(formatted3, QString("0,123"));
}

void CalculatorTest::testDivisionByZero()
{
    qDebug() << "\n=== TESTE: Divisão por Zero ===";
    
    calculator->m_currentOperation = "/";
    calculator->m_previousNumber = "5";
    calculator->m_currentNumber = "0";
    QString result = calculator->calculateResult();
    qDebug() << "5 / 0 =" << result << "(esperado: string vazia - erro)";
    QVERIFY(result.isEmpty());
}

void CalculatorTest::testLargeNumbers()
{
    qDebug() << "\n=== TESTE: Números Grandes ===";
    
    calculator->m_currentOperation = "+";
    calculator->m_previousNumber = "999999999999999";
    calculator->m_currentNumber = "1";
    QString result = calculator->calculateResult();
    qDebug() << "999999999999999 + 1 =" << result;
    QVERIFY(!result.isEmpty());
}

void CalculatorTest::testHistory()
{
    qDebug() << "\n=== TESTE: Histórico ===";
    
    CalculatorHistory history;
    QSignalSpy spy(&history, &CalculatorHistory::operationAdded);
    
    history.addOperation("2 + 3 = 5");
    history.addOperation("10 - 4 = 6");
    
    QCOMPARE(spy.count(), 2);
    QCOMPARE(history.getHistoryCount(), 2);
    QCOMPARE(history.getOperation(0), QString("2 + 3 = 5"));
    QCOMPARE(history.getOperation(1), QString("10 - 4 = 6"));
    
    qDebug() << "Histórico teste concluído com sucesso";
}

// Função principal para executar os testes
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "=================================================";
    qDebug() << "  BATERIA DE TESTES DA CALCULADORA QT";
    qDebug() << "=================================================";
    
    CalculatorTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "test_calculator.moc"
