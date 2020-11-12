/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AttackController.h"
#include <vector>

AttackController::AttackController(DungeonMap* map) : Controller() {
    attak_map = map;
    opfer = nullptr;
    attak = nullptr;
}

int AttackController::move() {
    std::vector<DungeonMap::Position> path;


    DungeonMap::Position opfer_pos = attak_map->findCharacter(opfer);
    DungeonMap::Position attak_pos = attak_map->findCharacter(attak);

    //   v = attak_map->getPathTo(attak_pos,opfer_pos);

    path = attak_map->getPathTo(attak_pos, opfer_pos);

    if (path.empty())
        return 5;
    DungeonMap::Position PositionNeu = path[path.size() - 2];

    if (PositionNeu.Reihe - attak_pos.Reihe == 0) {
        if (attak_pos.Spalte - PositionNeu.Spalte == 0)
            return 5;
        else if (PositionNeu.Spalte - attak_pos.Spalte == -1)
            return 4;
        else if (PositionNeu.Spalte - attak_pos.Spalte == 1)
            return 6;
    } else if (PositionNeu.Reihe - attak_pos.Reihe == -1) {
        if (attak_pos.Spalte - PositionNeu.Spalte == 0)
            return 8;
        else if (PositionNeu.Spalte - attak_pos.Spalte == -1)
            return 7;
        else if (PositionNeu.Spalte - attak_pos.Spalte == 1)
            return 9;
    } else if (PositionNeu.Reihe - attak_pos.Reihe == 1) {
        if (attak_pos.Spalte - PositionNeu.Spalte == 0)
            return 2;
        else if (PositionNeu.Spalte - attak_pos.Spalte == -1)
            return 1;
        else if (PositionNeu.Spalte - attak_pos.Spalte == 1)
            return 3;
    }
    std::cout << "outoutoutout";
}

std::string AttackController::typ() {
    return "attak";
}






//   for(auto const& w : v){
//       if (w.Reihe == 1 && w.Spalte == -1)
//        return 1;
//    else if (w.Reihe == 0 && w.Spalte == -1)
//        return 2;
//    else if (w.Reihe == -1 && w.Spalte == -1)
//        return 3;
//    else if (w.Reihe == 1 && w.Spalte == 0)
//        return 4;
//    else if (w.Reihe == 0 && w.Spalte == 0)
//        return 5;
//    else if (w.Reihe == -1 && w.Spalte == 0)
//        return 6;
//    else if (w.Reihe == 1 && w.Spalte == 1)
//        return 7;
//    else if (w.Reihe == 0 && w.Spalte == 1)
//        return 8;
//    else if (w.Reihe == -1 && w.Spalte == 1)
//        return 9;
//    else{
//        std::cout<<"kein pfad";
//        v.clear();
//        return 5;
//    }
//
//   }


