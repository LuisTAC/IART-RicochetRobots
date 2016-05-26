#include <iostream>

#include "Board.h"
#include <boost\graph\undirected_graph.hpp>
using namespace std;

int main() {
	Board board(1);

	// Test outputs
	//cout << board;
	vector<Board> b = board.createDescNodes();
	for (int i = 0; i < b.size(); i++)
	{
		cout << b[i];
	}
	cout << "\n";
	//cout << board;


	int num;
	cin >> num;
	return 0;
}