#ifndef WALL_H
#define WALL_H

#pragma once

enum Orientation { H, V };

class Wall {
private:
	Orientation orientation;
	pair<int, int> coords;
public:
	Wall(Orientation or , int x, int y);
	Wall(Wall const &w);

	Orientation getOrientation();
	pair<int, int> getCoords();
	friend bool operator==(const Wall& w1, const Wall& w2);
	friend bool operator!=(const Wall& w1, const Wall& w2);
};

Wall::Wall(Orientation or , int x, int y) {
	orientation = or ;
	coords = std::pair<int, int>(x, y);
}
Wall::Wall(Wall const &w) {
	orientation = w.orientation;
	coords = w.coords;
}

Orientation Wall::getOrientation() {
	return orientation;
}
pair<int, int> Wall::getCoords() {
	return coords;
}

bool operator==(const Wall& w1, const Wall& w2) {
	if (w1.orientation != w2.orientation) return false;
	if (w1.coords != w2.coords) return false;

	return true;
}
bool operator!=(const Wall& w1, const Wall& w2) {
	return !(w1 == w2);
}

#endif