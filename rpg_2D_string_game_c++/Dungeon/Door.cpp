#include "Door.h"
#include <iostream>

Door::Door() : Passive() {
    SetStatus(false);
}

void Door::Zeichen() {
    if (this->GetStatus() == true)
        std::cout << "/";
    else std::cout << "X";
}

void Door::onEnter(Character* c, Tile* fromTile) {

    if (this->GetStatus())
        Tile::onEnter(c, fromTile);
    else fromTile->SetCharacter(c);
}

bool Door::isTransparent() {
    if (this->GetStatus()) {
        return true;
    } else return false;
}

bool Door::isBetretbar() {
    if (this->GetStatus()) {
        return true;
    }
    return false;
}
