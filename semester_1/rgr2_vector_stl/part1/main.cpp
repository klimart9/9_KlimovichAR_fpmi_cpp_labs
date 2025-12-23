#include <iostream>
#include <vector>
#include <limits>
void PrintVector(const std::vector<int>& v){
	for (int i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int main() {
	try {
		std::vector<int> vec;
		int x;
		std::cout << "Enter letter to stop\n";
		while (std::cin >> x) {
			vec.push_back(x);
		}
		std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Start vector:" << std::endl;
		PrintVector(vec);

		int sum = 0;
		for (int i : vec) {
			sum += i;
		}
		std::cout << "\n" << sum << " - Sum of elemnts of vector" << std::endl;

		int size = 0;
		size = (int)vec.size();
		std::cout << "\n" << size << " - Size of vector" << std::endl;
		int count = 0;
		int n;
		try {
			std::cout << "\nEnter the number to find quantity of it in vector" << std::endl;
			if (!(std::cin >> n)) {
				throw "You must enter the number";
			}
			for (int i : vec) {
				if (i == n) {
					count++;
				}
			}
			std::cout << "Vector has " << count << " " << n << std::endl;;

		}
		catch (const char* msg) {
			std::cout << msg << std::endl;
			std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		count = 0;
		try {
			int k;
			std::cout << "\nEnter the number to find quantity of elements lower than it in vector" << std::endl;
			if (!(std::cin >> k)) {
				throw "You must enter the number";
			}
			for (int i : vec) {
				if (i < k) {
					count++;
				}
			}
			std::cout << count << " - Quantity of numbers that less than " << k << std::endl;
		}
		catch (const char* msg) {
			std::cout << msg;
			std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}
		try {
			if (size == 0) {
				throw "Cant find average if size = 0";
			}
			int res = sum / size;
			for (int& i : vec) {
				if (i == 0) {
					i = res;
				}
			}

			std::cout << "\nVector after changes:(0 = " << res << ")" << std::endl;
			PrintVector(vec);
		}
		catch (const char* msg) {
			std::cout << msg;
			std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}
		try {
			int a;
			std::cout << "\nEnter lower and upper bound" << std::endl;;
			if (!(std::cin >> a)) {
				throw "You must enter the number";
			}
			int b;
			if (!(std::cin >> b)) {
				throw "You must enter the number";
			}
			if (a > b) {
				throw "a must be lower than b";
			}
			if (a < 0) {
				throw "a must be positive number";
			}
			if (b >= size) {
				throw "b must be lower than size";
			}
			int sum_in_interv = 0;
			for (int i = a; i <= b; i++) {
				sum_in_interv += vec[i];
			}
			for (int& i : vec) {
				i += sum_in_interv;
			}
			std::cout << "\nVector after changes(all elements + " << sum_in_interv << ")" << std::endl;
			PrintVector(vec);
		}
		catch (const char* msg) {
			std::cout << msg << std::endl;
		}
		std::vector<int>::iterator max_elem = std::max_element(vec.begin(), vec.end());
		std::vector<int>::iterator min_elem = std::min_element(vec.begin(), vec.end());
		int max_val = *max_elem;
		int min_val = *min_elem;
		int diff = *max_elem - *min_elem;
		for (int& i : vec) {
			if (i % 2 == 0) {
				i = diff;
			}
		}
		std::cout << "\nVector after change(even element = " << "max - min = " << max_val << "-" << min_val << " = " << diff << ")" << std::endl;
		PrintVector(vec);

		std::vector<int> result;
		for (int i : vec) {
			int abs_val = std::abs(i);
			bool seen = false;
			for (int j : result) {
				if (abs_val == std::abs(j)) {
					seen = true;
					break;
				}
			}
			if (!seen) {
				result.push_back(i);
			}
		}

		std::cout << "\nVector after changes(all(except one) abs are deleted)" << std::endl;
		PrintVector(result);
	}

	catch(const char* msg){
		std::cout << msg;

	}
}




