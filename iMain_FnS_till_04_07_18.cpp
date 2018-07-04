#define _CRT_SECURE_NO_WARNINGS
# include "iGraphics.h"
# include "Gamestructure.h"     //this is the header file for the structure
#define WIDTH 1200              //along x, has to be fullscreen
#define HEIGHT 800              //along y



//***Note that if you add any extra thing in others code, you should comment like- N: blah blah/F: blah blah... I hope you get it

//All functions should be listed here with names in the comment
void ghostmove();                   //Shafayat
void fire_off() ;                   //Fahmid
void backbutton();                  //Shafayat
int structload();                   //Shafayat
void numtocharconvert(int num, char *p);    //Shafayat
int chartonumconvert(char * ch);    //Shafayat
void getscore();                    //Shafayat
//***Note that any value you need, just about anything, don't fear to declare a variable for it. Try to name it elegantly

//Declare all the variables here with proper commenting
int screenwidth, screenheight;      //S : self explainatory
int xchange, ychange;               //S : for changing ghost pos
int xchange2, ychange2;             //F : for changing cloud pos
int flag_p=0;                       //F : pause or resume
int flag_w=0;                       //F : for firing
int flag_g=1;                       //F : for ghost vanish
int xchange3=WIDTH/2, ychange3=HEIGHT-100;   // F : for changing hero pos
int hero_w=100,hero_h=50 ;          //F : hero width and height
int ghost_w=50,ghost_h=50 ;         //F : ghost width and height
int dx =10, dy=10;                  //S : increment, decrement variable
int dx2 =10, dy2=10;                //F : increment, decrement variable
int step=0;                         //S : this defines various states inside the app. For more info, check the wiki in github
int i, j;                           //S : Counter variable
int toggle_sound=0, toggle_sfx=0, toggle_difficulty=0; //S : toggles the on/off and difficulty buttons, also can be used to change sound and difficulty modes
struct playerdata player[5];        //S: for storing player info
FILE *file;

char buttonimages[7][100]={"bin\\Debug\\pictures\\buttons\\startnewgame.bmp", "bin\\Debug\\pictures\\buttons\\options.bmp", "bin\\Debug\\pictures\\buttons\\highscores.bmp", "bin\\Debug\\pictures\\buttons\\creators.bmp", "bin\\Debug\\pictures\\buttons\\exit.bmp","bin\\Debug\\pictures\\buttons\\back.bmp", ""};  //S: char for button image location
char background[][100]={"", "bin\\Debug\\pictures\\background\\skyback.bmp", "bin\\Debug\\pictures\\background\\options1.bmp", "bin\\Debug\\pictures\\background\\leaderboardsbackground.bmp", "bin\\Debug\\pictures\\background\\creatorscity.bmp", ""};
char optionsbutton[][100]={ "bin\\Debug\\pictures\\buttons\\sound.bmp", "bin\\Debug\\pictures\\buttons\\sfx.bmp", "bin\\Debug\\pictures\\buttons\\difficulty.bmp",""};
char onoffbutton[][100]= { "bin\\Debug\\pictures\\buttons\\on.bmp", "bin\\Debug\\pictures\\buttons\\off.bmp",""};
char difficultylvl[][100]= { "bin\\Debug\\pictures\\buttons\\lvleasy.bmp", "bin\\Debug\\pictures\\buttons\\lvlmedium.bmp", "bin\\Debug\\pictures\\buttons\\lvlhard.bmp",""};
/*
	function iDraw() is called again and again by the system. **
*/
void iDraw()
{
	iClear();

	if(step==0)  //for the main menu. Other step values mean the following buttons of the menu(Given below gradually):
    {
        iShowBMP(0, 0, background[1]);
        for(i=0; i<5; i++)      //S: for showing button images
        {
            iShowBMP2(WIDTH/2 - 154-20+(i*10), HEIGHT/2 - (i*90),  buttonimages[i], 0);

        }
    }

    else if(step==1)        //start new game button
    {
        if(flag_w==1&& (xchange3+hero_w/2)<=(xchange+ghost_w)&&(xchange3+hero_w/2)>=(xchange)) //S: Modified this relation a little
        {
            flag_g=0; // F : ghost vanishing  xchange3<=(xchange2+ghost_w)&&xchange3>=xchange2
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

        if(flag_p)      //F : Pause menu in game
        {
            iText(WIDTH/2-200, HEIGHT/2-20, " # # # PAUSED PRESS R FOR RESUME # # #  ", GLUT_BITMAP_TIMES_ROMAN_24);
        }
        iSetColor(0,0,0);

        if(flag_w) iLine(xchange3+hero_w/2,ychange3,xchange3+hero_w/2,0); // F : for firing

        if(flag_g)      // F :ghost move applied in game
        {
            iSetColor(255, 100, 255);
            iFilledRectangle(xchange, ychange+80,ghost_w,ghost_h); //F: Use a bmp image of ghost here
        }

        iSetColor(155, 255, 155);
        iFilledRectangle(xchange3, ychange3,hero_w,hero_h); //F :Hero
        iSetColor(255, 100, 255);
        iText(10, 40, " # # # NFS # # #  A and D for move  L is    for fire  P for pause R for resume\n", GLUT_BITMAP_TIMES_ROMAN_24); //
    }

    else if(step==2)        //options button
    {
        iSetColor(255, 100, 255);
        iShowBMP(0, 0, background[2]);

        iShowBMP2(1*WIDTH/4, 3*HEIGHT/4, optionsbutton[0], 0);    //S: shows sound button
        iShowBMP2(1*WIDTH/4, 2*HEIGHT/4, optionsbutton[1], 0);    //S: shows sfx button
        iShowBMP2(1*WIDTH/4, 1*HEIGHT/4, optionsbutton[2], 0);    //S: shows difficulty button

        iShowBMP2(2*WIDTH/4, 3*HEIGHT/4, onoffbutton[toggle_sound], 0); //S: shows on button primarily
        iShowBMP2(2*WIDTH/4, 2*HEIGHT/4, onoffbutton[toggle_sfx], 0); //S: shows on button primarily

        iShowBMP2(2*WIDTH/4, 1*HEIGHT/4, difficultylvl[toggle_difficulty], 0); //S:shows easy button primarily

        iText(10, 40, " Options Menu", GLUT_BITMAP_TIMES_ROMAN_24);
        backbutton();
    }

    else if(step==3)        //High scores button
    {
        iSetColor(255, 255, 255);
        iShowBMP(0, 0, background[3]);
        iText(10, 40, "High Scores Page", GLUT_BITMAP_TIMES_ROMAN_24); //
        backbutton();

        for(i=0; i<5; i++)
        {
            iText(2*WIDTH/8, ((3*HEIGHT)/4)-(i*40), player[i].serial, GLUT_BITMAP_TIMES_ROMAN_24);
            iText(3*WIDTH/8, ((3*HEIGHT)/4)-(i*40), player[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
            iText(5*WIDTH/8, ((3*HEIGHT)/4)-(i*40), player[i].score, GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }

    else if(step==4)        //Creators section
    {
        iSetColor(255, 100, 255);
        iShowBMP(0, 0, background[4]);
        iText(10, 40, "Creators Page", GLUT_BITMAP_TIMES_ROMAN_24); //
        backbutton();
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
		if(step==0)     //S: When menu page is on screen
        {
            if(mx>=(WIDTH/2-154-20)&&mx<=(WIDTH/2+154-20)&&my>=(HEIGHT/2)&&(HEIGHT/2+74))
            {
                step= 1;
            }
            else if(mx>=(WIDTH/2-154-10)&&mx<=(WIDTH/2+154-10)&&my>=(HEIGHT/2-90)&&(HEIGHT/2+74-90))
            {
                step= 2;
            }
            else if(mx>=(WIDTH/2-154)&&mx<=(WIDTH/2+154)&&my>=(HEIGHT/2-180)&&(HEIGHT/2+74-180))
            {
                step= 3;
            }
            else if(mx>=(WIDTH/2-154+10)&&mx<=(WIDTH/2+154+10)&&my>=(HEIGHT/2-270)&&(HEIGHT/2+74-270))
            {
                step= 4;
            }
            else if(mx>=(WIDTH/2-154+20)&&mx<=(WIDTH/2+154+20)&&my>=(HEIGHT/2-360)&&(HEIGHT/2+74-360))
            {
                step= 5;
            }
        }

        if(step==2) //S: when options page is onscreen
        {
            if(mx>=(2*WIDTH/4)&&mx<=(2*WIDTH/4+120)&&my>=(3*HEIGHT/4)&&my<=(3*HEIGHT/4+58)) //S: for toggling sound
            {
                if(toggle_sound) toggle_sound=0;
                else toggle_sound=1;
            }
            if(mx>=(2*WIDTH/4)&&mx<=(2*WIDTH/4+120)&&my>=(2*HEIGHT/4)&&my<=(2*HEIGHT/4+58)) //S: for toggling sfx
            {
                if(toggle_sfx) toggle_sfx=0;
                else toggle_sfx=1;
            }
            if(mx>=(2*WIDTH/4)&&mx<=(2*WIDTH/4+120)&&my>=(1*HEIGHT/4)&&my<=(1*HEIGHT/4+58)) //S: for toggling difficulty
            {
                if(toggle_difficulty==2) toggle_difficulty=0;
                else toggle_difficulty++;
            }
        }

        if(step==2||step==3||step==4) // steps where back button will work, diverts to main page
        {
            if(mx>=(WIDTH-160)&&mx<=(WIDTH-9)&&my>=(8)&&my<=(70))
            {
                step=0;
            }
        }
        //if(mx>=&&mx<=&&my>=&&my<=)    S: layout to use for button clickability
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
	if(step==1) //F: buttons declaring while in game
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
        }
        if(key == 'a') // F : move left
        {
            if(xchange3>=0)
            xchange3-=10;
        }
        if(key == 'l') // F : move left
        {
            flag_w=1;
        }
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
            xchange3+=10;
	}

	if(key == GLUT_KEY_LEFT)
	{

        if(xchange3>=0)
            xchange3-=10;
	}

	if(key == GLUT_KEY_END)
	{

	}
	//place your codes for other keys here
}

//turns off firing ammo
void fire_off()
{
    flag_w=0;
}

void backbutton()
{
    iShowBMP2(WIDTH-160, 8, buttonimages[5], 0);
}


/*This function moves the ghost. the variables xchange and ychange here are positions which move. Better the coder remove it and add a new function*/
void ghostmove()
{
	xchange += dx;
	xchange2+= dx2;

	if(xchange > WIDTH -50|| xchange < 0)dx = -dx;
	if(ychange > HEIGHT || ychange < 0)dy = -dy;
	if(xchange2 > WIDTH || xchange2 < 0) dx2 = 0;
	if(ychange2 > HEIGHT || ychange2 < 0)dy2 = 0;
}

/*this function loads the data from the file to the structure at the begining of the program*/
int structload()
{
    file=fopen("bin\\Debug\\resources\\PLAYERDATA.txt", "r");

    if(file==NULL)
    {
        printf("error in file reading\n");
        return -1;
    }
    for(i=0; i<5; i++)
    {
        fscanf(file, "%s %s %s",player[i].serial, player[i].name, player[i].score);
    }
    fclose(file);
}



//this function converts numbers to chars
void numtocharconvert(int num, char *p)
{
    int i, numlen=1, temp= num;
    do
    {
        temp/=10;
        numlen++;
    }while(temp);

    char ch[numlen];
    for(i=0; i<numlen-1; i++)
    {
        ch[i]=(num%10)+48;
        num/=10;
    }

    for(i=0; i<numlen-1; i++)
    {
        p[i]=ch[numlen-i-2];
    }

    p[numlen-1]='\0';

    return;
}

//this function converts chars to numbers
int chartonumconvert(char * ch)
{
    int len=strlen(ch);
    int i, num=0;

    for(i=0; i<len; i++)
    {
        num=(num*10)+ch[i]-48;
    }
    return num;
}

//this function gets the score of the
int main()
{
	//place your own initialization codes here.
	iSetTimer(200, ghostmove);
    iSetTimer(500, fire_off);

    structload();       //loads the file inside the structure
    //DWORD screenwidth = GetSystemMetrics(SM_CXSCREEN);
    //DWORD screenheight = GetSystemMetrics(SM_CYSCREEN);



	iInitialize(WIDTH, HEIGHT, "GameName");     //someone find a game name, PLEASE

	return 0;
}
