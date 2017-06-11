#include "particle.h"

#ifndef BALLDEFINITION_H_INCLUDED
#define BALLDEFINITION_H_INCLUDED
#define sk (.07 * KK)
// 对太阳系星球的参数进行调整用的宏
#define KK .00001
#define sk (.07 * KK)
#define k (.5 * KK)
#define vk (1.5 * KK)
#define fk (.5 * KK)
#define hfk (.4 * KK)
#define ffk (.3 * KK)
#define dk (1.07 * KK)
#define edk (1.12 * KK)
#define lsk (.3 * KK)
#define mk (15000 * KK)
#define mrk (1.6 * KK)
#define tk .3
#define ttk .2
#define tttk .1

// 自转速度（都定义为定值）
#define SelfRotate 1.5
#define ARRAY_SIZE 10
#define WIDTH 900
#define HEIGHT 1600

class Ball {
public:
	float color[4];
	float radius;
	float selfSpeed;
	float speed;
	float distance;
	Ball *ParentBall;
	Ball(float color1, float color2, float color3, float radius, float distance, float speed, float selfSpeed,  Ball *ParentBall);
	void DrawBall(int);
	void Update(long TimeSpan);
	void DrawLight();
protected:
    float AlphaSelf, Alpha;
};

#endif
