#include <iostream>
#include <cmath>
#include <random>

void printArray(double arr[], int size)
{
    std::cout << "[";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i];
        if (i < size - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

void fillRandomArray(double arr[], int size, double min = -10.0, double max = 10.0)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min, max);

    for (int i = 0; i < size; i++)
    {
        arr[i] = dist(gen);
    }
}

void fillKeyboardArray(double arr[], int size)
{
    std::cout << "Enter " << size << " elements:\n";
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }
}

void bubbleSort(double arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    std::cout << "Enter array size: ";
    std::cin >> n;

    if (n <= 0)
    {
        std::cout << "Enter number > 0\n";
        return 1;
    }

    double *arr = new double[n + 1];

    int choice;
    std::cout << "\nChoose input method:\n";
    std::cout << "1 - Keyboard input\n";
    std::cout << "2 - Random generation\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        fillKeyboardArray(arr, n);
        break;
    case 2:
        fillRandomArray(arr, n);
        break;
    default:
        std::cout << "Invalid choice. Using random generation.\n";
        fillRandomArray(arr, n);
        break;
    }

    std::cout << "\nOriginal array: ";
    printArray(arr, n);

    std::cout << "\n=== TASK 1 ===\n";

    int firstNeg = -1;
    int lastNeg = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            if (firstNeg == -1)
            {
                firstNeg = i;
            }
            lastNeg = i;
        }
    }

    if (lastNeg == firstNeg || firstNeg == -1)
    {
        std::cout << "Not enough negative elements\n";
    }
    else
    {
        double product = 1.0;
        for (int i = firstNeg + 1; i < lastNeg; i++)
        {
            product *= arr[i];
        }
        std::cout << "Product between first and last negative: " << product << std::endl;
    }

    std::cout << "\n=== TASK 2 ===\n";
    bubbleSort(arr, n);

    std::cout << "Sorted array: ";
    printArray(arr, n);

    double x;
    std::cout << "Enter element X to insert: ";
    std::cin >> x;

    int insertIndex = n;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > x)
        {
            insertIndex = i;
            break;
        }
    }

    for (int i = n; i > insertIndex; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[insertIndex] = x;

    std::cout << "Array after insertion: ";
    printArray(arr, n + 1);

    delete[] arr;
    return 0;
}
