/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Tile.h" 

Tile::Tile() {
    //    m_art = Kachel_typ;
    m_character = nullptr;
}

Character* Tile::GetCharacter() const {
    return m_character;
}

//int Tile::GetArt() const {
//    return m_art;
//}

void Tile::SetCharacter(Character* character) {

    m_character = character;
}

void Tile::onEnter(Character* c, Tile* fromTile) {
    if (this->m_character == nullptr)
        m_character = c;
    else {
        fromTile->SetCharacter(c);
//        int hp_attak, hp_opfer;
//        hp_opfer = c->GetController()->getOpfer()->GetHitpoints();
//        hp_attak = c->GetHitpoints();
//        c->GetController()->getOpfer()->SetHitpoints(hp_opfer - hp_attak);
//        c->showInfo();
//        c->GetController()->getOpfer()->showInfo();
//        std::cout << "ANGRIFF" << std::endl;
//        c->showInfo();
//        c->GetController()->getOpfer()->showInfo();
    }
}

void Tile::onLeave(Tile* toTile) {

    Character* Sicher;
    Sicher = m_character;
    m_character = nullptr;
    toTile->onEnter(Sicher, this);




}

bool Tile::isTransparent() {
    return true;
}

bool Tile::isBetretbar() {

    return true;

}