#include <gl\freeglut.h>  

static int x1 = 0 ,x2 = 0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0, 0.5, 0.0);//橙色
	//矩阵入栈
	glPushMatrix();  
	glutWireSphere(1.5f, 50.0f, 30.0f);  //绘制太阳
	glRotatef((GLfloat)x1, 0.0f, 1.0f, 0.0f); 
	glTranslatef(2.0f, 0.0f, 0.0f);
	glRotatef((GLfloat)x2, 0.0f, 1.0f, 0.0f);  
	glColor3f(0.0, 0.5, 1.0);//蓝色
	glutWireSphere(0.3f, 30.0f, 20.0f); //绘制地球
	glPopMatrix(); 
	glutSwapBuffers(); 
}


void reshape(int width, int height) {
	//视口设置
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	//矩阵重置
	glLoadIdentity();
	//眼睛睁开角度，宽高比，近截面、远截面距离
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//相机设置
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void controller(unsigned char key,int x,int y) {
	switch (key) {
	//控制自转、公转，以及是否关闭窗口（esc键）
	case int('d') :
		x2 = (x2 + 10) % 360;
		glutPostRedisplay();
		break;
	case int('D') :
		x2 = (x2 - 10) % 360;
		glutPostRedisplay();
		break;
	case int('y') :
		x1 = (x1 + 5) % 360;
		glutPostRedisplay();
		break;
	case int('Y') :
		x1 = (x1 - 5) % 360;
		glutPostRedisplay();
		break;	
	case (27):
		exit(0);
	default:
		break;

	}
}

int main(int argc, const char * argv[]) {

	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("homework 3");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_FLAT);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(controller);

	glutMainLoop();
	return 0;
}