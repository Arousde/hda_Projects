/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cube.h
 * Author: arous
 *
 * Created on 6. Mai 2018, 16:59
 */

#ifndef CUBE_H
#define CUBE_H

#include "GlutObjparent.h"


class Cube : public GlutObjparent{
public:
    Cube();
    Cube(double size, double posx, double posy, double posz, double scalex, double scaley, double scalez, double red, double green, double blue, double alpha);
    
    Cube(const Cube& orig);
    virtual ~Cube();
    void animate(double value);
	void renderScene();
   
	void translateInit(double transx, double transy, double transz);
	void rotateInit(double degree, double rotatex, double rotatey, double rotatez);

	void rotate(double degree, double rotatex, double rotatey, double rotatez);

private:
	double size;
	double posx, posy, posz;
	double scalexInit, scaleyInit, scalezInit;
        double red, green, blue, alpha;
	double degreeInit, rotatexInit, rotateyInit, rotatezInit;
	double transxInit, transyInit, transzInit;
	double degree, rotatex, rotatey, rotatez;


};

#endif /* CUBE_H */

