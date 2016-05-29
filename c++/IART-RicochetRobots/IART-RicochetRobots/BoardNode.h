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
	BoardNode(Board b, int(*heur)(Board));

	Board getState() const;
	int getCost() const;
	int getHeurValue() const;
	int getTotalEstCost() const;
	BoardNode* getParent() const;
	vector<BoardNode*> getChildren() const;
	vector<Board> getPathToRoot() const;

	void addChild(BoardNode *c);

	friend bool operator==(const BoardNode& r1, const BoardNode& r2);
	friend bool operator!=(const BoardNode& r1, const BoardNode& r2);
	friend bool operator<(const BoardNode& r1, const BoardNode& r2);
};

BoardNode::BoardNode(Board b, int(*heur)(Board)) {
	state = b;
	heurValue = heur(state);
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

void BoardNode::addChild(BoardNode *c) {
	children.push_back(c);
	c->parent = this;
	c->cost = cost + 1;
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

/*
vector<Board> a_star(Board start) {

	// The set of currently discovered nodes still to be evaluated.
	vector<BoardNode> openSet = { BoardNode(start,heurFunc) };
	// The set of nodes already evaluated.
	vector<BoardNode> closedSet;

	while (!openSet.empty()) {
		//get most fit node (least cost*)
		sort(openSet.begin(), openSet.end());
		BoardNode currNode = openSet.back();
		closedSet.push_back(currNode);
		openSet.pop_back();

		//add successors
		vector<Board> children = currNode.getState().createDescNodes();
		for (unsigned int i = 0; i < children.size(); i++) {
			BoardNode child = BoardNode(children[i], heurFunc);

			//check solution
			if (children[i].checkFinished()) {
				return child.getPathToRoot();
			}

			//search in openSet
			vector<BoardNode>::iterator openIT = find(openSet.begin(), openSet.end(), child);
			if (openIT != openSet.end() && child.getTotalEstCost() < (*openIT).getTotalEstCost())
				openSet.erase(openIT);

			//search in closeSet
			vector<BoardNode>::iterator closedIT = find(closedSet.begin(), closedSet.end(), child);
			if (closedIT != closedSet.end() && child.getTotalEstCost() < (*closedIT).getTotalEstCost())
				closedSet.erase(closedIT);

			openIT = find(openSet.begin(), openSet.end(), child);
			closedIT = find(closedSet.begin(), closedSet.end(), child);
			if (openIT == openSet.end() && closedIT == closedSet.end()) {
				currNode.addChild(&child);
				openSet.push_back(child);
			}

		}
	};
	return vector<Board>();
}*/
/*
vector<Board> bfs(Board start) {
	BoardNode root(start, heurFunc);

	queue<BoardNode> q;
	q.push(root);

	vector<Board*> visited;

	while (!q.empty()) {
		BoardNode curr = q.front();
		visited.push_back(&(curr.getState()));
		q.pop();

		vector<Board> children = curr.getState().createDescNodes();
		for (unsigned int i = 0; i < children.size(); i++) {

			bool found = false;
			for (unsigned int j = 0; j < visited.size(); j++) {
				if (children[i] == *(visited[j])) found = true;
			}

			if (!found) {
				BoardNode child(children[i], heurFunc);
				curr.addChild(&child);
				if (children[i].checkFinished())
					return child.getPathToRoot();
				q.push(child);
			}
		}

		visited.push_back(&curr.getState());

	}
	return vector<Board>();
}*/
#endif