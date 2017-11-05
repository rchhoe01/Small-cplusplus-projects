#include <GL/glut0.h>  
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

GLdouble anglex = 3.14/2;
GLdouble angley = 3.14 / 2;
GLdouble anglez = 3.14 / 2;
GLdouble axisSize = 200;
GLdouble angle = 0;



const GLfloat vertices[8][3] = { { -50,-50,-50 },{ 50,-50,-50 },{ 50,50,-50 },{ -50,50,-50 },
{ -50,-50,50 },{ 50,-50,50 },{ 50,50,50 },{ -50,50,50 } };
const GLfloat colors[6][3] = { { 1.0,0,0 },{ 0,1.0,0 },{ 0,0,1.0 },{ 1.0,1.0,0 },{ 1.0,0,1.0 },{ 0,1.0,1.0 } };

std::vector<std::vector<GLint>> v;
std::vector<GLint> temp;

void polygon(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void cube() {
	polygon(4, 5, 6, 7);
	polygon(5, 1, 2, 6);
	polygon(3, 7, 4, 0);
	polygon(2, 3, 7, 6);
	polygon(1, 0, 4, 5);
	polygon(0, 1, 2, 3);

}
void grass(GLfloat size) {
	glColor3f(0,0.8, 0.2);
	const GLfloat floor[4][3] = { { -size, 0, size },{ size, 0, size },
	{ size, 0, -size },{ -size, 0 , -size } };
	glBegin(GL_POLYGON);
	for (int a = 0; a < 4; a++) {
		glVertex3fv(floor[a]);
	}
	glEnd();
}



void stump(GLfloat rad, GLfloat height) {
	const GLfloat fstump[8][3] = { { -rad,0,-rad },{ rad,0,-rad },{ rad,height,-rad },{ -rad,height,-rad },
	{ -rad,0,rad },{ rad,0,rad },{ rad,height,rad },{ -rad,height,rad } };
	
	int faces[6][4] = { {4,5,6,7}, {5,1,2,6}, {3,7,4,0}, {2,3,7,6}, {1,0,4,5}, {0,1,2,3} };
	glColor3f(0.7, 0.8, 0.2);
	for (int a = 0; a < 6; a++) {
		glBegin(GL_POLYGON);
		for (int b = 0; b < 4; b++) {
			glVertex3fv(fstump[faces[a][b]]);
		}
		glEnd();
	}	
}

void leaves(GLfloat rad, GLfloat height) {
	GLfloat leafmult = 2;
	GLfloat bottom = height / 3;
	const GLfloat leaves[5][3] = {
		{ -rad*leafmult, bottom, rad*leafmult },{ rad*leafmult, bottom, rad*leafmult },
		{ rad*leafmult, bottom, -rad*leafmult },{ -rad*leafmult, bottom , -rad*leafmult },
		{ 0,bottom+bottom,0 }
	};

	int leaffaces[4][3] = { { 0,1,4 },{ 2,3,4 },{ 0,3,4 },{ 1,2,4 } };
	
	glBegin(GL_POLYGON);
	for (int b = 0; b < 4; b++)
	{
		glVertex3fv(leaves[b]);
	}
	glEnd();
	for (int a = 0; a < 4; a++) {
		glBegin(GL_POLYGON);
		for (int b = 0; b < 3; b++)
		{
			glVertex3fv(leaves[leaffaces[a][b]]);
		}
		glEnd();
	}
}

void tree(GLfloat rad, GLfloat height) {
	stump(rad, height);
	int increment = 0;
	GLfloat intensity = 0.5;
	for (int a = 0; a < 3; a++) {
		glColor3f(0.0, intensity, 0.1);
		leaves(rad, height + increment);
		increment = increment + (height/2);
		intensity = intensity + 0.1;
	}
}

void createTrees(int amount) {
	for (int a = 0; a < amount; a++) {
		int r1 = rand() % 4 + 3;
		int r2 = rand() % 59 + 25;
		int r3 = rand() % 400 - 200;
		int r4 = rand() % 400 - 200;
		int r5 = rand() % 360;
		temp.push_back(r1);
		temp.push_back(r2);
		temp.push_back(r3);
		temp.push_back(r4);
		temp.push_back(r5);
		v.push_back(temp);
		temp.clear();
	}
}

void axis() {
	//x
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(axisSize, 0.0, 0);
	glEnd();
	//y
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0);
	glVertex3f(0.0, axisSize, 0);
	glEnd();
	//z
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0);
	glVertex3f(0.0, 0.0, axisSize);
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(250.0*cos(anglex), 250.0*sin(angley), 250.0*sin(anglez), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	
	glRotatef(angle, 0 , 1 , 0);
	glTranslatef(150.0, 150.0, 0.0);
	glutWireSphere(25, 25, 25);
	glPopMatrix();

	axis();
	grass(2000);
	for (int a = 0; a < v.size(); a++) {
		glPushMatrix();
		glTranslatef(v[a][2], 0, v[a][3]);
		glRotatef(v[a][4], 0, 1, 0);
		tree(v[a][0],v[a][1]);
		glPopMatrix();
	}
	
	

	glutSwapBuffers();
}
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 100, 600);

	glEnable(GL_DEPTH_TEST);
	createTrees(100);
	
}

void mySpecials(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		anglex= anglex - 0.1;
		anglez = anglez - 0.1;

		glutPostRedisplay();

	}
	else if (key == GLUT_KEY_RIGHT) {
		anglex= anglex + 0.1;
		anglez = anglez + 0.1;

		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_UP) {
		angley = angley + 0.1;

		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_DOWN) {
		angley = angley - 0.1;

		glutPostRedisplay();
	}
}

void myKeyboard(unsigned char key, int x, int y) {
	if (key == 'r') {
		v.clear();
		createTrees(100);
		glutPostRedisplay();
	}
}
void myEvent(int) {
	angle += 0.25;
	glutPostRedisplay();
	glutTimerFunc(30, myEvent, 0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(150, 100);
	glutCreateWindow("OpenGL Demo");
	glutSpecialFunc(mySpecials);
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(display);
	glutTimerFunc(0, myEvent, 0);
	init();
	glutMainLoop();
}
