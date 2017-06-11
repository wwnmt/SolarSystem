#include"particle.h"
#define PI 3.1415926535

void particle::draw()
{
    const GLfloat x1 = -0.4, x2 = 0.4;
    const GLfloat y1 = -0.4, y2 = 0.4;
    const GLfloat point[4][2] = { { x1,y1 },{ x2,y1 },{ x2,y2 },{ x1,y2 } };
	const GLfloat R = 0.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++) {
       glVertex2fv(point[i]);
    }
    glEnd();
}

void particle::show() {
    if (life > 0 || is_forever) {
        if (has_tex) {
            glDepthMask(GL_FALSE);
            glPushMatrix();
            glTranslatef(x, y, 0);
            glRotatef(angle, 0, 0, 1);
            glScalef(size_x, size_y, size_z);
            glPopMatrix();
			z += speed_z;
            y += speed_y;
            x += speed_x;
			speed_z += acc_z;
            speed_y += acc_y;
            speed_x += acc_x;
            if (!is_forever)life -= 0.2f;
            glDepthMask(GL_TRUE);
        }
        else {
            glPushMatrix();
            glColor3f(color[0], color[1], color[2]);
            glTranslatef(x, y, 0);
            glRotatef(angle, 0, 0, 1);
            glScalef(size_x, size_y, size_z);
            draw();
            glPopMatrix();
			z += speed_z;
            y += speed_y;
            x += speed_x;
			speed_z += acc_z;
            speed_y += acc_y;
            speed_x += acc_x;
            if (!is_forever)life -= 0.2f;
            glColor3f(0, 0, 0);
        }
    }
}
particle::particle() {}

particle::particle(float _size_x, float _size_y, float _size_z,
	float _speed_x, float _speed_y, float _speed_z,
	float _acc_x, float _acc_y, float _acc_z,
	float _life, float _angle, unsigned int _texture, bool _is_forever) {
	size_x = _size_x;
	size_y = _size_y;
	size_z = _size_z;
	speed_x = _speed_x;
	speed_y = _speed_y;
	speed_z = _speed_z;
	acc_x = _acc_x;
	acc_y = _acc_y;
	acc_z = _acc_z;
	life = _life;
	texture = _texture;
	angle = _angle;
	has_tex = true;
	is_forever = _is_forever;
}

particle::particle(float _size_x, float _size_y, float _size_z,
    float _speed_x, float _speed_y, float _speed_z,
    float _acc_x, float _acc_y, float _acc_z,
    float _life, float _angle, unsigned char* _color, bool _is_forever) {
    size_x = _size_x;
    size_y = _size_y;
    size_z = _size_z;
    speed_x = _speed_x;
    speed_y = _speed_y;
    speed_z = _speed_z;
    acc_x = _acc_x;
    acc_y = _acc_y;
    acc_z = _acc_z;
    life = _life;
    if (_is_forever)_life = 1;
    color[0] = *_color;
    color[1] = *(_color + 1);
    color[2] = *(_color + 2);
    angle = _angle;
    has_tex = false;
    is_forever = _is_forever;
}

void emitter::emit(particle* (init)()) {
    for (int i = 0; i < speed; i++) {
        f = init;
        p[i] = init();
        int place = rand() % speed;
        p[i]->x = 1.0f*place / speed*(x2 - x1) + x1;
        p[i]->y = 1.0f*place / speed*(y2 - y1) + y1;
        p[i]->z = 1.0f*place / speed*(z2 - z1) + z1;
    }
}

void emitter::update() {
    int n = 50;
    for(int j = 0; j < n; j++)
		for (int i = 0; i < speed; i++) {
			p[i]->show();
			if (p[i]->life < 0) {
				delete p[i];
				p[i] = f();
				int place = rand() % speed;
				p[i]->x = (1.0f*place / speed*(x2 - x1) + x1);// *cos(2 * PI * i / n);
				p[i]->y = (1.0f*place / speed*(y2 - y1) + y1);// *sin(2 * PI * i / n);
				p[i]->z = 1.0f*place / speed*(z2 - z1) + z1;
			}
		}
}

emitter::emitter(int _speed,
    float _x1, float _x2,
    float _y1, float _y2,
    float _z1, float _z2) {
    speed = _speed;
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
    z1 = _z1;
    z2 = _z2;
    p = new particle*[speed];
}
