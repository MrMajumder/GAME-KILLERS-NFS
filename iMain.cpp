#define _CRT_SECURE_NO_WARNINGS
# include "iGraphics.h"
# include "Gamestructure.h" //this is the header file for the structure
#define WIDTH 800           //along x, has to be fullscreen
#define HEIGHT 600          //along y



//***Note that if you add any extra thing in others code, you should comment like- N: blah blah/F: blah blah... I hope you get it

//All functions should be listed here with names in the comment
void ghostmove();           //Shafayat


//***Note that any value you need, just about anything, don't fear to declare a variable for it. Try to name it elegantly

//Declare all the variables here with proper commenting
int xchange, ychange;       //S: for changing ghost pos
int dx, dy;                 //S: increment, decrement variable
int step=0;                 //S: this defines various states inside the app. For more info, check the wiki in github



/*
	function iDraw() is called again and again by the system. **
*/
void iDraw()
{
	iClear();


	if(step==0)  //for the main menu. Other step values mean the following buttons of the menu(Given below gradually):
    {
        //iShowBMP(0,0,"images\\3.bmp");
        //iShowBMP(0,0,"BACKGROUNDS\\3.bmp");
        //iShowBMP2(xchange, ychange,"images\\g1..bmp",0);

        iSetColor(255, 100, 10);
        iText(WIDTH/2-127.5, HEIGHT/2, "Game under development", GLUT_BITMAP_TIMES_ROMAN_24); //-127.5 for centering

    }
    else if(step==1)        //start new game button
    {

    }
    else if(step==2)        //options button
    {

    }
    else if(step==3)        //High scores button
    {

    }
    else if(step==4)        //About us section
    {

    }
    else if(step==5)        //exit button
    {
        exit(0);
    }

}



/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}



/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d %d\n", mx, my);  //S: a small technique I use to find out position on the screen
	}
}



/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'p')
	{
		//do something with 'p'
		//iPauseTimer(0);
	}
	if(key == 'r')
	{
		//iResumeTimer(0);
	}
	//place your codes for other keys here
}



/*
	function iSpecialKeyboard() is called whenever user hits special keys like-
	function keys, home, end, pg up, pg down, arrows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}



/*This function moves the ghost. Better the coder remove it and add a new function*/
void ghostmove()
{
	xchange += dx;
	ychange += dy;

	if(xchange > 400 || ychange < 0)dx = -dx;
	if(xchange > 400 || ychange < 0)dy = -dy;
}



int main()
{
	//place your own initialization codes here.
	//iSetTimer(5, ghostmove);
	FILE *fp;



	//part where file is manipulated
	fp= fopen("resources\\PLAYERDATA.txt", "a+");

	fclose(fp);


	dx = 5;
	dy = 7;

	iInitialize(WIDTH, HEIGHT, "GAMENAME");     //someone find a game name, PLEASE

	return 0;
}
