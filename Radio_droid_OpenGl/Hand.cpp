/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hand.cpp
 * Author: arous
 *   this->armLeft->
 * Created on 12. Mai 2018, 15:03
 */

#include <GL/gl.h>

#include "Hand.h"

Hand::Hand(char rODERl, double posx, double posy, double posz) {
    this->rODERl = rODERl;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;

    if (rODERl == 'l') {
        this->unterHand = new Cube(0.035, 0.0, 0.0, 0.0, 20., 1., 1., 0.0, 0.0, 0.0, 0.0);
        //        this->unterHand->translateInit(0.12,0.05,0.);
        // this->unterHand->translateInit(0.12,0.05,0.);
        this->oberHand = new Cube(0.035, 0.0, 0.0, 0., 20., 1., 1., 0.0, 0.0, 0.0, 0.0);
        //        this->oberHand->translateInit(0.12,-0.05,0.);
        //     this->oberHand->translateInit(0.12,-0.05,0.);

    }
    if (rODERl == 'r') {
        this->unterHand = new Cube(0.035, 0.0, 0.0, 0.0, 20., 1., 1., 0.0, 0.0, 0.0, 0.0);
        //       this->unterHand->translateInit(0.05,0.,0);
        this->oberHand = new Cube(0.035, 0.0, 0.0, 0., 20., 1., 1., 0.0, 0.0, 0.0, 0.0);
        //      this->oberHand->translateInit(0.05,0.,0);
    }

}

Hand::Hand(const Hand& orig) {
}

Hand::~Hand() {
}

void Hand::animate(double value) {
    animatehandRotation();
    animatehandswing();
}

void Hand::keyboardKeys(unsigned char key, int x, int y) {

}

void Hand::renderScene() {

    glPushMatrix();
    if (this->rODERl == 'l') {

        glPushMatrix();

        glRotatef(this->handrotation_y, 1.,0., 0.);
        glTranslatef(-this->handrunterrot,0.0,0.0);
        glTranslatef(0.7, 0.04, 0.0);
        glRotatef(this->handrotation, 0., 0., 1.);
        this->oberHand->renderScene();
        glPopMatrix();

        glPushMatrix();
        glRotatef(this->handrotation_y, 1., 0., 0.);
        glTranslatef(-this->handrunterrot,0.0,0.0);
        glTranslatef(0.7, -0.04, 0.0);
        glRotatef(this->handrotation, 0., 0., -1.);
        this->unterHand->renderScene();
        glPopMatrix();

    }
    if (this->rODERl == 'r') {

        glPushMatrix();
        glRotatef(this->handrotation_y, 1., 0., 0.);
        glTranslatef(this->handrunterrot,0.0,0.0);
        glTranslatef(-0.7, 0.04, 0.0);
        glRotatef(this->handrotation, 0., 0., -1.);
        this->oberHand->renderScene();
        glPopMatrix();

        glPushMatrix();
        glRotatef(this->handrotation_y, 1., 0., 0.);
        glTranslatef(this->handrunterrot,0.0,0.0);
        glTranslatef(-0.7, -0.04, 0.0);
        glRotatef(this->handrotation, 0., 0., 1.);
        this->unterHand->renderScene();
        glPopMatrix();

    }
    glPopMatrix();
    
    
    
    this->handHoch = false;
//    this->handswing=false;

//    //        if(this->handswing){
//    if (this->rODERl == 'l') {
//
//        glPushMatrix();
//        glTranslatef(0.5, 0.04, 0.0);
//        glRotatef(this->handrotation_y, 0., 1., 0.);
//        this->oberHand->renderScene();
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(0.5, -0.04, 0.0);
//        glRotatef(this->handrotation_y, 0., -1., 0.);
//        this->unterHand->renderScene();
//        glPopMatrix();
//
//    }
//    if (this->rODERl == 'r') {
//
//        glPushMatrix();
//        glTranslatef(-0.5, 0.04, 0.0);
//        glRotatef(this->handrotation_y, 0., -1., 0.);
//        this->oberHand->renderScene();
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(-0.5, -0.04, 0.0);
//        glRotatef(this->handrotation_y, 0., -1., 0.);
//        this->unterHand->renderScene();
//        glPopMatrix();

    }








void Hand::handhoch() {
    this->handHoch = true;
}

void Hand::swing() {
    this->handswing = true;
}

void Hand::animatehandRotation() {

    if (this->handHoch) {

        if (this->handrotation <= 90.0) {
            this->handrotation = this->handrotation + this->handhochvelocity; // Rotationswinkel aendern
            this->handrunter= this->handrunterrot + this->handrunter;
        }
    }
}

void Hand::animatehandswing() {

    if (this->handswing) {
        if (this->handrotation > 90.0) {
                this->handrotation_y = this->handrotation_y + this->handhochvelocity_y; // Rotationswinkel aendern
        }
    }
}
