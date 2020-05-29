#include "Cubic.h"
#include "Cube.h"
#include <time.h>
#include <stdlib.h>

#define TIMER 30
// координаты источника света
GLfloat lightPos[] = { 0, 100, 200, 0 };
// проекции угла поворота на оси
GLfloat xRot = 24, yRot = 34, zRot = 0;
// отдаление
GLfloat translateZ = -35.0;
// кубик-рубик
Cube cube;
Cubic myCube;
// флаг того, крутится куб сам, или нет (будет переключаться правой кнопкой мыши)
int timerOn = 0;
int solvingOn = 0;
const int angle = 30;

void list()
{
	std::cout << "F1 - initial state" << std::endl;
	std::cout << "L - load state from a file cubic.in.txt" << std::endl;
	std::cout << "S - save state to a file cubic.out.txt" << std::endl;
	std::cout << "P - print state to console" << std::endl;
	std::cout << "HOME - increase a scale of the cube" << std::endl;
	std::cout << "END - decrease a scale of the cube" << std::endl;
	std::cout << "ARROWS - change camera view" << std::endl;
	std::cout << "W - change direction of rotation (clockwise or not)" << std::endl;
	std::cout << "0 - rotate YELLOW side" << std::endl;
	std::cout << "1 - rotate WHITE side" << std::endl;
	std::cout << "2 - rotate BLUE side" << std::endl;
	std::cout << "3 - rotate GREEN side" << std::endl;
	std::cout << "4 - rotate RED side" << std::endl;
	std::cout << "5 - rotate ORANGE side" << std::endl;
	std::cout << "SPACE - find solution" << std::endl;
	std::cout << "RIGHT MOUSE - random scramle of the cube" << std::endl;
}

void display()
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glTranslatef(0, 0, translateZ);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
	cube.draw();
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(60, fAspect, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// инициализируем случайные числа
	srand((unsigned int) time(0));

	// освещение
	float mat_specular[] = { 0.3f, 0.3f, 0.3f, 0 };
	float diffuseLight[] = { 0.2f, 0.2f, 0.2f, 1 };
	float ambientLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void specialKeys(int key, int, int)
{
	// клавиши влево/вправо вращают по Y
	// клавиши вверх/вниз вращают по X
	// F1 - возвращает в начальное положение
	if (key == GLUT_KEY_DOWN)
	{
		xRot += 5;
		if (xRot >= 360)
			xRot -= 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_UP)
	{
		xRot -= 5;
		if (xRot < 0)
			xRot += 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_RIGHT)
	{
		yRot += 5;
		if (yRot >= 360)
			yRot -= 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_LEFT)
	{
		yRot -= 5;
		if (yRot < 0)
			yRot += 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_HOME)
	{
		translateZ += 5;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_END)
	{
		translateZ -= 5;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_F1)
	{
		cube.clear();
		myCube = Cubic();
		glutPostRedisplay();
	}
}

void keys(unsigned char key, int, int)
{
	if (cube.current == -1 && key == 'h' || key == 'H') {
		list();
	} else
	if (cube.current == -1 && key == 'l' || key == 'L') {
		try {
			cube.cubic.load();
		}
		catch (int a) {
			cube.clear();
			display();
			std::cerr << "Bad cubic: " << a << std::endl;
			return;
		}

		auto v(cube.cubic.moveList);
		auto u(cube.cubic.signList);
		std::reverse(v.begin(), v.end());
		std::reverse(u.begin(), u.end());

		cube.clear();

		while (v.size() > 0) {
			int move = v.front();
			int sign = u.front();
			if (sign == 3) {
				v.erase(v.begin());
				u.erase(u.begin());
				cube.Rotate(move, 90, true);
			} else
			if (sign == 1) {
				v.erase(v.begin());
				u.erase(u.begin());
				cube.Rotate(move, 90, false);
			} else {
				sign--;
				u.at(0) = sign;
				cube.Rotate(move, 90, false);
			}

			display();
		}
	} else
	if (cube.current == -1 && key == 's' || key == 'S') {
		cube.cubic.output(true);
	} else
	if (cube.current == -1 && key == 'p' || key == 'P') {
		cube.cubic.output(false);
	} else
	if (cube.current == -1 && key == 'w' || key == 'W') {
		cube.clockwise = !cube.clockwise;
	} else
	if (cube.current == -1 && key == ' ') {
		cube.Solve();
		solvingOn = 1;
	} else
	if (cube.current == -1 && key >= '0' && key < '6')
	{
		// если нажали клавишу от 0 до 5 - начинаем поворот на angle градусов
		cube.Rotate(key - '0', angle, cube.clockwise);
		display();
	}
}

void mouse(int key, int state, int, int)
{
	if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// переключаем флаг
		timerOn = 1 - timerOn;
	}
}

void timer(int)
{
	glutTimerFunc(TIMER, timer, 0);
	if (timerOn || solvingOn)
	{
		// если включен автоматический поворот, и смотрим
		// если сейчас никакая грань не крутится, то начинаем крутить случайную,
		// иначе крутим текущую
		if (cube.current == -1 && solvingOn) {
			auto v = cube.cubic.moveList;
			auto u = cube.cubic.signList;
			if (v.size() > 0) {
				int move = v.front();
				int sign = u.front();
				if (sign == 3) {
					v.erase(v.begin());
					u.erase(u.begin());
					cube.Rotate(move, angle, false);
				} else
				if (sign == 1) {
					v.erase(v.begin());
					u.erase(u.begin());
					cube.Rotate(move, angle, true);
				} else {
					sign--;
					u.at(0) = sign;
					cube.Rotate(move, angle, true);
				}
				
				display();
				cube.cubic.moveList = v;
				cube.cubic.signList = u;
			}
			else {
				solvingOn = 0;
				cube.Done();
			}
		}
		else
			if (cube.current == -1)
				keys(rand() % 6 + '0', 0, 0);
			else
				cube.Rotate(cube.current, angle, cube.clockwise);
	}
	else
	{
		if (cube.current != -1)
			cube.Rotate(cube.current, angle, cube.clockwise);
	}
	display();
}

int main(int argc, char** argv)
{
	std::cout << "Press a key H to list commands" << std::endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(1, 1);
	glutCreateWindow("Cubic Rubik 2.0");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glutTimerFunc(TIMER, timer, 0);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}
