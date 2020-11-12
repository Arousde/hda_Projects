/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trap.h
 * Author: arous
 *
 * Created on 25. Mai 2017, 14:31
 */

#ifndef TRAP_H
#define TRAP_H
#include "Floor.h"

class Trap : public Tile {
    public:
        Trap();
 
   virtual void onEnter(Character* c, Tile* fromTile)override ;
   virtual void Zeichen();
        private :
        bool m_aktivated ;
};


#endif /* TRAP_H */

