#pragma once
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

// класс частей кубика-рубика, большой кубик будет состоять из 27 маленьких.
const GLfloat vertex[6][5][3] = { { { 0, 0, 1 }, { 1, 1, 1 }, { 0, 1, 1 }, { 0, 0, 1 }, { 1, 0, 1 } },
	{ { 0, 0, -1 }, { 1, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 } },
	{ { 0, -1, 0 }, { 1, 0, 1 }, { 0, 0, 1 }, { 0, 0, 0 }, { 1, 0, 0 } },
	{ { 0, 1, 0 }, { 1, 1, 0 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 1, 1 } },
	{ { -1, 0, 0 }, { 0, 1, 1 }, { 0, 1, 0 }, { 0, 0, 0 }, { 0, 0, 1 } },
	{ { 1, 0, 0 }, { 1, 1, 0 }, { 1, 1, 1 }, { 1, 0, 1 }, { 1, 0, 0 } } };

class Small_Cube
{
public:
	// шесть граней куба - шесть цветов
	unsigned int color[6]; // (верх, низ, впереди, сзади, лево, право)
	// размер ребра
	GLfloat size;

	Small_Cube()
	{
		// по умолчанию черный цвет
		memset(color, 0, sizeof(color));
		size = 0.0;
	}

	// поворот на плоскости X0Y
	void rotateZ()
	{
		unsigned int tmp = color[5];
		color[5] = color[3];
		color[3] = color[4];
		color[4] = color[2];
		color[2] = tmp;
	}

	// поворот на плоскости X0Z
	void rotateY()
	{
		unsigned int tmp = color[2];
		color[2] = color[1];
		color[1] = color[3];
		color[3] = color[0];
		color[0] = tmp;
	}

	// поворот на плоскости Y0Z
	void rotateX()
	{
		unsigned int tmp = color[0];
		color[0] = color[4];
		color[4] = color[1];
		color[1] = color[5];
		color[5] = tmp;
	}

	void setColor(int i, int color)
	{
		this->color[i] = color;
	}

	unsigned char* at(int i)
	{
		// разбиваем color[i] на 3 составляющих
		// например для 0xFF0000 RGB(FF, 0, 00) - красный цвет;
		_color[0] = color[i] >> 16;
		_color[1] = color[i] >> 8;
		_color[2] = color[i];
		return _color;
	}

	// отрисовка куба: устанавливаем цвет и нормали
	void draw()
	{
		glPushMatrix();
		glBegin(GL_QUADS);
		for (int i = 0; i < 6; i++) {
			glColor3ubv(at(i));
			glNormal3f(vertex[i][0][0], vertex[i][0][1], vertex[i][0][2]);
			for(int j = 1; j < 5; j++)
				glVertex3f(vertex[i][j][0] * size, vertex[i][j][1] * size, vertex[i][j][2] * size);
		}
		glEnd();
		glPopMatrix();
	}

	// отрисовка куба со смещением (x, y, z)
	void draw(GLfloat x, GLfloat y, GLfloat z)
	{
		glPushMatrix();
		glTranslated(x, y, z);
		draw();
		glPopMatrix();
	}

private:
	unsigned char _color[4];
};
