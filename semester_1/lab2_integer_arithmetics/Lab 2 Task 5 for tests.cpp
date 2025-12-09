#include <iostream>

bool isPalindrome(int number) {
    int original = number;
    int reversed = 0;

    while (number > 0) {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    }

    return original == reversed;
}

bool isDoublePalindrome(int number) {
    return isPalindrome(number) && isPalindrome(number * number);
}

void findAllDoublePalindromes(int n) {
    for (int i = 1; i <= n; i++) {
        if (isDoublePalindrome(i)) {
            std::cout << "Number: " << i << ", Square: " << i * i << std::endl;
        }
    }
}

int main() {
    int n;
    std::cout << "Write number n: ";

    if (!(std::cin >> n && n > 0)) {
        std::cout << "Write number >=1\n";
        return 0;
    }

    findAllDoublePalindromes(n);

    return 0;
}