#ifndef MAP_H
#define MAP_H

namespace doom_nukem {


class Map
{

public:
	Map();
	~Map();

	int width() { return _width; }
	int height() { return _height; }

	int** map() { return _map; }

private:

	int** _map;

	int _width;
	int _height;
		
};

}

#endif // !MAP_H


