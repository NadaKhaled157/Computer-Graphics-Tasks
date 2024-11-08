// #include <GL/glew.h>
// #include <GL/freeglut.h>

// // Takes coordinates of back wall, left and right walls lengths, ceiling length, and floor length
// void roomSetup(float top_left_x, float top_left_y,
//                float top_right_x, float top_right_y,
//                float bottom_right_x, float bottom_right_y,
//                float bottom_left_x, float bottom_left_y,
//                float wall_length, float ceiling_length, float floor_length)
// {
//     glClear(GL_COLOR_BUFFER_BIT);

//     // Back Wall
//     glColor3f(0.2, 0.3, 0.4);
//     glBegin(GL_POLYGON);
//     glVertex3f(top_left_x, top_left_y, 0.0);
//     glVertex3f(top_right_x, top_right_y, 0.0);
//     glVertex3f(bottom_right_x, bottom_right_y, 0.0);
//     glVertex3f(bottom_left_x, bottom_left_y, 0.0);
//     glEnd();

//     // Right Wall
//     glColor3f(0.3, 0.5, 0.7);
//     glBegin(GL_POLYGON);
//     glVertex3f(top_right_x, top_right_y, 0.0); // top left (back wall top right)
//     glVertex3f(top_right_x + wall_length, top_right_y + ceiling_length, 0.0); // top right
//     glVertex3f(bottom_right_x + wall_length, bottom_right_y - floor_length, 0.0); // bottom right
//     glVertex3f(bottom_right_x, bottom_right_y, 0.0); // bottom left (back wall bottom right)
//     glEnd();

//     // Left Wall
//     glColor3f(0.3, 0.5, 0.7);
//     glBegin(GL_POLYGON);
//     glVertex3f(top_left_x - wall_length, top_left_y + ceiling_length, 0.0); // top left
//     glVertex3f(top_left_x, top_left_y, 0.0); // top right (back wall top left)
//     glVertex3f(bottom_left_x, bottom_left_y, 0.0); // bottom right (back wall bottom left)
//     glVertex3f(bottom_left_x - wall_length, bottom_left_y - floor_length, 0.0); // bottom left
//     glEnd();

//     // Ceiling
//     glColor3f(0.8, 0.9, 1.0);
//     glBegin(GL_POLYGON);
//     glVertex3f(top_left_x, top_left_y, 0.0); // top left (left wall top right)
//     glVertex3f(top_right_x, top_right_y, 0.0); // top right (right wall top left)
//     glVertex3f(top_right_x + wall_length, top_right_y + ceiling_length, 0.0); // bottom right (right wall bottom right)
//     glVertex3f(top_left_x - wall_length, top_left_y + ceiling_length, 0.0); // bottom left (left wall top right)
//     glEnd();

//     // Floor
//     glColor3f(0.6, 0.5, 0.4);
//     glBegin(GL_POLYGON);
//     glVertex3f(bottom_left_x, bottom_left_y, 0.0); // top left (back wall bottom left)
//     glVertex3f(bottom_right_x, bottom_right_y, 0.0); // top right (back wall bottom right)
//     glVertex3f(bottom_right_x + wall_length, bottom_right_y - floor_length, 0.0); // bottom right (right wall bottom right)
//     glVertex3f(bottom_left_x - wall_length, bottom_left_y - floor_length, 0.0); // bottom left (left wall bottom left)
//     glEnd();

//     glFlush();
// }

// void displayRoom() {
// 	roomSetup(150.0, 220.0, 350.0, 220.0, 350.0, 120.0, 150.0, 120.0,
// 		  100.0, 50.0, 50.0);
// }


// // OpenGL window reshape routine.
// void resize(int w, int h)
// {
// 	// drawing the entire window
// 	glViewport(0, 0, w, h);

// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();

// 	//glOrtho(left, right, bottom, top, near, far)
// 	//Sets up a viewing box span along the x-axis is from left to right, along the y-axis from bottom to top,
// 	// and along the z-axis from ?far to ?near.
// 	glOrtho(0.0, 500.0, 0.0, 300.0, -1.0, 1.0);

// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// }

// // Keyboard input processing routine. x & y are location of the mouse
// void keyInput(unsigned char key, int x, int y)
// {
// 	switch (key)
// 	{
// 	// ascii of escape key
// 	case 27:
// 		exit(0);
// 		break;
// 	default:
// 		break;
// 	}
// }

// // Main routine.
// int main(int argc, char **argv)
// {
// 	glutInit(&argc, argv);
// 	glutInitContextVersion(3, 3);
// 	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
// 	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
// 	glutInitWindowSize(1000, 800);
// 	glutInitWindowPosition(200, 10);
// 	glutCreateWindow("Projection Animation");
// 	glutDisplayFunc(displayRoom);
// 	glutReshapeFunc(resize);
// 	glutKeyboardFunc(keyInput);
// 	glewExperimental = GL_TRUE;
// 	glewInit();
// 	glClearColor(0.0, 0.0, 0.0, 0.0);
// 	glutMainLoop();

// }
