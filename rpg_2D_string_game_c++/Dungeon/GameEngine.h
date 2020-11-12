
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include<vector>
#include "DungeonMap.h"

class GameEngine {
public:
    GameEngine(int height, int width, const std::vector<std::string>& data, std::vector<std::string> &v);

//    DungeonMap GetWelt() const {
//        return m_welt;
//    }

    std::vector<Character*> GetVector() const {
        return m_vector;
    }
    void turn();
    void menue(int i);
    
    virtual ~GameEngine() ;
    
private:
    std::vector<Character*> m_vector;
    DungeonMap* m_welt;
    bool weiter ;
};

#endif /* GAMEENGINE_H */

