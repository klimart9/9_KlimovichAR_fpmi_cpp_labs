#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

bool isDelimiter(char c) {
    return std::ispunct(c) || std::isspace(c);
}

bool isAllDigits(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

std::string extractWords(const std::string& input) {
    std::string result;
    std::string currentWord;

    for (size_t i = 0; i < input.length(); i++) {
        char c = input[i];

        if (!isDelimiter(c)) {
            currentWord += c;
        }

        if (isDelimiter(c) || i == input.length() - 1) {
            if (!currentWord.empty()) {
                if (isAllDigits(currentWord)) {
                        int num = std::stoi(currentWord);
                        if (isPrime(num)) {
                            if (!result.empty()) {
                                result += " ";
                            }
                            result += currentWord;
                        }
                    }
                }

                currentWord.clear();
            }
        }
    return result;
}


int main() {
    try {
        std::string input;
        std::cout << "Write your string: " << std::endl;
        getline(std::cin, input);

        if (input.empty()) {
            throw "Your string is empty";
        }

        std::string result = extractWords(input);

        if (result.empty()) {
            throw "Input string doesn't contain simple numbers";
        }

        std::cout << "Simple numbers in your string: " << result << std::endl;
    }
    catch (const char* msg) {
        std::cout << msg;
    }
    return 0;
}
