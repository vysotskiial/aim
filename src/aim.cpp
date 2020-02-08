#include "GL/glut.h"
#include "aim_board.h"
#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

constexpr double delay = 1000.0 / 60.0;
constexpr int total_time = 30000;

void renderScene();
void mouse_func(int button, int state, int x, int y);
void draw_circle(int x, int y, double rad);
void timer_func(int id);

AimBoard my_board;
int time_left = 0;

void timer_func(int id)
{
	if (time_left <= 0) {
		time_left = 0;
		cout << "Score: " << my_board.score << endl;
		glutPostRedisplay();
		return;
	}

	my_board.step_into();
	time_left -= delay;

	glutPostRedisplay();
	glutTimerFunc(delay, timer_func, 0);
	return;
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!time_left)
	{
		glColor3f(1, 0, 0);
		draw_circle(ScrSize / 2, ScrSize / 2, BallMaxSize);
		glutSwapBuffers();
		return;
	}

	const vector<Ball> &balls = my_board.get_balls();

	for (unsigned int i = 0; i < balls.size(); i++)
	{
		glColor3f(0, 0, 1);
		draw_circle(balls[i].get_x(), balls[i].get_y(), balls[i].get_size());
	}

	glutSwapBuffers();
	return;
}

void draw_circle(int x, int y, double rad)
{
	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * M_PI; i += M_PI / 20) //<-- Change this Value
		glVertex3f(x + cos(i) * rad, y + sin(i) * rad, 0.0);
	glEnd();
}

void mouse_func(int button, int state, int x, int y)
{
	if ((!time_left) && (pow(x - 400, 2) + pow(y - 400, 2) <= pow(BallMaxSize, 2)))
	{
		my_board.reset();
		time_left = total_time;
		glutTimerFunc(delay, timer_func, 0);
		return;
	}

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		my_board.react_to_mouse(x, y);
	}

	return;
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ScrSize, ScrSize);
	glutCreateWindow("Aim");
	glClearColor(0, 0, 0, 1.0);
	glOrtho(0, ScrSize, ScrSize, 0, -5.0, 5.0);

	glutMouseFunc(mouse_func);
	glutDisplayFunc(renderScene);
	glutTimerFunc(delay, timer_func, 0);

	glutMainLoop();
	return 0;
}

