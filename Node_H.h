#pragma once
#include <string>

int const BOARD_SIZE = 3;

class Node {
private:
	int board[3][3];
	int spaceX;
	int spaceY;
	int cost;
	int h;
	std::string move;
	Node* parent;

	Node() {
		resetBoard();
		this->spaceY = -1;
		this->spaceX = -1;
		this->cost = -1;
		this->h = -1;
		this->parent = nullptr;
	}

	Node(int matrix[BOARD_SIZE][BOARD_SIZE], int spaceX, int spaceY, int cost, int h, Node* parent) {
		copyBoard(matrix);
		this->spaceY = spaceY;
		this->spaceX = spaceX;
		this->cost = cost;
		this->h = h;
		this->parent = parent;
	}

public:
	void copyBoard(int matrix[BOARD_SIZE][BOARD_SIZE]) {
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			for (int j = 0; j < BOARD_SIZE; ++j)
			{
				this->board[i][j] = matrix[i][j];
			}
		}
	}

	void loadBoard(std::string order) {
		for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i) {
			this->board[i / BOARD_SIZE][i % BOARD_SIZE] = order[i] - '0';
			if (order[i] - '0' == 0) {
				this->spaceX = (i - 1) % BOARD_SIZE;
				this->spaceY = (i - 1) / BOARD_SIZE;
			}
		}
	}

	void resetBoard() {
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			for (int j = 0; j < BOARD_SIZE; ++j)
			{
				this->board[i][j] = 0;
			}
		}
	}

	int getH() {
		return this->h;
	}

	int getCost() {
		return this->cost;
	}

	int getSpaceX() {
		return this->spaceX;
	}

	int getSpaceY() {
		return this->spaceY;
	}

	Node* spaceUp() {
		return new Node(std::swap(spaceX, spaceY - 1), this, spaceX, spaceY - 1, cost + 1, "down");
	}

	Node spaceDown() {
		return new Node(std::swap(spaceX, spaceY + 1), this, spaceX, spaceY + 1, cost + 1, "up");
	}

	Node spaceLeft() {
		return new Node(std::swap(spaceX - 1, spaceY), this, spaceX - 1, spaceY, cost + 1, "right");
	}

	Node spaceRight() {
		return new Node(std::swap(spaceX + 1, spaceY), this, spaceX + 1, spaceY, cost + 1, "left");
	}

};

class Compare {
	bool operator() (Node first, Node second) {
		int sumFirst = first.getCost() + first.getH();
		int sumSecond = second.getCost() + second.getH();
		return sumFirst > sumSecond;
	}
};

