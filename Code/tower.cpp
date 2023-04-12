#include <windows.h>
#include <gl/glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int pos[16] = {10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85};
int peg[3] = {50,150,250};
int moves[10000][3];
int max_moves;
int POLES[3][10];
int top[3]={-1,-1,-1};
int NUM_DISKS=3;
int cnt,counter;
int line1=90,line2=85;
float ycoordinate;
int lightflag=1,animationFlag=1;

void push(int p,int disk)
{
	POLES[p][++top[p]] = disk;
}

void pop(int p)
{
	top[p]--;
}

void tower(int n,int src,int temp,int dst)
{
	if(n>0)
	{
		tower(n-1,src,dst,temp);
		moves[cnt][0] = n;
		moves[cnt][1] = src;
		moves[cnt][2] = dst;
		cnt++;
		tower(n-1,temp,src,dst);
	}
}
void drawcylinder()
{
	GLUquadricObj *q;
	q = gluNewQuadric();
	gluCylinder(q, 2, 2, 60, 60, 20);	
}

void drawPegs()
{
	int i;
	glColor3f(0,0,0);
	for(i=0;i<3;i++)
	{
		glPushMatrix();
		glTranslatef(peg[i],5,0);
		glRotatef(-90,1,0,0);
		drawcylinder();
		glutSolidTorus(2,45, 20, 20);
		glPopMatrix();
	}	
}

void printString(char *text)
{
	int len=strlen(text),i;
	for(i=0;i<len;i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
}
void printS(char *text)
{
	int len=strlen(text),i;
	for(i=0;i<len;i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[i]);
}

void drawText()
{
	glColor3f(0,0,0);
	glRasterPos3f(-70,line1,0);
	printString("Move :");
	char str[5];
	sprintf(str, "%d", counter);
	glRasterPos3f(-40,line1,0);
	printString(str);
	glRasterPos3f(-70,line2,0);
	printString("Disk");
	char str1[10];
	sprintf(str1, "%d", moves[counter][0]);
	glRasterPos3f(-50,line2,0);
	printString(str1);
	glRasterPos3f(-40,line2,0);
	printString("from");
	char src[2];
	if(moves[counter][1]==0)strcpy(src,"A");
	else if(moves[counter][1]==1)strcpy(src,"B");
	else strcpy(src,"C");
	glRasterPos3f(-20,line2,0);
	printString(src);
	glRasterPos3f(-10,line2,0);
	printString("to");
	char dst[2];
	if(moves[counter][2]==0)strcpy(dst,"A");
	else if(moves[counter][2]==1)strcpy(dst,"B");
	else strcpy(dst,"C");
	glRasterPos3f(0,line2,0);
	printString(dst);
	glColor3f(0,0,1);
	glRasterPos3f(peg[0],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');
}
void displayName(){
	glColor3f(1,0,0);
	glRasterPos3f(40,line1,0);
	//printS("2JR18CS078 \n2JR18CS079");
}
void drawSolved()
{	
	glColor3f(0,0,1);
	glRasterPos3f(peg[0],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');
	glColor3f(0,0,1);
	glRasterPos3f(-60,77,0);
	if(moves[0][0]==0){
	printString("Select the number of disks");
	displayName();
	}
	else {
	printString("Solved !!");}
	displayName();
}

void display()
{
	int i,j,k;
	displayName();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	glPushMatrix();
	gluLookAt(0,ycoordinate,0,0,0,-1,0,1,0);
	drawPegs();
	for(i=0;i<3;i++)
	{
		k=0;
		for(j=0;j<=top[i];j++)
		{
			glPushMatrix();
			glTranslatef(peg[i],pos[k++],0);
			glRotatef(90,1,0,0);
			glColor3f(0.1*POLES[i][j],0.2*POLES[i][j],2);
			glutSolidTorus(2, 6*POLES[i][j], 20, 20);
			glPopMatrix();
		}
	}	
	glPopMatrix();
	glDisable(GL_LIGHTING);	
	if(counter==max_moves)
		drawSolved();
	else
		drawText();
	if(lightflag)glEnable(GL_LIGHTING);
	glutSwapBuffers();
}

void lighting()
{
	GLfloat shininess[] = {50};
	GLfloat white[] = {0.6,0.6,0.6,1};
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = {100,60, 10, 0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);
}

void init()
{	glClearColor(1.0,1.0,1.0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-80,350,-10,100,-100,100);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	lighting();
}

void mouse(int btn,int mode,int x,int y)
{
	if(btn == 4 && mode == GLUT_DOWN)
	{
		if(counter<max_moves)
		{
			pop(moves[counter][1]);
			
			push(moves[counter][2],moves[counter][0]);
			counter++;
		}
	}
	if(btn == 3 && mode == GLUT_DOWN)
	{
		if(counter>0)
		{
			counter--;
			pop(moves[counter][2]);
			
			push(moves[counter][1],moves[counter][0]);
		}
	}
	glutPostRedisplay();
}

void restart()
{
	int i;
	memset(POLES,0,sizeof(POLES));
	memset(moves,0,sizeof(POLES));
	memset(top,-1,sizeof(top));
	cnt=0,counter=0;
	ycoordinate=0.1;
	max_moves = pow(2,NUM_DISKS)-1;
	for(i=NUM_DISKS;i>0;i--)
	{
		push(0,i);
	}
	tower(NUM_DISKS,0,1,2);
}

void processMenuMain2(int option)
{
	
}

void processMenuRestart(int option)
{
	if(option==0)
	{
		restart();
		glutPostRedisplay();
	}
}

void processMenuExit(int option)
{
	if(option==0)exit(0);
}

void processMenuSolveCompletely(int option)
{
	int temp=animationFlag;
	animationFlag=0;
	int i,j;
	while(counter<max_moves)
	{
		mouse(4,GLUT_DOWN,0,0);
		display();
		for(i=0;i<1000000;i++)
			for(j=0;j<100;j++);
	}
	animationFlag=temp;
}

void processMenuNumDisks(int option)
{
	NUM_DISKS=option;
	restart();
	glutPostRedisplay();
}

void createGLUTMenus2()
{	
	int menu = glutCreateMenu(processMenuNumDisks);
	glutAddMenuEntry("3",3);
	glutAddMenuEntry("4",4);
	glutAddMenuEntry("5",5);
	glutAddMenuEntry("6",6);
	glutAddMenuEntry("7",7);
	glutAddMenuEntry("8",8);
	glutAddMenuEntry("9",9);
	glutAddMenuEntry("10",10);
	
	int menuExit = glutCreateMenu(processMenuExit);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	
	int menuRestart = glutCreateMenu(processMenuRestart);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	
	int menuSolveCompletely = glutCreateMenu(processMenuSolveCompletely);
	glutAddMenuEntry("Start",0);
	
	glutCreateMenu(processMenuMain2);
	glutAddSubMenu("Number of Disks",menu);
	glutAddSubMenu("Solve Completely",menuSolveCompletely);
	glutAddSubMenu("Restart",menuRestart);
	glutAddSubMenu("Exit",menuExit);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1024,800);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Tower of Hanoi");
	init();
	glutDisplayFunc(display);
	createGLUTMenus2();
	glutMainLoop();
	return 0;
}
