#ifndef PLAYER_H

#include <cmath>

class Player
{
public:
	Player();
	~Player();

	void	moveRight(int **worldMap);

	void	moveLeft(int **worldMap);

	void	moveForwards(int **worldMap);

	void	moveBackwards(int **worldMap);

	void	rotateRight(int **worldMap);

	void	rotateLeft(int **worldMap);
	
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

	float _moveSpeed = 5.0f;
	float _rotSpeed = 3.0f;

	float _planeX = 0.0f;
	float _planeY = 0.66f;
};

#endif // !PLAYER_H
