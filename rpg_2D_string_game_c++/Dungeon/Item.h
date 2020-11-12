/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.h
 * Author: arous
 *
 * Created on 20. Mai 2017, 12:31
 */


#ifndef ITEM_H
#define ITEM_H
class Item{
    public:
        Item();
      virtual  int modifyStrength(int strength )=0;
      virtual int modifyStamina(int stamina)=0;

      
    
    
};

#endif
 /* ITEM_H */

#ifndef ArmingSword_H
#define ArmingSword_H

class ArmingSword : public Item{
public :
    ArmingSword();
    int modifyStrength(int strength )override;
    int modifyStamina(int stamina )override;
};
#endif 


#ifndef Greatsword_H
#define Greatsword_H

class Greatsword : public Item{
public :
    Greatsword();
    int modifyStrength(int strength)override;
    int modifyStamina(int stamina)override;
};
#endif 


#ifndef Club_H
#define Club_H

class Club : public Item{
public :
    Club();
    int modifyStrength(int strength)override;
    int modifyStamina(int stamina)override;

};
#endif 


#ifndef RapierUndDagger_H
#define RapierUndDagger_H

class RapierUndDagger : public Item{
public :
    RapierUndDagger();
    int modifyStrength(int strength)override;
    int modifyStamina(int stamina)override;
};
#endif 


#ifndef Gambeson_H
#define Gambeson_H

class Gambeson : public Item{
public :
    Gambeson();
    int modifyStrength(int strength)override;
    int modifyStamina(int stamina)override;
};
#endif 


#ifndef MailArmour_H
#define MailArmour_H
class MailArmour : public Item{
public :
    MailArmour();
    int modifyStrength(int strength)override;
    int modifyStamina(int stamina)override;
};
#endif 

#ifndef Shield_H
#define Shield_H
class Shield : public Item{
public :
    Shield();
    int modifyStrength(int strength)override;
    int modifyStamina(int stamina)override;
};
#endif 


#ifndef FullPlateArmour_H
#define FullPlateArmour_H
class FullPlateArmour : public Item{
public :
    FullPlateArmour();
    int modifyStrength(int strength)override;
    int modifyStamina(int stamina)override;
};
#endif 



