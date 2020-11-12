#include "Wall.h"
#include <iostream>

Wall::Wall():Tile(){
    
}
void Wall::onEnter(Character* c, Tile* fromTile) {
   fromTile->SetCharacter(c);
}

//void Wall::onLeave(Tile* toTile) {
//    
//        Character* Sicher;
//        Sicher = Tile::GetCharacter();
//        this->SetCharacter(nullptr);
//        toTile->onEnter(Sicher, this);  
//}


  void Wall::Zeichen(){
      std::cout << "#";
  }
  
  bool Wall::isTransparent(){
      return false;
  }
  
  bool Wall::isBetretbar(){
      return false;
  }