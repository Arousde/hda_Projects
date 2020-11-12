/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Lever.h"

Lever::Lever():Aktive(){
    betreten = false;
}

void Lever::onEnter(Character* c, Tile* fromTile){
   

    if(!betreten)
    {
        Setbetreten(true);
        Ptr_pass->SetStatus(true);
    }
    else if(betreten) {
        Setbetreten(false);
          Ptr_pass->SetStatus(false);
    }
   Tile::onEnter(c, fromTile);
}


void Lever::Zeichen() {

    if (!betreten)
        std::cout << "?";
    else std::cout << "!";

}