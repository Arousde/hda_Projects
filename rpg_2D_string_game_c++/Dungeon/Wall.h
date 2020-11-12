/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wall.h
 * Author: arous
 *
 * Created on 5. Mai 2017, 18:54
 */
#include "Tile.h"
#ifndef WALL_H
#define WALL_H

class Wall : public Tile
{
    public:
        Wall();
//   virtual void onLeave(Tile* toTile) override ;
   virtual void onEnter(Character* c, Tile* fromTile) override ;
   virtual void Zeichen() override;
   bool isTransparent() override;
   bool isBetretbar() override;
};



#endif /* WALL_H */

