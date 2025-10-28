#include <iostream>
#include <random>

int **createMatrix(int rows, int cols)
{
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void deleteMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void fillMatrixFromKeyboard(int **matrix, int rows, int cols)
{
    std::cout << "Enter matrix elements:" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
}

void fillMatrixRandom(int **matrix, int rows, int cols, int a, int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(a, b);
    if (a > b)
    {
        std::cout << "a must be higher than b" << std::endl;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = dist(gen);
        }
    }
}

void printMatrix(int **matrix, int rows, int cols)
{
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void sortRowsBubble(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < cols - 1; k++)
        {
            for (int j = 0; j < cols - k - 1; j++)
            {
                if (matrix[i][j] > matrix[i][j + 1])
                {
                    int temp = matrix[i][j];
                    matrix[i][j] = matrix[i][j + 1];
                    matrix[i][j + 1] = temp;
                }
            }
        }
    }
}

void sortRowsShaker(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        int left = 0;
        int right = cols - 1;

        while (left < right)
        {
            for (int j = left; j < right; j++)
            {
                if (matrix[i][j] > matrix[i][j + 1])
                {
                    int temp = matrix[i][j];
                    matrix[i][j] = matrix[i][j + 1];
                    matrix[i][j + 1] = temp;
                }
            }
            right--;

            for (int j = right; j > left; j--)
            {
                if (matrix[i][j] < matrix[i][j - 1])
                {
                    int temp = matrix[i][j];
                    matrix[i][j] = matrix[i][j - 1];
                    matrix[i][j - 1] = temp;
                }
            }
            left++;
        }
    }
}

void sortRowsChoice(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols - 1; j++)
        {
            int minIndex = j;
            for (int k = j + 1; k < cols; k++)
            {
                if (matrix[i][k] < matrix[i][minIndex])
                {
                    minIndex = k;
                }
            }
            if (minIndex != j)
            {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][minIndex];
                matrix[i][minIndex] = temp;
            }
        }
    }
}

void quickSort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = arr[(left + right) / 2];
        int i = left;
        int j = right;

        while (i <= j)
        {
            while (arr[i] < mid)
                i++;
            while (arr[j] > mid)
                j--;
            if (i <= j)
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }

        quickSort(arr, left, j);
        quickSort(arr, i, right);
    }
}

void sortRowsQuick(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        quickSort(matrix[i], 0, cols - 1);
    }
}

void merge(int *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *leftArr = new int[n1];
    int *rightArr = new int[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void sortRowsMerge(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        mergeSort(matrix[i], 0, cols - 1);
    }
}

int main()
{
    int rows, cols;
    std::cout << "Enter number of matrix rows: ";
    if (!(std::cin >> rows))
    {
        std::cout << "You need to enter the number";
        return 1;
    }
    std::cout << "Enter number of matrix columns: ";
    if (!(std::cin >> cols))
    {
        std::cout << "Wrong information";
        return 1;
    }
    int **matrix = createMatrix(rows, cols);

    int choice;
    std::cout << "\nChoose matrix filling method:" << std::endl;
    std::cout << "1 - Keyboard input" << std::endl;
    std::cout << "2 - Random numbers" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> choice;

    if (choice == 1)
    {
        fillMatrixFromKeyboard(matrix, rows, cols);
    }
    else if (choice == 2)
    {
        int a, b;
        std::cout << "Enter lower bound of interval (a): ";
        std::cin >> a;
        std::cout << "Enter upper bound of interval (b): ";
        std::cin >> b;
        fillMatrixRandom(matrix, rows, cols, a, b);
    }
    else if ((choice != 1) and (choice != 2))
    {
        std::cout << "Input error" << std::endl;
        deleteMatrix(matrix, rows);
        return 1;
    }

    int sortChoice;
    std::cout << "\nChoose sorting algorithm:" << std::endl;
    std::cout << "1 - Bubble sort" << std::endl;
    std::cout << "2 - Shaker sort" << std::endl;
    std::cout << "3 - Choice sort" << std::endl;
    std::cout << "4 - Quick sort" << std::endl;
    std::cout << "5 - Merge sort" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> sortChoice;

    switch (sortChoice)
    {
    case 1:
        sortRowsBubble(matrix, rows, cols);
        std::cout << "\nMatrix after bubble sort:" << std::endl;
        break;
    case 2:
        sortRowsShaker(matrix, rows, cols);
        std::cout << "\nMatrix after shaker sort:" << std::endl;
        break;
    case 3:
        sortRowsChoice(matrix, rows, cols);
        std::cout << "\nMatrix after choice sort:" << std::endl;
        break;
    case 4:
        sortRowsQuick(matrix, rows, cols);
        std::cout << "\nMatrix after quick sort:" << std::endl;
        break;
    case 5:
        sortRowsMerge(matrix, rows, cols);
        std::cout << "\nMatrix after merge sort:" << std::endl;
        break;
    default:
        std::cout << "Invalid choice! Using bubble sort by default." << std::endl;
        sortRowsBubble(matrix, rows, cols);
        std::cout << "\nMatrix after bubble sort:" << std::endl;
        break;
    }
    std::cout << "\nOriginal matrix:" << std::endl;
    printMatrix(matrix, rows, cols);
    std::cout << "\nSorted matrix:" << std::endl;
    printMatrix(matrix, rows, cols);
    deleteMatrix(matrix, rows);

    return 0;
}