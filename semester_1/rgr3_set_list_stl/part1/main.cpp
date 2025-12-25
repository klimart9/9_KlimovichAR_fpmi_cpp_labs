#include <iostream>
#include <set>

int main() {
    try {
        int n;
        if (!(std::cin >> n)) {
            throw "Enter the number";
        }
        if (n < 2) {
            throw "Enter the number > 1";
        }
        if (n > 45000) {
            throw "Cant use the algorithm for those numbers. Enter number lower than 45000";

        }

        std::set<int> primes;
        for (int i = 2; i < n; ++i) {
            primes.insert(i);
        }

        for (std::set<int>::iterator it = primes.begin(); it != primes.end(); ++it) {
            int p = *it;
            for (int j = p * p; j < n; j += p) {
                primes.erase(j);
            }
        }

        for (std::set<int>::iterator it = primes.begin(); it != primes.end(); ++it) {
            std::cout << *it << " ";
        }
    }
    catch (const char* msg) {
        std::cout << msg;
    }

    return 0;
}
