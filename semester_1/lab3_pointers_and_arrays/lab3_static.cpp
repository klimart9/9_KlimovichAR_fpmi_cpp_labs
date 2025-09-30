#include <iostream>
#include <cmath>

const int MAX_SIZE = 100;

int main() {
    int n;
    double arr[MAX_SIZE];

    std::cout << "Enter array size (max " << MAX_SIZE << "): ";
    std::cin >> n;

    if (n <= 0 || n > MAX_SIZE) {
        std::cout << "Number must be lower than " << MAX_SIZE << "\n";
        return 1;
    }

    std::cout << "Enter " << n << " array elements:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << "\n=== RESULTS ===\n";

    std::cout << "\n1. Local minima:\n";
    std::cout << "Local minima indexes: ";
    bool found = false;

    for (int i = 0; i < n; i++) {
        bool isMin = true;

        if (i > 0 && arr[i] >= arr[i-1]) isMin = false;
        if (i < n-1 && arr[i] >= arr[i+1]) isMin = false;

        if (isMin) {
            std::cout << i << " ";
            found = true;
        }
    }

    if (!found) std::cout << "none found";
    std::cout << std::endl;

    std::cout << "\n2. Sum after first minimum:\n";
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }

    double sum = 0;
    for (int i = minIndex + 1; i < n; i++) {
        sum += arr[i];
    }

    std::cout << "First minimum: arr[" << minIndex << "] = " << arr[minIndex] << std::endl;
    std::cout << "Sum after first minimum: " << sum << std::endl;

    std::cout << "\n3. Sorted by absolute value:\n";
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (std::abs(arr[j]) > std::abs(arr[j+1])) {
                double temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    std::cout << "Sorted array: [";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n-1) std::cout << ", ";
    }
    std::cout << "]\n";

    return 0;
}
