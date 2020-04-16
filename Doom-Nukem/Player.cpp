#include "Player.hpp"

Player::Player()
{
}

Player::~Player()
{
}

void Player::moveRight(int **worldMap)
{
}

void Player::moveLeft(int **worldMap)
{
}

void Player::moveForwards(int **worldMap)
{
	if (worldMap[int(_posX + _dirX * _moveSpeed)][int(_posY)] == false)
		_posX += _dirX * _moveSpeed;
	if (worldMap[int(_posX)][int(_posY + _dirY * _moveSpeed)] == false)
		_posY += _dirY * _moveSpeed;
}

void Player::moveBackwards(int **worldMap)
{
	if (worldMap[int(_posX - _dirX * _moveSpeed)][int(_posY)] == false)
		_posX -= _dirX * _moveSpeed;
	if (worldMap[int(_posX)][int(_posY - _dirY * _moveSpeed)] == false)
		_posY -= _dirY * _moveSpeed;
}

void Player::rotateRight(int **worldMap)
{
	float oldDirX = _dirX;
	_dirX = _dirX * cos(-_rotSpeed) - _dirY * sin(-_rotSpeed);
	_dirY = oldDirX * sin(-_rotSpeed) + _dirY * cos(-_rotSpeed);
	float oldPlaneX = _planeX;
	_planeX = _planeX * cos(-_rotSpeed) - _planeY * sin(-_rotSpeed);
	_planeY = oldPlaneX * sin(-_rotSpeed) + _planeY * cos(-_rotSpeed);
}

void Player::rotateLeft(int **worldMap)
{
	float oldDirX = _dirX;
	_dirX = _dirX * cos(_rotSpeed) - _dirY * sin(_rotSpeed);
	_dirY = oldDirX * sin(_rotSpeed) + _dirY * cos(_rotSpeed);
	float oldPlaneX = _planeX;
	_planeX = _planeX * cos(_rotSpeed) - _planeY * sin(_rotSpeed);
	_planeY = oldPlaneX * sin(_rotSpeed) + _planeY * cos(_rotSpeed);
}

float Player::posX()
{
	return _posX;
}

float Player::posY()
{
	return _posY;
}

float Player::dirX()
{
	return _dirX;
}

float Player::dirY()
{
	return _dirY;
}

void Player::setMoveSpeed(float moveSpeed)
{
	_moveSpeed = moveSpeed;
}

float Player::moveSpeed()
{
	return _moveSpeed;
}

float Player::rotSpeed()
{
	return _rotSpeed;
}

void Player::setRotSpeed(float rotSpeed)
{
	_rotSpeed = rotSpeed;
}

float Player::planeX()
{
	return _planeX;
}

float Player::planeY()
{
	return _planeY;
}

