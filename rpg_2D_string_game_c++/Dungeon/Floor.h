/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Floor.h
 * Author: arous
 *
 * Created on 5. Mai 2017, 18:54
 */



#ifndef FLOOR_H
#define FLOOR_H
#include "Tile.h"

class Floor : public Tile {
public:
    Floor();
    //    virtual void onLeave(Tile* toTile) override;
       virtual void onEnter(Character* c, Tile* fromTile) override;
       virtual void Zeichen() override;
       void setItem(Item* item);
    virtual ~Floor();

//       bool isTransparent();
private:
    Item* m_item;
};


#endif /* FLOOR_H */




