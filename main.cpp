
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <string>
#include <vector>
#include <iostream>
#include "RgbImage.hpp"
#include "structs.hpp"

int i = 1;
int frameCount;
bool anim=false;
RgbImage imag;
using namespace std;
vector<char> pressed;
vector<particles*> snow_v;
vector< vector <int> > skyboxTextures;
bool atTemple = false;
bool snow;

GLfloat transp = 1;

void drawSkyBox() {
    int cube_size =70;
    // x,z,y
    vector<int> auxt;
    if(snow) {
        auxt = skyboxTextures[0];
    }
    else{
        auxt = skyboxTextures[1];
    }

    GLfloat offset=0.056f;
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[auxt[0]]);
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,offset); glVertex3f( -cube_size,  -cube_size, cube_size );
    glTexCoord2f(1.0f,1.0f);glVertex3f( cube_size,  -cube_size, cube_size );
    glTexCoord2f(offset,1.0f);glVertex3f(cube_size, -cube_size, -cube_size );
    glTexCoord2f(offset,offset);glVertex3f(-cube_size, -cube_size, -cube_size );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //back
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[auxt[2]]);
    glBegin(GL_QUADS);
    glRotatef(-90.0,0.0,0.0,1);
    glTexCoord2f(1.0f,offset);   glVertex3f(cube_size, -cube_size, -cube_size );
    glTexCoord2f(offset,offset)   ;glVertex3f(-cube_size, -cube_size, -cube_size );
    glTexCoord2f(offset,1.0f);    glVertex3f( -cube_size,  cube_size, -cube_size );
    glTexCoord2f(1.0f,1.0f);    glVertex3f( cube_size,  cube_size, -cube_size );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //front uses ft
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[auxt[5]]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f,offset);glVertex3f(-cube_size, -cube_size, cube_size );
    glTexCoord2f(offset,offset);glVertex3f( cube_size,  -cube_size, cube_size );
    glTexCoord2f(offset,1.0f);glVertex3f( cube_size,  cube_size, cube_size );
    glTexCoord2f(1.0f,1.0f); glVertex3f(-cube_size, cube_size, cube_size );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //left uses lf
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[auxt[3]]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f,offset);glVertex3f(-cube_size, -cube_size, -cube_size );
    glTexCoord2f(offset,offset);glVertex3f(-cube_size,  -cube_size, cube_size );
    glTexCoord2f(offset,1.0f); glVertex3f(-cube_size,  cube_size, cube_size );
    glTexCoord2f(1.0f,1.0f);glVertex3f(-cube_size, cube_size, -cube_size );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[auxt[4]]);
    glBegin(GL_QUADS);
    glTexCoord2f(offset,offset);glVertex3f(cube_size, -cube_size, -cube_size );
    glTexCoord2f(1.0f,offset);glVertex3f(cube_size,  -cube_size, cube_size );
    glTexCoord2f(1.0f,1.0f);glVertex3f(cube_size,  cube_size, cube_size );
    glTexCoord2f(offset,1.0f);glVertex3f(cube_size, cube_size, -cube_size );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //up
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[auxt[1]]);
    glBegin(GL_QUADS);
    glTexCoord2f(offset,1.0f  ); glVertex3f(-cube_size, cube_size, -cube_size );
    glTexCoord2f(1.0f,1.0f );glVertex3f( -cube_size, cube_size, cube_size );
    glTexCoord2f( 1.0f,offset);glVertex3f( cube_size, cube_size, cube_size );
    glTexCoord2f( offset,offset);glVertex3f(cube_size, cube_size, -cube_size );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawLamp() {
    glPushMatrix();

    glTranslatef(6,5.5,20);
    glRotatef(-90, 1, 0, 0);
    glutSolidSphere(0.8, 500, 500);
    glTranslatef(0, 0, 6);
    glPopMatrix();
    glPushMatrix();
    glLineWidth(5);
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex3f(6,5.5,20);
    glVertex3f(6,7.5,20);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(6,5.5,7);
    glRotatef(-90, 1, 0, 0);
    glutSolidSphere(0.8, 500, 500);
    glTranslatef(0, 0, 6);
    glPopMatrix();
    glPushMatrix();
    glLineWidth(5);
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex3f(6,5.5,7);
    glVertex3f(6,7.5,7);
    glEnd();
    glPopMatrix();
}

void criaDefineTexturas(){

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


    //----------------------------------------- Chao y=0
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexEnvf(GL_TEXTURE_ENV, GL_MODULATE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/materials/chao.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());


    //----------------------------------------- Front y=0
    glGenTextures(1, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/materials/stone.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());


    //----------------------------------------- Side
    glGenTextures(1, &texture[5]);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/materials/side.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    skyboxTextures.push_back(vector<int>());
    skyboxTextures.push_back(vector<int>());
    //----------------------------------------- ceu dia
    glGenTextures(1, &texture[6]);
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    skyboxTextures[0].push_back(6);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    imag.LoadBmpFile("images/sky/down.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    //----------------------------------------- ceu dia
    glGenTextures(1, &texture[7]);
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    skyboxTextures[0].push_back(7);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/sky/up.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    //----------------------------------------- ceu dia
    glGenTextures(1, &texture[8]);
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    skyboxTextures[0].push_back(8);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/sky/bk.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    //----------------------------------------- ceu dia
    glGenTextures(1, &texture[9]);
    glBindTexture(GL_TEXTURE_2D, texture[9]);
    skyboxTextures[0].push_back(9);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/sky/lf.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    //----------------------------------------- ceu dia
    glGenTextures(1, &texture[10]);
    glBindTexture(GL_TEXTURE_2D, texture[10]);
    skyboxTextures[0].push_back(10);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/sky/rt.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    //----------------------------------------- ceu dia
    glGenTextures(1, &texture[11]);
    glBindTexture(GL_TEXTURE_2D, texture[11]);
    skyboxTextures[0].push_back(11);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/sky/ft.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    //----------------------------------------- fanta
    glGenTextures(1, &texture[12]);
    glBindTexture(GL_TEXTURE_2D, texture[12]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/latas/fanta.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    glGenTextures(1, &texture[13]);
    glBindTexture(GL_TEXTURE_2D, texture[13]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/latas/lipton.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());


    glGenTextures(1, &texture[14]);
    glBindTexture(GL_TEXTURE_2D, texture[14]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/latas/sumol.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    glGenTextures(1, &texture[15]);
    glBindTexture(GL_TEXTURE_2D, texture[15]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/latas/sprite.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    glGenTextures(1, &texture[16]);
    glBindTexture(GL_TEXTURE_2D, texture[16]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/latas/pepsi.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    glGenTextures(1, &texture[17]);
    glBindTexture(GL_TEXTURE_2D, texture[17]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/latas/7up.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());


    //----------------------------------------- cocacola y=0
    glGenTextures(1, &texture[18]);
    glBindTexture(GL_TEXTURE_2D, texture[18]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/latas/cocacola.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    // NEVE


    glGenTextures(1, &texture[19]);
    glBindTexture(GL_TEXTURE_2D, texture[19]);
    skyboxTextures[1].push_back(19);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/snow/alps_dn.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    glGenTextures(1, &texture[20]);
    glBindTexture(GL_TEXTURE_2D, texture[20]);
    skyboxTextures[1].push_back(20);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/snow/alps_up.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    glGenTextures(1, &texture[21]);
    glBindTexture(GL_TEXTURE_2D, texture[21]);
    skyboxTextures[1].push_back(21);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/snow/alps_bk.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    glGenTextures(1, &texture[22]);
    glBindTexture(GL_TEXTURE_2D, texture[22]);
    skyboxTextures[1].push_back(22);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/snow/alps_lf.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    glGenTextures(1, &texture[23]);
    glBindTexture(GL_TEXTURE_2D, texture[23]);
    skyboxTextures[1].push_back(23);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/snow/alps_rt.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    glGenTextures(1, &texture[24]);
    glBindTexture(GL_TEXTURE_2D, texture[24]);
    skyboxTextures[1].push_back(24);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("images/snow/alps_ft.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());


}

void initLights(){
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  matAmbiente1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  matDifusa1);
    glLightfv(GL_LIGHT0, GL_SPECULAR,  matEspecular1);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  0.005);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,  0.06);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.05);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  matAmbiente2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  matDifusa2);
    glLightfv(GL_LIGHT1, GL_SPECULAR,  matEspecular2);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,  0.005);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION,  0.06);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.05);
    glEnable(GL_LIGHT1);
}

void snowStart() {
    for(int i = 0; i < MAX ; i++){
        particles* par;
        par = (particles*)malloc(sizeof(particles));
        par->xpos = (float) (rand() % 140)-70;
        par->ypos = (float) (rand() % 20)+25;
        while(true) {
            par->zpos = (float) (rand() % 140)-70;
            if(par->xpos > 12 || par->xpos <0)
                break;
            else{
                if(par->zpos > 20 || par->zpos < 0) break;
            }

        }

        par->gravity = 3 + (rand()% 4);
        snow_v.push_back(par);
    }
};

void init(void) {
    obsP[0]=6;
    obsP[1]=4;
    obsP[2]=200;
    glClearColor(0,0,0,1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_STENCIL_TEST);
    genRandomTex();
    initColors();
    snowStart();
    criaDefineTexturas();
    initLights();
    snow = true;
}

void drawSnow() {
    float x, y, z;
    int j;
    for (j = 0; j < 5000; j++) {
        particles* curr = (snow_v[j]);

            x = curr->xpos;
            y = curr->ypos;
            z = curr->zpos;

            // Draw particles
            glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            glTranslatef(x, y, z);
            glutSolidSphere(0.1, 8, 8);
            glPopMatrix();

            //Move
            curr->ypos -= curr->gravity;


            //Revive
            if (curr->ypos < -20) {
                curr->ypos = (float) (rand() % 10)+20;
                curr->gravity = 3 + (rand()% 4);
            }
    }
}

void initColors() {
    srand (time(NULL));
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==0)
                colors[i][j]=r[j];
            if(i==1)
                colors[i][j]=g[j];
            if(i==2)
                colors[i][j]=b[j];
        }
    }
    for(int i=0;i<3;i++){
        random_p[i] = rand()%3;
        if(random_p[i]==0){
            letters[i] = 'r';
            cout << "r"<< endl;
        }
        else if(random_p[i]==1){
            letters[i] = 'g';
            cout << "g"<< endl;
        }
        else if(random_p[i]==2){
            letters[i] = 'b';
            cout << "b"<< endl;
        }
    }
}

void genRandomTex() {
    int rand_n;
    srand (time(NULL));
    for(int i =0;i<30;i++){
        rand_n = rand() % 7 + 12;
        latasAtuais[i] = rand_n;
    }
}

void resizeWindow(GLsizei w, GLsizei h) {

    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void drawScene(){
    if(started) {
        i += 0.4;
        obsP[2] -= 0.5 * i;

        if (obsP[2] < 31.196) {
            started = false;
            atTemple = true;
        }

        if(obsP[2]<100 && luzGlobalCor[0]> 0.2){
            luzGlobalCor[0]-= 0.006;
            luzGlobalCor[1]-= 0.006;
            luzGlobalCor[2]-= 0.006;
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
        }
        else
            anim=true;
    }
    else{
        if(anim) {
            luzGlobalCor[0] += 0.009;
            luzGlobalCor[1] += 0.009;
            luzGlobalCor[2] += 0.009;
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
        }
        if(luzGlobalCor[0]>= 0.8){
            anim=false;
        }
        if(playing){
                if(ok)
                    drawSpheres();
            glColor3fv(g);
            glRasterPos3f(-9,-10,180);
            string a;
            a = "Insere agora a sequencia usando as teclas R G B";
            int len, i;
            len = a.size();
            for (i = 0; i < len; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, a[i]);
            }
            glRasterPos3f(-4,-10,185);
            string b = "Se ainda nao for desta, tenta mais uma vez!";
            len = b.size();
            for (i = 0; i < len; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, b[i]);
            }


        }
        else{
            glColor3fv(g);
            glRasterPos3f(-2.5,-10,185);
            string a;
            a = "Tecla 'y' para comecares a aventura";
            int len, i;
            len = a.size();
            for (i = 0; i < len; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, a[i]);
            }
            glRasterPos3f(-8,-10,181);
            a = "Vao aparecer 3 cores no ecra, tenta lembrar-te delas";
            len = a.size();
            for (i = 0; i < len; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, a[i]);
            }
        }

    }
    if(atTemple){
        //ciclo de dia e noite
        frameCount++;
        if(frameCount < 250){
            if(luzGlobalCor[0] <0.9){
                luzGlobalCor[0] += 0.009;
                luzGlobalCor[1] += 0.009;
                luzGlobalCor[2] += 0.009;
                glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
            }
        }else{
            if(luzGlobalCor[0] >0.1) {
                luzGlobalCor[0] -= 0.009;
                luzGlobalCor[1] -= 0.009;
                luzGlobalCor[2] -= 0.009;
                glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
            }
        }
        if(frameCount == 500){
            //TROCAR TEXTURA
            snow = !snow;
            //REINICIAR DIA
            frameCount=0;
        }

    }
    glLightfv(GL_LIGHT0, GL_POSITION, AmbLightPos);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,down);
    glLightfv(GL_LIGHT1, GL_POSITION, AmbLightPos2);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,down);

    glPushMatrix();
    drawLamp();
    glPopMatrix();

    drawSkyBox();

    drawTemple();

    glEnd();
    if(!snow)
        drawSnow();
}

void drawTemple() {
    GLUquadricObj*  y = gluNewQuadric ( );
    GLfloat floor_size = 0.0005;
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    for(int j=0;j<15;j++){
        for(int i=0;i<30;i++){
            glTranslatef(floor_size,0,0);
            glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);
            glColor4f(1,1,1,1);
            glTexCoord2f(0.0f, 0.0f);	glVertex3f(0,  0, 0);
            glTexCoord2f(0.0f, 20.0f);	glVertex3f(xC, 0, 0 );
            glTexCoord2f(20.0f, 20.0f);	glVertex3f(xC, 0, yC);
            glTexCoord2f(20.0f, 0.0f);	glVertex3f(0,  0,  yC);
            glEnd();
        }
    }
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //back
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[3]);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f,0.0f); glVertex3f( 0.3,  7.2, 0.3 );
    glTexCoord2f(2.5f,0.0f); glVertex3f(11.7, 7.2, 0.3 );
    glTexCoord2f(1.25f,2.5f); glVertex3f( 5.7, 10.5, 0.3 );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //front
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[3]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f,0.0f); glVertex3f( 0.3,  7.2, yC-0.3 );
    glTexCoord2f(2.5f,0.0f); glVertex3f(11.7, 7.2, yC-0.3 );
    glTexCoord2f(1.25f,2.5f); glVertex3f( 5.7, 10.5, yC-0.3 );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //side
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[5]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f); glVertex3f( 0.3,  7.2, 0.3 );
    glTexCoord2f(17.0f,0.0f); glVertex3f( 5.7, 10.5, 0.3 );
    glTexCoord2f(17.0f,17.0f); glVertex3f( 5.7, 10.5, yC-0.3 );
    glTexCoord2f(0.0f,17.0f); glVertex3f( 0.3,  7.2, yC-0.3 );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //side
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f); glVertex3f(11.7, 7.2, 0.3 );
    glTexCoord2f(17.0f,0.0f); glVertex3f( 5.7, 10.5, 0.3 );
    glTexCoord2f(17.0f,17.0f); glVertex3f( 5.7, 10.5, yC-0.3 );
    glTexCoord2f(0.0f,17.0f); glVertex3f(11.7, 7.2, yC-0.3 );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // interior
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f); glVertex3f( 0.3,  7.2, 0.3 );
    glTexCoord2f(17.0f,0.0f); glVertex3f( 0.3,  7.2, yC-0.3 );
    glTexCoord2f(17.0f,17.0f); glVertex3f(11.7, 7.2, yC-0.3 );
    glTexCoord2f(0.0f,17.0f); glVertex3f(11.7, 7.2, 0.3 );
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    // == latas ==

    glEnable(GL_COLOR_MATERIAL);
    glColor4f(1,1,1,transp);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    int dif=2;
    int rand_n;
    int count=0;
    for(int i=0;i<12;i++){
        glEnable(GL_TEXTURE_2D);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        if(randomize) {
            rand_n = rand() % 7 + 12;
            latasAtuais[count] = rand_n;
            glBindTexture(GL_TEXTURE_2D,texture[rand_n]);

        }
        else
            glBindTexture(GL_TEXTURE_2D,texture[latasAtuais[count]]);
        glPushMatrix();
        glTranslatef (1,0.2,1+i*dif);
        glRotatef (-90, 1, 0, 0);
        gluQuadricDrawStyle ( y, GLU_FILL   );
        gluQuadricNormals   ( y, GLU_SMOOTH );
        gluQuadricTexture   ( y, GL_TRUE    );
        gluCylinder( y, 0.6, 0.6, 7, 100, 100);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        count++;
    }
    gluDeleteQuadric ( y );
    y = gluNewQuadric ( );

    for(int i=0;i<6;i++){
        rand_n = rand()%7+12;
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        if(randomize) {
            rand_n = rand() % 7 + 12;
            latasAtuais[count] = rand_n;
            glBindTexture(GL_TEXTURE_2D,texture[rand_n]);
        }
        else
            glBindTexture(GL_TEXTURE_2D,texture[latasAtuais[count]]);
        glPushMatrix();
        glTranslatef (1+i*dif,0.2,1);
        glRotatef (-90, 1, 0, 0);
        gluQuadricDrawStyle ( y, GLU_FILL   );
        gluQuadricNormals   ( y, GLU_SMOOTH );
        gluQuadricTexture   ( y, GL_TRUE    );
        gluCylinder( y, 0.6, 0.6, 7, 100, 100);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        if(i!=0)
            count++;
    }
    gluDeleteQuadric ( y );
    y = gluNewQuadric ( );

    for(int i=0;i<11;i++){
        rand_n = rand()%7+12;
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        if(randomize) {
            rand_n = rand() % 7 + 12;
            latasAtuais[count] = rand_n;
            glBindTexture(GL_TEXTURE_2D,texture[rand_n]);
        }
        else
            glBindTexture(GL_TEXTURE_2D,texture[latasAtuais[count]]);
        glPushMatrix();
        glTranslatef (11,0.2,3+i*dif);
        glRotatef (-90, 1, 0, 0);
        gluQuadricDrawStyle ( y, GLU_FILL   );
        gluQuadricNormals   ( y, GLU_SMOOTH );
        gluQuadricTexture   ( y, GL_TRUE    );
        gluCylinder( y, 0.6, 0.6, 7, 100, 100);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        count++;
    }

    gluDeleteQuadric ( y );
    y = gluNewQuadric ( );
    for(int i=0;i<4;i++){
        rand_n = rand()%7+12;
        if(i!=1 && i!=2) {
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            if(randomize) {
                rand_n = rand() % 7 + 12;
                latasAtuais[count] = rand_n;
                glBindTexture(GL_TEXTURE_2D,texture[rand_n]);
            }
            else{
                glBindTexture(GL_TEXTURE_2D,texture[latasAtuais[count]]);
            }
            glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, woodAmb);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, woodDif);
            glMaterialfv(GL_FRONT, GL_SPECULAR, woodSpec);
            glMaterialf(GL_FRONT, GL_SHININESS, woodCoef);
            glTranslatef(3 + i * dif, 0.2, 23);
            glRotatef(-90, 1, 0, 0);
            gluQuadricDrawStyle(y, GLU_FILL);
            gluQuadricNormals(y, GLU_SMOOTH);
            gluQuadricTexture(y, GL_TRUE);
            gluCylinder(y, 0.6, 0.6, 7, 100, 100);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            count++;
        }
    }

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);


}

void drawSpheres() {
    GLfloat v1[] = {1.0, 1.0, 1.0};
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3fv(colors[random_p[0]]);
    glTranslatef(-13, 23, 180);
    glRotatef(-90, 1, 0, 0);
    glutSolidSphere(5, 15, 15);
    glColor3fv(v1);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3fv(colors[random_p[1]]);
    glTranslatef(6, 23, 180);
    glRotatef(-90, 1, 0, 0);
    glutSolidSphere(5, 15, 15);
    glColor3fv(v1);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3fv(colors[random_p[2]]);
    glTranslatef(25, 23, 180);
    glRotatef(-90, 1, 0, 0);
    glutSolidSphere(5, 15, 15);
    glColor3fv(v1);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    ok=false;
}

void display(void){

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Apagar ]
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glShadeModel(GL_SMOOTH);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Janela Visualizacao ]
    glViewport (0,0,wScreen, hScreen);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Projeccao]
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    switch (defineProj) {
        case 1: gluPerspective(110, wScreen/hScreen, 0.5, 5*zC); break;
        default: glOrtho (-xC,xC,-yC,yC,-zC,zC);
            break;
    }

    //[ Modelo+View(camera/observador) ]
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsP[0], obsP[1], obsP[2], lx,ly,lz, 0, 1, 0);

    drawScene();

    //Actualizacao
    glutSwapBuffers();
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(msec,Timer, 1);
}

void keyboard(unsigned char key, int x, int y) {
    int count=0;
    if(playing){
        pressed.push_back(key);
        if(pressed.size()==3){
            playing=false;
            for(int i=0;i<3;i++){
                if(pressed[i]==letters[i]){
                    count ++;
                }
            }
            if(count==3){
                started=true;
            }
            else{
                initColors();
                ok=true;
            }
        }
    }


    switch (key) {
        case 'y':
            playing=true;
            pressed.clear();
            break;

        case 'k':
            started = true;
            break;

        case 'j':
            if(randomize)
                randomize = false;
            else
                randomize =true;
            break;

        case 'p':
            if(luzGlobalCor[0]<1){
                luzGlobalCor[0] = static_cast<GLfloat>(luzGlobalCor[0] + 0.05);
            }
            if(luzGlobalCor[1]<1){
                luzGlobalCor[1] = static_cast<GLfloat>(luzGlobalCor[1] + 0.05);
            }
            if(luzGlobalCor[2]<1){
                luzGlobalCor[2] = static_cast<GLfloat>(luzGlobalCor[2] + 0.05);
            }
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
            glutPostRedisplay();
            break;

        case 'o':
            if(luzGlobalCor[0]>0){
                luzGlobalCor[0] = static_cast<GLfloat>(luzGlobalCor[0] - 0.05);
            }
            if(luzGlobalCor[1]>0){
                luzGlobalCor[1] = static_cast<GLfloat>(luzGlobalCor[1] - 0.05);
            }
            if(luzGlobalCor[2]>0){
                luzGlobalCor[2] = static_cast<GLfloat>(luzGlobalCor[2] - 0.05);
            }

            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
            glutPostRedisplay();
            break;
        case 'u':
            if(transp>0.2)
                transp-=0.1;
            break;
        case 'i':
            if(transp<1)
                transp+=0.1;
            break;

        case 27:
            exit(0);
            break;
    }
}

void teclasNotAscii(int key, int x, int y){
    if(key == GLUT_KEY_UP)
        obsP[1]=obsP[1]+incy;
    if(key == GLUT_KEY_DOWN)
        obsP[1]=obsP[1]-incy;
    if(key == GLUT_KEY_LEFT)
        angulo=angulo+inca;
    if(key == GLUT_KEY_RIGHT)
        angulo=angulo-inca;

    if (obsP[1]> yC)
        obsP[1]= yC;
    if (obsP[1]<-yC)
        obsP[1]=-yC;
    obsP[0] = raio*cos(angulo);
    obsP[2] = raio*sin(angulo);
}

void idle ( ) {
    glutPostRedisplay();
}


int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (1000, 1000);
    glutInitWindowPosition(0, 0);

    glutCreateWindow ("        ========== O TEMPLO ==========");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    init();


    glutDisplayFunc(display);
    glutSpecialFunc(teclasNotAscii);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutTimerFunc(msec, Timer, 1);
    glutMainLoop();

    return 0;
}

