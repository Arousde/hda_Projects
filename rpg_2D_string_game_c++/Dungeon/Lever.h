/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lever.h
 * Author: arous
 *
 * Created on 25. Mai 2017, 14:05
 */

#ifndef LEVER_H
#define LEVER_H
#include "Aktive.h"
class Lever : public Aktive {
    public:
    Lever();
     void onEnter(Character* c, Tile* fromTile)override ;
     void Zeichen() override;
};

#endif /* LEVER_H */

