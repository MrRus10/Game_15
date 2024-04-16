#include "game_15.h"

FifteenGame::FifteenGame() {
	font.loadFromFile("C:/Windows/Fonts/calibri.ttf");
	FillWithRandomUniqueNums();
}

void FifteenGame::FillWithRandomUniqueNums() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(MIN_NUMBER_OF_FILLING, MAX_NUMBER_OF_FILLING);
	for (int i = 0; i < GAME_SIZE; ++i) {
		for (int j = 0; j < GAME_SIZE; ++j) {
			int random_num = 0;
			do {
				random_num = dist(gen);
			} while (!IsUnique(random_num));
			numbers_[i][j] = random_num;
			std::cout << numbers_[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	TransformInOneDim();
}

bool FifteenGame::IsUnique(int random_num) {
	for (int i = 0; i < GAME_SIZE; ++i) {
		for (int j = 0; j < GAME_SIZE; ++j) {
			if (numbers_[i][j] == random_num) {
				return false;
			}
		}
	}
	return true;
}

std::pair<int, int> FifteenGame::FindZeroPosition() {
	for (int i = 0; i < GAME_SIZE; ++i) {
		for (int j = 0; j < GAME_SIZE; ++j) {
			if (numbers_[i][j] == 0) {
				ZeroX_ = i;
				ZeroY_ = j;
			}
		}
	}
	return {ZeroX_, ZeroY_};
}

bool FifteenGame::IsSolvable() {
	int N = 0, chaos = 0, current_num;
	for (int k = 0; k < GAME_SIZE * GAME_SIZE; ++k) {
		current_num = elements_[k];
		if (current_num == 0) {
			continue;
		}
		for (int l = k + 1; l < GAME_SIZE * GAME_SIZE; ++l) {
			if (current_num > elements_[l] && elements_[l] != 0) {
				++chaos;
			}
		}
	}
	N = chaos + FindZeroPosition().first + 1;
	if (N % 2 == 1) {
		std::cout << "Game is unsolvable" << std::endl;
		return false;
	}
	else {
		std::cout << "Game is solvable" << std::endl;
	}
	return true;
}

void FifteenGame::TransformInOneDim() {
	int k = 0;
	for (int i = 0; i < GAME_SIZE; ++i) {
		for (int j = 0; j < GAME_SIZE; ++j) {
			elements_[k] = numbers_[i][j];
			++k;
		}
	}
}

void FifteenGame::Move(Direction direction) {
	std::pair<int, int> zero = FindZeroPosition();
	if (direction == Direction::Left && zero.second != 0) {
		numbers_[zero.first][zero.second] = numbers_[zero.first][zero.second - 1];
		numbers_[zero.first][zero.second - 1] = 0;
		--zero.second;
		TransformInOneDim();
	}
	if (direction == Direction::Right && zero.second != GAME_SIZE - 1) {
		numbers_[zero.first][zero.second] = numbers_[zero.first][zero.second + 1];
		numbers_[zero.first][zero.second + 1] = 0;
		++zero.second;
		TransformInOneDim();
	}
	if (direction == Direction::Up && zero.first != 0) {
		numbers_[zero.first][zero.second] = numbers_[zero.first - 1][zero.second];
		numbers_[zero.first - 1][zero.second] = 0;
		++zero.first;
		TransformInOneDim();
	}
	if (direction == Direction::Down && zero.first != GAME_SIZE - 1) {
		numbers_[zero.first][zero.second] = numbers_[zero.first + 1][zero.second];
		numbers_[zero.first + 1][zero.second] = 0;
		--zero.first;
		TransformInOneDim();
	}

	std::cout << std::endl;
	for (int i = 0; i < GAME_SIZE; ++i) {
		for (int j = 0; j < GAME_SIZE; ++j) {
			std::cout << numbers_[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	solved = Check();
}

bool FifteenGame::Check() {
	for (int i = 0; i < GAME_SIZE * GAME_SIZE; i++) {
		if (elements_[i] > 0 && elements_[i] != i + 1) {
			return false;
		}
	}
	return true;
}

void FifteenGame::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	// Drawing the game field frame
	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	// Doing the frame for drawing of all cells 
	shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	// Doing text template for drawing of cells numbers
	sf::Text text("", font, 52);
	for (int i = 0; i < GAME_SIZE * GAME_SIZE; i++) {
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(std::to_string(elements_[i]));
		if (solved) {
			// Solved game is defined by another color
			shape.setOutlineColor(sf::Color::Cyan);
			text.setFillColor(sf::Color::Cyan);
		}
		else if (elements_[i] == i + 1) {
			text.setFillColor(sf::Color::Green);
		}

		if (elements_[i] > 0) {
			sf::Vector2f position(i % GAME_SIZE * CELL_SIZE + 10.f, i / GAME_SIZE * CELL_SIZE + 10.f);
			shape.setPosition(position);
			text.setPosition(position.x + 30.f + (elements_[i] < 10 ? 15.f : 0.f), position.y + 25.f);
			target.draw(shape, states);
			target.draw(text, states);
		}
	}
}