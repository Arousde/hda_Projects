
#include "Switch.h"
#include <iostream>

Switch::Switch() : Aktive() {

}

void Switch::Zeichen() {

    if (!betreten)
        std::cout << "?";
    else std::cout << "!";

}

//void Switch::Setbetreten() {
//    this->betreten = true;
//}
//
//bool Switch::Istbetreten() const {
//    return betreten;;
//}
//
//void Switch::Set_Ptr_passive(Passive* t_pass) {
//    this->Ptr_pass = t_pass;
//}

void Switch::onEnter(Character* c, Tile* fromTile) {

    if(!betreten)
    {
        Setbetreten(true);
        Ptr_pass->SetStatus(true);
    }
//    else if(betreten) {
//        Setbetreten(false);
//          Ptr_pass->SetStatus(false);
//    }
   Tile::onEnter(c, fromTile);
}

//void Switch::onLeave(Tile* toTile) {
//
//    Character* Sicher;
//    Sicher = this->GetCharacter();
//    this->SetCharacter(nullptr);
//    toTile->onEnter(Sicher, this);
//
//
//
//
//}
