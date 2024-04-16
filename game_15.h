#pragma once

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

const int GAME_SIZE = 4;
const int MAX_NUMBER_OF_FILLING = 15;
const int MIN_NUMBER_OF_FILLING = 0;
const int FIELD_SIZE = 500;
const int CELL_SIZE = 120;

enum class Direction {
	Left = 0, Right = 1, Up = 2, Down = 3
};

class FifteenGame : public sf::Drawable, public sf::Transformable {
public:
	FifteenGame();
	void FillWithRandomUniqueNums();
	bool IsSolvable();
	void Move(Direction direction);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool Check();
private:
	int numbers_[GAME_SIZE][GAME_SIZE];
	int elements_[GAME_SIZE * GAME_SIZE];
	int ZeroX_, ZeroY_;
	sf::Font font;
	bool solved = false;
	
	bool IsUnique(int random_num);
	void TransformInOneDim();
	std::pair<int, int> FindZeroPosition();
};
