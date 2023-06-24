#include <windows.h>
#include <gl/glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

// Array to store the positions of the disks
int pos[16] = {10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85};

// Array to store the positions of the pegs
int peg[3] = {50,150,250};

// Array to store the moves made during the Tower of Hanoi solution
int moves[10000][3];

// Maximum number of moves allowed
int max_moves;

// 2D array representing the poles and the disks on them
int POLES[3][10];

// Array to keep track of the top disk on each pole
int top[3]={-1,-1,-1};
int NUM_DISKS=3; // Total number of disks

// Variables for counting and animation
int cnt,counter;
int line1=90,line2=85;
float ycoordinate;

// Flags for light and animation
int lightflag=1,animationFlag=1;

// Function to push a disk onto a pole
void push(int p,int disk)
{
	POLES[p][++top[p]] = disk;
}

// Function to pop a disk from a pole
void pop(int p)
{
	top[p]--;
}

// Recursive function to solve the Tower of Hanoi problem
void tower(int n,int src,int temp,int dst)
{
	if(n>0)
	{
		tower(n-1,src,dst,temp); // Move n-1 disks from source to temporary peg
		moves[cnt][0] = n; // Store the current move in the moves array
		moves[cnt][1] = src; // Store the source peg index for the current move
		moves[cnt][2] = dst; // Store the destination peg index for the current move
		cnt++; // Increment the move count
		tower(n-1,temp,src,dst); // Move n-1 disks from the temporary peg to the destination peg
	}
}

// Function to draw a cylinder
void drawcylinder()
{
	// Create a new quadric object
	GLUquadricObj *q;
	q = gluNewQuadric();

	// Draw the cylinder using gluCylinder function
	// Parameters: (quad, base radius, top radius, height, slices, stacks)
	gluCylinder(q, 2, 2, 60, 60, 20);	
}

// Function to draw the pegs
void drawPegs()
{
	int i;
	glColor3f(0,0,0);

	// Iterate over each peg
	for(i=0;i<3;i++)
	{
		glPushMatrix();
		glTranslatef(peg[i],5,0);
		glRotatef(-90,1,0,0);
		drawcylinder(); // Draw the cylinder for the peg using the drawcylinder function
		// Draw the torus shape on top of the peg using glutSolidTorus function
		// Parameters: (inner radius, outer radius, sides, rings)
		glutSolidTorus(2,45, 20, 20);
		glPopMatrix();
	}	
}

// Function to print a string using GLUT bitmap fonts (Helvetica 18)
void printString(char *text)
{
	int len=strlen(text),i;
	// Iterate over each character in the string and print it using glutBitmapCharacter function
	for(i=0;i<len;i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
}

// Function to print a string using GLUT bitmap fonts (Times Roman 24)
void printS(char *text)
{
	int len=strlen(text),i;
	// Iterate over each character in the string and print it using glutBitmapCharacter function
	for(i=0;i<len;i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[i]);
}

// Function to draw the text on the screen
void drawText()
{
	// Set the text color to black
	glColor3f(0,0,0);

	// Draw "Move :" text
	glRasterPos3f(-70,line1,0);
	printString("Move :"); 

	// Convert the counter variable to a string and print it
	char str[5]; 
	sprintf(str, "%d", counter);

	// Draw the counter value
	glRasterPos3f(-40,line1,0);
	printString(str);

	// Draw "Disk" text
	glRasterPos3f(-70,line2,0);
	printString("Disk");

	// Convert the disk number to a string
	char str1[10];
	sprintf(str1, "%d", moves[counter][0]);

	// Draw the disk number
	glRasterPos3f(-50,line2,0);
	printString(str1);

	// Draw "from" text
	glRasterPos3f(-40,line2,0);
	printString("from");

	// Determine the source peg (A, B, or C) and draw it
	char src[2];
	if(moves[counter][1]==0)
		strcpy(src,"A");
	else if(moves[counter][1]==1)
		strcpy(src,"B");
	else 
		strcpy(src,"C");
	glRasterPos3f(-20,line2,0);
	printString(src);

	// Draw "to" text
	glRasterPos3f(-10,line2,0);
	printString("to");

	// Determine the destination peg (A, B, or C) and draw it
	char dst[2];
	if(moves[counter][2]==0)
		strcpy(dst,"A");
	else if(moves[counter][2]==1)
		strcpy(dst,"B");
	else 
		strcpy(dst,"C");
	glRasterPos3f(0,line2,0);
	printString(dst);

	// Set the color to blue
	glColor3f(0,0,1);

	// Draw peg labels A, B, and C
	glRasterPos3f(peg[0],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');
}

// Function to display the name
void displayName(){
	// Set the text color to red
	glColor3f(1,0,0);
	/ Set the position to display the name
	glRasterPos3f(40,line1,0);
	//printS("2JR18CS078 \n2JR18CS079");  //Prints our USN. Commented because not in use for now.
}

// Function to draw a "Solved" message or prompt to select the number of disks
void drawSolved()
{	
	// Set the color to blue
	glColor3f(0,0,1);

	// Draw peg labels A, B, and C
	glRasterPos3f(peg[0],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');

	// Set the color to blue
	glColor3f(0,0,1);

	// Set the position to display the message
	glRasterPos3f(-60,77,0);

	// Check if the first move is 0 to determine if the number of disks needs to be selected
	if(moves[0][0]==0)
	{
		// Print the prompt to select the number of disks
		printString("Select the number of disks");
		// Display the name
		displayName();
	}
	else 
	{	
		// Print "Solved !!" message
		printString("Solved !!");
	}
	// Display the name	
	displayName();
}

// Display function for OpenGL rendering
void display()
{
	int i,j,k;

	// Display the name
	displayName();

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	glPushMatrix();

	// Set the camera position
	gluLookAt(0,ycoordinate,0,0,0,-1,0,1,0);

	// Draw the pegs
	drawPegs();

	// Iterate over each pole
	for(i=0;i<3;i++)
	{
		k=0;
		// Iterate over each disk on the pole
		for(j=0;j<=top[i];j++)
		{
			glPushMatrix();
			glTranslatef(peg[i],pos[k++],0);
			glRotatef(90,1,0,0);

			// Set the color of the disk based on its value
			glColor3f(0.1*POLES[i][j],0.2*POLES[i][j],2);

			// Draw the disk using glutSolidTorus function
			// Parameters: (inner radius, outer radius, sides, rings)
			glutSolidTorus(2, 6*POLES[i][j], 20, 20);
			glPopMatrix();
		}
	}	
	glPopMatrix();

	// Disable lighting for the following text and messages
	glDisable(GL_LIGHTING);	

	// Check if the current move counter is equal to the maximum allowed moves
	if(counter==max_moves)
		drawSolved(); // Draw "Solved" message
	else
		drawText(); // Draw the current move details
	
	// Enable lighting again
	if(lightflag)
		glEnable(GL_LIGHTING);
	glutSwapBuffers();
}


// Function to set up lighting for the scene
void lighting()
{
	// Set the shininess value for materials
	GLfloat shininess[] = {50};

	// Set the color for ambient and diffuse lighting
	GLfloat white[] = {0.6,0.6,0.6,1};

	// Enable color material and set material properties
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

	// Set the ambient light properties
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };

	// Set the light position
	GLfloat light_position[] = {100,60, 10, 0.0 };

	// Set the ambient light and light position
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Set the diffuse and specular material properties
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);

	// Set the shininess of the material
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	// Enable light 0
	glEnable(GL_LIGHT0);
}


// Initialization function
void init()
{	
	// Set the clear color
	glClearColor(1.0,1.0,1.0,0);

	// Set the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the orthographic projection
	glOrtho(-80,350,-10,100,-100,100);

	// Set the modelview matrix
	glMatrixMode(GL_MODELVIEW);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Set up lighting
	lighting();
}

// Mouse function to handle button clicks
void mouse(int btn,int mode,int x,int y)
{
	// Check if the scroll wheel is scrolled up
	if(btn == 4 && mode == GLUT_DOWN)
	{
		// Check if the counter is less than the maximum allowed moves
		if(counter<max_moves)
		{
			// Move the disk from the source peg to the destination peg
			pop(moves[counter][1]);
			
			push(moves[counter][2],moves[counter][0]);
			counter++;
		}
	}

	// Check if the scroll wheel is scrolled down
	if(btn == 3 && mode == GLUT_DOWN)
	{
		// Check if the counter is greater than 0
		if(counter>0)
		{
			// Move the disk from the destination peg back to the source peg
			counter--;
			pop(moves[counter][2]);
			push(moves[counter][1],moves[counter][0]);
		}
	}
	glutPostRedisplay();
}

// Function to restart the game
void restart()
{
	int i;

	// Reset the pole, move, and top arrays
	memset(POLES,0,sizeof(POLES));
	memset(moves,0,sizeof(POLES));
	memset(top,-1,sizeof(top));
	cnt=0,counter=0;
	ycoordinate=0.1;

	// Calculate the maximum allowed moves based on the number of disks
	max_moves = pow(2,NUM_DISKS)-1;

	// Push the disks onto the source peg
	for(i=NUM_DISKS;i>0;i--)
	{
		push(0,i);
	}

	// Generate the moves to solve the game
	tower(NUM_DISKS,0,1,2);
}

// Function to handle main menu option selection (unused for now)
void processMenuMain2(int option)
{
	
}

// Function to handle the restart menu option
void processMenuRestart(int option)
{
	// Check if the option selected is 0 (Yes)
	if(option==0)
	{
		// Restart the game and redraw the scene
		restart();
		glutPostRedisplay();
	}
}

// Function to handle the exit menu option
void processMenuExit(int option)
{
	// Check if the option selected is 0 (Yes)
	if(option==0)
		exit(0); // Exit the program
}

// Function to solve the game completely
void processMenuSolveCompletely(int option)
{
	// Store the current animation flag value
	int temp=animationFlag;

	// Disable animation for faster solving
	animationFlag=0;
	
	int i,j;

	// Perform moves until the game is completely solved
	while(counter<max_moves)
	{
		mouse(4,GLUT_DOWN,0,0);
		display();

		// Add delay to visualize the solving process
		for(i=0;i<1000000;i++)
			for(j=0;j<100;j++);
	}
	
	// Restore the original animation flag value
	animationFlag=temp;
}

// Function to handle the number of disks menu option
void processMenuNumDisks(int option)
{
	// Update the number of disks based on the selected option
	NUM_DISKS = option;
	
	// Restart the game with the new number of disks
	restart();
	
	// Request to redraw the display
	glutPostRedisplay();
}

// Function to create GLUT menus for the game
void createGLUTMenus2()
{	
	// Create the menu for selecting the number of disks
	int menu = glutCreateMenu(processMenuNumDisks);
	glutAddMenuEntry("3",3);
	glutAddMenuEntry("4",4);
	glutAddMenuEntry("5",5);
	glutAddMenuEntry("6",6);
	glutAddMenuEntry("7",7);
	glutAddMenuEntry("8",8);
	glutAddMenuEntry("9",9);
	glutAddMenuEntry("10",10);
	
	// Create the menu for the exit option
	int menuExit = glutCreateMenu(processMenuExit);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	
	// Create the menu for the restart option
	int menuRestart = glutCreateMenu(processMenuRestart);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	
	// Create the menu for the solve completely option
	int menuSolveCompletely = glutCreateMenu(processMenuSolveCompletely);
	glutAddMenuEntry("Start",0);
	
	// Create the main menu
	glutCreateMenu(processMenuMain2);
	glutAddSubMenu("Number of Disks",menu);
	glutAddSubMenu("Solve Completely",menuSolveCompletely);
	glutAddSubMenu("Restart",menuRestart);
	glutAddSubMenu("Exit",menuExit);
	
	// Attach the menu to the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Main function of the program
int main(int argc, char** argv)
{
	// Initialize GLUT library and pass command line arguments
	glutInit(&argc, argv);
	
	// Set the display mode for GLUT window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	// Set the initial window size
	glutInitWindowSize(1024, 800);
	
	// Set the initial window position
	glutInitWindowPosition(100, 100);
	
	// Create a window with the specified title
	glutCreateWindow("Tower of Hanoi");
	
	// Perform initialization tasks
	init();
	
	// Specify the function to be called for rendering/displaying the graphics
	glutDisplayFunc(display);
	
	// Create the custom menus using GLUT
	createGLUTMenus2();
	
	// Enter the GLUT event processing loop
	glutMainLoop();
	
	// Program execution completed successfully
	return 0;
}
