// Function Definitions
#include "utilities.hpp"
#include <ctime>
#include <sstream>
#include <cmath>
#include <cctype>
#include <algorithm>

std::string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", ltm);
    return std::string(buffer);
}

std::string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
    return std::string(buffer);
}

bool isMathExpression(const std::string& input) {
    return input.find_first_of("+-*/") != std::string::npos;
}

double evaluateExpression(const std::string& input) {
    std::stringstream ss(input);
    double num1, num2;
    char op;
    ss >> num1 >> op >> num2;

    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return (num2 != 0) ? num1 / num2 : NAN;
        default: return NAN;
    }
}

// Trim leading and trailing whitespace
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}
