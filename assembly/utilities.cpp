#include "utilities.hpp"
#include "stack.hpp"
#include <iostream>
#include <fstream>
#include "../string/string.hpp"

String infixToPostfix(const String& infix) {
    stack<String> stack;
    std::vector<String> tokens = infix.split(' ');

    for (int i = 0; i < (int)tokens.size(); ++i) {
        String tok = tokens[i]; 

        if (tok.length() == 0 || tok == String(";")) continue;
        if (tok == String(")")) {
            String right = stack.pop();
            String op = stack.pop();
            String left = stack.pop();
            stack.push(left + String(" ") + right + String(" ") + op);
        } else if (tok == String("(")) {
            continue;
        } else {
            stack.push(tok);
        }
    }

    if (!stack.empty()) return stack.pop();
    return String();
}


void postfixToAssembly(const String& assembly) {
    stack<String> result;
    std::vector<String> token = assembly.split(' ');
    std::vector<bool> iter(token.size(), false);

    String left;
    String right;
    unsigned int location = 0;

    while (location < token.size() && token.at(location) != " ") {
        String op = token.at(location);
        ++location;

        if (op != "*" && op != "/" && op != "+" && op != "-") {
            result.push(op);
        } else {
            right = result.pop();
            left  = result.pop();
            result.push(evaluate(left, right, op, iter));
        }
    }
}


String intToString(const int num) {
	char newChar = num + '0';

    return String(newChar);
}

String evaluate(const String& lhs, const String& rhs, const String& oper, std::vector<bool>& iter) {
    String result;
    String operC;
    String load  = "LD";
    String store = "ST";

    int i = 0;

    while (iter[i])
        ++i;

    iter[i] = true;

    result = "TMP" + intToString(i + 1);

    if (oper == "+")
        operC = "AD";
    else if (oper == "-")
        operC = "SB";
    else if (oper == "*")
        operC = "MU";
    else if (oper == "/")
        operC = "DV";
    else
        operC = "UN";

    std::cout << "    " << load  << "          " << lhs    << std::endl;
    std::cout << "    " << operC << "          " << rhs    << std::endl;
    std::cout << "    " << store << "          " << result << std::endl;

    return result;
}