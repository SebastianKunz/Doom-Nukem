#include "RaycastingEngine.h"

namespace doom_nukem
{


RaycastingEngine::RaycastingEngine()
{
}

RaycastingEngine::~RaycastingEngine()
{
}

float RaycastingEngine::calculatePerpWallDist(int x, float playerPosX,
    float playerPosY, float rayDirX, float rayDirY, int** map,
    int *side, int *mapX, int *mapY)
{
    *mapX = playerPosX;
    *mapY = playerPosY;

    double posX = playerPosX;
    double posY = playerPosY;

     //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : std::abs((1 / rayDirX)));
    double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : std::abs(1 / rayDirY));
    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    int hit = 0; //was there a wall hit?

    //calculate step and initial sideDist
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - *mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (*mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - *mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (*mapY + 1.0 - posY) * deltaDistY;
    }


    //perform DDA (Digital Differential Analysis)
    while (hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            *mapX += stepX;
            *side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            *mapY += stepY;
            *side = 1;
        }
        //Check if ray has hit a wall
        if (map[*mapX][*mapY] > 0) hit = 1;
    }

    //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    if (*side == 0)
        perpWallDist = (*mapX - posX + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (*mapY - posY + (1 - stepY) / 2) / rayDirY;

    return perpWallDist;
}
}

