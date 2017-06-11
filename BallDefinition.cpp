#include "BallDefinition.h"
#include "tupian.h"
using namespace std;

void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks);

Ball::Ball(float color1, float color2, float color3, float radius, float distance, float speed, float selfSpeed,  Ball *ParentBall) {
    this->color[0] = color1;
    this->color[1] = color2;
    this->color[2] = color3;
    this->radius = radius;
    this->distance = distance;
    if(speed > 0)
        this->speed = 50.0f / speed;
    AlphaSelf = Alpha= 0;
    this->selfSpeed = selfSpeed;
    this->ParentBall = ParentBall;
}

// 对普通的球体进行移动和旋转
void Ball::DrawBall(int m) {

    int n = 1500;

    glPushMatrix();
    {
        //glDisable(GL_LIGHTING);

        // 公转
        if (ParentBall != 0 && ParentBall->distance > 0) {
            glRotatef(ParentBall->Alpha, 0, 0, 1);
            glTranslatef(ParentBall->distance, 0.0, 0.0);
            glBegin(GL_LINE_LOOP);
            for(int i=0; i<n; ++i)
                glVertex2f(distance * cos(2 * PI * i / n),
                    distance * sin(2 * PI * i / n));
            glEnd();
        } else {
            glBegin(GL_LINE_LOOP);
            for(int i=0; i<n; ++i)
                glVertex2f(distance * cos(2 * PI * i / n),
                    distance * sin(2 * PI * i / n));
            glEnd();
        }
        glRotatef(Alpha, 0, 0, 1);
        glTranslatef(distance, 0.0, 0.0);
        // 自转
        glRotatef(AlphaSelf, 0, 0, 1);
        // 绘图
		glBindTexture(GL_TEXTURE_2D, star[m]->texID);
		gltDrawSphere(radius, 40, 32);
		glEnable(GL_LIGHTING);
    }
    glPopMatrix();
}

void Ball::Update(long TimeSpan) {
    // TimeSpan 天
    Alpha += TimeSpan * speed;
    AlphaSelf += selfSpeed;
}

int count = 0;
// 对光源进行设置

void Ball::DrawLight() {	
	glEnable(GL_TEXTURE_2D);
	if (!count) {
		LoadAllTextures();
		count++;
	}
    GLfloat light0_position[] = {0.0f, 0.0f, 0.0f, 1.0f};   //位置
    GLfloat light0_ambient[]  = {1.0f, 1.0f, 1.0f, 1.0f};     //周围
    GLfloat light0_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};   //散射
    GLfloat light0_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};   //镜面反射

	GLfloat light1_diffuse[]= { 1.0f, .0f, .0f, 1.0f};
	GLfloat light1_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,light1_position);
	
	int n = 1440;
	
    glPushMatrix();
    {
        glDisable(GL_LIGHTING);
		/*GLfloat mat_ambient1[] = { 1,0,0,1 };
		GLfloat mat_emission[] = { 1,1,1,0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);*/
        // 自转
        glRotatef(AlphaSelf, 0, 0, 1);
        // 绘图
        //glColor3f(color[0], color[1], color[2]);
		
		glBindTexture(GL_TEXTURE_2D, star[0]->texID);
		gltDrawSphere(radius, 45, 36);			//绘制太阳
		
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
       //glEnable(GL_LIGHT1);
        glEnable(GL_DEPTH_TEST);

    }
    glPopMatrix();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
	GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat)iStacks;
	GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat)iSlices;
	GLfloat ds = 1.0f / (GLfloat)iSlices;
	GLfloat dt = 1.0f / (GLfloat)iStacks;
	GLfloat t = 1.0f;
	GLfloat s = 0.0f;
	GLint i, j;

	for (i = 0; i < iStacks; i++)
	{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));


		glBegin(GL_TRIANGLE_STRIP);
		s = 0.0f;
		for (j = 0; j <= iSlices; j++)
		{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));

			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;

			glTexCoord2f(s, t);
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);

			x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;
			glTexCoord2f(s, t - dt);
			s += ds;
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);
		}
		glEnd();

		t -= dt;
	}
}


