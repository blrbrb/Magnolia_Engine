//
//  DefaultGameState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/25/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef DefaultGameState_hpp
#define DefaultGameState_hpp
#include "GameStateModes.hpp"

class DefaultGameState : public GameStateModes
{
    
public:
    
    DefaultGameState(StateData* statedata, GameStateData* gamestatedata);
    virtual ~DefaultGameState();
    
    
    void updateInput(const float& dt);
    void update(const float& dt);
    void updateGUI(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
    
    
    
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updatePlayer(const float& dt);
    void updateEnemies(const float& dt);
    void updateEnemyEncounter();

private:
    
    sf::RenderTexture rendertexture;
    sf::Sprite rendersprite;
    sf::View view;
    


   
  
   
    

    
    
    
    
};

#endif /* DefaultGameState_hpp */
