/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arm.cpp
 * Author: arous
 * 
 * Created on 8. Mai 2018, 14:22
 */

#include <GL/gl.h>
#include <stdlib.h>

#include "Arm.h"

Arm::Arm(double posx, double posy, double posz) {
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    //    this->unterArmRight = new Cube(0.1, 0.1, 0.65, 0.0, 5., 1., 1., 0.0, 0.0, 0.0, 0.0);
    //    this->unterArmLeft = new Cube(0.1, -0.1, 0.65, 0.0, 5., 1., 1., 0.0, 0.0, 0.0, 0.0);
    //    this->oberArmRight = new Cube(0.1, 0.75, .05, 0.0, 1., 7., 1., 0.0, 0.0, 0.0, 0.0);
    //    this->oberArmLeft = new Cube(0.1, -0.75, .05, 0.0, 1., 7., 1., 0.0, 0.0, 0.0, 0.0);
    //    this->haende = new Hand();
    if (posx < 0) {
        this->unterArm = new Cube(0.1, 0.0, 0.0, 0.0, 5., 1., 1., 0., 0., 0., 0.);
        this->unterArm->translateInit(0.19,0.0,0.0);
        this->hand = new Hand('l',0.0, 0.0, 0.0);
    }
    if (posx > 0) {
        this->unterArm = new Cube(0.1, 0.0, 0.0, 0.0, 5., 1., 1., 0., 0., 0., 0.);
        this->unterArm->translateInit(-0.19,0.0,0.0);
        this->hand = new Hand('r',0.0, 0.0, 0.0);
    }
}

Arm::Arm() {

}

Arm::Arm(const Arm& orig) {
}

Arm::~Arm() {
}

void Arm::animate(double value) {
    this->animateArmRotation();
}

void Arm::animateArmRotation() {

    if (this->armHoch) {

        if (this->armrotation <= 87.5) {
            this->armrotation = this->armrotation + this->armswingvelocity; // Rotationswinkel aendern
        }

    }

}

void Arm::renderScene() {

    glPushMatrix();

    
    
    
  glTranslatef(this->posx, this->posy,this-> posz);
    //this->oberArm->renderScene();
    if (this->posx < 0) {
        
        glRotatef(this->armrotation, 0., 0., 1.);
    }
    if (this->posx > 0) {
   
        glRotatef(this->armrotation, 0., 0., -1.);
    }
 
      
        this->unterArm->renderScene();

      this->hand->renderScene(); 
   
    //    glRotatef(this->armrotation, 0., 0., 1.);
    //    if (this->armrotation != 0.0) {
    //
    //        this->unterArmLeft->translateInit(this->x, this->y, 0.);
    ////        this->haende->getOberHandLeft()->translateInit(this->x, this->y, 0.);
    ////        this->haende->getUnterHandLeft()->translateInit(this->x, this->y, 0.);
    //    }
    //    this->haende->getOberHandLeft()->renderScene();
    //    this->haende->getUnterHandLeft()->renderScene();
    //    this->unterArmLeft->renderScene();


    glPopMatrix();



    glPushMatrix();


    //    this->unterArmRight->renderScene();
    //    this->haende->getOberHandRight()->renderScene();
    //    this->haende->getUnterHandRight()->renderScene();
    //
    //    //   glRotatef(this->armrotation, 0.,0.,-1.);
    //    glPopMatrix();
    //    this->oberArmRight->renderScene();
    //    this->oberArmLeft->renderScene();

    this->armHoch = false;
}

void Arm::Armhoch() {
    this->armHoch = true;
    if (this->armrotation <= 90.) {
        this->x = this->x + 0.005;
        this->y = this->y + 0.004;
    }

}
