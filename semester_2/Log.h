#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include "Chess.h"

class MoveLogger {
protected:
	std::vector<std::string> moves;
	static int next_id;
	int id;

public:
	MoveLogger();
	~MoveLogger();

	MoveLogger(MoveLogger&&) noexcept = default;
	MoveLogger& operator=(MoveLogger&&) noexcept = default;

	void add_move(ChessPiece& piece, uint16_t x, uint16_t y);
	int get_id() const;
};
