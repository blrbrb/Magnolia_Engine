//
//  BattleState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 4/11/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef BattleState_hpp
#define BattleState_hpp
#include "State.hpp"
#include "GameState.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "PlayerGUI.hpp"
#include "BattleGUI.hpp"


class Enemy;
class State;
class GameStateData;

class BattleState : public State
{
 
public:
    
    BattleState(StateData* state_data, GameStateData* gamestatedata, Player* player, PlayerGUI* PlayerGUI,Enemy* enemy);
    
    virtual ~BattleState();
    
    //update functions
    void updateInput(const float& dt); 
    void update(const float& dt);
    void updateeventtime(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updateEnemies(const float& dt);
    void updateButtons(const float& dt);
    void updatePauseMenu(); 
    void updateBattleGUI(const float& dt);
    void updateCombat();
    void checkHP(); 
   
    void PlayerAttack(); 
    
    
    //modifiers
    void GiveEnemyDamage(const float& dt);

    
    //Accessors
    ///turn based battle accessor. Returns wether or not the player, or enemy has taken a turn
    bool getturn();
    const bool getEventtime();
    
    //render functions
    void render(sf::RenderTarget* target = NULL);
    void renderBattleGUI(sf::RenderTarget& target);
 
    //Misc
   
    

protected:
    
    //protected vars that send in conditional data about the player, the enemy to the battlestate constructor
    GameStateData* gamestatedata;
    Player* player;
    PlayerGUI* PlayerGUI;
    BattleGUI* battleGUI;
    Enemy* enemy;
    
    
private:
    
    
    //Mechanics Variable
    bool PlayerTurn;
    bool playerDed;
   
    bool enemyDed; 
    //core variables
    sf::Font font; 
    GameStateData* Gamestatedata;
    PauseMenu* pMenu;
    
    //Pause Menu Functions

    //initalizaion functions
    void initview(); 
    void initkeybinds();
    void initpausemenu();
    void initrender();
    void initplayerGUI();
    void initVariables(); 
    
    //Timing
    float eventtime;
    const float eventtimeMax; 
    //render varialbes
    sf::RenderTexture rendertexture;
    sf::Sprite rendersprite; 
    sf::View view;
    
};

#endif /* BattleState_hpp */
