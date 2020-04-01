//
//  GameStateModes.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/21/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef GameStateModes_hpp
#define GameStateModes_hpp
#include "Player.hpp"
#include "Enemies_Include.h"
#include "PlayerGUI.hpp"
#include "EnemySystem.hpp"
#include "State.hpp"
#include "TileMap.hpp"
#include "PauseMenu.hpp"



class GameStateData
{
public:
    
    GameStateData() {};
    
    sf::View* view; 
    
    float* keytime;
    float* ketyimeMax;
    Player* player;
    TileMap* Tilemap;
    std::vector<Enemy*> activeEnemies;
    Enemy* enemy;
    PlayerGUI* playerGUI;
    EnemySystem* enemysystem;
    sf::Shader* core_shader;
    sf::Font* font;
    
};

class GameStateModes
{
protected:
    
    StateData* statedata;
    GameStateData* gamestatedata;
    
public:
    
    GameStateModes(StateData* satedata, GameStateData* gamestatedata);
    virtual ~GameStateModes();
    
    //Acccessors
     const bool getkeytime();
        
    //Functions
    virtual void updateInput(const float& dt) = 0 ;
    virtual void update(const float& dt) = 0;
    virtual void updateGUI(const float& dt) = 0;
    virtual void renderGUI(sf::RenderTarget& target) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
    
    
private:
    
    
};

#endif /* GameStateModes_hpp */
