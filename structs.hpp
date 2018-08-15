#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <string>
#include <vector>
#include <iostream>


#define PI 3.14159

#define MAX 5000

typedef struct {
    float xpos;
    float ypos;
    float zpos;
    float vel;
    float gravity;
}particles;


GLfloat r[] = {1.0,0.0,0.0};
GLfloat g[] = {0.0,1.0,0.0};
GLfloat b[] = {0.0,0.0,1.0};
GLfloat colors[3][3];
GLint random_p[3];
char letters[3];

bool started;
bool randomize;
bool playing=false;
bool ok =true;

//Sistema Coordenadas
GLfloat   xC=12.0, yC=24.0, zC=30.0;
GLint     wScreen=800, hScreen=600;


// Observador
GLint    defineProj=1;
GLfloat  raio   = 31.75;
GLfloat  angulo = 0.42*PI;
GLfloat  obsP[3] ;
GLdouble lx=6,ly=3,lz;
GLfloat  incy   = 0.5;
GLfloat  inca   = 0.03;

GLint    msec=10;
GLuint  texture[25];



GLfloat luzGlobalCor[4] = { 0.9,0.9,0.9,1 };

GLfloat AmbLightPos[4] = {6,1.5,20,1 };
GLfloat matAmbiente1[] = {0.0,0.0,1.0,1.0};
GLfloat matDifusa1[]   = {1.0,1.0,1.0,1.0};
GLfloat matEspecular1[]= {1.0, 1.0, 1.0, 1.0};

GLfloat AmbLightPos2[4] = {6,5.5,7,1 };
GLfloat matAmbiente2[] = {1.0,0.0,0.0,1.0};
GLfloat matDifusa2[]   = {1.0,1.0,1.0,1.0};
GLfloat matEspecular2[]= {1.0, 1.0, 1.0, 1.0};

GLfloat down[] = {0,-1,0,1};

GLfloat  woodAmb[] = { 0.54725 ,0.54725 ,0.54725 ,1};
GLfloat  woodDif[] = { 0.35164 ,0.35164  ,0.35164,1};
GLfloat  woodSpec[] = { 0.45678 ,0.45678 ,0.45678,1};
GLint  woodCoef = static_cast<GLint>(0.7 * 128);

int latasAtuais[30];




void drawTemple();
void drawSpheres();
void drawSkyBox();
void genRandomTex();
void initColors();
void drawLamp();
void criaDefineTexturas();
void initLights();
void init(void);
void keyboard(unsigned char key, int x, int y);
void teclasNotAscii(int key, int x, int y);