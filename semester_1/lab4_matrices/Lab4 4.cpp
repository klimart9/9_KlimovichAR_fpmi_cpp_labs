
#include <iostream>
#include <random>
#include <iomanip>

int** createMatrix(int rows, int cols) {
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}
	return matrix;
}

void deleteMatrix(int** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void fillMatrixFromKeyboard(int** matrix, int rows, int cols) {
	std::cout << "Enter matrix elements:" << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << "Element [" << i << "][" << j << "]: ";
			if (!(std::cin >> matrix[i][j])) {
				throw "You need to enter the number";
			}
		}
	}
}

bool comparingNumbers(int a, int b) {
	return a < b;
}

void fillMatrixRandom(int** matrix, int rows, int cols, int a, int b) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(a, b);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = dist(gen);
		}
	}
}

void printMatrix(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << std::left << std::setw(10) << std::fixed << std::setprecision(2) << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void findSumInColumnsWithZero(int** matrix, int rows, int cols) {
	std::cout << "\nSum of elements in columns containing zero:" << std::endl;
	bool colWithZero = false;
	for (int j = 0; j < cols; j++) {
		bool hasZero = false;

		for (int i = 0; i < rows; i++) {
			if (matrix[i][j] == 0) {
				hasZero = true;
				break;
			}
		}

		if (hasZero) {
			colWithZero = true;
			int sum = 0;
			for (int i = 0; i < rows; i++) {
				sum += matrix[i][j];
			}
			std::cout << "Column " << j << ": sum = " << sum << std::endl;
		}
	}
	if (!colWithZero) {
		throw "No columns with zero";
	}
}

void sortEvenRows(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i += 2) {
		for (int k = 0; k < cols - 1; k++) {
			for (int j = 0; j < cols - k - 1; j++) {
				if (matrix[i][j] > matrix[i][j + 1]) {
					int temp = matrix[i][j];
					matrix[i][j] = matrix[i][j + 1];
					matrix[i][j + 1] = temp;
				}
			}
		}
	}
}

void sortOddRows(int** matrix, int rows, int cols) {
	for (int i = 1; i < rows; i += 2) {
		for (int k = 0; k < cols - 1; k++) {
			for (int j = 0; j < cols - k - 1; j++) {
				if (matrix[i][j] < matrix[i][j + 1]) {
					int temp = matrix[i][j];
					matrix[i][j] = matrix[i][j + 1];
					matrix[i][j + 1] = temp;
				}
			}
		}
	}
}

int main() {
	try {
		int rows, cols;
		std::cout << "Enter number of matrix rows: ";
		if (!(std::cin >> rows)) {
			throw "You need to enter the number";
		}
		std::cout << "Enter number of matrix columns: ";
		if (!(std::cin >> cols)) {
			throw "You need to enter the number";
		}
		int** matrix = createMatrix(rows, cols);

		int choice;
		std::cout << "\nChoose matrix filling method:" << std::endl;
		std::cout << "1 - Keyboard input" << std::endl;
		std::cout << "2 - Random numbers" << std::endl;
		std::cout << "Your choice: ";
		std::cin >> choice;

		if (choice == 1) {
			fillMatrixFromKeyboard(matrix, rows, cols);
		}
		else if (choice == 2) {
			int a;
			int b;
			std::cout << "Enter lower bound of interval (a): ";
			if (!(std::cin >> a)) {
				throw "lower bound must be a number";
			}
			std::cout << "Enter upper bound of interval (b): ";			
			if (!(std::cin >> b)) {
				throw "upper bound must be a number";
			}
			if (comparingNumbers(a, b)) {
				fillMatrixRandom(matrix, rows, cols, a, b);
			}
			else {
				fillMatrixRandom(matrix, rows, cols, b, a);
			}
		}
		else {
			deleteMatrix(matrix, rows);
			throw "Invalid choice";
		}

		std::cout << "\nOriginal matrix:" << std::endl;
		printMatrix(matrix, rows, cols);
		try {
			findSumInColumnsWithZero(matrix, rows, cols);
		}
		catch (const char* msg) {
			std::cout << msg;
		}

		sortEvenRows(matrix, rows, cols);
		sortOddRows(matrix, rows, cols);

		std::cout << "\nTransformed matrix:" << std::endl;
		printMatrix(matrix, rows, cols);

		deleteMatrix(matrix, rows);
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}
