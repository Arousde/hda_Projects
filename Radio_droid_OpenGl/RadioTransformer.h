/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RadioTransformer.h
 * Author: arous
 *
 * Created on 8. Mai 2018, 15:06
 */

#ifndef RADIOTRANSFORMER_H
#define RADIOTRANSFORMER_H

#include "GlutObjparent.h"
#include "Arm.h"
#include "Sphere.h"
#include "Hand.h"

class RadioTransformer  : public GlutObjparent{
public:
    RadioTransformer(double x, double y, double z);
    RadioTransformer(const RadioTransformer& orig);
    virtual ~RadioTransformer();
    
    void animate(double value);
	void renderScene();
	void keyboardKeys(unsigned char key, int x, int y);
            Arm* getArmLeft() const {
        return armLeft;
    }

    Arm* getArmRight() const {
        return armRight;
    }



private:
        double posx, posy, posz;
	double posyinit, posxinit, poszinit;
        
        Sphere *eyeright, *innerEyeRight,*innerEyeLeft, *eyePointRight, *eyePointLeft, *eyeleft;
        Sphere *schulterLeft, *schulterRight, *ellebogenRight, *ellebogenLeft;
	Cube *btn1,*btn2,*btn3,*btn4;
        Cube *head,*door, *innerdoor, *oberArmRight, *oberArmLeft;
//      Cube *oberArmLeft, *oberArmRight; 
//        Cube *oberHandLeft, *unterHandLeft, *oberHandRight, *unterHandRight;
      Arm *armRight, *armLeft ;
               
};

#endif /* RADIOTRANSFORMER_H */

