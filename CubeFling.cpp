#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <typeinfo>
#include <GL/glut.h>
using namespace std;

#define MIN_X_VIEW -50
#define MAX_X_VIEW 50
#define MIN_Y_VIEW -50
#define MAX_Y_VIEW 50
#define MIN_Z_VIEW -50
#define MAX_Z_VIEW 50
#define MIN_X_SCREEN 0
#define MAX_X_SCREEN 500
#define MIN_Y_SCREEN 0
#define MAX_Y_SCREEN 500

GLenum mode = GL_POLYGON;
float RotationDegrees = 15.0;
float CurrentX = 0;
float CurrentY = 0;
float VelocityX = 0;
float VelocityY = 0;
float PreviousX = 0;
float PreviousY = 0;
float Bounce = -0.8;
float FloorHits = 0.00;
int sleep = 75;
bool DisplayCube = false;
bool MouseDown = false;
bool RecentXBounce = false;
bool RecentYBounce = false;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(MIN_X_VIEW, MAX_X_VIEW, MIN_Y_VIEW, MAX_Y_VIEW, MIN_Z_VIEW, MAX_Z_VIEW);
}

void cube(float midx, float midy, float midz, float size)
{
	// Define 8 vertices
	float ax = midx - size / 2;
	float ay = midy - size / 2;
	float az = midz + size / 2;
	float bx = midx + size / 2;
	float by = midy - size / 2;
	float bz = midz + size / 2;
	float cx = midx + size / 2;
	float cy = midy + size / 2;
	float cz = midz + size / 2;
	float dx = midx - size / 2;
	float dy = midy + size / 2;
	float dz = midz + size / 2;
	float ex = midx - size / 2;
	float ey = midy - size / 2;
	float ez = midz - size / 2;
	float fx = midx + size / 2;
	float fy = midy - size / 2;
	float fz = midz - size / 2;
	float gx = midx + size / 2;
	float gy = midy + size / 2;
	float gz = midz - size / 2;
	float hx = midx - size / 2;
	float hy = midy + size / 2;
	float hz = midz - size / 2;

	// Draw 6 faces
	glBegin(mode);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(ax, ay, az);
	glVertex3f(bx, by, bz);
	glVertex3f(cx, cy, cz);
	glVertex3f(dx, dy, dz);
	glEnd();

	glBegin(mode);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(ax, ay, az);
	glVertex3f(dx, dy, dz);
	glVertex3f(hx, hy, hz);
	glVertex3f(ex, ey, ez);
	glEnd();

	glBegin(mode);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(ax, ay, az);
	glVertex3f(ex, ey, ez);
	glVertex3f(fx, fy, fz);
	glVertex3f(bx, by, bz);
	glEnd();

	glBegin(mode);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(gx, gy, gz);
	glVertex3f(fx, fy, fz);
	glVertex3f(ex, ey, ez);
	glVertex3f(hx, hy, hz);
	glEnd();

	glBegin(mode);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(gx, gy, gz);
	glVertex3f(cx, cy, cz);
	glVertex3f(bx, by, bz);
	glVertex3f(fx, fy, fz);
	glEnd();

	glBegin(mode);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(gx, gy, gz);
	glVertex3f(hx, hy, hz);
	glVertex3f(dx, dy, dz);
	glVertex3f(cx, cy, cz);
	glEnd();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(CurrentX, CurrentY, 0.0);
	glRotatef(RotationDegrees, 0.0, 1.0, 1.0);
	glTranslatef(-CurrentX, -CurrentY, 0.0);
	if (DisplayCube)
	{
		cube(CurrentX, CurrentY, 0.0, (MAX_Y_VIEW + MAX_X_VIEW + MAX_Z_VIEW) / 15);
	}
	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	// Calculate scale factors
	float x_scale = (float)(MAX_X_VIEW - MIN_X_VIEW) / (float)(MAX_X_SCREEN - MIN_X_SCREEN);
	float y_scale = (float)(MIN_Y_VIEW - MAX_Y_VIEW) / (float)(MAX_Y_SCREEN - MIN_Y_SCREEN);
	//cout << button << " " << state << " " << x << " " << y << endl;

	if (state == GLUT_DOWN)
	{
		CurrentX = MIN_X_VIEW + (x - MIN_X_SCREEN) * x_scale;
		CurrentY = MAX_Y_VIEW + (y - MIN_Y_SCREEN) * y_scale;
		if (MouseDown == false)
		{
			MouseDown = true;
			VelocityX = 0;
			VelocityY = 0;
			PreviousX = 0;
			PreviousY = 0;
			FloorHits = 0.00;
		}
		PreviousX = CurrentX;
		PreviousY = CurrentY;
		DisplayCube = true;
	}

	else if (state == GLUT_UP)
	{
		MouseDown = false;
		CurrentX = MIN_X_VIEW + (x - MIN_X_SCREEN) * x_scale;
		CurrentY = MAX_Y_VIEW + (y - MIN_Y_SCREEN) * y_scale;
		VelocityX = PreviousX - CurrentX;
		VelocityY = PreviousY - CurrentY;
		DisplayCube = true;
		glutPostRedisplay();
	}
}

void motion(int x, int y)
{
	// Calculate scale factors
	float x_scale = (float)(MAX_X_VIEW - MIN_X_VIEW) / (float)(MAX_X_SCREEN - MIN_X_SCREEN);
	float y_scale = (float)(MIN_Y_VIEW - MAX_Y_VIEW) / (float)(MAX_Y_SCREEN - MIN_Y_SCREEN);
	//cout << x << " " << y << endl;

	CurrentX = MIN_X_VIEW + (x - MIN_X_SCREEN) * x_scale;
	CurrentY = MAX_Y_VIEW + (y - MIN_Y_SCREEN) * y_scale;
	DisplayCube = true;
	glutPostRedisplay();
}

void rotation(int value)
{
	if (MouseDown == false)
	{
		CurrentX += VelocityX;
		CurrentY += VelocityY;
		if (Bounce - FloorHits <= 0)
		{
			VelocityY -= 9.81;
		}
		else
		{
			VelocityY = 0;
		}
		if (CurrentX > MAX_X_VIEW - 10 && RecentXBounce == false)
		{
			VelocityX *= Bounce;
			RecentXBounce = true;
		}
		if (CurrentX < MIN_X_VIEW + 10 && RecentXBounce == false)
		{
			VelocityX *= Bounce;
			RecentXBounce = true;
		}
		if (CurrentY > MAX_Y_VIEW && RecentYBounce == false)
		{
			VelocityY *= Bounce;
			RecentYBounce = true;
		}
		if (CurrentY <= MIN_Y_VIEW)
		{
			
			if (Bounce + FloorHits <= 0)
			{
				VelocityY *= (Bounce + FloorHits);
			}
			else
			{
				VelocityY = 0;
			}
			RecentYBounce = true;
			FloorHits += 0.01;
			
		}
		if (CurrentX < MAX_X_VIEW - 30 && CurrentX > MIN_X_VIEW + 30)
		{
			RecentXBounce = false;
		}
		if (CurrentY < MAX_Y_VIEW - 20 && CurrentY > MIN_Y_VIEW + 20)
		{
			RecentYBounce = false;
		}
		RotationDegrees += 15 % 360;
		
	}
	glutPostRedisplay();
	
	glutTimerFunc(sleep, rotation, 0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(MAX_Y_SCREEN, MAX_X_SCREEN);
	glutInitWindowPosition(MAX_Y_SCREEN / 2, MAX_X_SCREEN / 2);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("Cube");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(sleep, rotation, 0);
	init();
	printf("Mouse operations:\n");
	printf("   'Mouse button down' - Create New Cube\n");
	printf("   'Mouse motion while holding button' - Move Created Cube\n");
	printf("   'Mouse button up' - Fling Created Cube\n");
	glutMainLoop();
	return 0;
}
