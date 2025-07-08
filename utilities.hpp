//Header for Utility Functions
// utilities.hpp
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

std::string getCurrentTime();
std::string getCurrentDate();
bool isMathExpression(const std::string& input);
double evaluateExpression(const std::string& input);
std::string trim(const std::string& str);

#endif
