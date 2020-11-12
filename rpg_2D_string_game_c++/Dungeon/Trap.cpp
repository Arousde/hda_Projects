/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Trap.h"

Trap::Trap() : Tile() {
m_aktivated = false ;
}

void Trap::Zeichen() {

    if (this->m_aktivated)
        std::cout << "T";
    else std::cout << ".";
}

void Trap::onEnter(Character* c, Tile* fromTile) {
    if (this->m_aktivated) {
        Tile::onEnter(c, fromTile);
    } 
    else {
        this->m_aktivated = true;
        c->SetHitpoints(-20);
        Tile::onEnter(c, fromTile);
        
    }
}