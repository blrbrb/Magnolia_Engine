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

class BattleState : public State
{
    
public:
    
    BattleState(StateData* state_data);
    virtual ~BattleState();
    
    //Functions 
    void render(sf::RenderTarget* target = NULL);
    
    
    //update functions
    void update(const float& dt);
    void updatePlayerInput(const float& dt);
    void updateCombat(const float& dt);
    void updatePlayerGUI(const float& dt);
     
    
    
private:
    
   
    Player* player;
    sf::Shader core_shader;
    
    
    sf::Font font;
    
    //GUI
    sf::RectangleShape background;
    sf::RenderTexture rendertexture;
    sf::Sprite rendersprite;
    sf::View view; 
    
    sf::Vector2i ViewGridPosition;
    
    //initalizer functions
    void initkeybinds();
    void initbackground();
    void initdeferedrender();
    void initview();
    void inittextures();
    void initplayers();
    void initfonts();
    void initpausemenu();
    void initshaders();
    

       
};

#endif /* BattleState_hpp */
