/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sphere.h
 * Author: arous
 *
 * Created on 6. Mai 2018, 20:15
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "GlutObjparent.h"


class Sphere : public GlutObjparent {
public:
    Sphere();
    Sphere(double radius, double posx, double posy, double posz, double scalex, double scaley, double scalez, double red, double green, double blue, double alpha);
    
    Sphere(const Sphere& orig);
    virtual ~Sphere();
    void animate(double value);
    
    void renderScene();
    void rotate(double degree, double rotatex, double rotatey, double rotatez);

    void setColorInit(double red, double green, double blue, double alpha);
    
    
private:
double radius;
	double posx, posy, posz;
	double red, green, blue, alpha;
	double degree, rotatex, rotatey, rotatez;
        double scalexInit, scaleyInit, scalezInit;
};

#endif /* SPHERE_H */

