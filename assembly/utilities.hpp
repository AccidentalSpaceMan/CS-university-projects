#ifndef utilities_h
#define utilities_h

#include "../string/string.hpp"
#include "stack.hpp"
#include <iostream>
#include <fstream>


String infixToPostfix(const String&);
void postfixToAssembly(const String&);
String evaluate(const String&, const String&, const String&, std::vector<bool>&);
String intToString(const int);
#endif