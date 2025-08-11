#include "CalculatorHistory.h"

CalculatorHistory::CalculatorHistory(QObject *parent)
    : QObject(parent)
{
}

void CalculatorHistory::addOperation(const QString& operation)
{
    if (operation.isEmpty()) {
        return;
    }
    
    m_operations.append(operation);
    trimHistory();
    
    emit operationAdded(operation);
}

QStringList CalculatorHistory::getHistory() const
{
    return m_operations;
}

void CalculatorHistory::clearHistory()
{
    m_operations.clear();
    emit historyCleared();
}

int CalculatorHistory::getHistoryCount() const
{
    return m_operations.size();
}

QString CalculatorHistory::getOperation(int index) const
{
    if (index < 0 || index >= m_operations.size()) {
        return QString();
    }
    
    return m_operations.at(index);
}

bool CalculatorHistory::isEmpty() const
{
    return m_operations.isEmpty();
}

void CalculatorHistory::trimHistory()
{
    while (m_operations.size() > MAX_HISTORY_SIZE) {
        m_operations.removeFirst();
    }
}
