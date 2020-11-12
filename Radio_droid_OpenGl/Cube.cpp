/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cube.cpp
 * Author: arous
 * 
 * Created on 6. Mai 2018, 16:59
 */

#include <stddef.h>
#include <GL/gl.h>
#include <GL/freeglut_std.h>

#include "Cube.h"

Cube::Cube() {
}

Cube::Cube(double size, double posx, double posy, double posz, double scalex, double scaley, double scalez, double red, double green, double blue, double alpha) {

    this->size = size;
	this->posx = posx;
	this->posy = posy;
	this->posz = posz;
	this->scalexInit = scalex;
	this->scaleyInit = scaley;
	this->scalezInit = scalez;
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;

	this->degreeInit = NULL;
	this->transxInit = NULL;
	this->transyInit = NULL;
	this->transzInit = NULL;

	this->degree = NULL;
	this->rotatex = NULL;
	this->rotatey = NULL;
	this->rotatez = NULL;
}


//Cube::Cube(double size, double posx, double posy, double posz, double scalex, double scaley, double scalez, double red, double green, double blue, double alpha, double degree , double  rotatex,double  rotatey,double rotatez) {
//
//    this->size = size;
//	this->posx = posx;
//	this->posy = posy;
//	this->posz = posz;
//	this->scalexInit = scalex;
//	this->scaleyInit = scaley;
//	this->scalezInit = scalez;
//        this->red = red;
//        this->green = green;
//        this->blue = blue;
//        this->alpha = alpha;
//
//	this->degreeInit = NULL;
//	this->transxInit = NULL;
//	this->transyInit = NULL;
//	this->transzInit = NULL;
//
//	this->degree = degree;
//	this->rotatex = rotatex;
//	this->rotatey = rotatey;
//	this->rotatez = rotatez;
//}



Cube::Cube(const Cube& orig) {
}

Cube::~Cube() {
}

void Cube::animate(double value) {

}

void Cube::renderScene() {
        glPushMatrix();
	if (this->degree != NULL) {
		glRotatef(this->degree, this->rotatex, this->rotatey, this->rotatez);
	}
	if (this->transxInit != NULL || this->transyInit != NULL || this->transzInit != NULL)
		glTranslatef(this->transxInit, this->transyInit, this->transzInit);
	
	glScalef(this->scalexInit, this->scaleyInit, this->scalezInit);
         if (this->degreeInit != NULL)
		glRotatef(this->degreeInit, this->rotatexInit, this->rotateyInit, this->rotatezInit);
	glTranslatef(this->posx, this->posy, this->posz);
       
        glColor4f(red, green, blue, alpha);
	glutSolidCube(this->size);
	glPopMatrix();
}

void Cube::rotate(double degree, double rotatex, double rotatey, double rotatez) {
        this->degree = degree;
	this->rotatex = rotatex;
	this->rotatey = rotatey;
	this->rotatez = rotatez;
}

void Cube::rotateInit(double degree, double rotatex, double rotatey, double rotatez) {
        this->degreeInit = degree;
	this->rotatexInit = rotatex;
	this->rotateyInit = rotatey;
	this->rotatezInit = rotatez;
}

void Cube::translateInit(double transx, double transy, double transz) {
        this->transxInit = transx;
	this->transyInit = transy;
	this->transzInit = transz;
}
