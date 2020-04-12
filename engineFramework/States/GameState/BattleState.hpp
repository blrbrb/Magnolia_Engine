//
//  BattleState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 4/11/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef BattleState_hpp
#define BattleState_hpp
#include "State.hpp"


class BattleState : public State
{
 
public:
    
    BattleState(StateData* state_data);
    
    virtual ~BattleState();
    
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
    
    
    
private: 
    
    void initkeybinds();
    sf::RectangleShape tester; 
    
    
};

#endif /* BattleState_hpp */
