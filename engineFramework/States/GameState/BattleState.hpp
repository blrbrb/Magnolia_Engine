//
//  BattleState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/6/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef BattleState_hpp
#define BattleState_hpp
#include "State.hpp"
#include "Player.hpp"
#include "Enemies_Include.h"
#include "GameState.hpp"
#include "GameStateModes.hpp"


class BattleState : public GameStateModes
{
    
public:
    
    
    BattleState(StateData* statedata, GameStateData* gamestatedata);
    virtual ~BattleState();
    
    //Functions
    void updateInput(const float& dt);
    void update(const float& dt);
    void updateGUI(const float& dt);
    void updatecombat();
    void updateenemies(); 
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
    
    
private:

    sf::RectangleShape background;
    sf::Texture backgroundtexture;
    
};



#endif /* BattleState_hpp */
