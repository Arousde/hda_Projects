#ifndef PASSIVE_H
#define PASSIVE_H
#include "Tile.h"

class Passive : public Tile{
    public: 
        Passive();
       virtual void SetStatus(bool Status);
       virtual bool GetStatus() const;
        
        
        protected: 
            bool Status;
};

#endif /* PASSIVE_H */

