#ifndef BOARDNODE_H
#define BOARDNODE_H

#pragma once

#include <algorithm>

#include "Board.h"

class BoardNode
{
private:
	Board state;
	int heurValue;
	BoardNode *parent = NULL;
	vector<BoardNode*> children;

public:
	BoardNode(Board b, int(*heurFunction)(Board));

	Board getState() const;
	int getHeurValue() const;
	BoardNode* getParent() const;
	vector<BoardNode*> getChildren() const;

	bool addChild(BoardNode &c);

	friend bool operator==(const BoardNode& r1, const BoardNode& r2);
	friend bool operator!=(const BoardNode& r1, const BoardNode& r2);
};

BoardNode::BoardNode(Board b, int (*heurFunction)(Board)) {
	state = b;
	heurValue = heurFunction(state);
}

Board BoardNode::getState() const {
	return state;
}
int BoardNode::getHeurValue() const {
	return heurValue;
}
BoardNode* BoardNode::getParent() const {
	return parent;
}
vector<BoardNode*> BoardNode::getChildren() const {
	return children;
}

bool BoardNode::addChild(BoardNode &c) {
	for (unsigned int i = 0; i < children.size(); i++) {
		if (*(children[i]) == c) return false;
	}
	children.push_back(&c);
	c.parent = this;
	return true;
}

bool operator==(const BoardNode& n1, const BoardNode& n2) {
	if (n1.state != n2.state) return false;
	if (n1.heurValue != n2.heurValue) return false;
	if (n1.parent != n2.parent) return false;
	if (n1.children != n2.children) return false;
	return true;
}
bool operator!=(const BoardNode& n1, const BoardNode& n2) {
	return !(n1 == n2);
}

#endif