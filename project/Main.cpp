#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"	
#include <iostream>
#include <string>
#include <ctime>
#include <xsmf_control.h>

using namespace std;
#pragma region Intialisation

GLfloat angle1 = 45.0f;
int refreshmill = 1;

GLfloat angle2 = 25.0f;
int refreshmill2 = 1;
float speed = 1;
float xpos, ypos, direction;
double pi = 3.14;
double radToDer = 180 / pi;
double degToRad = pi / 180;
static double xLoc = 0;
double yLoc = 0;
float x = 2;
float y = 2;
float angle = 0;
;
float x4 = 20,
y4 = 20;
int fired = false;
int lol;
float bulletX, bulletY;
float bulletspeed = 0.5;
float bulletspeed2 = 0.2;
float bulletRadius = 1.0f;
float dirx;
bool menuTF = false;

#pragma region MyRegion

bool TF = true;
bool TF2 = true;
bool TF3 = true;
bool TF4 = true;

int appear = 1;
int appear2 = 1;
int appear3 = 1;
int appear4 = 1;

#pragma endregion

#pragma endregion        //Here we do an Initialisation
GLfloat red = 1.0, green = 1.0, blue = 1.0;
double score =0;
int colorCounter = 0;

double maxbulletonscreen = 8;

typedef struct
{
	int active = 0;
	double x, y, dx, dy, bullet_phi;
} Bullet;
static int shoot = 0;
static Bullet bullets[8];


#pragma region Random



double rnd()
{
	
	srand(time(NULL));
	static double random = rand() % 40 + 3;
	return random;
}

double rnd2()
{

//	srand(time(NULL));
	static double random = rand() % 40 + 10;
	return random;
}

double rnd3()
{

	//srand(time(NULL));
	static double random = rand() % 40 + 10;
	return random;
}

double rnd4()
{

	//(time(NULL));
	static double random = rand() % 40 + 10;
	return random;
}
#pragma endregion                                                     //Generates random number for the asteroids

void reshape(int width, int height)
{
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width <= height) /* aspect <= 1 */
		glOrtho(-50.0, 50.0, -50.0 / aspect, 50.0 / aspect, 50.0, 50.0);
	else /* aspect > 1 */
		glOrtho(-50.0*aspect, 50.0*aspect, -50.0, 50.0, -50.0, 50.0);
	glMatrixMode(GL_MODELVIEW);



}


bool collision2(double x1, double y1, double r1, double  x2, double y2, double r2) // Collision for asteroids by finding a distance between bulley and asteroids
{
	//just to not forget here is the Pythagoras formula for distance
	 // Square root(squared(x2-x1) + squared(y2-y1));
	int sqrX = x2 - x1;
	int sqrY = y2 - y1;
	int radSum = r1 + r2;

	int collide = (sqrX * sqrX) + (sqrY * sqrY) <= radSum * radSum;

	return collide;

}

void displayText(float x, float y, int r, int g, int b, const char *string) // Displays text
{
	int j = strlen(string);
	
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

	void displayText2(float x, float y, int r, int g, int b, const char *string) //Displays GAME OVER
{
		int j = strlen(string);
		glPushMatrix();
		glColor3f(r, g, b);
		glRasterPos2f(x, y);
		
		for (int i = 0; i < j; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
			
		}
		glPopMatrix();

}
#pragma region Asteroids



void asteroid1()
{
	int i = 0;
	float radius = 5.0f;
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.5, 1.0);
	x4 = rnd();
	y4 = rnd();

	for (double circleAngle = 0; circleAngle <= 360; circleAngle += 1)
	{
		glVertex2f(x4 + radius * cos(degToRad * circleAngle), y4 + radius * sin(degToRad * circleAngle));
	}

	glEnd();
	for (i = 0; i < 8; i++) {
		if (collision2(x4, y4, radius, bullets[i].x, bullets[i].y, bulletRadius)) {
			TF = false;
			appear = 0;
			displayText(30, 30, 1.0, 1.0, 1.0, "Collision");
			score += 10;
		}
	}

}

void asteroid2()
{
	int i = 0;
	float radius2 = 7.0f;
	

	glBegin(GL_LINE_LOOP);
	glColor3f(0.2, 0.5, 0.3);
	float x5 = rnd2();
	float y5 = -rnd2();

	for (double circleAngle = 0; circleAngle <= 360; circleAngle += 1)
	{
		glVertex2f(x5 + radius2 * cos(degToRad * circleAngle), y5 + radius2 * sin(degToRad * circleAngle));
	}

	glEnd();

	for (i = 0; i < 8; i++) {
		if (collision2(x5, y5, radius2, bullets[i].x, bullets[i].y, bulletRadius)) {
			TF2 = false;
			appear2 = 0;
			displayText(30, 30, 1.0, 1.0, 1.0, "Collision");
			score += 10;
		}
	}

}

void asteroid3()
{
	int i = 0;
	float radius3 = 10.0f;


	glBegin(GL_LINE_LOOP);
	glColor3f(0.7, 0.8, 0.6);
	float x6 = -rnd3();
	float y6 = rnd3();

	for (double circleAngle = 0; circleAngle <= 360; circleAngle += 30)
	{
		glVertex2f(x6 + radius3* cos(degToRad * circleAngle), y6 + radius3 * sin(degToRad * circleAngle));
	}

	glEnd();

	for (i = 0; i < 8; i++) {
		if (collision2(x6, y6, radius3, bullets[i].x, bullets[i].y, bulletRadius)) {
			TF3 = false;
			appear3 = 0;
			displayText(30, 30, 1.0, 1.0, 1.0, "Collision");
			score += 10;
		}
	}

}

void asteroid4()
{
	int i = 0;
	float radius4 = 10.0f;


	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.3, 0.6);
	float x7 = -rnd4();
	float y7 = -rnd4();

	for (double circleAngle = 0; circleAngle <= 360; circleAngle += 30)
	{
		glVertex2f(x7 + radius4 * cos(degToRad * circleAngle), y7 + radius4 * sin(degToRad * circleAngle));


	}

	glEnd();
	for (i = 0; i < 8; i++) {
		if (collision2(x7, y7, radius4, bullets[i].x, bullets[i].y, bulletRadius)) {
			TF4 = false;
			appear4 = 0;
			displayText(30, 30, 1.0, 1.0, 1.0, "Collision");
			score += 10;
		}
	}

}
#pragma endregion // Creates Asteroids



void drawAspaceShip()   // This function draw a spaceship
{

	//glMatrixMode(GL_MODELVIEW);
	//	glLoadIdentity();
	glPushMatrix();
	if (colorCounter == 0)
	{
		glColor3f(1.0, 0.0, 1.0);
	}
	if(colorCounter == 1)
	{
		glColor3f(1.0, 1.0, 0.0);
	}
	if (colorCounter == 2)
	{
		glColor3f(0.0, 1.0, 1.0);
	}
	if (colorCounter == 3)
	{
		glColor3f(0.1, 0.2, 1.0);
	}
	if (colorCounter == 4)
	{
		glColor3f(1.0, 0.2, 0.3);
	}
	glTranslatef(xpos, ypos, 0.0);
	glRotatef(direction, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	
	glVertex2f(4.0f, 0);
	glVertex2f(-4.0f, 4.0f);
	glVertex2f(-4.0f, -4.0f);
	glVertex2f(4.0f, 0);
	glEnd();
	glPopMatrix();
	//glutSwapBuffers();


}

#pragma region Coding for bullets



void moveBullet()
{
	int i;
	if (shoot == 1)
	{
		for (i = 0; i < 8; i++)
		{
			if (bullets[i].active == 0)
			{
				bullets[i].active = 1;
				bullets[i].x = xpos;
				bullets[i].y = ypos;
				bullets[i].bullet_phi = direction;
				bullets[i].dx += cos((pi / 180)*direction) * bulletspeed2;
				bullets[i].dy += sin((pi / 180)* direction) * bulletspeed2;
				break;
			}
		}
		shoot = 0;
	}

	for (i = 0; i < 8; i++)
	{
		if (bullets[i].active == 1)
		{
			bullets[i].x = bullets[i].x + bullets[i].dx;
			bullets[i].y = bullets[i].y + bullets[i].dy;
		}
	}


}
void myTimer(int value)
{
	//rotate();
	moveBullet();

	glutPostRedisplay();
	glutTimerFunc(33, myTimer, value);

}
void drawBullet(Bullet *b, GLfloat posX, GLfloat posY)
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(b->x + 2, b->y - 1, 0.0);
	glRotatef(b->bullet_phi, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);

	for (double circleAngle = 0; circleAngle <= 360; circleAngle += 1)
	{
		glVertex2f(posX + bulletRadius * cos(degToRad * circleAngle), posY + bulletRadius * sin(degToRad * circleAngle));
	}

	glEnd();
	glPopMatrix();


}
#pragma endregion    Cerates an animation and a drawing for a bullet(8 max)
void rotate(unsigned char rot, int x1, int y1)
{

	//(pi/180)*degrees(sin(theta)or cos(theta))
	int value = 1;
	switch (rot)
	{
	case 'w':
		xpos += cos((pi / 180)* direction) * speed;
		ypos += sin((pi / 180)* direction) * speed;
		break;

	case'a':
		direction += 5;
		break;
	case'd':
		direction -= 5;
		break;

	case 'e':

		myTimer(value);
		shoot = 1;

		break;

	default:
		break;
	}
	glutPostRedisplay();
}
void drawAsteroids() //true false for removing asteroids from screens
{
	if (TF = true && appear == 1) {

		asteroid1();
	}
	else { appear = 0;  };

	if (TF2 = true && appear2 == 1) {

		asteroid2();
	}
	else { appear2 = 0; };

	if (TF3 = true && appear3 == 1) {

		asteroid3();
	}
	else { appear3 = 0; };

	if (TF4 = true && appear4 == 1) {

		asteroid4();
	}
	else { appear4 = 0;  };


	


}





void display(void) //displays everything (asteroids, spaceship, bullets)
{
	
		glClear(GL_COLOR_BUFFER_BIT);   /* clear window */
		
		
		glLoadIdentity();
		int i = 0;

		drawAspaceShip();

		for (i = 0; i < 8; i++)
		{

			if (bullets[i].active)
			{
				drawBullet(&bullets[i], 4.0f, 4.0f);

				if (score < 40 && i == 7)
				{
					displayText2(-65, 0, 1.0, 0.0, 0.0, "G");
					displayText2(-50, 0, 1.0, 1.0, 1.0, "A");
					displayText2(-35, 0, 0.0, 1.0, 0.0, "M");
					displayText2(-20, 0, 1.0, 0.0, 0.0, "E");
					displayText2(-5, 0, 0.0, 1.0, 1.0, "O");
					displayText2(10, 0, 0.4, 0.0, 1.0, "V");
					displayText2(25, 0, 1.0, 1.0, 0.0, "E");
					displayText2(40, 0, 1.0, 0.6, 1.0, "R");
					displayText(-65, -10, 1.0, 1.0, 0.8, "You have ran out of bullets");
				}

			}


		}

		glutSwapBuffers();
		drawAsteroids();
		displayText(30, 45, 1.0, 0.2, 0.8, "The score is");
		char buf[100] = { 0 };
		snprintf(buf, 100, " %.1f", score);
		displayText(60, 45, 1.0, 0.2, 0.8, buf);
		if (score >= 40)
		{
			displayText2(-65, 0, 1.0, 0.0, 0.0, "G");
			displayText2(-50, 0, 1.0, 1.0, 1.0, "A");
			displayText2(-35, 0, 0.0, 1.0, 0.0, "M");
			displayText2(-20, 0, 1.0, 0.0, 0.0, "E");
			displayText2(-5, 0, 0.0, 1.0, 1.0, "O");
			displayText2(10, 0, 0.4, 0.0, 1.0, "V");
			displayText2(25, 0, 1.0, 1.0, 0.0, "E");
			displayText2(40, 0, 1.0, 0.6, 1.0, "R");
		}

	
		glFlush();

}

void GoMenu(int value)  //POP UP MENU
{
	switch(value)
	{
	case 1:
		colorCounter = 1;
		break;
	case 2:
		colorCounter = 2;
		break;
	case 3:
		colorCounter = 3;
		break;
	case 4:
		colorCounter = 4;
		break;
	case 5:
		exit(0);
		break;
	}
	glutPostRedisplay();
}




void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);  
}


int main(int argc, char** argv)
{

	cout << "CONTROLS:" << endl;
	cout << "press 'W' to go forward" << endl;
	cout << "press 'A' or 'D' to rotate " << endl;
	cout << "Press SPACEBAR or 'E' key to shoot" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Example 1");
	init();
	int sub1 = glutCreateMenu(GoMenu);
	glutAddMenuEntry("Just Yellow", 1);
	glutAddMenuEntry("Cyan", 2);
	glutAddMenuEntry("Kinda Blue", 3);
	glutAddMenuEntry("Almost Red", 4);
	glutCreateMenu(GoMenu);
	glutAddSubMenu("Colours", sub1);
	glutAddMenuEntry("Exit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(rotate);
	glutMainLoop();
	return 0;
}
