#pragma once

#include <vector>
#include <iostream>

#include "Robot.h"
#include "Wall.h"

using namespace std;

enum Direction {N, E, S, W};

class Board {
private:
	Robot robots[4]; //Blue, Green, Red, Yellow

	vector <pair<int, int> > targetsBlue;
	vector <pair<int, int> > targetsGreen;
	vector <pair<int, int> > targetsRed;
	vector <pair<int, int> > targetsYellow;

	vector<Wall> walls;

public:
	Board(int type);

	Robot getRobotBlue();
	Robot getRobotGreen();
	Robot getRobotRed();
	Robot getRobotYellow();
	vector <pair<int, int> > getTargetsBlue();
	vector <pair<int, int> > getTargetsGreen();
	vector <pair<int, int> > getTargetsRed();
	vector <pair<int, int> > getTargetsYellow();
	vector<Wall> getWalls();

	void moveRobot(Color c, Direction d);
};

Board::Board(int type) {
	switch (type)
	{
	case 1:
		robots[0] = Robot(B, 13, 6);
		robots[1] = Robot(G, 2, 5);
		robots[2] = Robot(R, 11, 7);
		robots[3] = Robot(Y, 0, 4);

		targetsBlue.push_back(pair<int, int>(6, 5));
		targetsBlue.push_back(pair<int, int>(12, 6));
		targetsBlue.push_back(pair<int, int>(6, 10));
		targetsBlue.push_back(pair<int, int>(13, 11));

		targetsGreen.push_back(pair<int, int>(9, 1));
		targetsGreen.push_back(pair<int, int>(1, 2));
		targetsGreen.push_back(pair<int, int>(9, 13));
		targetsGreen.push_back(pair<int, int>(3, 14));

		targetsRed.push_back(pair<int, int>(10, 4));
		targetsRed.push_back(pair<int, int>(3, 6));
		targetsRed.push_back(pair<int, int>(1, 13));
		targetsRed.push_back(pair<int, int>(14, 14));

		targetsYellow.push_back(pair<int, int>(6, 1));
		targetsYellow.push_back(pair<int, int>(14, 2));
		targetsYellow.push_back(pair<int, int>(4, 9));
		targetsYellow.push_back(pair<int, int>(8, 10));

		walls.push_back(Wall(V, 4, 0));
		walls.push_back(Wall(V, 10, 0));
		walls.push_back(Wall(V, 6, 1));
		walls.push_back(Wall(V, 8, 1));
		walls.push_back(Wall(V, 0, 2));
		walls.push_back(Wall(V, 14, 2));
		walls.push_back(Wall(V, 10, 4));
		walls.push_back(Wall(V, 6, 5));
		walls.push_back(Wall(V, 11, 6));
		walls.push_back(Wall(V, 6, 7));
		walls.push_back(Wall(V, 8, 7));
		walls.push_back(Wall(V, 6, 8));
		walls.push_back(Wall(V, 8, 8));
		walls.push_back(Wall(V, 3, 9));
		walls.push_back(Wall(V, 5, 10));
		walls.push_back(Wall(V, 8, 10));
		walls.push_back(Wall(V, 12, 11));
		walls.push_back(Wall(V, 7, 12));
		walls.push_back(Wall(V, 1, 13));
		walls.push_back(Wall(V, 8, 13));
		walls.push_back(Wall(V, 3, 14));
		walls.push_back(Wall(V, 11, 15));
		

		walls.push_back(Wall(H, 1, 1));
		walls.push_back(Wall(H, 1, 12));
		walls.push_back(Wall(H, 3, 6));
		walls.push_back(Wall(H, 3, 14));
		walls.push_back(Wall(H, 4, 9));
		walls.push_back(Wall(H, 6, 1));
		walls.push_back(Wall(H, 6, 4));
		walls.push_back(Wall(H, 6, 9));
		walls.push_back(Wall(H, 7, 6));
		walls.push_back(Wall(H, 7, 8));
		walls.push_back(Wall(H, 7, 11));
		walls.push_back(Wall(H, 8, 6));
		walls.push_back(Wall(H, 8, 8));
		walls.push_back(Wall(H, 8, 10));
		walls.push_back(Wall(H, 9, 1));
		walls.push_back(Wall(H, 9, 13));
		walls.push_back(Wall(H, 13, 10));
		walls.push_back(Wall(H, 14, 1));
		walls.push_back(Wall(H, 14, 13));
		walls.push_back(Wall(H, 15, 4));
		walls.push_back(Wall(H, 15, 9));

		break;
		case 2:
		break;
	default:
		cout << "Invalid Board type [1-1]";
		break;
	}
}

Robot Board::getRobotBlue() {
	return robots[B];
}
Robot Board::getRobotGreen() {
	return robots[G];
}
Robot Board::getRobotRed() {
	return robots[R];
}
Robot Board::getRobotYellow() {
	return robots[Y];
}
vector <pair<int, int> > Board::getTargetsBlue() {
	return targetsBlue;
}
vector <pair<int, int> > Board::getTargetsGreen() {
	return targetsGreen;
}
vector <pair<int, int> > Board::getTargetsRed() {
	return targetsRed;
}
vector <pair<int, int> > Board::getTargetsYellow() {
	return targetsYellow;
}
vector<Wall> Board::getWalls() {
	return walls;
}

void Board::moveRobot(Color c, Direction d) {

}