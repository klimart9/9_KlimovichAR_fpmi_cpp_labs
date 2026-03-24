#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include <stdexcept>

enum class Color { White, Black };

class ChessPiece {
protected:
	enum Color color;
	int cur_x_;
	int cur_y_;
public:
	virtual std::string GetInfo() = 0;
	virtual bool CanMove(uint16_t x, uint16_t y) = 0;
	virtual void Move(uint16_t x, uint16_t y) = 0;
	ChessPiece() = default;
	virtual int get_x() = 0;
	virtual int get_y() = 0;
	ChessPiece(const Color& color, int cur_x_, int cur_y_)
		: color(color), cur_x_(cur_x_), cur_y_(cur_y_) {
	};
	virtual void set_x(int x) = 0;
	virtual void set_y(int y) = 0;

	virtual Color getColor() const = 0;

	ChessPiece(ChessPiece&&) noexcept = default;
	ChessPiece& operator=(ChessPiece&&) noexcept = default;

	virtual ~ChessPiece();
};

class Bishop : virtual public ChessPiece {
public:
	Bishop(const Color& color, int cur_x_, int cur_y_);
	Bishop() = default;

	Bishop(Bishop&&) noexcept = default;
	Bishop& operator=(Bishop&&) noexcept = default;

	std::string GetInfo();
	bool CanMove(uint16_t x, uint16_t y);
	void Move(uint16_t x, uint16_t y);
	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);

	Color getColor() const { return color; }
};

class Rock : virtual public ChessPiece {
public:
	Rock(const Color& color, int cur_x_, int cur_y_);
	Rock() = default;

	Rock(Rock&&) noexcept = default;
	Rock& operator=(Rock&&) noexcept = default;

	std::string GetInfo();
	bool CanMove(uint16_t x, uint16_t y);
	void Move(uint16_t x, uint16_t y);
	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);

	Color getColor() const { return color; }
};

class Queen : public Rock, public Bishop {
public:
	Queen(const Color& color, int cur_x_, int cur_y_);

	Queen(Queen&&) noexcept = default;
	Queen& operator=(Queen&&) noexcept = default;

	std::string GetInfo();
	bool CanMove(uint16_t x, uint16_t y);
	void Move(uint16_t x, uint16_t y);
	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);

	Color getColor() const { return color; }
};
