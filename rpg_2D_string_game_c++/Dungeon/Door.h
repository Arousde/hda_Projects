#ifndef DOOR_H
#define DOOR_H
#include "Passive.h"

class Door : public Passive {
public:
    Door();
//    virtual void onLeave(Tile* toTile) override;
    virtual void onEnter(Character* c, Tile* fromTile) override;
//    virtual void SetStatus(bool Status) override;
//    virtual bool GetStatus() const override;
    virtual void Zeichen() override;
    bool isTransparent()override;
    bool isBetretbar() override;
};


#endif /* DOOR_H */




