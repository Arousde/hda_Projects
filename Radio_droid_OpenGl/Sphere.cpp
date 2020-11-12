/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sphere.cpp
 * Author: arous
 * 
 * Created on 6. Mai 2018, 20:15
 */

#include <stddef.h>
#include <GL/gl.h>
#include <GL/freeglut_std.h>

#include "Sphere.h"

Sphere::Sphere() {
}
Sphere::Sphere(double radius, double posx, double posy, double posz, double scalex, double scaley, double scalez, double red, double green, double blue, double alpha) {
	this->radius = radius;
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

	this->degree = NULL;
}


Sphere::Sphere(const Sphere& orig) {
}

Sphere::~Sphere() {
}

void Sphere::setColorInit(double red, double green, double blue, double alpha) {
	this->red = red;
	this->blue = blue;
	this->green = green;
	this->alpha = alpha;
}

void Sphere::animate(double value) {

}

void Sphere::renderScene() { 
	glPushMatrix();
	glTranslatef(this->posx, this->posy, this->posz);
	if (this->degree != NULL)
		glRotatef(this->degree, this->rotatex, this->rotatey, this->rotatez);
        glScalef(this->scalexInit, this->scaleyInit, this->scalezInit);
	glColor4f(this->red, this->green, this->blue, this->alpha);
	glutSolidSphere(this->radius, 80., 80.);
	
	glPopMatrix();
}

void Sphere::rotate(double degree, double rotatex, double rotatey, double rotatez) {
	this->degree = degree;
	this->rotatex = rotatex;
	this->rotatey = rotatey;
	this->rotatez = rotatez;
}


