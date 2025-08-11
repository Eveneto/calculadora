#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QSplitter>
#include <QGroupBox>
#include <QFont>
#include <QString>
#include <QStringList>
#include <memory>
#include <QKeyEvent>
#include "CalculatorHistory.h"

/**
 * @brief Classe principal da calculadora com interface gráfica Qt
 * 
 * Esta classe implementa uma calculadora básica com as seguintes funcionalidades:
 * - Operações matemáticas básicas (+, -, *, /)
 * - Histórico de operações
 * - Interface gráfica moderna e intuitiva
 */
class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construtor da calculadora
     * @param parent Widget pai (opcional)
     */
    explicit Calculator(QWidget *parent = nullptr);
    
    /**
     * @brief Destrutor virtual
     */
    virtual ~Calculator() = default;

private slots:
    /**
     * @brief Slot chamado quando um botão numérico é pressionado
     */
    void onNumberButtonClicked();
    
    /**
     * @brief Slot chamado quando um botão de operação é pressionado
     */
    void onOperationButtonClicked();
    
    /**
     * @brief Slot chamado quando o botão de igual é pressionado
     */
    void onEqualsButtonClicked();
    
    /**
     * @brief Slot chamado quando o botão de limpar é pressionado
     */
    void onClearButtonClicked();
    
    /**
     * @brief Slot chamado quando o botão de limpar histórico é pressionado
     */
    void onClearHistoryButtonClicked();
    
    /**
     * @brief Slot chamado quando um item do histórico é clicado
     * @param item Item do histórico selecionado
     */
    void onHistoryItemClicked(QListWidgetItem* item);

private:
    /**
     * @brief Configura a interface do usuário
     */
    void setupUI();
    
    /**
     * @brief Cria os botões da calculadora
     */
    void createButtons();
    
    /**
     * @brief Configura o layout da calculadora
     */
    void setupLayout();
    
    /**
     * @brief Configura os estilos CSS da interface
     */
    void setupStyles();
    
    /**
     * @brief Atualiza o display da calculadora
     * @param text Texto a ser exibido
     */
    void updateDisplay(const QString& text);
    
    /**
     * @brief Calcula o resultado da operação atual
     * @return Resultado do cálculo ou QString vazio se houver erro
     */
    QString calculateResult();
    
    /**
     * @brief Valida se uma string representa um número válido
     * @param str String a ser validada
     * @return true se for um número válido
     */
    bool isValidNumber(const QString& str) const;
    
    /**
     * @brief Formata um número para exibição com separadores de milhares
     * @param number Número a ser formatado
     * @return String formatada do número
     */
    QString formatNumber(const QString& number) const;
    
    /**
     * @brief Remove formatação de um número para cálculos
     * @param formattedNumber Número formatado
     * @return String sem formatação
     */
    QString unformatNumber(const QString& formattedNumber) const;

protected:
    /**
     * @brief Manipula eventos de teclado
     * @param event Evento de tecla pressionada
     */
    void keyPressEvent(QKeyEvent *event) override;

    // Widgets da interface
    QWidget* m_centralWidget;
    QSplitter* m_mainSplitter;
    QGroupBox* m_calculatorGroup;
    QGroupBox* m_historyGroup;
    
    // Display e entrada
    QLineEdit* m_display;
    QLabel* m_operationLabel;
    
    // Botões
    QGridLayout* m_buttonLayout;
    QPushButton* m_numberButtons[10];
    QPushButton* m_operationButtons[4];  // +, -, *, /
    QPushButton* m_equalsButton;
    QPushButton* m_clearButton;
    QPushButton* m_decimalButton;
    QPushButton* m_clearHistoryButton;
    
    // Histórico
    QListWidget* m_historyList;
    std::unique_ptr<CalculatorHistory> m_history;
    
    // Estado da calculadora
    QString m_currentNumber;
    QString m_previousNumber;
    QString m_currentOperation;
    bool m_waitingForNewNumber;
};

#endif // CALCULATOR_H
