/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controller.h
 * Author: arous
 *
 * Created on 8. Mai 2017, 13:14
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <string>
class Character;

class Controller{
public:
   Controller();
   virtual int move() =0;
   void setControl_character(Character* control_character);
   Character* getControl_character() const;
   void setOpfer(Character* opfer);
   Character* getOpfer() const;
  
   
  virtual std::string typ()= 0 ;
   void setAttak(Character* attak);
   Character* getAttak() const;
   
private:
   Character* control_character;
protected:
    Character* opfer;
     Character* attak;
};


#endif /* CONTROLLER_H */

