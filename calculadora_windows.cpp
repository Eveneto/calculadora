#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

// IDs dos controles
#define ID_DISPLAY 1001
#define ID_HISTORY 1002
#define ID_BUTTON_0 1010
#define ID_BUTTON_1 1011
#define ID_BUTTON_2 1012
#define ID_BUTTON_3 1013
#define ID_BUTTON_4 1014
#define ID_BUTTON_5 1015
#define ID_BUTTON_6 1016
#define ID_BUTTON_7 1017
#define ID_BUTTON_8 1018
#define ID_BUTTON_9 1019
#define ID_BUTTON_PLUS 1020
#define ID_BUTTON_MINUS 1021
#define ID_BUTTON_MULTIPLY 1022
#define ID_BUTTON_DIVIDE 1023
#define ID_BUTTON_EQUALS 1024
#define ID_BUTTON_DECIMAL 1025
#define ID_BUTTON_CLEAR 1026
#define ID_BUTTON_CLEAR_HISTORY 1027

class Calculator {
private:
    std::string m_display;
    std::string m_currentNumber;
    std::string m_operator;
    double m_storedValue;
    bool m_hasOperator;
    bool m_justCalculated;
    std::vector<std::string> m_history;

public:
    Calculator() : m_storedValue(0), m_hasOperator(false), m_justCalculated(false) {
        m_display = "0";
    }

    void addDigit(char digit) {
        if (m_justCalculated) {
            clear();
            m_justCalculated = false;
        }
        
        if (m_currentNumber == "0") {
            m_currentNumber = digit;
        } else {
            m_currentNumber += digit;
        }
        updateDisplay();
    }

    void addDecimal() {
        if (m_justCalculated) {
            clear();
            m_justCalculated = false;
        }
        
        if (m_currentNumber.empty()) {
            m_currentNumber = "0.";
        } else if (m_currentNumber.find('.') == std::string::npos) {
            m_currentNumber += ".";
        }
        updateDisplay();
    }

    void setOperator(const std::string& op) {
        if (!m_currentNumber.empty()) {
            if (m_hasOperator) {
                calculate();
            } else {
                m_storedValue = std::stod(m_currentNumber);
            }
            m_currentNumber.clear();
        }
        m_operator = op;
        m_hasOperator = true;
        m_justCalculated = false;
    }

    void calculate() {
        if (!m_hasOperator || m_currentNumber.empty()) {
            return;
        }

        double currentValue = std::stod(m_currentNumber);
        double result = m_storedValue;

        std::string operation = formatNumber(m_storedValue) + " " + m_operator + " " + formatNumber(currentValue);

        if (m_operator == "+") {
            result = m_storedValue + currentValue;
        } else if (m_operator == "-") {
            result = m_storedValue - currentValue;
        } else if (m_operator == "*") {
            result = m_storedValue * currentValue;
        } else if (m_operator == "/") {
            if (currentValue != 0) {
                result = m_storedValue / currentValue;
            } else {
                m_display = "Erro: Divisão por zero";
                return;
            }
        }

        std::string resultStr = formatNumber(result);
        operation += " = " + resultStr;
        m_history.push_back(operation);

        m_display = resultStr;
        m_storedValue = result;
        m_currentNumber = resultStr;
        m_hasOperator = false;
        m_justCalculated = true;
    }

    void clear() {
        m_currentNumber.clear();
        m_operator.clear();
        m_storedValue = 0;
        m_hasOperator = false;
        m_justCalculated = false;
        m_display = "0";
    }

    void clearHistory() {
        m_history.clear();
    }

    std::string getDisplay() const {
        return m_display;
    }

    std::vector<std::string> getHistory() const {
        return m_history;
    }

private:
    void updateDisplay() {
        if (!m_currentNumber.empty()) {
            m_display = m_currentNumber;
        } else if (m_hasOperator) {
            m_display = formatNumber(m_storedValue) + " " + m_operator;
        } else {
            m_display = "0";
        }
    }

    std::string formatNumber(double value) const {
        // Remover zeros desnecessários
        std::stringstream ss;
        ss << std::fixed << std::setprecision(10) << value;
        std::string str = ss.str();
        
        // Remover zeros à direita após o ponto decimal
        if (str.find('.') != std::string::npos) {
            str = str.substr(0, str.find_last_not_of('0') + 1);
            if (str.find('.') == str.size() - 1) {
                str = str.substr(0, str.size() - 1);
            }
        }
        
        return str;
    }
};

// Variáveis globais
HWND g_hDisplay, g_hHistory;
Calculator g_calculator;

// Declaração da função WndProc
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void UpdateDisplay() {
    SetWindowTextA(g_hDisplay, g_calculator.getDisplay().c_str());
}

void UpdateHistory() {
    std::string historyText;
    auto history = g_calculator.getHistory();
    for (const auto& entry : history) {
        historyText += entry + "\r\n";
    }
    SetWindowTextA(g_hHistory, historyText.c_str());
    
    // Rolar para o final
    SendMessage(g_hHistory, EM_SETSEL, historyText.length(), historyText.length());
    SendMessage(g_hHistory, EM_SCROLLCARET, 0, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Registrar classe da janela
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "CalculatorClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Falha ao registrar classe da janela!", "Erro", MB_ICONERROR);
        return 0;
    }

    // Criar janela principal
    HWND hwnd = CreateWindowEx(
        0,
        "CalculatorClass",
        "Calculadora C++ - Windows",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 600,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        MessageBox(NULL, "Falha ao criar janela!", "Erro", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Loop de mensagens
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Display
            g_hDisplay = CreateWindow("EDIT", "0",
                WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY,
                10, 10, 470, 40,
                hwnd, (HMENU)ID_DISPLAY, NULL, NULL);

            // Histórico
            CreateWindow("STATIC", "Historico:",
                WS_CHILD | WS_VISIBLE,
                10, 60, 100, 20,
                hwnd, NULL, NULL, NULL);

            g_hHistory = CreateWindow("EDIT", "",
                WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY,
                10, 80, 470, 120,
                hwnd, (HMENU)ID_HISTORY, NULL, NULL);

            // Botões numéricos e operadores
            int buttonWidth = 60;
            int buttonHeight = 40;
            int startX = 10;
            int startY = 220;
            int spacing = 70;

            // Primeira linha: 7, 8, 9, /
            CreateWindow("BUTTON", "7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_7, NULL, NULL);
            CreateWindow("BUTTON", "8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_8, NULL, NULL);
            CreateWindow("BUTTON", "9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing * 2, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_9, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing * 3, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_DIVIDE, NULL, NULL);

            // Segunda linha: 4, 5, 6, *
            startY += 50;
            CreateWindow("BUTTON", "4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_4, NULL, NULL);
            CreateWindow("BUTTON", "5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_5, NULL, NULL);
            CreateWindow("BUTTON", "6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing * 2, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_6, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing * 3, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_MULTIPLY, NULL, NULL);

            // Terceira linha: 1, 2, 3, -
            startY += 50;
            CreateWindow("BUTTON", "1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_1, NULL, NULL);
            CreateWindow("BUTTON", "2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_2, NULL, NULL);
            CreateWindow("BUTTON", "3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing * 2, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_3, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing * 3, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_MINUS, NULL, NULL);

            // Quarta linha: 0, ., C, +
            startY += 50;
            CreateWindow("BUTTON", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_0, NULL, NULL);
            CreateWindow("BUTTON", ".", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_DECIMAL, NULL, NULL);
            CreateWindow("BUTTON", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing * 2, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_CLEAR, NULL, NULL);
            CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing * 3, startY, buttonWidth, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_PLUS, NULL, NULL);

            // Quinta linha: =, Limpar Histórico
            startY += 50;
            CreateWindow("BUTTON", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX, startY, buttonWidth * 2 + 10, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_EQUALS, NULL, NULL);
            CreateWindow("BUTTON", "Limpar Historico", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                startX + spacing * 2, startY, buttonWidth * 2 + 10, buttonHeight,
                hwnd, (HMENU)ID_BUTTON_CLEAR_HISTORY, NULL, NULL);

            // Definir fonte para todos os controles
            HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");

            EnumChildWindows(hwnd, [](HWND hwndChild, LPARAM lParam) -> BOOL {
                SendMessage(hwndChild, WM_SETFONT, (WPARAM)lParam, TRUE);
                return TRUE;
            }, (LPARAM)hFont);

            UpdateDisplay();
            break;
        }

        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            
            switch (wmId) {
                case ID_BUTTON_0: g_calculator.addDigit('0'); break;
                case ID_BUTTON_1: g_calculator.addDigit('1'); break;
                case ID_BUTTON_2: g_calculator.addDigit('2'); break;
                case ID_BUTTON_3: g_calculator.addDigit('3'); break;
                case ID_BUTTON_4: g_calculator.addDigit('4'); break;
                case ID_BUTTON_5: g_calculator.addDigit('5'); break;
                case ID_BUTTON_6: g_calculator.addDigit('6'); break;
                case ID_BUTTON_7: g_calculator.addDigit('7'); break;
                case ID_BUTTON_8: g_calculator.addDigit('8'); break;
                case ID_BUTTON_9: g_calculator.addDigit('9'); break;
                case ID_BUTTON_DECIMAL: g_calculator.addDecimal(); break;
                case ID_BUTTON_PLUS: g_calculator.setOperator("+"); break;
                case ID_BUTTON_MINUS: g_calculator.setOperator("-"); break;
                case ID_BUTTON_MULTIPLY: g_calculator.setOperator("*"); break;
                case ID_BUTTON_DIVIDE: g_calculator.setOperator("/"); break;
                case ID_BUTTON_EQUALS: g_calculator.calculate(); UpdateHistory(); break;
                case ID_BUTTON_CLEAR: g_calculator.clear(); break;
                case ID_BUTTON_CLEAR_HISTORY: g_calculator.clearHistory(); UpdateHistory(); break;
            }
            
            UpdateDisplay();
            break;
        }

        case WM_KEYDOWN: {
            switch (wParam) {
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                    g_calculator.addDigit((char)wParam);
                    break;
                case VK_DECIMAL: case '.': case ',':
                    g_calculator.addDecimal();
                    break;
                case '+': g_calculator.setOperator("+"); break;
                case '-': g_calculator.setOperator("-"); break;
                case '*': g_calculator.setOperator("*"); break;
                case '/': g_calculator.setOperator("/"); break;
                case VK_RETURN: case '=':
                    g_calculator.calculate();
                    UpdateHistory();
                    break;
                case VK_ESCAPE: case 'C': case 'c':
                    g_calculator.clear();
                    break;
            }
            UpdateDisplay();
            break;
        }

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
