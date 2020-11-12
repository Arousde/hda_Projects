
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Controller.h"
#include "ConsoleController.h"
#include "Item.h"
#include <vector>
class Controller;

class Character {
public:

    Character(char Zeichen,int Strength,int Stamina,Controller* c);
    virtual ~Character();
    void SetController(Controller* Controller);
    
    int move();
    Controller* GetController() const;
    void SetZeichen(char Zeichen);
    char GetZeichen() const;
    int getMaxHP();
    void showInfo();
    int GetStamina() ;
    int GetStrength();
    void addItem(Item* item);
    void SetHitpoints(int Hitpoints);
    int GetHitpoints() const;

private:
    char m_Zeichen;
    Controller* m_Controller;
    int m_Strength;
    int m_Stamina;
    int m_Hitpoints;
    std::vector<Item*> m_vec_Item;
};


#endif /* CHARACTER_H */
