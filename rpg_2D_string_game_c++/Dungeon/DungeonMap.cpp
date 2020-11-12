/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DungeonMap.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <limits>
#include <c++/6/bits/stl_iterator.h>
#include <c++/6/bits/algorithmfwd.h>
#include <c++/6/bits/stl_algo.h>

DungeonMap::DungeonMap(int height, int width) : m_Hoehe(height), m_Breite(width) {


    m_map = new Tile** [height];

    for (int i = 0; i < height; i++)

        m_map[i] = new Tile*[width];


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            m_map[i][j] = nullptr;
        }

    }

}

DungeonMap::DungeonMap(int height, int width, const std::vector<std::string>& data, std::vector<std::string>v) : DungeonMap(height, width) {



    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            std::string zeichen = data[i].substr(j, 1);

            if (zeichen == ".") {
                m_map[i][j] = new Floor;

            } else
                if (zeichen == "#") {
                m_map[i][j] = new Wall;

            }

        }
    }


}

void DungeonMap::place(Position pos, Character* c) {
    m_map[pos.Reihe][pos.Spalte]->SetCharacter(c);
}

void DungeonMap::placeT(Position pos, Tile* t) {
    if (m_map[pos.Reihe][pos.Spalte] != nullptr) {
        delete m_map[pos.Reihe][pos.Spalte];
    }
    m_map[pos.Reihe][pos.Spalte] = t;
}

const int DungeonMap::getBreite() const {
    return m_Breite;
}

const int DungeonMap::getHoehe() const {
    return m_Hoehe;
}

DungeonMap::Position DungeonMap::findTile(Tile* t) {

    for (int i = 0; i < m_Hoehe; i++) {
        for (int j = 0; j < m_Breite; j++) {
            if (m_map[i][j] == t) {
                Position p;
                p.Reihe = i;
                p.Spalte = j;
                return p;
            }

        }

    }
    throw ("nicht gefunden");

}

Tile* DungeonMap::findTile(Position pos) {

    return m_map[pos.Reihe][pos.Spalte];
}

DungeonMap::Position DungeonMap::findCharacter(Character* c) {

    for (int i = 0; i < m_Hoehe; i++) {
        for (int j = 0; j < m_Breite; j++) {
            if (m_map[i][j]->GetCharacter() == c) {
                Position p;
                p.Reihe = i;
                p.Spalte = j;
                return p;
            }

        }

    }
    throw ("nicht gefunden");

}

void DungeonMap::print() {
    Tile* T;
    for (int i = 0; i < m_Hoehe; i++) {
        for (int j = 0; j < m_Breite; j++) {

            if (m_map[i][j]->GetCharacter() != nullptr)
                std::cout << m_map[i][j]->GetCharacter()->GetZeichen();
            else {

                T = findTile({i, j});
                T->Zeichen();
            }
        }
        std::cout << std::endl;

    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void DungeonMap::print(Position p) {
    Tile* T;
    for (int i = 0; i < m_Hoehe; ++i) {
        for (int j = 0; j < m_Breite; ++j) {
            Position Pos;
            Pos.Reihe = i;
            Pos.Spalte = j;

            if (m_map[i][j]->GetCharacter() != nullptr)
                std::cout << m_map[i][j]->GetCharacter()->GetZeichen();



            else if (hasLineOfSight(Pos, p)) {
                T = findTile({i, j});
                T->Zeichen();
            } else {
                std::cout << "#";

            }
        }

        std::cout << std::endl;

    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

}

bool DungeonMap::hasLineOfSight(DungeonMap::Position from, DungeonMap::Position to) {





    //    double x1, y1, xn, yn;
    //
    //    x1 = from.Reihe;
    //    y1 = from.Spalte;
    //    xn = to.Reihe;
    //    yn = to.Spalte;
    //
    //
    //
    //        double error, x, y, dx, dy;
    //        dx = xn - x1;
    //        dy = yn - y1;
    //        error = (-dx) / 2;
    //        y = y1;
    //        
    //        for (x = x1; x <= xn; ++x) {
    //            
    //            if (m_map[static_cast<int> (x)][static_cast<int> (y)]->isTransparent()== false) 
    //                 return false;
    //                error = error +dy;
    //                 if (error > 0) {
    //                    y++;
    //                    error  = error- dx;
    //                   
    //                }
    //            
    //        }
    //
    //        return true ;
    //    



    //             double x1, x2, y1, y2 ,x , y ;
    //            
    //            y1 = from.Reihe;
    //            y2 = to.Reihe;
    //            x1 = from.Spalte;
    //            x2 = to.Spalte;
    //            
    //             double len = std::max(abs(x2-x1), abs(y2-y1)) ;
    //               
    //            for( double i = 0; i < len; i++ ){
    //                
    //                double t = i/len ;
    //                 x = (x1 * (1.0-t) + x2 * t);
    //                 y = (y1 * (1.0-t) + y2 * t);
    //                 
    //                 
    //                 if( m_map[static_cast<int>(x)][static_cast<int>(y)]->isTransparent()== false )
    //                    return false;
    //                 else
    //                    return true;
    //            }

    //   len = max(abs(x2-x1), abs(y2-y1))
    //loop for i from 0 to len:
    //    # interpolate between (x1,y1) and (x2,y2)
    //    t = float(i)/len
    //    # at t=0.0 we get (x1,y1); at t=1.0 we get (x2,y2)
    //    x = round(x1 * (1.0-t) + x2 * t)
    //    y = round(y1 * (1.0-t) + y2 * t)
    //    # now check tile (x,y)
    //    
    //    
    // 



    double x = to.Spalte - from.Spalte;
    double y = to.Reihe - from.Reihe;
    double len = sqrt((x * x) + (y * y));


    double steigungx = x / len;
    double steigungy = y / len;

    x = from.Spalte;
    y = from.Reihe;
    for (double i = 0; i < len; i++) {
        if (m_map[static_cast<int> (round(y))][static_cast<int> (round(x))]->isTransparent() == false)
            return false;
        else
            x = x + steigungx;
        y = y + steigungy;

    }


    return true;






    //        double x1, x2, y1, y2, dx, dy;
    //        
    //        y1 = from.Reihe;
    //        y2 = to.Reihe;
    //        x1 = from.Spalte;
    //        x2 = to.Spalte;
    //        
    //        dx= x2 - x1;
    //        dy= y2 - y1;
    //        
    //        double m = dy/dx;
    //        
    //        for (double x= x1; x < x2; x++) {
    //                double y = m * (x-x1) +y1;
    //                if (m_map[static_cast<int> (y)][static_cast<int> (x)]->isTransparent()){
    //                    return false;
    //                }
    //        }
    //        return true;


    //function line_lerp(x1, y1, x2, y2) {
    //    x1 = Math.floor(x1);
    //    x2 = Math.floor(x2);
    //    y1 = Math.floor(y1);
    //    y2 = Math.floor(y2);
    //    var length = Math.max(Math.abs(x1 - x2), Math.abs(y1 - y2));
    //    var tIncr = 1/length ;
    //    for (var t = 0; t <= 1; t+=tIncr) {
    //        var lx = Math.round(x1 * t + x2 * (1 - t));
    //        var ly = Math.round(y1 * t + y2 * (1 - t));
    //        context.fillRect(lx, ly, 1, 1);
    //    }
    //}
    //








}

double DungeonMap::round(double x) {
    if (x > 0) {
        x += 0.5;
    }
    if (x < 0) {
        x -= 0.5;
    }
    return x;
}

Tile& DungeonMap::operator()(int reihe, int spalte) {

    return *m_map[reihe][spalte];
}

const Tile& DungeonMap::operator()(int reihe, int spalte) const {

    return *m_map[reihe][spalte];



}

bool operator<(const DungeonMap::Position& to, const DungeonMap::Position& from) {

    //return (to.Reihe < from.Reihe || (to.Reihe == from.Reihe && to.Spalte < from.Spalte));
    if (from.Reihe != to.Reihe)
        return from.Reihe < to.Reihe;
    return from.Spalte < to.Spalte;

}

bool operator==(const DungeonMap::Position& to, const DungeonMap::Position& from) {


    return (to.Reihe == from.Reihe && to.Spalte == from.Spalte);
}

bool operator!=(const DungeonMap::Position& to, const DungeonMap::Position& from) {

    return (to.Reihe != from.Reihe || to.Spalte != from.Spalte);
}

bool operator<(const DungeonMap::Kanten& kante1, const DungeonMap::Kanten& kante2) {

    //    return (kante1.p1 < kante2.p1 || (kante1.p1 == kante2.p1 && kante1.p2 < kante2.p2));
    if (kante1.p1 != kante2. p1)
        return kante1.p1 < kante2.p1;
    return kante1.p2 < kante2.p2;


}

std::ostream& operator<<(std::ostream& os, DungeonMap::Position p) {

    os << p.Reihe << "/" << p.Spalte;

    return os;

}

std::istream& operator>>(std::istream& is, DungeonMap::Position p) {
    char irgendwas;

    is >> p.Reihe >> irgendwas >> p.Spalte;

    return is;

}

std::vector<DungeonMap::Position> DungeonMap::getPathTo(DungeonMap::Position from, DungeonMap::Position to) {

    std::vector<DungeonMap::Position> pfad;
    std::set<DungeonMap::Kanten> nachbarn;
    std::set<DungeonMap::Position> Graph;
    std::map<Position, Position> Prev;
    std::map<Position, int> Dist;
    int inf = std::numeric_limits<int>::max();
    Position v, u;

    for (int i = 0; i < m_Hoehe; i++) { // Graph Initialization 
        for (int j = 0; j < m_Breite; j++) {
            Position Pos;
            Pos.Reihe = i;
            Pos.Spalte = j;

            if (m_map[i][j]->isBetretbar()) {
                Graph.insert(Pos);
                Dist[Pos] = inf; // Unknown distance from source to v
                Prev[Pos] = {-1, -1}; // Previous node in optimal path from source
            }
        }
    }

    for (auto const& p : Graph) { // Kanten (Nachbarn) Initialization
        if (m_map[p.Reihe + 1][p.Spalte - 1]->isBetretbar())
            nachbarn.insert(Kanten(p,{p.Reihe + 1, p.Spalte - 1}));

        if (m_map[p.Reihe + 1][p.Spalte]->isBetretbar())
            nachbarn.insert(Kanten(p,{p.Reihe + 1, p.Spalte}));

        if (m_map[p.Reihe + 1][p.Spalte + 1]->isBetretbar())
            nachbarn.insert(Kanten(p,{p.Reihe + 1, p.Spalte + 1}));

        if (m_map[p.Reihe][p.Spalte - 1]->isBetretbar())
            nachbarn.insert(Kanten(p,{p.Reihe, p.Spalte - 1}));

        if (m_map[p.Reihe][p.Spalte + 1]->isBetretbar())
            nachbarn.insert(Kanten(p,{p.Reihe, p.Spalte + 1}));


        if (m_map[p.Reihe - 1][p.Spalte - 1]->isBetretbar())
            nachbarn.insert(Kanten(p,{p.Reihe - 1, p.Spalte - 1}));


        if (m_map[p.Reihe - 1][p.Spalte]->isBetretbar())
            nachbarn.insert(Kanten(p,{p.Reihe - 1, p.Spalte}));

        if (m_map[p.Reihe - 1][p.Spalte + 1]->isBetretbar())
            nachbarn.insert(Kanten(p,{p.Reihe - 1, p.Spalte + 1}));

    }





    //   auto u = Dist.[*Dist.begin()] ; // Node with the least distance will be selected first

    //        std::map<Position, int>::iterator p;
    //    //
    //    //   it = Dist.begin();
    //    //    u = it->first;
    //    int min = inf;
    //    for ( p= Dist.begin();p!=Dist.end(); p++) {
    //
    //        if (min < p->second) {
    //            min = p->second;
    //           
    //        }
    //    }


//    for (auto k : nachbarn) {
//        //    std::cout << k.p1 << "<->" << k.p2 << std::endl;
//    }



    Dist[from] = 0; // Distance from source to source
    while (Graph.size()!=0) {

        
        int min = inf;
        for (auto  p : Graph) {
            if (min > Dist[p]) {
                min = Dist[p];
                u = p;
            }
        }
        


        if (u == to)
            break;
       
        //        if (min != inf) {
        Graph.erase(u); // remove u from Q 



        //   auto newKante = *nachbarn.find(u,{u.Reihe+1,u.Spalte+1});
        //    for (auto const& p : kanten} 

        //auto newKante = nachbarn.find() ;

        for (auto const& kante : nachbarn) {

            if (kante.p1 == u) {
                int alt = Dist[u] + 1; // 
                if (alt < Dist[kante.p2]) {
                    Dist[kante.p2] = alt;
                    Prev[kante.p2] = u;
                }
            }  if (kante.p2 == u) {

                int alt = Dist[u] + 1; // 
                if (alt < (Dist[kante.p1])) {
                    Dist[kante.p1] = alt;
                    Prev[kante.p1] = u;
                }

            }
            
        }

              
                 
          
    } 

     if (Dist[to] == inf)
        return pfad;        
        
     
    v = to;
    while (v != from) {
        pfad.push_back(v);
        v = Prev[v];
    }

    pfad.push_back(from);

    //    std::reverse(pfad.begin(), pfad.end());

    return pfad;

}

//void DungeonMap::PrintPathforControll() {
//
//    //    
//    //     std::set<DungeonMap::Position> Path;
//    //
//    //    for (int i = 0; i < m_Hoehe; ++i) {
//    //        for (int j = 0; j < m_Breite; j++) {
//    //            Position Pos;
//    //            Pos.Reihe = i;
//    //            Pos.Spalte = j;
//    //
//    //            if (m_map[i][j]->isBetretbar())
//    //                Path.insert(Pos);
//    //
//    //        }
//    //    }
//    //    
//    //for (auto const& p : Path)
//    //    {
//    //        std::cout << p << ' ';
//
//    //    }
//}
//

DungeonMap::~DungeonMap() {






    for (int i = 0; i < m_Hoehe; i++) {
        for (int j = 0; j < m_Breite; j++) {
            delete m_map[i][j];
        }

    }

    for (int i = 0; i < m_Hoehe; i++) {

        delete[] m_map[i];
    }


    delete [] m_map;



    //    
    //         for (int i = 0; i < m_Hoehe; i++){
    //
    //        delete m_map[i] ;
    //         }




}
