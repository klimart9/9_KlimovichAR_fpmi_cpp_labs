#include "Log.h"
#include <iostream>

int MoveLogger::next_id = 1;

MoveLogger::MoveLogger() {
	id = next_id;
	next_id++;
}

MoveLogger::~MoveLogger() {
	std::string filename = "game_" + std::to_string(moves.size()) + "_log.txt";
	std::ofstream file(filename);

	if (file.is_open()) {
		for (size_t i = 0; i < moves.size(); i++) {
			file << (i + 1) << ". " << moves[i] << std::endl;
		}
		file.close();
	}
}

void MoveLogger::add_move(ChessPiece& piece, uint16_t x, uint16_t y) {
	if (piece.CanMove(x, y)) {
		std::string color_str;
		if (piece.getColor() == Color::White) {
			color_str = "white";
		}
		else {
			color_str = "black";
		}
		std::string letters = "abcdefgh";
		std::string move = color_str + ": " + letters[piece.get_x() - 1] + std::to_string(piece.get_y()) + " - " + letters[x - 1] + std::to_string(y);
		moves.push_back(move);
		piece.Move(x, y);
	}
	else {
		piece.Move(x, y);
	}
}

int MoveLogger::get_id() const {
	return id;
}
