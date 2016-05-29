#include <iostream>
#include <fstream>

#include "Board.h"
#include "Graph.h"

using namespace std;

int heurFunc(Board b) {
	return 0;
}


template<class T>
vector<T> pathToRoot(Vertex<T> *start) {
	vector<T> ret;

	Vertex<T> *v = start;
	while (v->path != NULL) {
		ret.push_back(v->getInfo());
		v = v->path;
	}

	return ret;
}


vector<Board> bfs(Board start) {

	Vertex<Board> *v = &Vertex<Board>(start);
	v->path = NULL;

	vector<Board> ret;
	queue<Vertex<Board> *> q;
	
	vector<Board> visited;
	q.push(v);

	while (!q.empty()) {
		Vertex<Board> *v1 = q.front();
		q.pop();
		ret.push_back(v1->getInfo());
		
		v1->setVisited(true);
		visited.push_back(v1->getInfo());

		//generate successors
		vector<Board> successors = v1->getInfo().createDescNodes();
		typename vector<Board>::iterator itS = successors.begin();
		typename vector<Board>::iterator itSe = successors.end();
		for (; itS != itSe; itS++) {
			Vertex<Board> *child = &Vertex<Board>(*itS);
			if (itS->checkFinished()) {
				v1->addEdge(child, 1);
				child->path = v1;
				return pathToRoot(child);
			}

			vector<Board>::iterator itF = find(visited.begin(),visited.end(),*itS);
			if (itF == visited.end()) { //!visited
				v1->addEdge(child, 1);
				child->path = v1;
				v1->setVisited(true);
				visited.push_back(*itS);
				q.push(child);
			}
		}
		visited.push_back(*itS);
	}

	return vector<Board>();

}

int main() {
	/* initialize random seed: */
	srand(time(NULL));
	Board b(1);
	cout << b << endl;
	cout << b.moveRobot(Y,W) << endl;
	cout << b << endl;

	int num;
	cin >> num;
	return 0;
}