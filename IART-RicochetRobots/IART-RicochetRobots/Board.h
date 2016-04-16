#pragma once

#include <vector>
#include <iostream>
#include <cmath>

#include "Robot.h"
#include "Wall.h"

using namespace std;

enum Direction {N, E, S, W};

class Board {
private:
	Robot robots[4]; //Blue, Green, Red, Yellow

	vector <pair<int, int> > targets[4];

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
	int minDistanceToTarget(Color clr);
	int sumMinDistances();

	void moveRobot(Color clr, Direction dir);
};

Board::Board(int type) {
	switch (type)
	{
	case 1:
		robots[0] = Robot(B, 13, 6);
		robots[1] = Robot(G, 2, 5);
		robots[2] = Robot(R, 11, 7);
		robots[3] = Robot(Y, 0, 4);

		targets[B].push_back(pair<int, int>(6, 5));
		targets[B].push_back(pair<int, int>(12, 6));
		targets[B].push_back(pair<int, int>(6, 10));
		targets[B].push_back(pair<int, int>(13, 11));

		targets[G].push_back(pair<int, int>(9, 1));
		targets[G].push_back(pair<int, int>(1, 2));
		targets[G].push_back(pair<int, int>(9, 13));
		targets[G].push_back(pair<int, int>(3, 14));

		targets[R].push_back(pair<int, int>(10, 4));
		targets[R].push_back(pair<int, int>(3, 6));
		targets[R].push_back(pair<int, int>(1, 13));
		targets[R].push_back(pair<int, int>(14, 14));

		targets[Y].push_back(pair<int, int>(6, 1));
		targets[Y].push_back(pair<int, int>(14, 2));
		targets[Y].push_back(pair<int, int>(4, 9));
		targets[Y].push_back(pair<int, int>(8, 10));

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
int Board::minDistanceToTarget(Color clr) {
	Robot robot = robots[clr];
	pair<int, int> coordsRobot = robot.getCoords();
	int min = 50;
	for (unsigned int i = 0; i < targets[clr].size(); i++) {
		pair<int, int> target = targets[clr][i];
		int dist = (target.first - coordsRobot.first) + (target.second - coordsRobot.second);
		if (dist < min) min = dist;
	}
	return min;
}
int Board::sumMinDistances() {
	int total = 0;
	for (int i = 0; i < 4; i++) {
		total += minDistanceToTarget(Color(i));
	}
}

void Board::moveRobot(Color clr, Direction dir) {
	Robot robot = robots[clr];
	pair<int, int> coordsRobot = robot.getCoords();
	switch (dir)
	{
	case N:
		if (coordsRobot.second == 0) return;
		int max = 0;
		for (unsigned int i = 0; i < walls.size(); i++) {
			Wall wall = walls[i];
			if (wall.getOrientation() == H && wall.getCoords().first == coordsRobot.first &&
				wall.getCoords().second<coordsRobot.second && wall.getCoords().second>max)
					max = wall.getCoords().second;
		}
		if (max != 0) robot.setCoords(coordsRobot.first, max);
		break;
	case E:
		if (coordsRobot.first == 15) return;
		int min = 15;
		for (unsigned int i = 0; i < walls.size(); i++) {
			Wall wall = walls[i];
			if (wall.getOrientation() == V && wall.getCoords().second == coordsRobot.second &&
				wall.getCoords().first>coordsRobot.first && wall.getCoords().first<min)
				min = wall.getCoords().first;
		}
		if (min != 15) robot.setCoords(min, coordsRobot.second);
		break;
	case S:
		if (coordsRobot.second == 15) return;
		int min = 15;
		for (unsigned int i = 0; i < walls.size(); i++) {
			Wall wall = walls[i];
			if (wall.getOrientation() == H && wall.getCoords().first == coordsRobot.first &&
				wall.getCoords().second>coordsRobot.second && wall.getCoords().second<min)
				min = wall.getCoords().second;
		}
		if (min != 15) robot.setCoords(coordsRobot.first, min);
		break;
	case W:
		if (coordsRobot.first == 0) return;
		int max = 0;
		for (unsigned int i = 0; i < walls.size(); i++) {
			Wall wall = walls[i];
			if (wall.getOrientation() == V && wall.getCoords().second == coordsRobot.second &&
				wall.getCoords().first<coordsRobot.first && wall.getCoords().first>max)
				max = wall.getCoords().first;
		}
		if (max != 0) robot.setCoords(max, coordsRobot.second);
		break;
	}
}