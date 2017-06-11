#pragma once
#define BITMAP_ID 0x4D42
#define PI 3.1415926535
#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>	

//---------- 纹理数据结构
typedef struct {
	int width;				//纹理宽度
	int height;				//纹理高度
	unsigned int texID;		//纹理对象 ID
	unsigned char * data;	//实际纹理数据
}texture;


static float year = 0, month = 0, day = 0, angle = 30;
static bool first = false;

texture *star[11];			//纹理指针
char *filename[11] = { "Data\\taiyang.bmp", "Data\\shuixing.bmp", "Data\\jinxing.bmp", "Data\\earth.bmp","Data\\mars.bmp",
	"Data\\muxing.bmp","Data\\tuxing.bmp","Data\\hwx.bmp", "Data\\twx.bmp", "Data\\yueqiu.bmp", "Data\\star.bmp" };
											//---------- 调入位图作为纹理数据
unsigned char * LoadBmpFile(char * filename, BITMAPINFOHEADER * bmpInfoHeader) {

	FILE * file;
	BITMAPFILEHEADER bmpFileHeader;
	unsigned char * image;
	unsigned int imageIdx = 0;
	unsigned char tempRGB;

	file = fopen(filename, "rb");
	if (file == NULL)
		return 0;

	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, file);			// 读取 BMP 文件头

	if (bmpFileHeader.bfType != BITMAP_ID)							// 验证是否是一个 BMP 文件
	{
		fclose(file);
		return 0;
	}

	fread(bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);			// 读位图信息头
	fseek(file, bmpFileHeader.bfOffBits, SEEK_SET);					// 将文件指针移到位图数据的开始处
	image = (unsigned char *)malloc(bmpInfoHeader->biSizeImage);	// 分配内存给位图数据

	if (!image)
	{
		free(image);
		fclose(file);
		return 0;
	}

	fread(image, 1, bmpInfoHeader->biSizeImage, file);					// 读取位图数据
	if (image == NULL)
	{
		fclose(file);
		return 0;
	}

	// 反转 R 和 B 值以得到 RGB，因为位图颜色格式是 BGR
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
		thisTexture->data = LoadBmpFile(filename[i], &texInfo);	// 调入纹理数据并检查有效性
		if (thisTexture->data == NULL)
		{
			free(thisTexture);
			return 0;
		}
		thisTexture->width = texInfo.biWidth;				// 设置纹理的宽和高
		thisTexture->height = texInfo.biHeight;
		glGenTextures(1, &thisTexture->texID);				// 生成纹理对象名
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