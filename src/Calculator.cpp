#include "Calculator.h"
#include "CalculatorHistory.h"
#include <QApplication>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSizePolicy>
#include <QHeaderView>
#include <cmath>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainSplitter(nullptr)
    , m_calculatorGroup(nullptr)
    , m_historyGroup(nullptr)
    , m_display(nullptr)
    , m_operationLabel(nullptr)
    , m_buttonLayout(nullptr)
    , m_equalsButton(nullptr)
    , m_clearButton(nullptr)
    , m_decimalButton(nullptr)
    , m_clearHistoryButton(nullptr)
    , m_historyList(nullptr)
    , m_history(std::make_unique<CalculatorHistory>(this))
    , m_currentNumber("0")
    , m_previousNumber("")
    , m_currentOperation("")
    , m_waitingForNewNumber(true)
{
    setupUI();
    setupStyles();
    
    // Configurar foco para receber eventos de teclado
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void Calculator::setupUI()
{
    setWindowTitle("Calculadora Qt - Com Histórico");
    setMinimumSize(600, 400);
    resize(800, 600);
    
    // Widget central
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    // Splitter principal para dividir calculadora e histórico
    m_mainSplitter = new QSplitter(Qt::Horizontal, m_centralWidget);
    
    // Grupo da calculadora
    m_calculatorGroup = new QGroupBox("Calculadora", m_mainSplitter);
    m_calculatorGroup->setMinimumWidth(300);
    
    // Grupo do histórico
    m_historyGroup = new QGroupBox("Histórico", m_mainSplitter);
    m_historyGroup->setMinimumWidth(250);
    
    // Configurar proporções do splitter
    m_mainSplitter->addWidget(m_calculatorGroup);
    m_mainSplitter->addWidget(m_historyGroup);
    m_mainSplitter->setStretchFactor(0, 2);
    m_mainSplitter->setStretchFactor(1, 1);
    
    // Layout principal
    QHBoxLayout* mainLayout = new QHBoxLayout(m_centralWidget);
    mainLayout->addWidget(m_mainSplitter);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    
    setupLayout();
    createButtons();
}

void Calculator::setupLayout()
{
    // Layout da calculadora
    QVBoxLayout* calcLayout = new QVBoxLayout(m_calculatorGroup);
    
    // Label para mostrar a operação atual
    m_operationLabel = new QLabel("", m_calculatorGroup);
    m_operationLabel->setAlignment(Qt::AlignRight);
    m_operationLabel->setMinimumHeight(35);
    QFont operationFont("Consolas", 14);  // Fonte monoespaçada
    if (!operationFont.exactMatch()) {
        operationFont = QFont("Monaco", 14);
        if (!operationFont.exactMatch()) {
            operationFont = QFont("DejaVu Sans Mono", 14);
        }
    }
    operationFont.setItalic(true);
    m_operationLabel->setFont(operationFont);
    
    // Display principal
    m_display = new QLineEdit("0", m_calculatorGroup);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setReadOnly(true);
    m_display->setMinimumHeight(70);
    QFont displayFont("Consolas", 20);  // Fonte monoespaçada para melhor alinhamento
    if (!displayFont.exactMatch()) {
        displayFont = QFont("Monaco", 20);  // Alternativa no Linux
        if (!displayFont.exactMatch()) {
            displayFont = QFont("DejaVu Sans Mono", 20);  // Padrão Linux
        }
    }
    displayFont.setBold(true);
    m_display->setFont(displayFont);
    
    calcLayout->addWidget(m_operationLabel);
    calcLayout->addWidget(m_display);
    
    // Layout dos botões
    m_buttonLayout = new QGridLayout();
    m_buttonLayout->setSpacing(5);
    calcLayout->addLayout(m_buttonLayout);
    
    // Layout do histórico
    QVBoxLayout* historyLayout = new QVBoxLayout(m_historyGroup);
    
    m_historyList = new QListWidget(m_historyGroup);
    m_historyList->setAlternatingRowColors(true);
    
    m_clearHistoryButton = new QPushButton("Limpar Histórico", m_historyGroup);
    
    historyLayout->addWidget(m_historyList);
    historyLayout->addWidget(m_clearHistoryButton);
    
    // Conectar signals do histórico
    connect(m_clearHistoryButton, &QPushButton::clicked, 
            this, &Calculator::onClearHistoryButtonClicked);
    connect(m_historyList, &QListWidget::itemClicked,
            this, &Calculator::onHistoryItemClicked);
    connect(m_history.get(), &CalculatorHistory::operationAdded,
            [this](const QString& operation) {
                m_historyList->addItem(operation);
                m_historyList->scrollToBottom();
            });
    connect(m_history.get(), &CalculatorHistory::historyCleared,
            [this]() {
                m_historyList->clear();
            });
}

void Calculator::createButtons()
{
    // Criar botões numéricos
    for (int i = 0; i < 10; ++i) {
        m_numberButtons[i] = new QPushButton(QString::number(i), m_calculatorGroup);
        m_numberButtons[i]->setMinimumSize(60, 60);
        m_numberButtons[i]->setToolTip(QString("Tecla: %1").arg(i));
        QFont buttonFont = m_numberButtons[i]->font();
        buttonFont.setPointSize(14);
        buttonFont.setBold(true);
        m_numberButtons[i]->setFont(buttonFont);
        connect(m_numberButtons[i], &QPushButton::clicked, 
                this, &Calculator::onNumberButtonClicked);
    }
    
    // Criar botões de operação
    QStringList operations = {"+", "-", "×", "/"};
    QStringList operationKeys = {"+", "-", "*", "/"};
    for (int i = 0; i < 4; ++i) {
        m_operationButtons[i] = new QPushButton(operations[i], m_calculatorGroup);
        m_operationButtons[i]->setMinimumSize(60, 60);
        m_operationButtons[i]->setToolTip(QString("Tecla: %1").arg(operationKeys[i]));
        QFont buttonFont = m_operationButtons[i]->font();
        buttonFont.setPointSize(14);
        buttonFont.setBold(true);
        m_operationButtons[i]->setFont(buttonFont);
        connect(m_operationButtons[i], &QPushButton::clicked, 
                this, &Calculator::onOperationButtonClicked);
    }
    
    // Botão de igual
    m_equalsButton = new QPushButton("=", m_calculatorGroup);
    m_equalsButton->setMinimumSize(60, 60);
    m_equalsButton->setToolTip("Tecla: Enter ou =");
    QFont equalsFont = m_equalsButton->font();
    equalsFont.setPointSize(16);
    equalsFont.setBold(true);
    m_equalsButton->setFont(equalsFont);
    connect(m_equalsButton, &QPushButton::clicked, 
            this, &Calculator::onEqualsButtonClicked);
    
    // Botão de limpar
    m_clearButton = new QPushButton("C", m_calculatorGroup);
    m_clearButton->setMinimumSize(60, 60);
    m_clearButton->setToolTip("Tecla: Esc, Del ou C");
    QFont clearFont = m_clearButton->font();
    clearFont.setPointSize(14);
    clearFont.setBold(true);
    m_clearButton->setFont(clearFont);
    connect(m_clearButton, &QPushButton::clicked, 
            this, &Calculator::onClearButtonClicked);
    
    // Botão decimal
    m_decimalButton = new QPushButton(".", m_calculatorGroup);
    m_decimalButton->setMinimumSize(60, 60);
    m_decimalButton->setToolTip("Tecla: . ou ,");
    QFont decimalFont = m_decimalButton->font();
    decimalFont.setPointSize(14);
    decimalFont.setBold(true);
    m_decimalButton->setFont(decimalFont);
    connect(m_decimalButton, &QPushButton::clicked, 
            this, &Calculator::onNumberButtonClicked);
    
    // Organizar botões no layout
    // Linha 0: Clear e operações
    m_buttonLayout->addWidget(m_clearButton, 0, 0, 1, 2);
    m_buttonLayout->addWidget(m_operationButtons[2], 0, 2); // ×
    m_buttonLayout->addWidget(m_operationButtons[3], 0, 3); // /
    
    // Linhas 1-3: Números e operações
    m_buttonLayout->addWidget(m_numberButtons[7], 1, 0);
    m_buttonLayout->addWidget(m_numberButtons[8], 1, 1);
    m_buttonLayout->addWidget(m_numberButtons[9], 1, 2);
    m_buttonLayout->addWidget(m_operationButtons[1], 1, 3); // -
    
    m_buttonLayout->addWidget(m_numberButtons[4], 2, 0);
    m_buttonLayout->addWidget(m_numberButtons[5], 2, 1);
    m_buttonLayout->addWidget(m_numberButtons[6], 2, 2);
    m_buttonLayout->addWidget(m_operationButtons[0], 2, 3); // +
    
    m_buttonLayout->addWidget(m_numberButtons[1], 3, 0);
    m_buttonLayout->addWidget(m_numberButtons[2], 3, 1);
    m_buttonLayout->addWidget(m_numberButtons[3], 3, 2);
    m_buttonLayout->addWidget(m_equalsButton, 3, 3, 2, 1); // = (2 linhas)
    
    // Linha 4: 0, decimal
    m_buttonLayout->addWidget(m_numberButtons[0], 4, 0, 1, 2);
    m_buttonLayout->addWidget(m_decimalButton, 4, 2);
}

void Calculator::setupStyles()
{
    QString style = R"(
        QGroupBox {
            font-weight: bold;
            border: 2px solid #cccccc;
            border-radius: 8px;
            margin-top: 1ex;
            padding-top: 10px;
        }
        
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px 0 5px;
        }
        
        QLineEdit {
            border: 2px solid #34495e;
            border-radius: 10px;
            padding: 12px 15px;
            background-color: #2c3e50;
            color: #ecf0f1;
            selection-background-color: #3498db;
            font-family: 'Consolas', 'Monaco', 'DejaVu Sans Mono', monospace;
        }
        
        QLineEdit:focus {
            border-color: #3498db;
            background-color: #34495e;
        }
        
        QPushButton {
            border: 2px solid #bdc3c7;
            border-radius: 8px;
            background-color: #ecf0f1;
            color: #2c3e50;
            padding: 8px;
            font-weight: bold;
        }
        
        QPushButton:hover {
            background-color: #d5dbdb;
            border-color: #95a5a6;
            color: #2c3e50;
        }
        
        QPushButton:pressed {
            background-color: #bdc3c7;
            border-color: #7f8c8d;
            color: #2c3e50;
        }
        
        QListWidget {
            border: 1px solid #34495e;
            border-radius: 5px;
            background-color: #ecf0f1;
            alternate-background-color: #d5dbdb;
            color: #2c3e50;
            selection-background-color: #3498db;
            selection-color: white;
        }
        
        QListWidget::item {
            padding: 8px;
            border-bottom: 1px solid #bdc3c7;
            color: #2c3e50;
        }
        
        QListWidget::item:selected {
            background-color: #3498db;
            color: white;
        }
        
        QLabel {
            color: #7f8c8d;
            background-color: transparent;
            padding: 5px;
        }
    )";
    
    setStyleSheet(style);
    
    // Estilos específicos para botões de operação
    QString operationStyle = "QPushButton { background-color: #3498db; color: white; border: 2px solid #2980b9; font-weight: bold; } "
                           "QPushButton:hover { background-color: #2980b9; } "
                           "QPushButton:pressed { background-color: #21618c; }";
    
    for (int i = 0; i < 4; ++i) {
        m_operationButtons[i]->setStyleSheet(operationStyle);
    }
    
    // Estilo para botão de igual
    QString equalsStyle = "QPushButton { background-color: #27ae60; color: white; border: 2px solid #229954; font-weight: bold; } "
                         "QPushButton:hover { background-color: #229954; } "
                         "QPushButton:pressed { background-color: #1e8449; }";
    m_equalsButton->setStyleSheet(equalsStyle);
    
    // Estilo para botão de limpar
    QString clearStyle = "QPushButton { background-color: #e74c3c; color: white; border: 2px solid #c0392b; } "
                        "QPushButton:hover { background-color: #c0392b; } "
                        "QPushButton:pressed { background-color: #a93226; }";
    m_clearButton->setStyleSheet(clearStyle);
    
    // Estilo para botão de limpar histórico
    QString clearHistoryStyle = "QPushButton { background-color: #95a5a6; color: white; border: 2px solid #7f8c8d; } "
                               "QPushButton:hover { background-color: #7f8c8d; } "
                               "QPushButton:pressed { background-color: #6c7b7d; }";
    m_clearHistoryButton->setStyleSheet(clearHistoryStyle);
}

void Calculator::onNumberButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    QString digit = button->text();
    
    if (digit == ".") {
        if (m_currentNumber.contains(".")) {
            return; // Já tem decimal
        }
        if (m_waitingForNewNumber) {
            m_currentNumber = "0.";
            m_waitingForNewNumber = false;
        } else {
            m_currentNumber += ".";
        }
    } else {
        if (m_waitingForNewNumber) {
            m_currentNumber = digit;
            m_waitingForNewNumber = false;
        } else {
            if (m_currentNumber == "0" && digit != ".") {
                m_currentNumber = digit;
            } else {
                m_currentNumber += digit;
            }
        }
    }
    
    updateDisplay(m_currentNumber);
}

void Calculator::onOperationButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    QString operation = button->text();
    
    if (!m_currentOperation.isEmpty() && !m_waitingForNewNumber) {
        QString result = calculateResult();
        if (!result.isEmpty()) {
            m_currentNumber = result;
            updateDisplay(m_currentNumber);
        }
    }
    
    m_previousNumber = m_currentNumber;
    m_currentOperation = operation;
    m_waitingForNewNumber = true;
    
    QString formattedNumber = formatNumber(m_previousNumber);
    m_operationLabel->setText(formattedNumber + " " + m_currentOperation);
}

void Calculator::onEqualsButtonClicked()
{
    if (m_currentOperation.isEmpty() || m_waitingForNewNumber) {
        return;
    }
    
    QString result = calculateResult();
    if (!result.isEmpty()) {
        // Criar string de operação para histórico com números formatados
        QString formattedPrevious = formatNumber(m_previousNumber);
        QString formattedCurrent = formatNumber(m_currentNumber);
        QString formattedResult = formatNumber(result);
        
        QString operation = formattedPrevious + " " + m_currentOperation + " " + formattedCurrent + " = " + formattedResult;
        m_history->addOperation(operation);
        
        m_currentNumber = result;
        updateDisplay(m_currentNumber);
        m_operationLabel->setText("");
        m_currentOperation.clear();
        m_waitingForNewNumber = true;
    }
}

void Calculator::onClearButtonClicked()
{
    m_currentNumber = "0";
    m_previousNumber.clear();
    m_currentOperation.clear();
    m_waitingForNewNumber = true;
    
    updateDisplay(m_currentNumber);
    m_operationLabel->setText("");
}

void Calculator::onClearHistoryButtonClicked()
{
    m_history->clearHistory();
}

void Calculator::onHistoryItemClicked(QListWidgetItem* item)
{
    if (!item) return;
    
    QString operation = item->text();
    // Extrair o resultado da operação (após o "=")
    int equalsIndex = operation.lastIndexOf(" = ");
    if (equalsIndex != -1) {
        QString result = operation.mid(equalsIndex + 3);
        // Converter resultado formatado para número simples
        QString unformattedResult = unformatNumber(result);
        if (isValidNumber(unformattedResult)) {
            m_currentNumber = unformattedResult;
            updateDisplay(m_currentNumber);
            m_waitingForNewNumber = true;
            m_currentOperation.clear();
            m_operationLabel->setText("");
        }
    }
}

void Calculator::updateDisplay(const QString& text)
{
    QString formattedText = formatNumber(text);
    m_display->setText(formattedText);
}

QString Calculator::calculateResult()
{
    if (m_currentOperation.isEmpty() || m_previousNumber.isEmpty()) {
        return QString();
    }
    
    bool ok1, ok2;
    double num1 = unformatNumber(m_previousNumber).toDouble(&ok1);
    double num2 = unformatNumber(m_currentNumber).toDouble(&ok2);
    
    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Erro", "Números inválidos");
        return QString();
    }
    
    double result = 0.0;
    bool validOperation = true;
    
    if (m_currentOperation == "+") {
        result = num1 + num2;
    } else if (m_currentOperation == "-") {
        result = num1 - num2;
    } else if (m_currentOperation == "×") {
        result = num1 * num2;
    } else if (m_currentOperation == "/") {
        if (num2 == 0.0) {
            QMessageBox::warning(this, "Erro", "Divisão por zero não é permitida");
            return QString();
        }
        result = num1 / num2;
    } else {
        validOperation = false;
    }
    
    if (!validOperation) {
        return QString();
    }
    
    // Verificar se o resultado é muito grande
    if (qAbs(result) > 1e15) {
        QMessageBox::warning(this, "Erro", "Resultado muito grande para exibir");
        return QString();
    }
    
    // Formatação do resultado com precisão limitada
    QString resultStr;
    if (qAbs(result - qRound(result)) < 0.0000001) {
        // Número inteiro
        resultStr = QString::number(qRound(result));
    } else {
        // Número decimal - limitar a 8 casas decimais
        resultStr = QString::number(result, 'f', 8);
        
        // Remover zeros desnecessários
        while (resultStr.contains('.') && (resultStr.endsWith('0') || resultStr.endsWith('.'))) {
            resultStr.chop(1);
            if (resultStr.endsWith('.')) {
                resultStr.chop(1);
                break;
            }
        }
    }
    
    return resultStr;
}

bool Calculator::isValidNumber(const QString& str) const
{
    bool ok;
    unformatNumber(str).toDouble(&ok);
    return ok;
}

QString Calculator::formatNumber(const QString& number) const
{
    QString cleanNumber = unformatNumber(number);
    
    if (cleanNumber.isEmpty() || cleanNumber == "0") {
        return "0";
    }
    
    bool ok;
    double value = cleanNumber.toDouble(&ok);
    if (!ok) {
        return number; // Retorna original se não conseguir converter
    }
    
    // Formatação para números inteiros e decimais
    QString result;
    
    // Verifica se é um número inteiro ou tem casas decimais
    if (qAbs(value - qRound(value)) < 0.0000001) {
        // Número inteiro - formatar com separadores de milhares
        result = QString::number(qRound(value));
        
        // Adicionar separadores de milhares
        int pos = result.length() - 3;
        while (pos > 0 && result.at(0) != '-') {
            result.insert(pos, '.');
            pos -= 3;
        }
        // Para números negativos, ajustar posição
        if (result.at(0) == '-' && pos > 1) {
            result.insert(pos, '.');
        }
    } else {
        // Número decimal - limitar casas decimais e formatar
        result = QString::number(value, 'f', 8);
        
        // Remover zeros desnecessários no final
        while (result.endsWith('0') && result.contains('.')) {
            result.chop(1);
        }
        if (result.endsWith('.')) {
            result.chop(1);
        }
        
        // Separar parte inteira e decimal
        QStringList parts = result.split('.');
        if (parts.size() == 2) {
            QString integerPart = parts[0];
            QString decimalPart = parts[1];
            
            // Formatar parte inteira com separadores
            int pos = integerPart.length() - 3;
            while (pos > 0 && integerPart.at(0) != '-') {
                integerPart.insert(pos, '.');
                pos -= 3;
            }
            if (integerPart.at(0) == '-' && pos > 1) {
                integerPart.insert(pos, '.');
            }
            
            result = integerPart + "," + decimalPart;
        }
    }
    
    return result;
}

QString Calculator::unformatNumber(const QString& formattedNumber) const
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

void Calculator::keyPressEvent(QKeyEvent *event)
{
    QString key = event->text();
    int keyCode = event->key();
    
    // Números (0-9)
    if (keyCode >= Qt::Key_0 && keyCode <= Qt::Key_9) {
        // Simular clique no botão correspondente
        int digit = keyCode - Qt::Key_0;
        if (digit >= 0 && digit <= 9) {
            m_numberButtons[digit]->animateClick();
        }
    }
    // Operações
    else if (keyCode == Qt::Key_Plus) {
        m_operationButtons[0]->animateClick(); // +
    }
    else if (keyCode == Qt::Key_Minus) {
        m_operationButtons[1]->animateClick(); // -
    }
    else if (keyCode == Qt::Key_Asterisk) {
        m_operationButtons[2]->animateClick(); // ×
    }
    else if (keyCode == Qt::Key_Slash) {
        m_operationButtons[3]->animateClick(); // ÷
    }
    // Decimal
    else if (keyCode == Qt::Key_Period || keyCode == Qt::Key_Comma) {
        m_decimalButton->animateClick();
    }
    // Igual/Enter
    else if (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter || keyCode == Qt::Key_Equal) {
        m_equalsButton->animateClick();
    }
    // Clear/Escape/Delete
    else if (keyCode == Qt::Key_Escape || keyCode == Qt::Key_Delete || keyCode == Qt::Key_C) {
        m_clearButton->animateClick();
    }
    // Backspace (apagar último dígito)
    else if (keyCode == Qt::Key_Backspace) {
        if (!m_waitingForNewNumber && m_currentNumber.length() > 1) {
            m_currentNumber.chop(1);
            updateDisplay(m_currentNumber);
        } else if (!m_waitingForNewNumber && m_currentNumber.length() == 1) {
            m_currentNumber = "0";
            m_waitingForNewNumber = true;
            updateDisplay(m_currentNumber);
        }
    }
    
    // Chamar método pai para outros eventos
    QMainWindow::keyPressEvent(event);
}
