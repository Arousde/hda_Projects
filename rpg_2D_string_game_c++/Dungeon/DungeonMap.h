/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DungeonMap.h
 * Author: arous
 *
 * Created on 23. April 2017, 12:18
 */

#ifndef DUNGEONMAP_H
#define DUNGEONMAP_H
#include <vector>
#include <string>
#include <set>
#include <map>
#include "Tile.h"
#include "Wall.h"
#include "Floor.h"
#include "Passive.h"
#include "Aktive.h"
#include "Door.h"
#include "Switch.h"
#include <ostream>
#include <istream>

class DungeonMap {
public:
    DungeonMap(int height, int width);
    DungeonMap(int height, int width, const std::vector<std::string>& data, std::vector<std::string> v);

    struct Position {
//        Position(int a , int b){
//            Reihe = a ;
//            Spalte = b ;
//        }
        int Reihe;
        int Spalte;
        friend bool operator<(const Position& to, const Position& from);
        friend bool operator==(const Position& to, const Position& from);
        friend bool operator!=(const Position& to, const Position& from);
        friend std::ostream& operator<<( std::ostream& os ,  Position p );
        friend std::istream& operator>>( std::ostream& is ,  Position p );
    };

    struct Kanten {
        Position p1;
        Position p2;

        Kanten(Position from, Position to) {
            if (from < to) {
                p1 = from;
                p2 = to;
            } else {
                p1 = to;
                p2 = from;
            }
        }
friend bool operator<(const DungeonMap::Kanten& kante1, const DungeonMap::Kanten& kante2) ;
    };

    Tile* findTile(Position pos);
    Position findTile(Tile* t);
    Position findCharacter(Character* c);
    void place(Position pos, Character* c);
    void placeT(Position pos, Tile* t);
    const int getBreite() const;
    const int getHoehe() const;
    void print();
    void print(Position);
    bool hasLineOfSight(Position, Position);
 
    Tile& operator()(int reihe, int spalte);
    const Tile& operator()(int reihe, int spalte) const;

    virtual ~DungeonMap(); 

    

    std::vector<Position> getPathTo(Position from, Position to);
    
    void PrintPathforControll();
    double round(double x );
private:
    const int m_Hoehe;
    const int m_Breite;
    Tile*** m_map;

};


#endif /* DUNGEONMAP_H */

