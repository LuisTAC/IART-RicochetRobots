#pragma once

#include <utility>

using namespace std;

enum Color { B, G, R, Y };

class Robot {
private:
	Color color;
	pair<int, int> start;
	pair<int, int> coords;
public:
	Robot();
	Robot(Color c, int x, int y);
	Robot(Robot const &r);

	Color getColor();
	pair<int, int> getStart();
	pair<int, int> getCoords();

	void setCoords(int x, int y);

	friend bool operator==(const Robot& r1, const Robot& r2);
	friend bool operator!=(const Robot& r1, const Robot& r2);
};

Robot::Robot() {
	color = B;
	start = coords = pair<int, int>(-1, -1);
}
Robot::Robot(Color c, int x, int y) {
	color = c;
	start = std::pair<int, int>(x, y);
	coords = std::pair<int, int>(x, y);
}
Robot::Robot(Robot const &r)
{
	this->color = r.color;
	this->coords = r.coords;
	this->start = r.start;
}


Color Robot::getColor() {
	return color;
}
pair<int, int> Robot::getStart() {
	return start;
}
pair<int, int> Robot::getCoords() {
	return coords;
}

void Robot::setCoords(int x, int y) {
	this->coords.first = x;
	this->coords.second = y;
}

bool operator==(const Robot& r1, const Robot& r2) {
	if (r1.color != r2.color) return false;
	if (r1.start != r2.start) return false;
	if (r1.coords != r2.coords) return false;

	return true;
}
bool operator!=(const Robot& r1, const Robot& r2) {
	return !(r1 == r2);
}