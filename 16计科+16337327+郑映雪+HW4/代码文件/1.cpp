#include <iostream>
#include <math.h>
#include <gl\freeglut.h>
#include <gl\GL.h>
#include <vector>
using namespace std;
vector<pair<GLfloat, GLfloat> > points;
bool line = false;
bool curve = false;
void drawline() {
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(2.0);
	for (int i = 0; i <= 2; i++) {
		glBegin(GL_LINES);
		glVertex2f(points[i].first, points[i].second);
		glVertex2f(points[i + 1].first, points[i + 1].second);
		glEnd();
	}
}
void drawcurve() {
	glColor3f(0.5f, 0.0f, 0.4f);
	glPointSize(2.0);
	for (GLfloat t = 0; t <= 1.0; t += 0.0001) {
		GLfloat x = points[0].first*pow(1.0f - t, 3) + 3 * points[1].first*t*pow(1.0f - t, 2) + 3 * points[2].first*t*t*(1.0f - t) + points[3].first*pow(t, 3);
		GLfloat y = points[0].second*pow(1.0f - t, 3) + 3 * points[1].second*t*pow(1.0f - t, 2) + 3 * points[2].second*t*t*(1.0f - t) + points[3].second*pow(t, 3);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
}
void Display() {
	glFlush();
}
void Mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN){
		if (points.size() < 4) {
			glBegin(GL_POINTS);  //��glbegin��glend���������߼����Ҫ������
			glVertex2i(x, 500-y);
			glEnd();
			points.push_back(make_pair(GLfloat(x), GLfloat(500-y)));
		}
		else if (points.size() == 4) {
			if (!line) {
				drawline();
				line = true;
			}
			else if (line&& !curve) {
				drawcurve();
				curve = true;
			}
			else if (line&& curve) {
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(1.0f, 0, 0);
				glPointSize(5.0);
				line = false;
				curve = false;
				while (!points.empty()) {
					points.pop_back();
				}
			}
		}
		glFlush();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);//��ʼ��ʾģʽ�趨ΪRGBģʽ�Ĵ���
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("homework 4");
	glColor3f(1.0f, 0, 0);
	glPointSize(5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, 500, 0.0, 500);
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutMainLoop();
	return 0;
}