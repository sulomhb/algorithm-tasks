/*
Problem: How can convert Infix to Prefix expression using stack?

In the below section, there is explanation about how to convert infix to prefix expression. You need to use stack to solve this problem. Consider your program more comprehensive, and it should work for a complex Infix as well. Your program should calculate the final result of Infix and Prefix as well. Suppose if the user enter infix: (3+4)*2/2+4/2*8 it should print the result as 23. Add more functionality to your program based on your understanding.

1. Infix to prefix conversion will have 2 Marks.

2. Getting the result of basic infix equation like (3+46)*2/12+4/2*8 will have 2 Marks.

3. Getting the result of complex euqation like 3*log(100)+sin^2(90)-cos(log(1000))+2-3*4+12 will have 2 Marks.

4. Extra functionality of your program based on the usage of customer will have 1 Marks. This part include( The program did not accept ++, --, //,%%) and also the user should be able to use your program without any knowledge or programming!

Algorithm Instruction:

Initially reverse the expression given for the infix.
One by one scan of characters.
If character is an operand, then copy it to the output of the prefix notation.
When the character is a parenthesis closing then push it to the stack.
If the character is an opening parenthesis, pop the elements in the stack till we find the closing parenthesis that corresponds.
If a character scanned is operator.
If the operator has greater or equal precedence than the top of the stack, push the operator to the stack.
If the operator has less precedence than the top of the stack, pop the operator and output it to the output of the prefix notation, then check the above condition with the new top of the stack again.
After scanning all the characters, reverse the notation output for the prefix.
Example:

  Infix: K+L-M*N+(O^P)*W/V/V*T+Q

  Prefix: ++-+KL*MN*//*^OPWVVTQ

 
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <regex>
/* written by Andreas Stiansen, Odd-Harald Lillestø Myhren, Shaheen Thayalan and 
Suleyman Selcuk */
// template stack implementation
template<typename T>
class Stack {
    int top = -1;
    static const int size = 100;
    T stack[size]{0};
public:
    int len = 0;
    bool is_full() const {
        bool result = (top == (size - 1));
        return result;
    }
    bool is_empty() const {
        bool result = (top == -1);
        return result;
    }
    void push(T input) {
        if (is_full())
            return;
        len++;
        stack[++top] = input;
    }
    void pop() {
        if (is_empty())
            return;
        len--;
        top--;
    }
    T peek() {
        if (is_empty())
            return 0;
        return stack[top];
    }
};
int operator_priority(char character) {
    switch (character) {
        case '!': {
        }
        case '@': {
        }
        case '#': {
            return 4;
        }
        case '^': {
            return 3;
        }
        case '*': {
        }
        case '/': {
            return 2;
        }
        case '+': {
        }
        case '-': {
            return 1;
        }
        default:
            return -1;
    }
}
bool is_operand(char character) {
    return (character >= '0' && character <= '9') ||
           (character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z');
}
bool is_operator(char character) {
    return (character == '+' || character == '-' || character == '*' ||
            character == '/' || character == '^' || character == '!' ||
            character == '@' || character == '#');
}
bool is_complex(char character) {
    return (character == '!' || character == '@' || character == '#');
}
float calculate(float op1, char op, float op2) {
    switch (op) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
        case '^':
            return pow(op1, op2);
        default:
            return 0.0;
    }
}
float calculate_complex(float x, char op) {
    switch (op) {
        case '!':
            return sin(x);
        case '@':
            return cos(x);
        case '#':
            return log10(x);
        default:
            return 0.0;
    }
}
void replace(std::string &subject, const std::string &search, const std::string 
&replace) {
    size_t position = 0;
    if (search.empty())
        return;
    while ((position = subject.find(search, position)) != std::string::npos) {
        subject.replace(position, search.length(), replace);
        position += replace.length();
    }
}
std::string convert(std::string input) {
    Stack<char> stack;
    // find and replace complex operators with single character symbols for simpler
parsing
    replace(input, "sin", "!");
    replace(input, "cos", "@");
    replace(input, "log", "#");
    // move (sin|cos|log)^2(\d+) to (sin|cos|log)(\d+)^2
    std::regex caret_regex("(!|@|#)\\^(\\d+)\\((\\d+)\\)");
    std::string fixed = std::regex_replace(input, caret_regex, "$1\\($3\\)^$2");
    
    // add space at each number for multi-digits
    std::regex operator_regex("\\d+");
    std::string inputExpression = std::regex_replace(fixed, operator_regex, " $& 
");
    std::string prefixExpression;
    // reverse the expression before parsing
    std::reverse(inputExpression.begin(), inputExpression.end());
    bool operatorFlag = false;
    for (char character: inputExpression) {
      if (character == ' ') {
        prefixExpression += character;
      };
      
        // operands are put directly into the prefix expression
        if (is_operand(character)) {
            operatorFlag = false;
            prefixExpression += character;
        }
        // since we're parsing the expression reversed, we encounter closing before
opening parenthesis
        else if (character == ')') {
            stack.push(character);
        }
        // when we find the corresponding opening parenthesis, append everything 
from the stack that
        // was pushed since the closing parenthesis
        else if (character == '(') {
            while ((stack.peek() != ')') && (!stack.is_empty())) {
                prefixExpression += stack.peek();
                stack.pop();
            }
            if (stack.peek() == ')')
                stack.pop();
        }
        // if the character is an operator with a higher or the same priority as 
the current top of the stack, we push
        // it so that it becomes the new highest priority operator, if it has lower
priority we append from and pop
        // the stack until we have a operator with the same or higher priority in 
the stack top
        else if (is_operator(character)) {
            if (stack.is_empty()) {
                if (character != '-') operatorFlag = true;
                stack.push(character);
            } else {
                // throw error if expression has 2 ore more binary operators in a 
row
                if (character == '+' || character == '*' || character == '/') {
                    if (operatorFlag) return "Invalid use of operators";
                    operatorFlag = true;
                }
                if (operator_priority(character) > operator_priority(stack.peek()))
{
                    stack.push(character);
                } else if ((operator_priority(character) ==
                            operator_priority(stack.peek())) &&
                           (character == '^')) {
                    while ((operator_priority(character) ==
                            operator_priority(stack.peek()))) {
                        prefixExpression += stack.peek();
                        stack.pop();
                    }
                    stack.push(character);
                } else if (operator_priority(character) ==
                           operator_priority(stack.peek())) {
                    stack.push(character);
                } else {
                    while ((!stack.is_empty()) && (operator_priority(character) <
                                                   
operator_priority(stack.peek()))) {
                        prefixExpression += stack.peek();
                        stack.pop();
                    }
                    stack.push(character);
                }
            }
        }
    }
    // after parsing we append the rest of the stack
    while (!stack.is_empty()) {
        prefixExpression += stack.peek();
        stack.pop();
    }
    // reverse the expression from postfix to obtain the prefix expression
    std::reverse(prefixExpression.begin(), prefixExpression.end());
    return prefixExpression;
}
float evaluatePrefix(std::string prefix) {
    Stack<float> operandStack;
    Stack<char> operatorStack;
    for (int i = prefix.length(); i >= 0; i--) {
        // Push to respective stacks
        if (is_operand(prefix[i])) {
            std::string digits;
            while (i >= 0 && prefix[i] != ' ')
                digits.insert(0, 1, prefix[i--]);
            float number = std::stof(digits);
            operandStack.push(number);
        } else if (is_operator(prefix[i]))
            operatorStack.push(prefix[i]);
        if (operandStack.len >= 1 && operatorStack.len >= 1 && 
is_complex(operatorStack.peek())) {
            // If we have 1 or more numbers and sin, cos, log as operator
            float number = operandStack.peek();
            operandStack.pop();
            char complex = operatorStack.peek();
            operatorStack.pop();
            float result = calculate_complex(number, complex);
            operandStack.push(result);
        } else if (operandStack.len >= 2 && operatorStack.len >= 1) {
            // If we have 2 or more numbers and an operator
            float left = operandStack.peek();
            operandStack.pop();
            float right = operandStack.peek();
            operandStack.pop();
            char middle = operatorStack.peek();
            operatorStack.pop();
            float result = calculate(left, middle, right);
            operandStack.push(result);
        } else continue;
    }
    return operandStack.peek();
}
int main() {
    std::cout << "Expression: ";
    std::string input;
    std::getline(std::cin, input);
    std::string prefix = convert(input);
    std::regex whitespace_regex("\\s+");
    std::cout << "Prefix: " << std::regex_replace(prefix, whitespace_regex, " ") <<
std::endl;
    float result = evaluatePrefix(prefix);
    std::cout << "Result: " << result << std::endl;
    return 0;
}