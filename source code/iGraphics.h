/*
	author: S. M. Shahriar Nirjon
	last modified: March 12, 2008
*/

/* Modified by Prof. Ashikur Rahman
   for BMP file loading in CodeBlocks
   Last modified: April 27 2017
*/

// structure added by Prof. Ashikur Rahman

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

typedef struct Image Image;



# include <stdio.h>
# include <stdlib.h>
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")
#include <gl/glut.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <gl\glaux.h>

int iScreenHeight, iScreenWidth;
int iMouseX, iMouseY;
int ifft=0;
void (*iAnimFunction[10])(void)={0};
int iAnimCount=0;
int iAnimDelays[10];
int iAnimPause[10];


void iDraw();
void iKeyboard(unsigned char);
void iSpecialKeyboard(unsigned char);
void iMouseMove(int, int);
void iMouse(int button, int state, int x, int y);

static void  __stdcall iA0(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[0])iAnimFunction[0]();}
static void  __stdcall iA1(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[1])iAnimFunction[1]();}
static void  __stdcall iA2(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[2])iAnimFunction[2]();}
static void  __stdcall iA3(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[3])iAnimFunction[3]();}
static void  __stdcall iA4(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[4])iAnimFunction[4]();}
static void  __stdcall iA5(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[5])iAnimFunction[5]();}
static void  __stdcall iA6(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[6])iAnimFunction[6]();}
static void  __stdcall iA7(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[7])iAnimFunction[7]();}
static void  __stdcall iA8(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[8])iAnimFunction[8]();}
static void  __stdcall iA9(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[9])iAnimFunction[9]();}

int iSetTimer(int msec, void (*f)(void))
{
	int i = iAnimCount;

	if(iAnimCount>=10){printf("Error: Maximum number of already timer used.\n");return -1;}

	iAnimFunction[i] = f;
	iAnimDelays[i] = msec;
	iAnimPause[i] = 0;

	if(iAnimCount == 0) SetTimer(0, 0, msec, iA0);
	if(iAnimCount == 1) SetTimer(0, 0, msec, iA1);
	if(iAnimCount == 2) SetTimer(0, 0, msec, iA2);
	if(iAnimCount == 3) SetTimer(0, 0, msec, iA3);
	if(iAnimCount == 4) SetTimer(0, 0, msec, iA4);

	if(iAnimCount == 5) SetTimer(0, 0, msec, iA5);
	if(iAnimCount == 6) SetTimer(0, 0, msec, iA6);
	if(iAnimCount == 7) SetTimer(0, 0, msec, iA7);
	if(iAnimCount == 8) SetTimer(0, 0, msec, iA8);
	if(iAnimCount == 9) SetTimer(0, 0, msec, iA9);
	iAnimCount++;

	return iAnimCount-1;
}

void iPauseTimer(int index){
	if(index>=0 && index <iAnimCount){
		iAnimPause[index] = 1;
	}
}

void iResumeTimer(int index){
	if(index>=0 && index <iAnimCount){
		iAnimPause[index] = 0;
	}
}


void iGetPixelColor (int cursorX, int cursorY, int rgb[])
{
	GLubyte pixel[3];
	glReadPixels(cursorX, cursorY,1,1,
		GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);

	rgb[0] = pixel[0];
	rgb[1] = pixel[1];
	rgb[2] = pixel[2];

	//printf("%d %d %d\n",pixel[0],pixel[1],pixel[2]);
}

// Added by Prof. Ashikur Rahman

int ImageLoad(char *filename, Image *image) {
        FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int plane; // number of planes in image

    unsigned short int bpp; // number of bits per pixel
    char temp; // temporary color storage for
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL){
        printf("Hey HEY\n\n\n");
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
   // printf("Width of %s: %lu\n", filename, image->sizeX);
    // read the height
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
   // printf("Height of %s: %lu\n", filename, image->sizeY);
    // read the planes
    if ((fread(&plane, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (plane != 1) {
        printf("Planes from %s is not 1: %u\n", filename, plane);
        return 0;
    }
    // read the bitsperpixel
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    int biRGB;
    // read the bitsperpixel
    if ((i = fread(&biRGB, 4, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }

    if ((i = fread(&size, 4, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }

   // printf("Size of BMP Data :%d \n",size);

    // seek past the rest of the bitmap header.
    fseek(file, 16, SEEK_CUR);


    int pad = 0; // Set pad byte count per row to zero by default.
    // Each row needs to be a multiple of 4 bytes.
    if ((image->sizeX * 3) % 4 != 0) pad = 4 - ((image->sizeX * 3) % 4); // 4 - remainder(width * 3 / 4).
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
//    int skipBytes = (4-(image->sizeX*3)%4)%4;
    size = (image->sizeX*3+pad) * image->sizeY;
//    printf("Size of BMP Data :%d %d\n",size,pad);
 //   printf("Bytes to be skipped: %d\n",pad);
    // read the data.
    char* p = (char *) malloc(size);
    if (p == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    if ((i = fread(p, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY*3;
    // read the data.
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    int j,k;
    for(i = 0,j=1,k=0; i < size;){
        image->data[i++] = p[k++];
        image->data[i++] = p[k++];
        image->data[i++] = p[k++];
        if(j == image->sizeX){
            j = 1;
            k += pad;
        }
        else j++;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }
    fclose(file);
    // we're done.
    free(p);
    return 1;
}

// Added by Prof. Ashikur Rahman

Image * loadTexture(char* filename){
    Image *image1;
    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
    printf("Error allocating space for image");
    exit(0);
    }
    //pic.bmp is a 64x64 picture
    if (!ImageLoad(filename, image1)) {
        exit(1);
    }
    return image1;
}


void iText(GLdouble x, GLdouble y, char *str, void* font=GLUT_BITMAP_8_BY_13)
{
   glRasterPos3d(x, y, 0);
   int i;
   for (i=0; str[i]; i++) {
      glutBitmapCharacter(font, str[i]); //,GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_24
   }
}

void iPoint(double x, double y, int size=0)
{
	int i, j;
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	for(i=x-size;i<x+size;i++)
	{
		for(j=y-size; j<y+size;j++)
		{
			glVertex2f(i, j);
		}
	}
	glEnd();
}
// Heavily Modified by Prof. Ashikur Rahman
//
// This is a very tricky algorithm!!!!
//
//
// Puts a BMP image on screen
//
// parameters:
//  x - x coordinate
//  y - y coordinate
//  filename - name of the BMP file
//  ignoreColor - A specified color that should not be rendered. If you have an
//                image strip that should be rendered on top of another back
//                ground image, then the background of the image strip should
//                not get rendered. Use the background color of the image strip
//                in ignoreColor parameter. Then the strip's background does
//                not get rendered.
//
//                To disable this feature, put -1 in this parameter
//
void iShowBMP2(int x, int y, char filename[], int ignoreColor)
{
    Image *TextureImage = loadTexture(filename);
    if(TextureImage == NULL){
       printf("Image was not returned from loadTexture\n");
       exit(0);
    }

    // glRasterPos2f(x, y);
    // glDrawPixels(TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);

    int i,j,k;
    int width = TextureImage->sizeX;
    int height = TextureImage->sizeY;
    int nPixels = width * height;
    //int *rgPixels = new int[nPixels];
    unsigned char *bgraBuffer = new unsigned char[nPixels*4];

    int posBgr = 0;
    int posBgra = 0;
    int pi = 0;
    for (int i = 0; i < nPixels; i++){
        pi = 0;
        pi |= TextureImage->data[posBgr];
        pi &= 0x000000FF;
        pi = (pi << 8)|TextureImage->data[posBgr+1];
        pi &= 0x0000FFFF;
        pi = (pi << 8)|TextureImage->data[posBgr+2];
        pi &= 0x00FFFFFF;
        //Sets the alpha buffer value.
        if (ignoreColor == pi){
                int rgb[3];
                iGetPixelColor (x+i%TextureImage->sizeX, y+i/TextureImage->sizeX, rgb);
                bgraBuffer[posBgra] = rgb[0];
                bgraBuffer[posBgra+1] = rgb[1];
                bgraBuffer[posBgra+2] = rgb[2];
                bgraBuffer[posBgra + 3] = 0;
        }
        else
        {
            bgraBuffer[posBgra] = TextureImage->data[posBgr];          //This is the buffer value of R.
            bgraBuffer[posBgra + 1] = TextureImage->data[posBgr + 1];  //This is the buffer value of G.
            bgraBuffer[posBgra + 2] = TextureImage->data[posBgr+2];  //This is the buffer value of B.
            bgraBuffer[posBgra + 3] = 255;
        }
        //bgraBuffer[posBgra + 3] = 0;
        posBgr += 3;
        posBgra += 4;
}

    glRasterPos2f(x, y);
    glDrawPixels(TextureImage->sizeX, TextureImage->sizeY, GL_RGBA, GL_UNSIGNED_BYTE, bgraBuffer);

    /*for(i = 0; i < TextureImage->sizeY; i++){
        glRasterPos2f(x, y+i);
        glDrawPixels(TextureImage->sizeX, 1, GL_RGBA, GL_UNSIGNED_BYTE, bgraBuffer+i*4*TextureImage->sizeX);
    }*/
   // glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, bgraBuffer);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureImage->sizeX, TextureImage->sizeY, 0, GL_BGR(A)_EXT GL.GL_UNSIGNED_BYTE, pBgraBuffer);glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgPixels);

    delete []bgraBuffer;
    free(TextureImage->data);
    free(TextureImage);
}

void iShowBMP(int x, int y, char filename[])
{
    //Commented out by Prof. Ashikur Rahman

//	AUX_RGBImageRec *TextureImage;

//	TextureImage = auxDIBImageLoad(filename);

    // Added by Prof. Ashikur Rahman

//    Image *TextureImage = loadTexture(filename);
//    if(TextureImage == NULL){
//       printf("Image was not returned from loadTexture\n");
//       exit(0);
//    }

     //Following was like before from Nirjon

 //    glRasterPos2f(x, y);
 //    glDrawPixels(TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE,TextureImage->data);//The change is here GL_UNSIGNED_BYTE,

//	free(TextureImage->data);
//	free(TextureImage);

   iShowBMP2(x, y, filename,-1);

}



void iLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void iFilledPolygon(double x[], double y[], int n)
{
	int i;
	if(n<3)return;
	glBegin(GL_POLYGON);
	for(i = 0; i < n; i++){
		glVertex2f(x[i], y[i]);
	}
	glEnd();
}

void iPolygon(double x[], double y[], int n)
{
	int i;
	if(n<3)return;
	glBegin(GL_LINE_STRIP);
	for(i = 0; i < n; i++){
		glVertex2f(x[i], y[i]);
	}
	glVertex2f(x[0], y[0]);
	glEnd();
}

void iRectangle(double left, double bottom, double dx, double dy)
{
	double x1, y1, x2, y2;

	x1 = left;
	y1 = bottom;
	x2=x1+dx;
	y2=y1+dy;

	iLine(x1, y1, x2, y1);
	iLine(x2, y1, x2, y2);
	iLine(x2, y2, x1, y2);
	iLine(x1, y2, x1, y1);
}

void iFilledRectangle(double left, double bottom, double dx, double dy)
{
	double xx[4], yy[4];
	double x1, y1, x2, y2;

	x1 = left;
	y1 = bottom;
	x2=x1+dx;
	y2=y1+dy;

	xx[0]=x1;
	yy[0]=y1;
	xx[1]=x2;
	yy[1]=y1;
	xx[2]=x2;
	yy[2]=y2;
	xx[3]=x1;
	yy[3]=y2;

	iFilledPolygon(xx, yy, 4);

}

void iFilledCircle(double x, double y, double r, int slices=100)
{
	double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
	dt = 2*PI/slices;
	xp = x+r;
	yp = y;
	glBegin(GL_POLYGON);
	for(t = 0; t <= 2*PI; t+=dt)
	{
		x1 = x + r * cos(t);
		y1 = y + r * sin(t);

		glVertex2f(xp, yp);
		xp = x1;
		yp = y1;
	}
	glEnd();
}

void iCircle(double x, double y, double r, int slices=100)
{
	double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
	dt = 2*PI/slices;
	xp = x+r;
	yp = y;
	for(t = 0; t <= 2*PI; t+=dt)
	{
		x1 = x + r * cos(t);
		y1 = y + r * sin(t);
		iLine(xp, yp, x1, y1);
		xp = x1;
		yp = y1;
	}
}

void iEllipse(double x, double y, double a, double b, int slices=100)
{
	double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
	dt = 2*PI/slices;
	xp = x+a;
	yp = y;
	for(t = 0; t <= 2*PI; t+=dt)
	{
		x1 = x + a * cos(t);
		y1 = y + b * sin(t);
		iLine(xp, yp, x1, y1);
		xp = x1;
		yp = y1;
	}
}

void iFilledEllipse(double x, double y, double a, double b, int slices=100)
{
	double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
	dt = 2*PI/slices;
	xp = x+a;
	yp = y;
	glBegin(GL_POLYGON);
	for(t = 0; t <= 2*PI; t+=dt)
	{
		x1 = x + a * cos(t);
		y1 = y + b * sin(t);
		glVertex2f(xp, yp);
		xp = x1;
		yp = y1;
	}
	glEnd();
}


void iSetColor(double r, double g, double b)
{
	double mmx;
	mmx = r;
	if(g > mmx)mmx = g;
	if(b > mmx)mmx = b;
	mmx = 255;
	if(mmx > 0){
		r /= mmx;
		g /= mmx;
		b /= mmx;
	}
	glColor3f(r, g, b);
}

void iDelay(int sec)
{
	int t1, t2;
	t1 = time(0);
	while(1){
		t2 = time(0);
		if(t2-t1>=sec)
			break;
	}
}


void iClear()
{
	glClear( GL_COLOR_BUFFER_BIT) ;
	glMatrixMode(GL_MODELVIEW) ;
	glClearColor(0,0,0,0);
		glFlush();
}

void displayFF(void){

	//iClear();
	iDraw();
	glutSwapBuffers() ;
}



void animFF(void)
{
	//iAnimation();
	if(ifft == 0){
		ifft = 1;
		iClear();
	}
	glutPostRedisplay();
}

void keyboardHandler1FF(unsigned char key, int x, int y)
{
	iKeyboard(key);
	glutPostRedisplay();
}
void keyboardHandler2FF(int key, int x, int y)
{
	iSpecialKeyboard(key);
	glutPostRedisplay();
}

void mouseMoveHandlerFF(int mx, int my)
{
	iMouseX = mx;
	iMouseY = iScreenHeight - my;
	iMouseMove(iMouseX, iMouseY);

	glFlush();
}

void mouseHandlerFF(int button, int state, int x, int y)
{
	iMouseX = x;
	iMouseY = iScreenHeight - y;

	iMouse(button, state, iMouseX, iMouseY);

	glFlush();
}

void iInitialize(int width=500, int height=500, char *title="iGraphics")
{
	iScreenHeight = height;
	iScreenWidth = width;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;
	glutInitWindowSize(width , height ) ;
	glutInitWindowPosition( 10 , 10 ) ;
	glutCreateWindow(title) ;
	glClearColor( 0.0 , 0.0 , 0.0 , 0.0 ) ;
	glMatrixMode( GL_PROJECTION) ;
	glLoadIdentity() ;
	glOrtho(0.0 , width , 0.0 , height , -1.0 , 1.0) ;
	//glOrtho(-100.0 , 100.0 , -100.0 , 100.0 , -1.0 , 1.0) ;
	//SetTimer(0, 0, 10, timer_proc);

	iClear();

	glutDisplayFunc(displayFF) ;
	glutKeyboardFunc(keyboardHandler1FF); //normal
 	glutSpecialFunc(keyboardHandler2FF); //special keys
	glutMouseFunc(mouseHandlerFF);
	glutMotionFunc(mouseMoveHandlerFF);
	glutIdleFunc(animFF) ;

	glutMainLoop() ;
}

/*int main()
{
	iInitialize(600, 600);

	return 0 ;
}*/
