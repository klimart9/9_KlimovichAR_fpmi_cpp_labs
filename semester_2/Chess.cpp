#include "Chess.h"

ChessPiece::~ChessPiece() {}

Bishop::Bishop(const Color& color, int cur_x_, int cur_y_)
	: ChessPiece::ChessPiece(color, cur_x_, cur_y_) {}

std::string Bishop::GetInfo() {
	std::string letters = "abcdefgh";
	return ("B" + letters[cur_x_ - 1] + std::to_string(cur_y_));
}

bool Bishop::CanMove(uint16_t x, uint16_t y) {
	if (x - cur_x_ == y - cur_y_) {
		return true;
	}
	return false;
}

void Bishop::Move(uint16_t x, uint16_t y) {
	if (CanMove(x, y)) {
		cur_x_ = x;
		cur_y_ = y;
	}
	else {
		throw std::invalid_argument("Bishop cant move like that");
	}
}

int Bishop::get_x() { return cur_x_; }
int Bishop::get_y() { return cur_y_; }
void Bishop::set_x(int x) { cur_x_ = x; }
void Bishop::set_y(int y) { cur_y_ = y; }

Rock::Rock(const Color& color, int cur_x_, int cur_y_)
	: ChessPiece::ChessPiece(color, cur_x_, cur_y_) {}

std::string Rock::GetInfo() {
	std::string letters = "abcdefgh";
	return ("R" + letters[cur_x_ - 1] + std::to_string(cur_y_));
}

bool Rock::CanMove(uint16_t x, uint16_t y) {
	if (x - cur_x_ == 0 || y - cur_y_ == 0) {
		return true;
	}
	return false;
}

void Rock::Move(uint16_t x, uint16_t y) {
	if (CanMove(x, y)) {
		cur_x_ = x;
		cur_y_ = y;
	}
	else {
		throw std::invalid_argument("Rock cant move like that");
	}
}

int Rock::get_x() { return cur_x_; }
int Rock::get_y() { return cur_y_; }
void Rock::set_x(int x) { cur_x_ = x; }
void Rock::set_y(int y) { cur_y_ = y; }

Queen::Queen(const Color& color, int cur_x_, int cur_y_)
	: ChessPiece::ChessPiece(color, cur_x_, cur_y_) {}

std::string Queen::GetInfo() {
	std::string letters = "abcdefgh";
	return ("Q" + letters[cur_x_ - 1] + std::to_string(cur_y_));
}

bool Queen::CanMove(uint16_t x, uint16_t y) {
	if (Bishop::CanMove(x, y) || Rock::CanMove(x, y)) {
		return true;
	}
	return false;
}

void Queen::Move(uint16_t x, uint16_t y) {
	if (Bishop::CanMove(x, y) || Rock::CanMove(x, y)) {
		cur_x_ = x;
		cur_y_ = y;
	}
	else {
		throw std::invalid_argument("Queen cant move like that");
	}
}

int Queen::get_x() { return cur_x_; }
int Queen::get_y() { return cur_y_; }
void Queen::set_x(int x) { cur_x_ = x; }
void Queen::set_y(int y) { cur_y_ = y; }
