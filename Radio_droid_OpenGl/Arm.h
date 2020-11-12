/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arm.h
 * Author: arous
 *
 * Created on 8. Mai 2018, 14:22
 */

#ifndef ARM_H
#define ARM_H

#include "GlutObjparent.h"
#include "Cube.h"
#include "Sphere.h"
#include "Hand.h"
class Arm : public GlutObjparent {
public:
    Arm(double posx, double posy, double posz);
    Arm(const Arm& orig);
    Arm();
    virtual ~Arm();

    void animate(double value);
    void renderScene();

    void Armhoch();
Hand* getHand() const {
        return hand;
    }
private:
    Sphere *schulterRight, *schulterLeft;
  //  Cube *unterArmLeft,  *unterArmRight ,*oberArmLeft, *oberArmRight; 
    double posx, posy, posz;
    double degree, rotatex, rotatey, rotatez;
    double armrotation = 0.0;
    double handrotation = 0.0;
    double armswingvelocity = 2.5;
    bool armrotationdirection = true;
    bool armHoch;
   float x=0.07 ,y=0.09; 
    void animateArmRotation();
    

      Hand* hand;
      Cube *unterArm,*oberArm;
      Sphere *ellebogen;
};

#endif /* ARM_H */

