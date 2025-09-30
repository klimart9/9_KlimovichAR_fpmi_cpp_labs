#include <iostream>
#include <cmath>

int main() {
    int n;
    std::cout << "Enter array size: ";
    std::cin >> n;
    
    if (n <= 0) {
        std::cout << "Enter number > 0\n";
        return 1;
    }
    
    double* arr = new double[n];
    
    std::cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    std::cout << "\n=== TASK 1 ===\n";
    
    int firstNeg = -1, lastNeg = -1;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            if (firstNeg == -1) firstNeg = i;
            lastNeg = i;
        }
    }
    
    if (lastNeg == firstNeg) {
        std::cout << "Not enough negative elements\n";
    } else {
        double product = 1.0;
        for (int i = firstNeg + 1; i < lastNeg; i++) {
            product *= arr[i];
        }
        std::cout << "Product between first and last negative: " << product << std::endl;
    }
    
    std::cout << "\n=== TASK 2 ===\n";
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    std::cout << "Sorted array: [";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    double x;
    std::cout << "Enter element X to insert: ";
    std::cin >> x;
    
    double* newArr = new double[n + 1];
    int insertIndex = 0;
    
    while (insertIndex < n && arr[insertIndex] < x) {
        newArr[insertIndex] = arr[insertIndex];
        insertIndex++;
    }
    
    newArr[insertIndex] = x;
    
    for (int i = insertIndex; i < n; i++) {
        newArr[i + 1] = arr[i];
    }
    
    std::cout << "Array after insertion: [";
    for (int i = 0; i < n + 1; i++) {
        std::cout << newArr[i];
        if (i < n) std::cout << ", ";
    }
    std::cout << "]\n";
    
    delete[] arr;
    delete[] newArr;
    
    return 0;
}
