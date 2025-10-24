#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>  // 后续扩展数学运算可能用到

using namespace std;

class RPNCalculator {
private:
    stack<double> dataStack;  // 存储操作数的栈

public:
    // 向栈中压入数字
    void push(double value) {
        dataStack.push(value);
    }

    // 从栈中弹出数字（处理栈空错误）
    double pop() {
        if (dataStack.empty()) {
            throw runtime_error("栈空错误：无法弹出元素（栈已空）");
        }
        double topVal = dataStack.top();
        dataStack.pop();
        return topVal;
    }

    // 清空栈
    void clear() {
        while (!dataStack.empty()) {
            dataStack.pop();
        }
    }

    // 检查栈是否为空
    bool isEmpty() const {
        return dataStack.empty();
    }

    // 获取栈顶元素（不弹出，用于显示）
    double top() const {
        if (dataStack.empty()) {
            throw runtime_error("栈空错误：无法获取栈顶元素（栈已空）");
        }
        return dataStack.top();
    }

    // 显示当前栈内容（从顶到底）
    void printStack() const {
        if (dataStack.empty()) {
            cout << "当前栈为空" << endl;
            return;
        }

        // 复制栈以避免修改原栈
        stack<double> temp = dataStack;
        cout << "栈内容（顶 -> 底）：";
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }

    // 执行运算（支持四则运算）
    void calculate(const string& op) {
        // 检查操作符合法性
        if (op != "+" && op != "-" && op != "*" && op != "/") {
            throw runtime_error("无效操作符：" + op + "（支持的操作符：+、-、*、/）");
        }

        // 检查栈中操作数是否足够
        if (dataStack.size() < 2) {
            throw runtime_error("操作数不足：" + op + "需要2个操作数（当前栈中元素数：" + to_string(dataStack.size()) + "）");
        }

        // 弹出两个操作数（注意顺序：后弹出的是第一个操作数）
        double b = pop();
        double a = pop();
        double result;

        // 执行对应运算
        if (op == "+") {
            result = a + b;
        } else if (op == "-") {
            result = a - b;
        } else if (op == "*") {
            result = a * b;
        } else {  // 除法
            if (b == 0) {
                throw runtime_error("除零错误：除数不能为0");
            }
            result = a / b;
        }

        // 结果入栈
        push(result);
    }
};

// 解析用户输入并执行对应操作
void processInput(RPNCalculator& calc, const string& input) {
    istringstream iss(input);
    string token;
    bool hasError = false;

    while (iss >> token) {
        try {
            // 尝试解析为数字（整数或浮点数）
            size_t parsePos;
            double num = stod(token, &parsePos);
            // 检查是否完全解析（避免"12a"这类无效输入）
            if (parsePos == token.size()) {
                calc.push(num);
            } else {
                throw runtime_error("输入格式错误：" + token + "（包含非数字字符）");
            }
        } catch (const invalid_argument&) {
            // 不是数字，尝试作为操作符处理
            try {
                calc.calculate(token);
            } catch (const runtime_error& e) {
                cout << "[错误] " << e.what() << endl;
                hasError = true;
                break;
            }
        } catch (const out_of_range&) {
            cout << "[错误] 数字超出范围：" << token << endl;
            hasError = true;
            break;
        } catch (const runtime_error& e) {
            cout << "[错误] " << e.what() << endl;
            hasError = true;
            break;
        }
    }

    // 如果无错误且栈非空，输出最终结果
    if (!hasError && !calc.isEmpty()) {
        // 若栈中剩余多个元素，仅输出栈顶（符合RPN计算逻辑）
        cout << "计算结果：" << calc.top() << endl;
    }
}

int main() {
    RPNCalculator calc;
    string input;

    // 程序欢迎信息
    cout << "=====================================" << endl;
    cout << "          C++ RPN 计算器             " << endl;
    cout << "=====================================" << endl;
    cout << "支持操作：" << endl;
    cout << "  - 输入数字（整数/浮点数）或操作符（+、-、*、/）" << endl;
    cout << "  - 命令：c（清空栈）、p（显示栈）、q（退出程序）" << endl;
    cout << "示例：输入 '1 2 + 3 *' 计算 (1+2)*3" << endl;
    cout << "=====================================" << endl;

    // 交互循环
    while (true) {
        cout << "\n请输入表达式或命令: ";
        getline(cin, input);

        // 处理退出命令
        if (input == "q") {
            cout << "程序已退出" << endl;
            break;
        }

        // 处理清空栈命令
        if (input == "c") {
            calc.clear();
            cout << "栈已清空" << endl;
            continue;
        }

        // 处理显示栈命令
        if (input == "p") {
            calc.printStack();
            continue;
        }

        // 处理表达式输入
        if (!input.empty()) {
            processInput(calc, input);
        }
    }

    return 0;
}