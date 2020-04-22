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
#include "GameState.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "PlayerGUI.hpp"

class PlayerGUI;
class Enemy;
class State;
class GameStateData;

class BattleState : public State
{
 
public:
    
    BattleState(StateData* state_data, GameStateData* gamestatedata, Player* player, PlayerGUI* PlayerGUI, Enemy* enemy);
    
    virtual ~BattleState();
    
    //update functions
    void updateInput(const float& dt); 
    void update(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updatePlayer(const float& dt);
    void updateEnemies(const float& dt);
    void updateButtons();
    void updateBattleGUI(const float& dt, const sf::Vector2i MousePos);
    
    //Accessors
    ///turn based battle accessor. Returns wether or not the player, or enemy has taken a turn
    bool getturn();
    
    //render functions
    void render(sf::RenderTarget* target = NULL);
    void renderBattleGUI(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    

protected:
    
    //protected vars that send in conditional data about the player, the enemy to the battlestate constructor
    GameStateData* gamestatedata;
    Player* player;
    PlayerGUI* playerGUI;
    Enemy* enemy;
    
    
private:
    
    //core variables
    void initkeybinds();
    sf::RectangleShape background; 
    GameStateData* Gamestatedata;
    
    //Battle GUI variables / initalizers
    void initbattleGUI();
    sf::RectangleShape BattleGUIcontainer;
    std::map<std::string, GUI::Button*> BUTTONS;
    sf::Font font; 

    //initalizaion functions
    void initview(); 
    
    //render varialbes
    
    sf::View view;
    
};

#endif /* BattleState_hpp */
