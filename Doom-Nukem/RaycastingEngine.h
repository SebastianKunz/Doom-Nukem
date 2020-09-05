#ifndef RAYCASTING_ENGINE_H
#define RAYCASTING_ENGINE_H

#include <cmath>        // std::abs

namespace doom_nukem
{


class RaycastingEngine
{
public:
	RaycastingEngine();
	~RaycastingEngine();
	
	// Calculates perpendicular wall distance
	static float calculatePerpWallDist(int x, float playerPosX,
		float playerPosY, float rayDirX, float rayDirY, int** map,
		int *side, int *mapX, int *mapY);

private:

	//static void _calcInitalSideAndStepDist();

	//double _deltaDistX;
	//double _deltaDistY;

	//bool _side;

	//int _mapX;
	//int _mapY;

};
}

#endif // !RAYCASTING_ENGINE_H
