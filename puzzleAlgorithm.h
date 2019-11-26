#pragma once
#include "Node_H.h"
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <algorithm>


class PuzzleAlgorithm {
private:
	int matrix[BOARD_SIZE][BOARD_SIZE];
	int spaceX;
	int spaceY;
	

	std::priority_queue<Node*, std::vector<Node*>, Compare> pathQueue;
	std::vector<Node*> pathNodes;
	std::vector<Node*> visited;

public:
	PuzzleAlgorithm() {
		resetBoard();
		this->spaceY = -1;
		this->spaceX = -1;
	}

	void resetBoard() {
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			for (int j = 0; j < BOARD_SIZE; ++j)
			{
				this->matrix[i][j] = 0;
			}
		}
	}
	
	void loadBoard(std::string order) {
		for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i) {
			this->matrix[i / BOARD_SIZE][i % BOARD_SIZE] = order[i] - '0';
			if (order[i] - '0' == 0) {
				spaceX = i / BOARD_SIZE;
				spaceY = i % BOARD_SIZE;
			}
		}
	}

	void algorithm(std::string order) {
		loadBoard(order);
		Node *startNode = new Node(matrix, spaceX, spaceY, 0, nullptr,"");
		Node *currentState = startNode;

		while (!currentState->isSolution()) {
			putSuccessors(currentState);
			currentState = pathQueue.top();
			pathNodes.erase(std::remove(pathNodes.begin(), pathNodes.end(), pathQueue.top()), pathNodes.end());
			pathQueue.pop();
		}

		std::cout << currentState->getCost() << std::endl;
		currentState->printBoard();
	}

	bool contains(Node* node, std::vector<Node*> vec) {
		return std::find(vec.begin(), vec.end(), node) != vec.end();
	}

	void addUnique(Node* node) {
		if (!contains(node, visited) && !contains(node, pathNodes)) {
			pathQueue.push(node);
			pathNodes.push_back(node);
		}
	}

	void putSuccessors(Node* currentState) {
		Node* childNode;

		visited.push_back(currentState);
		if (currentState->getSpaceX() != 0) {
			childNode = currentState->spaceUp();
			addUnique(childNode);
		}
		if (currentState->getSpaceX() != BOARD_SIZE - 1) {
			childNode = currentState->spaceDown();
			addUnique(childNode);
		}
		if (currentState->getSpaceY() != 0) {
			childNode = currentState->spaceLeft();
			addUnique(childNode);
		}
		if (currentState->getSpaceY() != BOARD_SIZE - 1) {
			childNode = currentState->spaceRight();
			addUnique(childNode);
		}
	}
};



