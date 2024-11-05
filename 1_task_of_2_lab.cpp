#include "structures/stack.h"

uint8_t priority(char c) {

    if (c == '!') return 3;
    else if (c == '&') return 2;
    else if (c == '|' || c == '^') return 1;

    return 0;
}

uint8_t realize_operators(uint8_t a, uint8_t b, char oper) {

    switch (oper) {
    case '&': return a & b;
    case '|': return a | b;
    case '^': return a ^ b;
    default: throw invalid_argument("Invalid operator");
    }
}

void process_operator(Stack<char>& operators, Stack<uint8_t>& operands) {

    char oper = operators.top(); operators.pop();
    uint8_t b = operands.top(); operands.pop();

    if (oper == '!') {
        operands.push(!b);
    }
    else {
        int a = operands.top(); operands.pop();
        operands.push(realize_operators(a, b, oper));
    }
}

bool calc_a_log_expres(string expression) {

    Stack<char> operators;
    Stack<uint8_t> operands;
    uint8_t bracket_count = 0;
    bool expect_operator = false; // Ожидание оператора между операндами

    for (size_t i = 0; i < expression.length(); ++i) {
        char current = expression[i];

        if (isspace(current)) continue;

        if (current == '1' || current == '0') {
            if (expect_operator) {
                cout << "Invalid expression: missing operator between operands\n";
                exit(-1);
            }
            operands.push(current - '0');
            expect_operator = true; // Теперь ожидаем оператор после операнда
        }
        else if (current == '(') {
            operators.push(current);
            bracket_count++;
            expect_operator = false; // После '(' ожидаем операнд
        }
        else if (current == ')') {
            bracket_count--;
            if (bracket_count < 0) {
                cout << "Invalid expression: extra closing parenthesis\n";
                exit(-1);
            }
            while (!operators.is_empty() && operators.top() != '(') {
                process_operator(operators, operands);
            }
            operators.pop(); // Удалить '('
            expect_operator = true; // После закрытия скобки ожидаем оператор
        }
        else if (current == '!' || current == '&' || current == '|' || current == '^') {
            if (current == '!') {
                if (expect_operator) {
                    cout << "Invalid expression: missing operator before '!'\n";
                    exit(-1);
                }
                operators.push(current);
                expect_operator = false; // После '!' ожидаем операнд
            }
            else {
                if (!expect_operator) {
                    cout << "Invalid expression: missing operand before operator '" << current << "'\n";
                    exit(-1);
                }
                while (!operators.is_empty() && operators.top() != '(' && priority(operators.top()) >= priority(current)) {
                    process_operator(operators, operands);
                }
                operators.push(current);
                expect_operator = false; // После оператора ожидаем операнд
            }
        }
        else {
            cout << "Invalid character: " << current << endl;
            exit(-1);
        }
    }

    // Обработка оставшихся операторов
    while (!operators.is_empty()) {
        process_operator(operators, operands);
    }

    if (bracket_count != 0) {
        cout << "Invalid expression: unbalanced parentheses\n";
        exit(-1);
    }

    return operands.top();
}


int main() {
    cout << "Enter a Boolean expression: ";
    string expression;
    getline(cin, expression);

    bool result = calc_a_log_expres(expression);
    cout << "Result: " << result << endl;

    return 0;
}
