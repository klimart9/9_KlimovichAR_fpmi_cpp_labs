#include <iostream>
#include <cmath>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <stdexcept>


class Function {
	static int next_id;
	int id;
public:
	enum FunctionType {Linear, Quadratic};
	Function() : id(next_id++) {}
	virtual double Evaluate(double) = 0;
	virtual void Solve(std::ostream&) = 0;
	virtual void PrintEquation(std::ostream&) = 0;
	static Function* create_function(FunctionType type, double a, double b, double c = 0);
};

int Function::next_id = 1;

class LinearFunction : public Function {
	double a_;
	double b_;
public:
	LinearFunction(double a = 0, double b = 0) : a_(a), b_(b) {};


	double Evaluate(double x) {
		return (a_ * x + b_);
	}

	void Solve(std::ostream& out) {
		out << "x = " << -b_ / a_ << '\n' << '\n';
	}

	void PrintEquation(std::ostream& out) {
		out << a_ << 'x' << " + " << b_ << " = " << '0' << '\n';
	}

	double get_a_linear() const {
		return a_;
	}

	double get_b_linear() const {
		return b_;
	}

};

class QuadraticFunction : public Function {
	double a_;
	double b_;
	double c_;
public:
	QuadraticFunction(double a = 0, double b = 0, double c = 0) {
		if (a == 0) {
			throw::std::invalid_argument("Cant create quadratic function with a = 0");
		}
		a_ = a;
		b_ = b;
		c_ = c;
	};

	double find_dicsr() const {
		return b_ * b_ - 4 * a_ * c_;
	}

	double Evaluate(double x) {
		return(a_ * x * x + b_ * x + c_);
	}

	void Solve(std::ostream& out) {
		double discr = find_dicsr();
		if (discr < 0) {
			out << "Equation has no answers" << '\n' << '\n';
		}
		else {
			out << "x1 = " << (-b_ + sqrt(discr)) / (2 * a_) << '\n' << "x2 = " << -b_ - sqrt(discr) / (2 * a_) << '\n' << '\n';

		}
	}

	void PrintEquation(std::ostream& out) {
		out << a_ << "(x**2)" << " + " << b_ << 'x' << " + " << c_ << " = " << '0' << '\n';
	}

	double get_a_quadratic() const {
		return a_;
	}

	double get_b_quadratic() const {
		return b_;
	}

	double get_c_quadratic() const {
		return c_;
	}
};

double get_number() {
	double x;
	if (!(std::cin >> x)) {
		throw std::invalid_argument("Expected number: finded 'char'");
	}
	return x;

}

void print_information_in_file(Function** functions, int size) {
	std::ofstream out{ "output.txt" };
	if (!(out.is_open())) {
		throw std::runtime_error("Cant open output file");
	}
	for (int i = 0; i < size; ++i) {
		functions[i]->PrintEquation(out);
		functions[i]->Solve(out);
	}
	out.close();
}

void count_functions(Function** functions, int size) {
	int linear_count = 0;
	int quaratic_count = 0;
	for (int i = 0; i < size; ++i) {
		if (typeid(*functions[i]) == typeid(LinearFunction)) {
			linear_count += 1;
		}
		if (typeid(*functions[i]) == typeid(QuadraticFunction)) {
			quaratic_count += 1;
		}
	}
	std::cout << "Number of linear functions: " << linear_count << std::endl;
	std::cout << "Number of quadratic functions: " << quaratic_count << std::endl << '\n';
}

void no_answer(Function** functions, int size) {
	std::cout << "Functions without answers:" << std::endl << '\n';
	for (int i = 0; i < size; ++i) {
		QuadraticFunction* qf = dynamic_cast<QuadraticFunction*>(functions[i]);
		if (qf && qf->find_dicsr() < 0) {
			qf->PrintEquation(std::cout);
			qf->Solve(std::cout);
		}
	}
}

void find_value(Function** functions, int size, double x, double y) {
	for (int i = 0; i < size; ++i) {
		if (std::abs(functions[i]->Evaluate(x) - y) < DBL_EPSILON) {
			functions[i]->PrintEquation(std::cout);
			std::cout << '\n';
		}
	}
}

bool compare_a_b_linear(LinearFunction* p) {
	return p->get_b_linear() > p->get_a_linear();
}

bool compare_b_desc(LinearFunction* a, LinearFunction* b) {
	return a->get_b_linear() > b->get_b_linear();
}

bool compare_a_app(QuadraticFunction* a, QuadraticFunction* b) {
	return a->get_a_quadratic() > b->get_a_quadratic();
}

void sort_linear_desc(Function** functions, int size) {
	LinearFunction* lin_func[100];
	int linear_count = 0;
	for (int i = 0; i < size; ++i) {
		LinearFunction* lf = dynamic_cast<LinearFunction*>(functions[i]);
		if (lf && compare_a_b_linear(lf)) {
			lin_func[linear_count++] = lf;
		}
	}
	if (linear_count == 0) {
		std::cout << "No linear functions with b > a" << std::endl;
	}
	else {
		std::sort(lin_func, lin_func + linear_count, compare_b_desc);
		std::cout << "Sorted linear functions;" << std::endl;
		for (int i = 0; i < linear_count; i++) {
			lin_func[i]->PrintEquation(std::cout);
		}
	}
}

void sort_quadratic_app(Function** functions, int size) {
	QuadraticFunction* quad_func[100];
	int quad_count = 0;
	for (int i = 0; i < size; ++i) {
		QuadraticFunction* qf = dynamic_cast<QuadraticFunction*>(functions[i]);
		if (qf) {
			double a = qf->get_a_quadratic();
			double b = qf->get_b_quadratic();
			double c = qf->get_c_quadratic();
			double dou_a_c = 2 * sqrt(a * c);
			if (dou_a_c - b == 0) {
				quad_func[quad_count++] = qf;
			}
		}
	}
	if (quad_count == 0) {
		std::cout << "No full aquares in programm" << std::endl;
	}
	else {
		std::cout << "Sorted quadratic fucntions:" << '\n';
		std::sort(quad_func, quad_func + quad_count, compare_a_app);
		for (int i = 0; i < quad_count; ++i) {
			quad_func[i]->PrintEquation(std::cout);
		}
	}
}
Function* Function::create_function(FunctionType type, double a, double b, double c) {
	switch (type) {
	case Linear:
		return new LinearFunction(a, b);
		break;
	case Quadratic:
		return new QuadraticFunction(a, b, c);
		break;
	default:
		throw std::invalid_argument("Unknown function type");
	}
}

int main() {
	Function** functions = nullptr;
	int size = 0;
	try {
		std::cout << "Enter array size:" << std::endl;
		if (!(std::cin >> size) || size < 0) {
			throw std::invalid_argument("Error: invalid size// Try to enter number higher than 0");
		}
		functions = new Function * [size];
		char choose;
		for (int i = 0; i < size; ++i) {
			std::cout << "Choose type (l - linear, q - quadratic)" << std::endl;
			char type;
			std::cin >> type;
			if (type != 'l' && type != 'q') {
				throw std::invalid_argument("Wrong type input");
			}
			double a = get_number();
			double b = get_number();

			if (type == 'l') {
				functions[i] = Function::create_function(Function::Linear, a, b);
			}
			else if (type == 'q') {
				double c = get_number();
				functions[i] = Function::create_function(Function::Quadratic, a, b, c);
			}
			

		}
		print_information_in_file(functions, size);
		count_functions(functions, size);
		no_answer(functions, size);
		std::cout << "Enter x0 and y0 to find equations that equal for this x0 and y0" << std::endl;
		double x = get_number();
		double y = get_number();
		find_value(functions, size, x, y);
		sort_linear_desc(functions, size);
		sort_quadratic_app(functions, size);
		for (int i = 0; i < size; ++i) {
			delete functions[i];
		}
		delete[] functions;

	}

	catch (const std::invalid_argument& error) {
		std::cout << error.what() << std::endl;
		if (functions != nullptr) {
			for (int i = 0; i < size; ++i) {
				delete functions[i];
			}
			delete[] functions;
		}
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		if (functions != nullptr) {
			for (int i = 0; i < size; ++i) {
				delete functions[i];
			}
			delete[] functions;
		}
	}
}