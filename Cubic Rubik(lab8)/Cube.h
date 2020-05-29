#pragma once
#include "Cubic.h"
#include "Small_Cube.h"
#include <iostream>

#define CUBE_SIZE 13
// обозначаем цвета:       (верх,      низ,   впереди,   сзади,    лево,      право)
unsigned int colors[9] = { 0xFFFFFF, 0xFFFF00, 0x000088, 0x008800, 0x880000, 0xff8800 };

class Cube
{
public:
	// 27 частей
	Small_Cube a[3][3][3];
	// храним угол поворота каждой грани
	int rotate[6];
	// размер кубика-рубика
	GLfloat size = CUBE_SIZE;
	// цвета граней
	unsigned int color[6];

	Cubic cubic;
	// храним номер грани, которая в данный момент поварачивается, или -1 если ничего не поварачивается
	int current = -1;
	int clockwise = true;

	Cube() {
		clear();
	}

	void clear()
	{
		GLfloat size = CUBE_SIZE;
		unsigned int* color = colors;

		cubic = Cubic();

		memset(rotate, 0, sizeof(rotate));
		this->size = size;
		current = -1;

		int i, j, k;
		for (i = 0; i < 6; i++)
			this->color[i] = color[i];

		// верх
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				a[i][j][2].setColor(0, color[0]);

		// низ
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				a[i][j][0].setColor(1, color[1]);

		// спереди
		for (k = 0; k < 3; k++)
			for (j = 0; j < 3; j++)
				a[j][0][k].setColor(2, color[2]);

		// сзади
		for (k = 0; k < 3; k++)
			for (j = 0; j < 3; j++)
				a[j][2][k].setColor(3, color[3]);

		// слева
		for (i = 0; i < 3; i++)
			for (k = 0; k < 3; k++)
				a[0][k][i].setColor(4, color[4]);

		// справа
		for (i = 0; i < 3; i++)
			for (k = 0; k < 3; k++)
				a[2][k][i].setColor(5, color[5]);

		// устанавливаем размеры мелких деталей
		// это будет треть всего размера, умноженная на коэффициент немного меньший еденицы
		// (чтобы детали не были слишком плотно)
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				for (k = 0; k < 3; k++)
					a[i][j][k].size = (size / 3.0f) * 0.95f;
	}

	void draw()
	{
		const GLfloat K = 0.65f;
		// рисуем корпус - это просто куб черного цвета, размер которого равен K*size
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(((1.0f - K) / 2.0f) * size + K * size / 2.0f, ((1.0f - K) / 2.0f) * size + K * size / 2.0f, ((1.0f - K) / 2.0f) * size + K * size / 2.0f);
		glutSolidCube((GLdouble) size * (GLdouble) K);
		glPopMatrix();

		// ok[i][j][k] показывает, находится ли в состоянии покоя деталь с координатами (i, j, k)
		memset(ok, true, sizeof(ok));
		if (current != -1)
		{
			glPushMatrix();
			int i, j, k;

			if (current == 0 || current == 1)
			{
				// 0 <= current <= 1 показывает, что сейчас крутится грань на плоскости X0Y
				// current = 0 - нижняя часть
				// current = 1 - верхняя часть
				k = (current & 1) * 2;
				// следовательно ok слоя  k  устанавливаем в false
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						ok[i][j][k] = false;

				// теперь нужно покрутить грань под номером current на угол rotate[current]
				// относительно центра этой грани
				// для этого сдвинемся к центру, покрутим, сдвинемся обратно
				glTranslated(size / 2, size / 2, 0);   // сдвигаемся к центру
				glRotatef((GLfloat) rotate[current], 0, 0, 1);   // крутим
				glTranslated(-size / 2, -size / 2, 0); // сдвигаемся обратно
				// рисуем
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			}
			// аналагично с остальными четырмя гранями
			else if (current == 2 || current == 3)
			{
				j = (current & 1) * 2;
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						ok[i][j][k] = false;

				glTranslated(size / 2, 0, size / 2);
				glRotatef((GLfloat) rotate[current], 0, 1, 0);
				glTranslated(-size / 2, 0, -size / 2);
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						a[i][j][k].draw(size / 3.0f * i, size / 3.0f * j, size / 3.0f * k);
			}
			else if (current == 4 || current == 5)
			{
				i = (current & 1) * 2;
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						ok[i][j][k] = false;

				glTranslated(0, size / 2, size / 2);
				glRotatef((GLfloat) rotate[current], 1, 0, 0);
				glTranslated(0, -size / 2, -size / 2);
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			}
			glPopMatrix();
		}

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					if (ok[i][j][k])
						// теперь рисуем те детали, которые не поварачивались выше,
						// они отмечены ok[i][j][k] = true
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
	}

public:
	void Done()
	{
		cubic = Cubic();
	}
	void Solve()
	{
		cubic.solve(true);
	}
	void rot90(int idx, int sign)
	{
		int i, j, k;
		// sign задаётся в зависимости он направления
		// sign = -1, sign = 1
		// если sign = -1, значит крутим 3 раза
		if (sign == -1)
			sign = 3;
		switch (idx)
		{
		case 0: cubic.B(4 - sign); break;
		case 1: cubic.F(sign); break;
		case 2: cubic.D(sign); break;
		case 3: cubic.U(4 - sign); break;
		case 4: cubic.L(4 - sign); break;
		case 5: cubic.R(sign); break;
		}
		while (sign--)
		{
			if (idx == 0 || idx == 1)
			{
				// низ/верх
				k = (idx & 1) * 2;
				// копируем повёрнутую на 90 градусов верхнюю/нижнюю грань
				// в массив tmp, затем грани присваиваем tmp
				// и не забываем повернуть каждую деталь этой грани
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						tmp[j][2 - i] = a[i][j][k];
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						tmp[i][j].rotateZ(), a[i][j][k] = tmp[i][j];
			}
			// аналогично с остальными четырмя гранями
			else if (idx == 2 || idx == 3)
			{
				// лево/право
				j = (idx & 1) * 2;
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						tmp[k][2 - i] = a[i][j][k];
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						tmp[i][k].rotateX(), a[i][j][k] = tmp[i][k];
			}
			else if (idx == 4 || idx == 5)
			{
				// впереди/сзади
				i = (idx & 1) * 2;
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						tmp[k][2 - j] = a[i][j][k];
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						tmp[j][k].rotateY(), a[i][j][k] = tmp[j][k];
			}
		}
	}

	// крутит грань под номером idx на угол angle (в градусах)
	void Rotate(int idx, int angle, bool _clockwise)
	{
		// мы пытаемся покрутить грань с номером idx
		// значит нужно проверить что другая грань уже не крутится
		if (current == -1 || current == idx)
		{
			// обновляем поворот
			if (((idx == 1 || idx == 3 || idx == 5) && _clockwise) || ((idx == 0 || idx == 2 || idx == 4) && !_clockwise))
				rotate[idx] -= angle;
			else
				rotate[idx] += angle;

			if (rotate[idx] % 90 != 0)
			{
				clockwise = _clockwise;
				current = idx;
			}
			else
			{
				if ((idx == 0 || idx == 3 || idx == 4) && _clockwise || (idx == 1 || idx == 2 || idx == 5) && !_clockwise)
					rot90(idx, -1);
				else
					rot90(idx, 1);

				rotate[idx] = 0;
				current = -1;
			}
		}
	}
private:
	bool ok[4][4][4];
	Small_Cube tmp[4][4];
};
