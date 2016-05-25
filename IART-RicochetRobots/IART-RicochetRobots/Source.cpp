#include <iostream>

#include "Board.h"
#include <boost\graph\undirected_graph.hpp>
using namespace std;

int main() {
	
	Board board(1);
	cout << board;
	int num;
	cin >> num;
	return 0;
}