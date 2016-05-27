#include <iostream>

#include <boost\graph\undirected_graph.hpp>

#include "BoardNode.h"
using namespace std;

int heurFunc(Board b) {
	return 0;
}


vector<Board> a_star(Board start) {
	
	// The set of currently discovered nodes still to be evaluated.
	vector<BoardNode> openSet = { BoardNode(start,heurFunc) };
	// The set of nodes already evaluated.
	vector<BoardNode> closedSet;
	
	while (!openSet.empty()) {
		//get most fit node (least cost*)
		sort(openSet.begin(),openSet.end());
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
				currNode.addChild(child);
				openSet.push_back(child);
			}

		}
	};
	return vector<Board>();

}

int main() {
	/* initialize random seed: */
	srand(time(NULL));

	Board b(1);
	b.setCurrGoal(0);
	cout << b.checkFinished();

	int num;
	cin >> num;
	return 0;
}