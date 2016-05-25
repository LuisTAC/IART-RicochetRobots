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
	Robot robots[4]; //Blue;      Green;      Red;      Yellow
					 //A,C,D,E    F,H,I,J     Q,S,T,U   V,W,X,Z

	vector <pair<int, int> > targets[4];

	vector<Wall> walls;

public:
	Board(int type);

	Robot getRobotBlue() const;
	Robot getRobotGreen() const;
	Robot getRobotRed() const;
	Robot getRobotYellow() const;
	vector <pair<int, int> > getTargetsBlue() const;
	vector <pair<int, int> > getTargetsGreen() const;
	vector <pair<int, int> > getTargetsRed() const;
	vector <pair<int, int> > getTargetsYellow() const;
	vector<Wall> getWalls() const;
	string toString() const;

	void moveRobot(Color clr, Direction dir);

	friend ostream& operator<<(ostream& os, const Board& board);
};

Board::Board(int type) {
	switch (type)
	{
	case 1:
		robots[0] = Robot(B, 13, 6);
		robots[1] = Robot(G, 2, 5);
		robots[2] = Robot(R, 11, 7);
		robots[3] = Robot(Y, 0, 4);

		//Saturno
		//Triangulo
		//Lua
		//Estrela

		targets[B].push_back(pair<int, int>(6, 5));
		targets[B].push_back(pair<int, int>(12, 6));
		targets[B].push_back(pair<int, int>(6, 10));
		targets[B].push_back(pair<int, int>(13, 11));

		targets[G].push_back(pair<int, int>(3, 14));
		targets[G].push_back(pair<int, int>(1, 2));
		targets[G].push_back(pair<int, int>(9, 13));
		targets[G].push_back(pair<int, int>(9, 1));

		targets[R].push_back(pair<int, int>(10, 4));
		targets[R].push_back(pair<int, int>(14, 14));
		targets[R].push_back(pair<int, int>(3, 6));
		targets[R].push_back(pair<int, int>(1, 13));

		targets[Y].push_back(pair<int, int>(8, 10));
		targets[Y].push_back(pair<int, int>(4, 9));
		targets[Y].push_back(pair<int, int>(14, 2));
		targets[Y].push_back(pair<int, int>(6, 1));

		walls.push_back(Wall(V, 4, 0));
		walls.push_back(Wall(V, 10, 0));
		walls.push_back(Wall(V, 6, 1));
		walls.push_back(Wall(V, 8, 1));
		walls.push_back(Wall(V, 0, 2));
		walls.push_back(Wall(V, 14, 2));
		walls.push_back(Wall(V, 10, 4));
		walls.push_back(Wall(V, 6, 5));
		walls.push_back(Wall(V, 2, 6));
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
		walls.push_back(Wall(V, 14, 14));
		walls.push_back(Wall(V, 4, 15));
		walls.push_back(Wall(V, 11, 15));

		walls.push_back(Wall(H, 0, 5));
		walls.push_back(Wall(H, 0, 10));
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
		walls.push_back(Wall(H, 10, 4));
		walls.push_back(Wall(H, 12, 5));
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

Robot Board::getRobotBlue() const {
	return robots[B];
}
Robot Board::getRobotGreen() const {
	return robots[G];
}
Robot Board::getRobotRed() const {
	return robots[R];
}
Robot Board::getRobotYellow() const {
	return robots[Y];
}
vector <pair<int, int> > Board::getTargetsBlue() const {
	return targets[B];
}
vector <pair<int, int> > Board::getTargetsGreen() const {
	return targets[G];
}
vector <pair<int, int> > Board::getTargetsRed() const {
	return targets[R];
}
vector <pair<int, int> > Board::getTargetsYellow() const {
	return targets[Y];
}
vector<Wall> Board::getWalls() const {
	return walls;
}
string Board::toString() const {
	//top line (walls)
	vector<char> top;
	top.push_back(char(201));
	for (unsigned int i = 0; i < 31; i++)
		top.push_back(char(205));
	top.push_back(char(187));
	top.push_back('\n');

	//bottom line (walls)
	vector<char> bottom;
	bottom.push_back(char(200));
	for (unsigned int i = 0; i < 31; i++)
		bottom.push_back(char(205));
	bottom.push_back(char(188));
	bottom.push_back('\n');

	//left line (walls)
	vector<char> left;
	for (unsigned int i = 0; i < 31; i++)
		left.push_back(char(186));

	//right line (walls)
	vector<char> right;
	for (unsigned int i = 0; i < 31; i++)
		right.push_back(char(186));

	vector< vector<char> > str(31, vector<char>(31, ' '));
	//grid (no-walls)
	for (unsigned int i = 1; i < 31; i += 2) {
		for (unsigned int j = 0; j < 31; j++) {
			if (j<13 || j>17 || i<13 || i>17) str[i][j] = char(196);
		}
	}
	for (unsigned int i = 1; i < 31; i += 2) {
		for (unsigned int j = 0; j < 31; j++) {
			if (j<13 || j>17 || i<13 || i>17) str[j][i] = char(179);
		}
	}
	for (unsigned int i = 1; i < 31; i += 2) {
		for (unsigned int j = 1; j < 31; j += 2) {
			if (j<13 || j>17 || i<13 || i>17) str[j][i] = char(197);
		}
	}

	//center (walls)
	str[13][15] = char(205);
	str[17][15] = char(205);
	str[15][13] = char(186);
	str[15][17] = char(186);
	str[13][13] = char(201);
	str[13][17] = char(187);
	str[17][13] = char(200);
	str[17][17] = char(188);

	//walls
	for (unsigned int i = 0; i < walls.size(); i++) {
		Wall wall = walls[i];
		int x = wall.getCoords().first;
		int y = wall.getCoords().second;

		if (wall.getOrientation() == V) {
			str[y * 2][x * 2 + 1] = char(186);
			if (y == 0) top[x * 2 + 2] = char(203);
			else if (y == 15) bottom[x * 2 + 2] = char(202);
			else {
				if (str[y * 2 - 1][x * 2] == char(205))
					str[y * 2 - 1][x * 2 + 1] = char(187);
				else if (str[y * 2 - 1][x * 2 + 2] == char(205))
					str[y * 2 - 1][x * 2 + 1] = char(201);
				else if (str[y * 2 + 1][x * 2 + 2] == char(205))
					str[y * 2 + 1][x * 2 + 1] = char(200);
				else if (str[y * 2 + 1][x * 2] == char(205))
					str[y * 2 + 1][x * 2 + 1] = char(188);
			}
		}
		else if (wall.getOrientation() == H) {
			str[y * 2 + 1][x * 2] = char(205);
			if (x == 0) left[y * 2 + 1] = char(204);
			else if (x == 15) right[y * 2 + 1] = char(185);
			else {
				if (str[y * 2][x * 2 - 1] == char(186))
					str[y * 2 + 1][x * 2 - 1] = char(200);
				else if (str[y * 2][x * 2 + 1] == char(186))
					str[y * 2 + 1][x * 2 + 1] = char(188);
				else if (str[y * 2 + 2][x * 2 + 1] == char(186))
					str[y * 2 + 1][x * 2 + 1] = char(187);
				else if (str[y * 2 + 2][x * 2 - 1] == char(186))
					str[y * 2 + 1][x * 2 - 1] = char(201);
			}
		}
	}

	//targets - blue
	char targetsBlueRep[] = {'A','C','D','E'};
	for (unsigned int i = 0; i < targets[B].size(); i++) {
		int x = targets[B][i].first;
		int y = targets[B][i].second;
		str[y*2][x*2] = targetsBlueRep[i];
	}
	//targets - green
	char targetsGreenRep [] = { 'F','H','I','J' };
	for (unsigned int i = 0; i < targets[G].size(); i++) {
		int x = targets[G][i].first;
		int y = targets[G][i].second;
		str[y * 2][x * 2] = targetsGreenRep[i];
	}
	//targets - red
	char targetsRedRep [] = { 'Q','S','T','U' };
	for (unsigned int i = 0; i < targets[R].size(); i++) {
		int x = targets[R][i].first;
		int y = targets[R][i].second;
		str[y * 2][x * 2] = targetsRedRep[i];
	}
	//targets - yellow
	char targetsYellowRep [] = { 'V','W','X','Z' };
	for (unsigned int i = 0; i < targets[Y].size(); i++) {
		int x = targets[Y][i].first;
		int y = targets[Y][i].second;
		str[y * 2][x * 2] = targetsYellowRep[i];
	}

	//robots
	for (unsigned int i = 0; i < 4; i++) {
		Robot robot = robots[i];
		int x = robot.getCoords().first;
		int y = robot.getCoords().second;
		char clr = '\0';
		switch (robot.getColor()) {
		case B:
			clr = 'B';
			break;
		case G:
			clr = 'G';
			break;
		case R:
			clr = 'R';
			break;
		case Y:
			clr = 'Y';
			break;
		}
		str[y*2][x*2] = clr;
	}

	string ret = "";
	//output
	for (unsigned int i = 0; i < top.size(); i++) {
		ret += top[i];
	}
	for (unsigned int i = 0; i < 31; i++) {
		ret += left[i];
		for (unsigned int j = 0; j < 31; j++) {
			ret += str[i][j];
		}
		ret += right[i];
		ret += "\n";
	}
	for (unsigned int i = 0; i < bottom.size(); i++) {
		ret += bottom[i];
	}
	return ret;
}

void Board::moveRobot(Color clr, Direction dir) {
	Robot robot = robots[clr];
	pair<int, int> coordsRobot = robot.getCoords();
	int max = 0;
	int min = 15;
	switch (dir)
	{
	case N:
		if (coordsRobot.second == 0) return;
		for (unsigned int i = 0; i < walls.size(); i++) {
			Wall wall = walls[i];
			if (wall.getOrientation() == H && wall.getCoords().first == coordsRobot.first &&
				wall.getCoords().second<coordsRobot.second && wall.getCoords().second>max)
					max = wall.getCoords().second;
		}
		for (unsigned int i = 0; i < 4; i++) {
			if (i == clr) continue;
			Robot robot2 = robots[i];
			if (robot2.getCoords().first == coordsRobot.first && robot2.getCoords().second<coordsRobot.second &&
				robot2.getCoords().second>max) max = robot2.getCoords().second;
		}
		if (max != 0) robot.setCoords(coordsRobot.first, max);
		break;
	case E:
		if (coordsRobot.first == 15) return;
		for (unsigned int i = 0; i < walls.size(); i++) {
			Wall wall = walls[i];
			if (wall.getOrientation() == V && wall.getCoords().second == coordsRobot.second &&
				wall.getCoords().first>coordsRobot.first && wall.getCoords().first<min)
				min = wall.getCoords().first;
		}
		for (unsigned int i = 0; i < 4; i++) {
			if (i == clr) continue;
			Robot robot2 = robots[i];
			if (robot2.getCoords().second == coordsRobot.second && robot2.getCoords().first>coordsRobot.first &&
				robot2.getCoords().first<min) min = robot2.getCoords().first;
		}
		if (min != 15) robot.setCoords(min, coordsRobot.second);
		break;
	case S:
		if (coordsRobot.second == 15) return;
		for (unsigned int i = 0; i < walls.size(); i++) {
			Wall wall = walls[i];
			if (wall.getOrientation() == H && wall.getCoords().first == coordsRobot.first &&
				wall.getCoords().second>coordsRobot.second && wall.getCoords().second<min)
				min = wall.getCoords().second;
		}
		for (unsigned int i = 0; i < 4; i++) {
			if (i == clr) continue;
			Robot robot2 = robots[i];
			if (robot2.getCoords().first == coordsRobot.first && robot2.getCoords().second>coordsRobot.second &&
				robot2.getCoords().second<min) min = robot2.getCoords().second;
		}
		if (min != 15) robot.setCoords(coordsRobot.first, min);
		break;
	case W:
		if (coordsRobot.first == 0) return;
		for (unsigned int i = 0; i < walls.size(); i++) {
			Wall wall = walls[i];
			if (wall.getOrientation() == V && wall.getCoords().second == coordsRobot.second &&
				wall.getCoords().first<coordsRobot.first && wall.getCoords().first>max)
				max = wall.getCoords().first;
		}
		for (unsigned int i = 0; i < 4; i++) {
			if (i == clr) continue;
			Robot robot2 = robots[i];
			if (robot2.getCoords().second == coordsRobot.second && robot2.getCoords().first<coordsRobot.first &&
				robot2.getCoords().first>max) max = robot2.getCoords().first;
		}
		if (max != 0) robot.setCoords(max, coordsRobot.second);
		break;
	}
}

ostream& operator<<(ostream& os, Board& board)
{
	os << board.toString().c_str();
	return os;
}