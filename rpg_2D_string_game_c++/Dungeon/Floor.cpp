/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Floor.h"
#include "Tile.h"
#include <iostream>

Floor::Floor() : Tile() {
    m_item = nullptr;
}

void Floor::onEnter(Character* c, Tile* fromTile) {
    if (m_item != nullptr) {
        c->addItem(m_item);

        this->m_item = nullptr;
    }
    if (this->GetCharacter() == nullptr)
        this->SetCharacter(c);
    else {
        //        std::cout << "VOR DEM ANGRIFF" << std::endl;
        //        c->showInfo();
        //        this->GetCharacter()->showInfo();

        int hp_attak, hp_opfer;
        hp_opfer = this->GetCharacter()->GetHitpoints();
        hp_attak = c->GetStrength();
        this->GetCharacter()->SetHitpoints(hp_opfer - hp_attak);

        std::cout << "NACH DEM ANGRIFF" << std::endl;
        c->showInfo();
        this->GetCharacter()->showInfo();


        fromTile->SetCharacter(c);

        //        if (!(c->GetController()->getOpfer()->GetHitpoints() <= 0)) {
        //            int hp_attak, hp_opfer;
        //            hp_opfer = c->GetHitpoints();
        //            hp_attak = this->GetCharacter()->GetStrength();
        //            c->SetHitpoints(hp_opfer - hp_attak);
        //            c->showInfo();
        //
        //        }
    }

}

Floor::~Floor() {
    if(m_item != nullptr)
        delete m_item;
}


//
//void Floor::onLeave(Tile* toTile) {
//    
//        Character* Sicher;
//        Sicher = this->GetCharacter();
//        this->SetCharacter(nullptr) ;
//        toTile->onEnter(Sicher, this);
//
//    
//    
//}

void Floor::Zeichen() {
    if (m_item != nullptr)
        std::cout << "*";
    else
        std::cout << ".";
}

void Floor::setItem(Item* item) {
    m_item = item;
}

//bool Floor::isTransparent(){
//    return true ;
//}