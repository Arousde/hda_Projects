/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GameEngine.h"
#include "Trap.h"
#include "Lever.h"
#include "StationaryController.h"
#include "AttackController.h"
#include <iostream>
#include <sstream>

using namespace std;

GameEngine::GameEngine(int height, int width, const std::vector<std::string>& data, std::vector<std::string>& v) {
    m_welt = new DungeonMap(height, width, data, v);
    weiter = true;
    int Reihe, Spalte, Strength, Stamina, RReihe, RSpalte;
    std::string key, controller, LeveroderSwitch, itemm;
    char zeichen;




    for (int j = 0; j < v.size(); j++) {

        std::stringstream tada(v[j]), tadaba(v[j]);
        Controller* c;


        tada>> key;
        if (key == "Character") {

            tadaba >> key >> zeichen >> Strength >> Stamina >> controller >> Reihe>>Spalte;
            if (controller == "ConsoleController")
                c = new ConsoleController;
            else if (controller == "StationaryController")
                c = new StationaryController;
            else c = new AttackController(m_welt);
            Character* character = new Character(zeichen, Stamina, Strength, c);
            c->setAttak(character);
            m_vector.push_back(character);
            m_welt->place({Reihe, Spalte}, m_vector[m_vector.size() - 1]);




        } else if (key == "Door") {
            tadaba >> key >> Reihe >> Spalte >> LeveroderSwitch >> RReihe>>RSpalte;
            Door* d = new Door;
            DungeonMap::Position doorPos;
            doorPos.Reihe = Reihe;
            doorPos.Spalte = Spalte;
            m_welt->placeT(doorPos, d);



            if (LeveroderSwitch == "Switch") {
                Switch* s = new Switch;
                s->Set_Ptr_passive(d);
                DungeonMap::Position switchPos;
                switchPos.Reihe = RReihe;
                switchPos.Spalte = RSpalte;
                m_welt->placeT(switchPos, s);




            } else
                if (LeveroderSwitch == "Lever") {
                Lever* l = new Lever;
                l->Set_Ptr_passive(d);
                DungeonMap::Position LeverPos;
                LeverPos.Reihe = RReihe;
                LeverPos.Spalte = RSpalte;
                m_welt->placeT(LeverPos, l);
            }




        } else if (key == "Trap") {
            tadaba >> key >> Reihe>>Spalte;

            Trap* t = new Trap;
            DungeonMap::Position trapPos;
            trapPos.Reihe = Reihe;
            trapPos.Spalte = Spalte;
            m_welt->placeT(trapPos, t);

        } else {

            tadaba >> itemm >> Reihe>>Spalte;

            if (itemm == "ArmingSword") {

                Item* item = new ArmingSword;

                DungeonMap::Position itemPos;
                itemPos.Reihe = Reihe;
                itemPos.Spalte = Spalte;

                Floor* f;
                f = dynamic_cast<Floor*> (m_welt->findTile(itemPos));
                f->setItem(item);

            } else if (itemm == "Greatsword") {


                Item* item = new Greatsword;
                DungeonMap::Position itemPos;
                itemPos.Reihe = Reihe;
                itemPos.Spalte = Spalte;

                Floor* f;
                f = dynamic_cast<Floor*> (m_welt->findTile(itemPos));
                f->setItem(item);
            } else if (itemm == "Club") {


                Item* item = new Club;

                DungeonMap::Position itemPos;
                itemPos.Reihe = Reihe;
                itemPos.Spalte = Spalte;
                Floor* f;
                f = dynamic_cast<Floor*> (m_welt->findTile(itemPos));
                f->setItem(item);
            } else if (itemm == "RapierUndDagger") {


                Item* item = new RapierUndDagger;

                DungeonMap::Position itemPos;
                itemPos.Reihe = Reihe;
                itemPos.Spalte = Spalte;
                Floor* f;
                f = dynamic_cast<Floor*> (m_welt->findTile(itemPos));
                f->setItem(item);
            } else if (itemm == "Gambeson") {


                Item* item = new Gambeson;

                DungeonMap::Position itemPos;
                itemPos.Reihe = Reihe;
                itemPos.Spalte = Spalte;
                Floor* f;
                f = dynamic_cast<Floor*> (m_welt->findTile(itemPos));
                f->setItem(item);
            } else if (itemm == "MailArmour") {


                Item* item = new MailArmour;

                DungeonMap::Position itemPos;
                itemPos.Reihe = Reihe;
                itemPos.Spalte = Spalte;
                Floor* f;
                f = dynamic_cast<Floor*> (m_welt->findTile(itemPos));
                f->setItem(item);
            } else if (itemm == "Shield") {


                Item* item = new Shield;

                DungeonMap::Position itemPos;
                itemPos.Reihe = Reihe;
                itemPos.Spalte = Spalte;
                Floor* f;
                f = dynamic_cast<Floor*> (m_welt->findTile(itemPos));
                f->setItem(item);
            } else if (itemm == "FullPlateArmour") {


                Item* item = new FullPlateArmour;

                DungeonMap::Position itemPos;
                itemPos.Reihe = Reihe;
                itemPos.Spalte = Spalte;
                Floor* f;
                f = dynamic_cast<Floor*> (m_welt->findTile(itemPos));
                f->setItem(item);
                std::cout << "item mriguel" << std::endl;
            }

        }




    }
    Character* opfer = nullptr;
    Character* angreifer = nullptr;

    for (Character* p : m_vector) {
        if (p->GetController()->typ() == "control")
            opfer = p;
        if (p->GetController()->typ() == "attak")
            angreifer = p;
    }

    Controller* c_angreifer;

    angreifer->GetController()->setOpfer(opfer);

}

void GameEngine::menue(int i) {

    cout << " Spielerinfos 1 // return 2 // beneden 3 // " << endl;
    int wahl;
    cin>>wahl;


    switch (wahl) {
        case 1:
            m_vector[i]->showInfo();
            break;
        case 2:

            break;
        case 3:
            weiter = false;
            
            break;


    }
}

GameEngine::~GameEngine() {
    delete m_welt;
}


void GameEngine::turn() {

    Tile* neu_t;
    m_welt->print();
    while (weiter) {






        //        if( m_vector[m_vector.size()-1]->GetController()->getOpfer()->GetHitpoints()<=0){
        ////               m_vector[m_vector.size()-1]->GetController()->getOpfer()->~Character();
        //                cout<<"game over"<<endl;
        //                ende = false ;
        //                return;
        //            }
        //        
        //        

        for (int i = 0; i < m_vector.size(); i++) {
            //            
repeat:

            if (m_vector.empty()) {
                weiter = false;
                return;
            }

            if (m_vector[i]->GetHitpoints() < 0) {
               m_vector.erase(m_vector.begin() + i - 1);
                return;
            }
int controller= 0;
            for (Character* c : m_vector) {
                if ((c->GetController()->typ() == "control")) {
                    controller++;
                }
            }

if(controller == 0){
    weiter = false;
    return;
}
            int a = m_vector[i]->GetController()->move();
            DungeonMap::Position p = m_welt->findCharacter(m_vector[i]);
            Tile* t = m_welt->findTile(p);
            DungeonMap::Position p_neu;

            int r = p.Reihe;
            int s = p.Spalte;
            if (a == 1) {
                p_neu.Reihe = r + 1;
                p_neu.Spalte = s - 1;
            } else if (a == 2) {
                p_neu.Reihe = r + 1;
                p_neu.Spalte = s;
            } else if (a == 3) {
                p_neu.Reihe = r + 1;
                p_neu.Spalte = s + 1;
            } else if (a == 4) {
                p_neu.Reihe = r;
                p_neu.Spalte = s - 1;
            } else if (a == 5) {
                p_neu.Reihe = r;
                p_neu.Spalte = s;
                std::cout << " stehen bleiben" << std::endl;
            } else if (a == 6) {
                p_neu.Reihe = r;
                p_neu.Spalte = s + 1;
            } else if (a == 7) {
                p_neu.Reihe = r - 1;
                p_neu.Spalte = s - 1;
            } else if (a == 8) {
                p_neu.Reihe = r - 1;
                p_neu.Spalte = s;
            } else if (a == 9) {
                p_neu.Reihe = r - 1;
                p_neu.Spalte = s + 1;
            } else if (a == 0) {
                menue(i);
                m_welt->print();
                if (weiter == false)
                    return;
                else
                         goto repeat;
                   
            } else {
                std::cout << "1/2/3/4/5/6/7/8/9" << std::endl;
                m_welt->print();
                ////                goto repeat;
                return;
            }

            neu_t = m_welt->findTile(p_neu);
            t->onLeave(neu_t);
            m_welt->print();
        }
    }
}


