#include <iostream>
#include <time.h>
#include "BallDefinition.h"
using namespace std;


enum STARS {Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Moon};
Ball *Balls[ARRAY_SIZE];

void initBalls() {
    // 定义星球，这些星球的数据是经过不同比例变化过的
    // 太阳
    Balls[Sun] = new Ball(0.8, 0, 0, sk*696300000, 0, 60, 0.5, NULL);
    // 水星
    Balls[Mercury] = new Ball(0.2, 0.2, 0.5, vk*4880000, dk*58000000, 87, SelfRotate, Balls[Sun]);
    // 金星
    Balls[Venus] = new Ball(1, 0.7, 0.5, vk * 12103600, dk * 108000000, 225, SelfRotate, Balls[Sun]);
    // 地球
    Balls[Earth] = new Ball(0, 0.7, 0.8, vk * 12756300, edk * 150000000, 365, SelfRotate, Balls[Sun]);
    // 月亮
    Balls[Moon] = new Ball(1, 1, 1, mrk * 3844010.0f , mk * 1734.0f, 30, SelfRotate, Balls[Earth]);
    // 火星
    Balls[Mars] = new Ball(1, 0, 0, vk * 6794000, KK * 228000000, 687, SelfRotate, Balls[Sun]);
    // 木星
    Balls[Jupiter] = new Ball(1, 1, 0.5, lsk * 142984000,  fk * 778000000, tk * 4328, SelfRotate, Balls[Sun]);
    // 土星
    Balls[Saturn] = new Ball(0.5, 1, 0.5, lsk * 120536000, fk * 1427000000, ttk * 10752, SelfRotate, Balls[Sun]);
    // 天王星
    Balls[Uranus] = new Ball(0.4, 0.4, 0.4, k * 51118000, hfk * 2870000000, tttk * 30664, SelfRotate, Balls[Sun]);
    // 海王星
    Balls[Neptune] = new Ball(0.5, 0.5, 1, k * 49532000, ffk * 4497000000, tttk * 60148, SelfRotate, Balls[Sun]);
}

emitter *e1;	//粒子发射器
particle* init_particle()
{
    float size_x = rand() % 100 * 0.4f;
    float size_y = rand() % 100 * 0.4f;
    float size_z = rand() % 100 * 0.4f;
    float speed_x = float(rand() % 100 - 4) / 40;
    float speed_y = float(rand() % 100 - 4) / 40;
    float speed_z = float(rand() % 100 - 4) / 40;
    float acc_x = 1.0 / 10000;
    float acc_y = 1.0 / 10000;
    float acc_z = 1.0 / 10000;
	unsigned char color[] = { 1.0f,1.0f,1.0f };
    particle* p = new particle(size_x, size_y, size_z,
                               speed_x, speed_y, speed_z,
                               acc_x, acc_y, acc_z,
                               rand() % 10000, rand() % 360, color,false);
    return p;
}

void initStars() {
    srand(unsigned(time(NULL)));
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glColor4f(1.0, 1.0, 1.0, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    e1 = new emitter(2000, ffk*5000000000, ffk*-5000000000,
                     ffk*3000000000, ffk*1000000000,
                     ffk*5000000000, ffk*-5000000000);
    e1->emit(init_particle);
}

// 初始视角（ 视点在(+z, -y)处 ）
#define REST (700000000 * KK)
#define REST_Z (REST)
#define REST_Y (-REST)

// lookAt参数
GLdouble eyeX = 0, eyeY = REST_Y, eyeZ = REST_Z;
GLdouble centerX = 0, centerY = 0, centerZ = 0;
GLdouble upX = 0, upY = 0, upZ = 1;
GLfloat	angle_Z;

void OnDraw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.7, .7, .7, .1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

	// 实际绘制
	Balls[0]->DrawLight();
	for (int i = 1; i < ARRAY_SIZE; i++) {
		Balls[i]->DrawBall(i);
	}
	//e1->update();
    glutSwapBuffers();
}

// 每次更新 看做过去了 1 天
#define TimePast 1
void OnUpdate(void) {
	// 实际更新
	for (int i = 0; i<ARRAY_SIZE; i++) {
		Balls[i]->Update(TimePast);
	}
	OnDraw();
}

// 每次按键移动的距离
#define OFFSET (20000000 * KK)

// 按键操作变化视角
// w(+y方向)   a(-x方向)   d(+x方向)   x(-y方向)   s(+z 方向)   S(-z 方向)   r(reset)
void keyboard (unsigned char key, int x, int y) {
    switch (key)   
	{
		glClearColor(.7, .7, .7, .1);
    case 'w': eyeY += OFFSET; break;
    case 's': eyeZ += OFFSET; break;
    case 'S': eyeZ -= OFFSET; break;
    case 'a': eyeX -= OFFSET; break;
    case 'd': eyeX += OFFSET; break;
    case 'x': eyeY -= OFFSET; break;
	case 'p': Sleep(3000);		break;
    case 'r':
        eyeX = 0; eyeY = REST_Y; eyeZ= REST_Z;
        centerX= 0; centerY= 0; centerZ= 0;
        upX= 0; upY= 0; upZ= 1;
        break;
    case 27: exit(0); break;
    default: break;
    }
}



int main(int argc, char*  argv[])
{
    initBalls();
    initStars();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA |  GLUT_DOUBLE);
    glutInitWindowPosition(150, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OurSolarSystem");
    glutDisplayFunc(&OnDraw);
    glutIdleFunc(&OnUpdate);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
