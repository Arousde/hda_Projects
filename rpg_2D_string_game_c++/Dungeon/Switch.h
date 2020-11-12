/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Switch.h
 * Author: arous
 *
 * Created on 6. Mai 2017, 12:03
 */


#ifndef SWITCH_H
#define SWITCH_H
#include "Aktive.h"

class Switch : public Aktive {
public:
    Switch();
//    virtual void Setbetreten() override;
//    virtual bool Istbetreten() const override;
//    virtual void Set_Ptr_passive(Passive* t_pass) override ;
//    virtual void onLeave(Tile* toTile)override ;
    virtual void onEnter(Character* c, Tile* fromTile)override ;
    virtual void Zeichen() override;
};


#endif /* SWITCH_H */

