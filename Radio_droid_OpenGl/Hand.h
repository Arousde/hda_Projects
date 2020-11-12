/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hand.h
 * Author: arous
 *
 * Created on 12. Mai 2018, 15:03
 */

#ifndef HAND_H
#define HAND_H

#include "GlutObjparent.h"
#include "Cube.h"


class Hand  : public GlutObjparent{
public:
    Hand(char rODERl ,double posx, double posy, double posz);
    Hand(const Hand& orig);
    virtual ~Hand();
    
    void animate(double value) override;
    void renderScene() override;
    void keyboardKeys(unsigned char key, int x, int y) override;

    Cube* getOberHandRight() const {
        return oberHand;
    }



    Cube* getUnterHand() const {
        return unterHand;
    }

    void swing();
 void handhoch();
    
private:

     Cube *oberHand, *unterHand;
    
     double handrotation = 0.0;
     double handhochvelocity = 2.5;
  
      double handrotation_y = 0.0;
     double handhochvelocity_y = 50.;
     
     double handrunter = 0.0;
     double handrunterrot = .25;
    bool handHoch ;
    bool handswing;
    void animatehandRotation();
    void animatehandswing();
    char rODERl ;
    
        double posx, posy, posz;

};

#endif /* HAND_H */

