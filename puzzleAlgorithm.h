#pragma once
#include "Node_H.h"
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <algorithm>

//template< class Node, class Container = std::vector<Node>, class Comparator = Compare>
//class MyQueue : public std::priority_queue<int, std::vector<Node>, Comparator>
//{
//public:
//	typedef typename std::priority_queue<Node, std::vector<Node>, Comparator>::container_type::const_iterator const_iterator;
//
//	const_iterator find(Node node) const
//	{
//		auto first = this->c.cbegin();
//		auto last = this->c.cend();
//		while (first != last) {
//			if (*first == node) return first;
//			++first;
//		}
//		return last;
//	}
//};

class PuzzleAlgorithm {
private:
	Node startNode;
	std::priority_queue<Node, std::vector<Node>, Compare> pathQueue;
	std::vector<Node> pathNodes;
	std::vector<Node> visited;

	//auto ptr = pathQueue;
	
	int manhattanDistance(int arr[BOARD_SIZE][BOARD_SIZE]) {
		int result = 0;

		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				if (arr[i][j] != 0) {
					int number = arr[i][j] - 1;
					int x = number % BOARD_SIZE;
					int y = number / BOARD_SIZE;
					result += abs(x - j) + abs(y - i);
				}
			}
		}

		return result;
	}

	bool isSolution(int board[BOARD_SIZE][BOARD_SIZE]) {
		return manhattanDistance(board) == 0;
	}

	void algorithm(std::string order) {
		startNode.loadBoard(order);
	}

	bool contains(Node node, std::vector<Node> vec) {
		return std::find(vec.begin(), vec.end(), node) != vec.end();
	}

	void addUnique(Node node) {
		if (!contains(node, visited) && !contains(node, pathNodes)) {
			pathQueue.push(node);
		}
	}

	void putSuccessors(Node currentState) {
		
		Node childNode;

		visited.push_back(currentState);
		if (currentState.getSpaceY() != 0) {
			childNode = currentState.spaceUp();
			addUnique(childNode);
		}
		if (currentState.getSpaceY() != BOARD_SIZE - 1) {
			childNode = currentState.spaceDown();
			addUnique(childNode);
		}
		if (currentState.getSpaceX() != 0) {
			childNode = currentState.spaceLeft();
			addUnique(childNode);
		}
		if (currentState.getSpaceX() != BOARD_SIZE - 1) {
			childNode = currentState.spaceRight();
			addUnique(childNode);
		}
	}

	
};



