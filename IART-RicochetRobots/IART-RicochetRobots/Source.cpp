#include <iostream>

#include <boost\graph\undirected_graph.hpp>

#include "Board.h"
using namespace std;

void a_star() {

}

int main() {
	/* initialize random seed: */
	srand(time(NULL));

	Board b(1);
	Board b2(1);
	Board b3(b);
	Board b4(1);
	cout << "b.currGoal : " << b.getCurrGoal() << endl;
	cout << "b2.currGoal : " << b2.getCurrGoal() << endl;
	cout << "b3.currGoal : " << b3.getCurrGoal() << endl;
	cout << "b4.currGoal : " << b4.getCurrGoal() << endl;
	cout << "b==b2: " << (b == b2) << endl;
	cout << "b==b3: " << (b == b3) << endl;
	cout << "b==b4: " << (b == b4) << endl;
	cout << "b2==b4: " << (b2 == b4) << endl;

	int num;
	cin >> num;
	return 0;
}