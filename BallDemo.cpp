#define _CRT_SECURE_NO_WARNINGS
# include "iGraphics.h"
# include "Gamestructure.h" //this is the header file for the structure
#define WIDTH 1200         //along x, has to be fullscreen
#define HEIGHT 800        //along y



//***Note that if you add any extra thing in others code, you should comment like- N: blah blah/F: blah blah... I hope you get it

//All functions should be listed here with names in the comment
void ghostmove();           //Shafayat
void fire_off() ;                // Fahmid
void tostring(char str[], int num); //Fahmid
void ghost_come(); //Fahmid
void life_down(); //Fahmid

//***Note that any value you need, just about anything, don't fear to declare a variable for it. Try to name it elegantly

//Declare all the variables here with proper commenting
int game_over=1;
int score_count=0; // F : score int
char life_str[10]; // F : life string
int life_count=3; // F : life int
char score_str[10]; // F : score string
int xchange, ychange;       //S: for changing ghost pos
int xchange2, ychange2;   // F : for changing cloud pos
int flag_p=0;                      // F : pause or resume
int flag_w=0;                      // F : for firing
int flag_r=0;                      // F : for red sky
int flag_g=1;                      // F : for ghost vanis
int xchange3=WIDTH/2, ychange3=HEIGHT-200;   // F : for changing hero pos
int hero_w=248,hero_h=159 ;//F : hero widgh and hight
int ghost_w=150,ghost_h=170 ;//F : ghost widgh and hight
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
        if(flag_w==1&& (xchange3+hero_w/2)<(xchange+ghost_w)&&(xchange3+hero_w/2)>xchange)
        {
            if(flag_g==0&&game_over==1) score_count+=1000; // F : if kill 1000 point plus
            flag_g=0; // F : ghost vanishing after kill
            flag_r=0 ; //F :  red sky off
        }



    iSetColor(150,230,255);
    iFilledRectangle(0,0,WIDTH,HEIGHT); //F : blue sky
    if(flag_r)
    {
    iSetColor(255,0,0);
    iFilledRectangle(0,0,WIDTH,HEIGHT); //F : red sky
    }
    //iShowBMP(0,0,"bin\\debug\\picture\\BG1.bmp");


    iSetColor(210,10,10);
    iFilledRectangle(0,0,WIDTH,HEIGHT/4+30); // F : edge
    iShowBMP(0,0,"bin\\debug\\picture\\BG2.bmp");
    //iSetColor(200,230,255);
    //iFilledRectangle(0,0,WIDTH,HEIGHT/4);
    iSetColor(255,255,255);
    iFilledCircle(xchange2+100,HEIGHT,100);
     iSetColor(255,255,255);
    iFilledCircle(xchange2+380,HEIGHT,250);
     iSetColor(255,255,255);
    iFilledCircle(xchange2+680,HEIGHT,100);
    iSetColor(0,0,255);
    tostring(score_str,score_count);
    iText(WIDTH-200, HEIGHT-100, " SCORE = ", GLUT_BITMAP_TIMES_ROMAN_24); // F: score show
    iText(WIDTH-200, HEIGHT-150,   score_str, GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,0,0);
    tostring(life_str,life_count);
    iText(60, HEIGHT-100, " LIFE = ", GLUT_BITMAP_TIMES_ROMAN_24); // F: life show
    iText(150, HEIGHT-100,   life_str, GLUT_BITMAP_TIMES_ROMAN_24);
      if(flag_p)  iText(WIDTH/2-200, HEIGHT/2-20, " # # # PAUSED PRESS R FOR RESUME # # #  ", GLUT_BITMAP_TIMES_ROMAN_24); //
     iSetColor(252,251,250);
      if(flag_w) iLine(xchange3+hero_w/2,ychange3,xchange3+hero_w/2,0); // F : for fireing

       if(flag_g)
       {
        iShowBMP2(xchange, ychange,"bin\\debug\\picture\\ghost1.bmp",0);  // F :ghost main
        //iSetColor(255, 100, 255);
        //iFilledRectangle(xchange, ychange+80,ghost_w,ghost_h);// F :ghost demo
       }
        iSetColor(155, 255, 155);
        //iFilledRectangle(xchange3, ychange3,hero_w,hero_h); //F :Hero demo
         iShowBMP2(xchange3, ychange3,"bin\\debug\\picture\\spaceship2.bmp",0); //F :Hero main
        iSetColor(255, 100, 255);
        iText(10, 40, " # # # NFS # # #  A and D for move  L is    for fire  P for pause R for resume\n", GLUT_BITMAP_TIMES_ROMAN_24); //
        if(!game_over)
        {
            // F : pauseing game and show game over
            iSetColor(0,255,0);
            iText(500, 400, " # # # GAME OVER # # # ", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(500, 360, " YOUR SCORE IS = ", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(500, 320,    score_str, GLUT_BITMAP_TIMES_ROMAN_24);
            iPauseTimer(0);

        }
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
	if(key == 'n')
	{
		life_count=10;
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
    if(key == GLUT_KEY_RIGHT)
	{
	    if((xchange3+hero_w)<=WIDTH)
	    xchange3+=50;
	}if(key == GLUT_KEY_LEFT)
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
void tostring(char str[], int num)

{

    int i, rem, len = 0, n;



    n = num;

    while (n != 0)

    {

        len++;

        n /= 10;

    }

    for (i = 0; i < len; i++)

    {

        rem = num % 10;

        num = num / 10;

        str[len - (i + 1)] = rem + '0';

    }

    str[len] = '\0';

}

void life_down()
{
      flag_r=1; // F: for red sky
      if(life_count>0) life_count--; // F: life down
      if (life_count==0) game_over=0; // F : for game over
}

void ghost_come()
{
    flag_g=1;
}
void fire_off()
{
    flag_w=0;
}
/*This function moves the ghost. Better the coder remove it and add a new function*/
void ghostmove()
{
	xchange += dx; //F : ghost
	xchange2+= dx2; // F : cloud
	//ychange += dy;
    ////ychange2 += dy2;
	if(xchange > WIDTH -ghost_w|| xchange < 0)dx = -dx;
	if(ychange > HEIGHT || ychange < 0)dy = -dy;
	if(xchange2 > WIDTH ) xchange2= 0;
	if(ychange2 > HEIGHT || ychange2 < 0) ychange2 = 0;
	score_count+=1;
}



int main()
{
	//place your own initialization codes here.
	if(game_over)
    {
       iSetTimer(200, ghostmove);
	   iSetTimer(1000, fire_off);
	   iSetTimer(10000, ghost_come);
	   iSetTimer(10000, life_down);
    }

	FILE *fp;



	//part where file is manipulated
	fp= fopen("resources\\PLAYERDATA.txt", "a+");

	fclose(fp);




	iInitialize(WIDTH, HEIGHT, "GAMENAME");     //someone find a game name, PLEASE

	return 0;
}

