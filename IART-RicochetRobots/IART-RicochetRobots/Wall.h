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