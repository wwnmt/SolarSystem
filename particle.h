#pragma once
#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED
#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/GLAUX.H>
#include <math.h>
#include<stdlib.h>

class particle {
    bool is_forever;//����
    bool has_tex;//�������ɫ
	unsigned int texture;//����
    float x, y, z;//λ��
    float size_x;//��С
    float size_y;
    float size_z;
    float speed_x;//�ٶ�
    float speed_y;
    float speed_z;
    float acc_x;//���ٶ�
    float acc_y;
    float acc_z;
    float life;//����
    float angle;//�Ƕ�
    unsigned char color[3];//��ɫ
    friend class emitter;
	void draw(GLuint texture);//�������ӣ�����
    void draw();//�������ӣ���ɫ��
    void show();
public:
    particle();
	particle(float _size_x, float _size_y, float _size_z,
		float _speed_x, float _speed_y, float _speed_z,
		float _acc_x, float _acc_y, float _acc_z,
		float _life, float _angle, unsigned int _texture, bool _is_forever);
    particle(float _size_x, float _size_y, float _size_z,
        float _speed_x, float _speed_y, float _speed_z,
        float _acc_x, float _acc_y, float _acc_z,
        float _life, float _angle, unsigned char* _color, bool _is_forever);
};

class emitter {
    float x1, y1, x2, y2, z1, z2; //������λ��
    int speed;//��������
    particle **p;//��������
    particle* (*f)(); //��ʼ�����ӵĺ���ָ��
public:
    void emit(particle* (init)());
    void update();
    emitter(int _speed,
            float _x1, float _x2,
            float _y1, float _y2,
            float _z1, float _z2);
};



#endif // PARTICLE_H_INCLUDED
