#include <iostream>
#include <gl\freeglut.h>
#include <cmath>
#include <string>
#include <OpenMesh\Core\IO\MeshIO.hh>
#include <OpenMesh\Core\Mesh\TriMesh_ArrayKernelT.hh>
using namespace std;
typedef OpenMesh::TriMesh_ArrayKernelT<> Mymesh;
int mouse = 0;
GLfloat Oldx = 0;
GLfloat Oldy = 0;
float x = 0, y = 0;
float ty = 0;
float scale = 1;
Mymesh mesh;
const string file1 = "cow.obj";
const string file2 = "cactus.ply";
const string file3 = "Armadillo.off";
int currentfile = 1;
GLuint showFaceList, showWireList;
int showstate = 1;
bool showface = true, showwire = false, showflatlines = false;
void initGL() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(2.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0); 
	showFaceList = glGenLists(1);
	showWireList = glGenLists(1);
	int temp = mesh.n_edges();
	glNewList(showWireList, GL_COMPILE);//列表中命令只是编译
	glDisable(GL_LIGHTING);
	glLineWidth(1.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	for (Mymesh::HalfedgeIter he_it = mesh.halfedges_begin(); he_it != mesh.halfedges_end(); ++he_it) {
		glVertex3fv(mesh.point(mesh.from_vertex_handle(*he_it)).data());
		glVertex3fv(mesh.point(mesh.to_vertex_handle(*he_it)).data());
	}
	glEnd();
	glEnable(GL_LIGHTING);
	glEndList();

	// new：平面绘制
	glNewList(showFaceList, GL_COMPILE);
	for (Mymesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
		glBegin(GL_TRIANGLES);//创建三角形绘制
		for (Mymesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
			glNormal3fv(mesh.normal(*fv_it).data());
			glVertex3fv(mesh.point(*fv_it).data());
		}
		glEnd();
	}
	glEndList();
}

void myReshape(GLint w, GLint h){//投影
	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w > h)
		glOrtho(-static_cast<GLdouble>(w) / h, static_cast<GLdouble>(w) / h, -1.0, 1.0, -100.0, 100.0);
	else
		glOrtho(-1.0, 1.0, -static_cast<GLdouble>(h) / w, static_cast<GLdouble>(h) / w, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void readfile(string file) {
	// 请求顶点法线
	mesh.request_vertex_normals();
	if (!mesh.has_vertex_normals()){
		cout << "not found" << endl;
		return;
	} 
	OpenMesh::IO::Options opt;
	if (!OpenMesh::IO::read_mesh(mesh, file, opt)){
		cout << "file not found" << file << endl;
		return;
	}
	else cout << "success" << file << endl;
	cout << endl; 
	if (!opt.check(OpenMesh::IO::Options::VertexNormal)){
		mesh.request_face_normals();
		mesh.update_normals();
		mesh.release_face_normals();
	}
}

void mySpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		cout <<  file1<< endl;
		readfile(file1);
		scale = 1.0;
		currentfile = 1;
		initGL();
		break;
	case GLUT_KEY_F2:
		cout << file2 << endl;
		readfile(file2);
		scale = 1.2;
		currentfile = 2;
		initGL();
		break;
	case GLUT_KEY_F3:
		cout <<  file3 <<  endl;
		readfile(file3);
		scale = 0.01;
		currentfile = 3;
		initGL();
		break;
	case GLUT_KEY_F12:
		if (showface == true) {
			showface = false;
			showwire = true;
			cout << "WireFrame" << endl;
		}
		else if (showwire == true){
			showwire = false;
			showflatlines = true;
			cout << "Flatlines" << endl;
		}
		else if (showflatlines == true) {
			showflatlines = false;
			showface = true;
			cout << "Flat" << endl;
		}
		break;
	case GLUT_KEY_UP:
		ty += 0.01;
		break;
	case GLUT_KEY_DOWN:
		ty -= 0.01;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouse = 1;
		Oldx = x;
		Oldy = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		mouse = 0;
	//滚轮
	if (state == GLUT_UP && button == 3) {
		if (currentfile == 3)
			scale -= 0.002;
		else
			scale -= 0.1;
	}
	if (state == GLUT_UP && button == 4) {
		if (currentfile == 3)
			scale += 0.002;
		else
			scale += 0.1;
	}
	glutPostRedisplay();
}

void onMouseMove(int x1, int y1) {
	if (mouse) {
		//x对应y是因为对应的是法向量
		y += x1 - Oldx;
		glutPostRedisplay();
		Oldx = x1;
		x += y1 - Oldy;
		glutPostRedisplay();
		Oldy = y1;
	}
}

void myDisplay()
{
	//要清除之前的深度缓存
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(x, 1.0f, 0.0f, 0.0f); // 旋转函数（角度，旋转的法向量）
	glRotatef(y, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, ty);
	glScalef(scale, scale, scale); // 缩放
	if (showface)
		glCallList(showFaceList);
	if (showflatlines) {
		glCallList(showFaceList);
		glCallList(showWireList);
	}
	if (showwire)
		glCallList(showWireList);
	glutSwapBuffers(); 
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // 双缓存
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Mesh Viewer");
	//一开始默认读取文件1
	readfile(file1);
	initGL();
	glutMouseFunc(myMouse);
	glutMotionFunc(onMouseMove); // 鼠标移动的时候的函数
	glutSpecialFunc(&mySpecial);
	glutReshapeFunc(&myReshape);
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}