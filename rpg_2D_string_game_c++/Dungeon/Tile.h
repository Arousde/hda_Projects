/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.h
 * Author: arous
 *
 * Created on 22. April 2017, 20:54
 */

#ifndef TILE_H
#define TILE_H
#include "Character.h"

class Tile {
public:
    
//    enum Kacheltypen {
//        Floor, Wall
//    };
    Tile();

    Character* GetCharacter() const;

//    int GetArt() const;
    void SetCharacter(Character* character);
   virtual void onLeave(Tile* toTile) ;
   virtual void onEnter(Character* c, Tile* fromTile) ;
   virtual void Zeichen()=0;
    
  virtual  bool isTransparent();
  virtual bool isBetretbar();
    virtual ~Tile() {
        if(m_character!= nullptr)
        delete m_character;
    }

private:
//    Kacheltypen m_art;
    Character* m_character;
  
};

#endif /* TILE_H */
