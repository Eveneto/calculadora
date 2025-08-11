#ifndef CALCULATOR_HISTORY_H
#define CALCULATOR_HISTORY_H

#include <QObject>
#include <QStringList>
#include <QString>

/**
 * @brief Classe responsável pelo gerenciamento do histórico de operações
 * 
 * Esta classe mantém um registro de todas as operações realizadas na calculadora,
 * permitindo visualizar e reutilizar cálculos anteriores.
 */
class CalculatorHistory : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construtor do histórico
     * @param parent Objeto pai (opcional)
     */
    explicit CalculatorHistory(QObject *parent = nullptr);
    
    /**
     * @brief Destrutor virtual
     */
    virtual ~CalculatorHistory() = default;
    
    /**
     * @brief Adiciona uma nova operação ao histórico
     * @param operation Operação completa (ex: "5 + 3 = 8")
     */
    void addOperation(const QString& operation);
    
    /**
     * @brief Obtém todo o histórico de operações
     * @return Lista com todas as operações realizadas
     */
    QStringList getHistory() const;
    
    /**
     * @brief Limpa todo o histórico
     */
    void clearHistory();
    
    /**
     * @brief Obtém o número de operações no histórico
     * @return Quantidade de operações armazenadas
     */
    int getHistoryCount() const;
    
    /**
     * @brief Obtém uma operação específica do histórico
     * @param index Índice da operação (0-based)
     * @return Operação no índice especificado ou QString vazio se inválido
     */
    QString getOperation(int index) const;
    
    /**
     * @brief Verifica se o histórico está vazio
     * @return true se não há operações no histórico
     */
    bool isEmpty() const;

signals:
    /**
     * @brief Signal emitido quando uma nova operação é adicionada
     * @param operation Operação que foi adicionada
     */
    void operationAdded(const QString& operation);
    
    /**
     * @brief Signal emitido quando o histórico é limpo
     */
    void historyCleared();

private:
    QStringList m_operations;  ///< Lista de operações do histórico
    static const int MAX_HISTORY_SIZE = 100;  ///< Tamanho máximo do histórico
    
    /**
     * @brief Remove operações antigas se o histórico exceder o tamanho máximo
     */
    void trimHistory();
};

#endif // CALCULATOR_HISTORY_H
