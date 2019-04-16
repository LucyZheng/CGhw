#include <gl\freeglut.h>  

static int x1 = 0 ,x2 = 0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0, 0.5, 0.0);//��ɫ
	//������ջ
	glPushMatrix();  
	glutWireSphere(1.5f, 50.0f, 30.0f);  //����̫��
	glRotatef((GLfloat)x1, 0.0f, 1.0f, 0.0f); 
	glTranslatef(2.0f, 0.0f, 0.0f);
	glRotatef((GLfloat)x2, 0.0f, 1.0f, 0.0f);  
	glColor3f(0.0, 0.5, 1.0);//��ɫ
	glutWireSphere(0.3f, 30.0f, 20.0f); //���Ƶ���
	glPopMatrix(); 
	glutSwapBuffers(); 
}


void reshape(int width, int height) {
	//�ӿ�����
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	//��������
	glLoadIdentity();
	//�۾������Ƕȣ���߱ȣ������桢Զ�������
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//�������
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void controller(unsigned char key,int x,int y) {
	switch (key) {
	//������ת����ת���Լ��Ƿ�رմ��ڣ�esc����
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