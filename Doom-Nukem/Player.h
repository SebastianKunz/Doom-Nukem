#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>

namespace doom_nukem
{


class Player
{
public:
	Player();
	~Player();

	/*
		TODO: Should the world map really be passed every time, or keept as a reference?
	*/

	void	moveRight(int **worldMap);

	void	moveLeft(int **worldMap);

	void	moveForwards(int **worldMap);

	void	moveBackwards(int **worldMap);

	void	rotateRight();

	void	rotateLeft();
	
	float	posX();
	float	posY();
	
	float	dirX();
	float	dirY();

	void	setMoveSpeed(float moveSpeed);
	float	moveSpeed();

	float	rotSpeed();
	void	setRotSpeed(float rotSpeed);

	float	planeX();
	float	planeY();

private:
	
	// player pos
	float _posX = 22;
	float _posY = 12;

	// player direction
	float _dirX = -1.0f;
	float _dirY = 0.0f;

	float _moveSpeed = 0.01f;
	float _rotSpeed = 0.02f;

	float _planeX = 0.0f;
	float _planeY = 0.66f;
};

}
#endif // !PLAYER_H
