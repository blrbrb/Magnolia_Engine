//
//  GameState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp
#include "State.hpp"
#include "Player.hpp"
#include "PlayerGUI.hpp"
#include "PauseMenu.hpp"
#include "TileMap.hpp"
#include "Enemy.hpp"

class Enemy;
class PlayerGUI;
class PauseMenu;
class Player;
class TileMap;



class GameState : public State {


public:
    //Constructor et Destructor
    GameState(StateData* state_data);
    virtual ~GameState();
       
    //Functions
    void updateView(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
    void checkforendstate();
    void updateInput(const float& dt);
    void updatebuttons();
    void updatetilemap(const float& dt);
    
    
private:
    
    //View and Camera
    sf::View view;
    float cameraspeed;
    
    //Componet init
    Player* player;
    PlayerGUI* playerGUI;
    PauseMenu* pMenu;
    TileMap* Tilemap;
    Enemy* test_enemy; 
    sf::Font font;
    sf::RenderTexture rendertexture;
    sf::Sprite rendersprite;
    
    //Shaders
    sf::Shader core_shader;
    
    //Sounds
    sf::SoundBuffer buffer;
    sf::Sound sound; 
    sf::Vector2i ViewGridPosition;
    
    
    
    
    //Init Functions
    void initdeferedrender();
    void initview(); 
    void initkeybinds();
    void inittextures();
    void initplayers();
    void initplayerGUI();
    void initfonts();
    void initpausemenu();
    void inittilemap();
    void initshaders();
    
};
#endif /* GameState_hpp */
