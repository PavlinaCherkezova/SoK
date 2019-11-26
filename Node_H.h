#pragma once
#include <string>
#include <iostream>

int const BOARD_SIZE = 3;

class Node {
private:
	int board[BOARD_SIZE][BOARD_SIZE];
	int spaceX;
	int spaceY;
	int cost;
	int h;
	Node* parent;
	std::string move;

public:
	Node() {
		this->spaceY = -1;
		this->spaceX = -1;
		this->cost = -1;
		this->h = -1;
		this->parent = nullptr;
		this->move = "";
	}

	Node(int matrix[BOARD_SIZE][BOARD_SIZE], int spaceX, int spaceY, int cost, Node* parent, std::string move) {
		copyBoard(matrix, this->board);
		this->spaceX = spaceX;
		this->spaceY = spaceY;
		this->cost = cost;
		this->h = manhattanDistance();
		this->parent = parent;
		this->move = move;
	}


	void copyBoard(int matrix[BOARD_SIZE][BOARD_SIZE], int crrBoard[BOARD_SIZE][BOARD_SIZE]) {
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			for (int j = 0; j < BOARD_SIZE; ++j)
			{
				crrBoard[i][j] = matrix[i][j];
			}
		}
	}

	void swap(int matrix[BOARD_SIZE][BOARD_SIZE], int x1, int y1, int x2, int y2) {
		int number = matrix[x1][y1];
		matrix[x1][y1] = matrix[x2][y2];
		matrix[x2][y2] = number;
	}

	void printBoard() {
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				std::cout << this->board[i][j]<<" ";
			}
			std::cout << std::endl;
		}
	}

	int manhattanDistance() {
		int result = 0;

		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				if (this->board[i][j] != 0) {
					int number = this->board[i][j];
					int x = number % BOARD_SIZE;
					int y = number / BOARD_SIZE;
					result += abs(x - j) + abs(y - i);
				}
			}
		}

		return result;
	}

	bool isSolution() {
		return manhattanDistance() == 0;
	}

	Node* spaceUp() {
		int newBoard[BOARD_SIZE][BOARD_SIZE];
		copyBoard(this->board, newBoard);
		swap(newBoard, spaceX, spaceY, spaceX -1, spaceY);

		return new Node(newBoard, spaceX -1, spaceY, cost + 1, this, "down");
	}
	
	Node* spaceDown() {
		int newBoard[BOARD_SIZE][BOARD_SIZE];
		copyBoard(this->board, newBoard);
		swap(newBoard, this->spaceX, this->spaceY, this->spaceX +1 , this->spaceY);

		return new Node(newBoard, spaceX + 1, spaceY, cost + 1, this, "up");
	}

	Node* spaceLeft() {
		int newBoard[BOARD_SIZE][BOARD_SIZE];
		copyBoard(this->board, newBoard);
		swap(newBoard, this->spaceX, this->spaceY, this->spaceX, this->spaceY - 1);

		return new Node(newBoard, spaceX, spaceY -1, cost + 1, this, "right");
	}

	Node* spaceRight() {
		int newBoard[BOARD_SIZE][BOARD_SIZE];
		copyBoard(this->board, newBoard);
		swap(newBoard, this->spaceX, this->spaceY, this->spaceX, this->spaceY + 1);

		return new Node(newBoard, spaceX, spaceY + 1, cost + 1, this, "left");
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

	auto getBoard() {
		return this->board;
	}
};

	class Compare {
	public:
		bool operator() (Node* first, Node *second) {
			int sumFirst = first->getCost() + first->getH();
			int sumSecond = second->getCost() + second->getH();
			return sumFirst > sumSecond;
		}
	};

