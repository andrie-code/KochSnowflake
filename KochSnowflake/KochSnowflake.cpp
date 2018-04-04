#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/glut.h>

#define H_DIM 600.0		// horizontal dimension of window
#define V_DIM H_DIM/2		// vertical dimension of window
#define C_X H_DIM/2		// horizontal center point of window
#define C_Y V_DIM/2		// vertical center point of window
#define S_LEN 100.0		// side length of hexagon, which is also of the same length as the radius of hexagon

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	// black background
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, H_DIM, 0.0, V_DIM);
}

void triangle(GLint cx, GLint cy, GLfloat slen)
{
	GLint xVertex1, yVertex1, xVertex2, yVertex2, xVertex3, yVertex3;

	glColor3f(0.5, 0.0, 0.5);	// purple

	xVertex1 = cx + slen * cos(7 * M_PI / 6);
	yVertex1 = cy + slen * sin(7 * M_PI / 6);
	xVertex2 = cx + slen * cos(11 * M_PI / 6);
	yVertex2 = cy + slen * sin(11 * M_PI / 6);
	xVertex3 = cx + slen * cos(M_PI / 2);
	yVertex3 = cy + slen * sin(M_PI / 2);


	/* first line */
	// first vertex of a triangle
	glVertex2i(xVertex1, yVertex1);
	// second vertex of a triangle
	glVertex2i(xVertex2, yVertex2);

	// recursively draw line segment for each existing line
	if (slen > 1)
	{
		triangle((xVertex1 + xVertex2) / 3, (yVertex1 + yVertex2) / 3, slen / 3);
	}


	/* second line */
	// second vertex of a triangle
	glVertex2i(xVertex2, yVertex2);
	// third vertex of a triangle
	glVertex2i(xVertex3, yVertex3);

	// recursively draw line segment for each existing line
	if (slen > 1)
	{
		triangle((xVertex2 + xVertex3) / 2, (yVertex2 + yVertex3) / 2, slen / 3);
	}


	/* third line */
	// second vertex of a triangle
	glVertex2i(xVertex3, yVertex3);
	// third vertex of a triangle
	glVertex2i(xVertex1, yVertex1);

	// recursively draw line segment for each existing line
	if (slen > 1)
	{
		triangle((xVertex3 + xVertex1) / 2, (yVertex3 + yVertex1) / 2, slen / 3);
	}

	return;
}

void lineSegment(GLint cx, GLint cy, GLfloat slen)
{
	GLint xVertex1, yVertex1, xVertex2, yVertex2;

	for (int point = 0; point < 6; point++)     // 6 points for a hexagon
	{
		switch (point)	// colors of sides
		{
		case 0:
			glColor3f(1.0, 1.0, 1.0);	// white
			break;
		case 1:
			glColor3f(0.0, 1.0, 0.0);	// green
			break;
		case 2:
			glColor3f(0.5, 0.0, 0.5);	// purple
			break;
		case 3:
			glColor3f(1.0, 0.5, 0.0);	// orange
			break;
		case 4:
			glColor3f(0.5, 0.25, 0.25);	// brown
			break;
		case 5:
			glColor3f(1.0, 1.0, 0.0);	// yellow
		}

		// Vertices of lines are calculated using the following formula (side length = radius):
		//    x-coordinate = horizontal center of hexagon + side length * cosine(point * pi/3)
		//    y-coordinate = vertical center of hexagon + side length * sine(point * pi/3)

		xVertex1 = cx + slen * cos(point * M_PI / 3);
		yVertex1 = cy + slen * sin(point * M_PI / 3);
		xVertex2 = cx + slen * cos((point + 1) * M_PI / 3);
		yVertex2 = cy + slen * sin((point + 1) * M_PI / 3);

		// first vertex of a 2-point line
		glVertex2i(xVertex1, yVertex1);
		// second vertex of a 2-point line
		glVertex2i(xVertex2, yVertex2);

		// recursively draw line segment for each existing line
		if (slen > 1)
		{
			//lineSegment(xVertex1 + slen / 10 * cos(M_PI / 3), yVertex1 + slen /10 * sin(M_PI / 3), slen / 3);
			lineSegment((xVertex1 + xVertex2) / 2, (yVertex1 + yVertex2) / 2, slen / 3);
		}
	}

	return;
}

void startDrawing(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);

	triangle(C_X, C_Y, S_LEN);

	glEnd();
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(H_DIM, V_DIM);
	glutCreateWindow("Andrie Tanusetiawan - Assignment 1");

	init();
	glutDisplayFunc(startDrawing);
	glutMainLoop();
}