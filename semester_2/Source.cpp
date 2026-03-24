#include "Chess.h"
#include "Log.h"

int main() {
	try {
		MoveLogger logger;
		Queen b(Color::White, 2, 2);
		Queen j(Color::Black, 1, 1);
		Bishop l(Color::White, 1, 2);

		logger.add_move(b, 4, 4);
		logger.add_move(j, 3, 3);
		logger.add_move(l, 7, 2);
	}
	catch (...) {
		std::cout << "Error";
	}
}