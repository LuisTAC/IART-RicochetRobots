#ifndef BOARDNODE_H
#define BOARDNODE_H

#pragma once

#include <algorithm>

#include "Board.h"

class BoardNode
{
private:
	Board state;
	int cost = 0;
	int heurValue;
	BoardNode *parent = NULL;
	vector<BoardNode*> children;

public:
	BoardNode(Board b, int(*heurFunction)(Board b));

	Board getState() const;
	int getCost() const;
	int getHeurValue() const;
	int getTotalEstCost() const;
	BoardNode* getParent() const;
	vector<BoardNode*> getChildren() const;
	vector<Board> getPathToRoot() const;

	bool addChild(BoardNode &c);

	friend bool operator==(const BoardNode& r1, const BoardNode& r2);
	friend bool operator!=(const BoardNode& r1, const BoardNode& r2);
	friend bool operator<(const BoardNode& r1, const BoardNode& r2);
};

BoardNode::BoardNode(Board b, int (*heurFunction)(Board b)) {
	state = b;
	heurValue = heurFunction(state);
}

Board BoardNode::getState() const {
	return state;
}
int BoardNode::getCost() const {
	return cost;
}
int BoardNode::getHeurValue() const {
	return heurValue;
}
int BoardNode::getTotalEstCost() const {
	return cost + heurValue;
}
BoardNode* BoardNode::getParent() const {
	return parent;
}
vector<BoardNode*> BoardNode::getChildren() const {
	return children;
}
vector<Board> BoardNode::getPathToRoot() const {
	vector<Board> ret;
	ret.push_back(state);

	BoardNode const *currNode = this;
	while(currNode->parent != NULL) {
		currNode = currNode->parent;
		ret.push_back(currNode->state);
	}

	return ret;
}

bool BoardNode::addChild(BoardNode &c) {
	for (unsigned int i = 0; i < children.size(); i++) {
		if (*(children[i]) == c) return false;
	}
	children.push_back(&c);
	c.parent = this;
	c.cost = cost + 1;
	return true;
}

bool operator==(const BoardNode& n1, const BoardNode& n2) {
	if (n1.state != n2.state) return false;
	/*
	if (n1.heurValue != n2.heurValue) return false;
	if (n1.parent != n2.parent) return false;
	if (n1.children != n2.children) return false;
	*/
	return true;
}
bool operator!=(const BoardNode& n1, const BoardNode& n2) {
	return !(n1 == n2);
}
bool operator<(const BoardNode& n1, const BoardNode& n2) {
	return n1.getTotalEstCost() > n2.getTotalEstCost();
}

#endif