/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RadioTransformer.cpp
 * Author: arous
 * 
 * Created on 8. Mai 2018, 15:06
 */

#include <GL/gl.h>
#include <GL/freeglut_std.h>

#include "RadioTransformer.h"

RadioTransformer::RadioTransformer(double x, double y, double z) {
    this->posyinit = y;
    this->posxinit = x;
    this->poszinit = z;
    this->posx = x;
    this->posz = z;
    this->posy = y;
    
    
    //silber
    this->head = new Cube(0.6, 0., 0.0, 0.0, 2., 1., 1., 0.9, 0.91, 0.98, 0.);
    this->door = new Cube(0.25, 0., -0.1, 0.26, 1.5, 1., 1., 0.2, 0.2, 0.2, 0.);
    this->innerdoor = new Cube(0.2, 0., -0.1, 0.3, 1.5, 1., 1., .6, 0.6, 0.6, 0.9);
    

    //Knopf Rot
    this->btn1 = new Cube(0.1, 0.56, 0.27, 0.26, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
    //Knopf schwarz
    this->btn2 = new Cube(0.1, 0.46, 0.27, 0.26, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0);
    //Knopf blau
    this->btn3 = new Cube(0.1, 0.36, 0.27, 0.26, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);
    //        this->btn4 = new Cube();
    
    
    this->eyeleft = new Sphere(0.15, -0.4, 0.0, 0.3, 1.0, 1.0, -.1, 0.0, 0.0, 0., 0.0);
    this->innerEyeLeft = new Sphere(0.1, -0.4, 0.0, 0.31, 1.0, 1.0, -.1, 1.0, 1.0, 1.0, 0.);
    this->eyePointLeft = new Sphere(0.05, -0.4, 0.0, 0.32, 1.0, 1.0, -.1, 0.0, 0.0, 0.0, 0.0);

    
    this->eyeright = new Sphere(0.15, 0.4, 0.0, 0.3, 1.0, 1.0, -.1, 0.0, 0.0, 0., 0.0);
    this->innerEyeRight = new Sphere(0.1, 0.4, 0.0, 0.31, 1.0, 1.0, -.1, 1.0, 1.0, 1.0, 0.);
    this->eyePointRight = new Sphere(0.05, 0.4, 0.0, 0.32, 1.0, 1.0, -.1, 0.0, 0.0, 0.0, 0.0);
    
    
    //        this->armleft = new Arm();
 this->schulterRight = new Sphere(0.3, 0.6, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0);
this->schulterLeft = new Sphere(0.3, -0.6, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0);

this->oberArmRight = new Cube(0.12, 0.75, .05, 0.0, 1., 7., 1., 0.0, 0.0, 0.0, 0.0);
this->oberArmLeft = new Cube(0.12, -0.75, 0.05, 0.0, 1., 7., 1., 0.0, 0.0, 0.0, 0.0);

//this->ellebogenRight= new Sphere(0.067, 0.75, 0.67, 0.0, 1., 1., 1., 0.0, 0.0, 0.0, 0.0);
//this->ellebogenLeft= new Sphere(0.067, -0.75, 0.67, 0.0, 1., 1., 1., 0.0, 0.0, 0.0, 0.0);
//this->unterArmRight = new Cube(0.1, 0.1, 0.65, 0.0, 5., 1., 1., 0.0, 0.0, 0.0, 0.0);
//this->unterArmLeft = new Cube(0.1, -0.1, .65, 0.0, 5., 1., 1., 0.0, 0.0, 0.0, 0.0);

//this->unterHandRight = new Cube(0.05, 0.025, 0.6, 0.0, 5, 1., 1., 0.0, 0.0, 0.0, 0.0);
//this->unterHandLeft = new Cube(0.05, -0.025, 0.6, 0.0, 5, 1., 1., 0.0, 0.0, 0.0, 0.0);
//
//this->oberHandRight = new Cube(0.05, 0.025, 0.7, 0.0, 5., 1., 1., 0.0, 0.0, 0.0, 0.0);
//this->oberHandLeft = new Cube(0.05, -0.025, 0.7, 0.0, 5., 1., 1., 0.0, 0.0, 0.0, 0.0);

this->armLeft= new Arm(-0.75, 0.8, 0.0);
//this->armLeft->
this->armRight= new Arm(0.75, 0.8, 0.0);


}

RadioTransformer::RadioTransformer(const RadioTransformer& orig) {
}

RadioTransformer::~RadioTransformer() {
}

void RadioTransformer::animate(double value) {
            
            this->armLeft->animate(value);
    	    this->armRight->animate(value);
             this->armLeft->getHand()->animate(value);
    	    this->armRight->getHand()->animate(value);
            
}

void RadioTransformer::keyboardKeys(unsigned char key, int x, int y) {

}

void RadioTransformer::renderScene() {
    glPushMatrix();
    this->armRight->renderScene();
    this->armLeft->renderScene();
    this->head->renderScene();
    this->door->renderScene();
    this->innerdoor->renderScene();
    
    this->btn1->renderScene();
    this->btn2->renderScene();
    this->btn3->renderScene();
    //        this->btn4->renderScene();
    this->eyeleft->renderScene();
    this->innerEyeRight->renderScene();
    this->eyePointRight->renderScene();
    this->eyeright->renderScene();
    this->innerEyeLeft->renderScene();
    this->eyePointLeft->renderScene();
//
//    
    this->schulterRight->renderScene();
    this->schulterLeft->renderScene();
    
    
    this->oberArmRight->renderScene();
    this->oberArmLeft->renderScene();
    
  //  this->ellebogenRight->renderScene();
//this->ellebogenLeft->renderScene();
//    this->unterArmRight->renderScunterHandRightene();
//    this->unterArmLeft->renderScene();
//    
//    this->unterHandRight->renderScene();
//    this->unterHandLeft->renderScene();
//    this->oberHandRight->renderScene();
//    this->oberHandLeft->renderScene();
    //        this->armleft->renderScene();
    //this->armright->renderScene();
  //  this->aerme->renderScene();
  
    glPopMatrix();
}

