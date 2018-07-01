#define _CRT_SECURE_NO_WARNINGS
# include "iGraphics.h"
# include "Gamestructure.h" //this is the header file for the structure
#define WIDTH 1200         //along x, has to be fullscreen
#define HEIGHT 800        //along y



//***Note that if you add any extra thing in others code, you should comment like- N: blah blah/F: blah blah... I hope you get it

//All functions should be listed here with names in the comment
void ghostmove();           //Shafayat
void fire_off() ;                // Fahmid

//***Note that any value you need, just about anything, don't fear to declare a variable for it. Try to name it elegantly

//Declare all the variables here with proper commenting
int xchange, ychange;       //S: for changing ghost pos
int xchange2, ychange2;   // F : for changing cloud pos
int flag_p=0;                      // F : pause or resume
int flag_w=0;                      // F : for firing;
int flag_g=1;                      // F : for ghost vanis;
int xchange3=WIDTH/2, ychange3=HEIGHT-100;   // F : for changing hero pos
int hero_w=100,hero_h=50 ;//F : hero widgh and hight
int ghost_w=50,ghost_h=50 ;//F : ghost widgh and hight
int dx =10, dy=10;                 //S: increment, decrement variable
int dx2 =10, dy2=10;                 //F: increment, decrement variable
int step=0;                 //S: this defines various states inside the app. For more info, check the wiki in github



/*
	function iDraw() is called again and again by the system. **
*/
void iDraw()
{
	iClear();

    //iShowBMP(0,0,"bin\\debug\\picture\\BG1.bmp");



	if(step==0)  //for the main menu. Other step values mean the following buttons of the menu(Given below gradually):
    {
        if(flag_w==1&& xchange3<=(xchange2+ghost_w)&&xchange3>=xchange2)
        {
            flag_g=0; // F : ghost vanishing
        }
         iSetColor(150,230,255);
    iFilledRectangle(0,0,WIDTH,HEIGHT);
    iSetColor(210,240,255);
    iFilledRectangle(0,0,WIDTH,HEIGHT/4+20);
    iSetColor(200,230,255);
    iFilledRectangle(0,0,WIDTH,HEIGHT/4);
    iSetColor(255,255,255);
    iFilledCircle(xchange2+100,HEIGHT,100);
     iSetColor(255,255,255);
    iFilledCircle(xchange2+380,HEIGHT,250);
     iSetColor(255,255,255);
    iFilledCircle(xchange2+680,HEIGHT,100);
    iSetColor(0,0,0);
      if(flag_p)  iText(WIDTH/2-200, HEIGHT/2-20, " # # # PAUSED PRESS R FOR RESUME # # #  ", GLUT_BITMAP_TIMES_ROMAN_24); //
     iSetColor(0,0,0);
      if(flag_w) iLine(xchange3+hero_w/2,ychange3,xchange3+hero_w/2,0); // F : for fireing
       // iShowBMP2(xchange, ychange,"bin\\debug\\picture\\ghost1.bmp",0);
       if(flag_g)
       {

        iSetColor(255, 100, 255);
        iFilledRectangle(xchange, ychange+80,ghost_w,ghost_h);// F :ghost
       }
        iSetColor(155, 255, 155);
        iFilledRectangle(xchange3, ychange3,hero_w,hero_h); //F :Hero
        iSetColor(255, 100, 255);
        iText(10, 40, " # # # NFS # # #  A and D for move  L is    for fire  P for pause R for resume\n", GLUT_BITMAP_TIMES_ROMAN_24); //

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
		iPauseTimer(0);
        flag_p=1;
	}
	if(key == 'r')
	{
		iResumeTimer(0);
		flag_p=0;
	}
	if(key == 'd') //F: move right
	{
	    if((xchange3+hero_w)<=WIDTH)
	    xchange3+=10;
		//do something with 'p'
		//iPauseTimer(0);
	}
	if(key == 'a') // F : move left
	{
	    if(xchange3>=0)
	    xchange3-=10;
		//do something with 'p'
		//iPauseTimer(0);
	}
	if(key == 'l') // F : move left
	{
	    flag_w=1;
		//do something with 'p'
		//iPauseTimer(0);
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
    if(key == 'GLUT_KEY_RIGHT')
	{
	    if((xchange3+hero_w)<=WIDTH)
	    xchange3+=50;
	}if(key == 'GLUT_KEY_LEFT')
	{
	    if(xchange3>=0)
	    xchange3-=50;
	}

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}


void fire_off()
{
    flag_w=0;
}
/*This function moves the ghost. Better the coder remove it and add a new function*/
void ghostmove()
{
	xchange += dx;
	xchange2+= dx2;
	//ychange += dy;
    ////ychange2 += dy2;
	if(xchange > WIDTH -50|| xchange < 0)dx = -dx;
	if(ychange > HEIGHT || ychange < 0)dy = -dy;
	if(xchange2 > WIDTH || xchange2 < 0) dx2 = 0;
	if(ychange2 > HEIGHT || ychange2 < 0)dy2 = 0;
}



int main()
{
	//place your own initialization codes here.
	iSetTimer(200, ghostmove);
	iSetTimer(500, fire_off);
	FILE *fp;



	//part where file is manipulated
	fp= fopen("resources\\PLAYERDATA.txt", "a+");

	fclose(fp);




	iInitialize(WIDTH, HEIGHT, "GAMENAME");     //someone find a game name, PLEASE

	return 0;
}
