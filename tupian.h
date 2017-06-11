#pragma once
#define BITMAP_ID 0x4D42
#define PI 3.1415926535
#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>	

//---------- �������ݽṹ
typedef struct {
	int width;				//������
	int height;				//����߶�
	unsigned int texID;		//������� ID
	unsigned char * data;	//ʵ����������
}texture;


static float year = 0, month = 0, day = 0, angle = 30;
static bool first = false;

texture *star[11];			//����ָ��
char *filename[11] = { "Data\\taiyang.bmp", "Data\\shuixing.bmp", "Data\\jinxing.bmp", "Data\\earth.bmp","Data\\mars.bmp",
	"Data\\muxing.bmp","Data\\tuxing.bmp","Data\\hwx.bmp", "Data\\twx.bmp", "Data\\yueqiu.bmp", "Data\\star.bmp" };
											//---------- ����λͼ��Ϊ��������
unsigned char * LoadBmpFile(char * filename, BITMAPINFOHEADER * bmpInfoHeader) {

	FILE * file;
	BITMAPFILEHEADER bmpFileHeader;
	unsigned char * image;
	unsigned int imageIdx = 0;
	unsigned char tempRGB;

	file = fopen(filename, "rb");
	if (file == NULL)
		return 0;

	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, file);			// ��ȡ BMP �ļ�ͷ

	if (bmpFileHeader.bfType != BITMAP_ID)							// ��֤�Ƿ���һ�� BMP �ļ�
	{
		fclose(file);
		return 0;
	}

	fread(bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);			// ��λͼ��Ϣͷ
	fseek(file, bmpFileHeader.bfOffBits, SEEK_SET);					// ���ļ�ָ���Ƶ�λͼ���ݵĿ�ʼ��
	image = (unsigned char *)malloc(bmpInfoHeader->biSizeImage);	// �����ڴ��λͼ����

	if (!image)
	{
		free(image);
		fclose(file);
		return 0;
	}

	fread(image, 1, bmpInfoHeader->biSizeImage, file);					// ��ȡλͼ����
	if (image == NULL)
	{
		fclose(file);
		return 0;
	}

	// ��ת R �� B ֵ�Եõ� RGB����Ϊλͼ��ɫ��ʽ�� BGR
	for (imageIdx = 0; imageIdx < bmpInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = image[imageIdx];
		image[imageIdx] = image[imageIdx + 2];
		image[imageIdx + 2] = tempRGB;
	}
	fclose(file);
	return image;

}

BOOL LoadAllTextures() {
	//sun = LoadTexFile("sun.bmp");
	BITMAPINFOHEADER texInfo;
	texture * thisTexture;
	int i;
	for (i = 0; i < 11; i++) {
		thisTexture = (texture *)malloc(sizeof(texture));
		if (thisTexture == NULL)
			return 0;
		thisTexture->data = LoadBmpFile(filename[i], &texInfo);	// �����������ݲ������Ч��
		if (thisTexture->data == NULL)
		{
			free(thisTexture);
			return 0;
		}
		thisTexture->width = texInfo.biWidth;				// ��������Ŀ�͸�
		thisTexture->height = texInfo.biHeight;
		glGenTextures(1, &thisTexture->texID);				// �������������
		star[i] = thisTexture;
		if (star == NULL)
			return FALSE;
		glBindTexture(GL_TEXTURE_2D, star[i]->texID);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, star[i]->width, star[i]->height, GL_RGB, GL_UNSIGNED_BYTE, star[i]->data);
	}
	return TRUE;
}