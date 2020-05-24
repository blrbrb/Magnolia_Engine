//
//  BattleGUI.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 5/17/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef BattleGUI_hpp
#define BattleGUI_hpp
#include "GUI.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


class BattleGUI
{
private:
        //initilization functions
        void initcontainer();
        void initButtons();
        void inittext();
        void initfont();
        void initenemyHPbar();
       
        
        sf::RectangleShape BattleGUIcontainer;
        sf::RectangleShape enemyLevelTag;
        std::map<std::string, GUI::Button*> BUTTONS;
        sf::Text enemyStats;
        sf::Font font;
        sf::Text enemyleveltag;
        sf::VideoMode& vm;
        
       GUI::ProgressBar* enemyHP;
        
        Player* player;
        Enemy* enemy;
    

    public:
        
        BattleGUI(Player* player, Enemy* enemy, sf::VideoMode& vm);
        virtual ~BattleGUI();
    
    //Accessors
          const bool isButtonPressed(const std::string key);
    
        void update(const float& dt);
        void updatebuttons(const sf::Vector2i MousePos);
        void updateenemyHPbar();
        void render(sf::RenderTarget& target);
        void renderHPBar(sf::RenderTarget& target);
        void renderButtons(sf::RenderTarget& target);
        void renderContainer(sf::RenderTarget& target);
        void renderTag(sf::RenderTarget& target);
        
    
};

#endif /* BattleGUI_hpp */
