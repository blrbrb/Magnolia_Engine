//
//  PlayerGUI.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/24/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef PlayerGUI_hpp
#define PlayerGUI_hpp
#include "GUI.hpp"
#include "Player.hpp"

class Player;



class PlayerGUI
{
private:
    
    Player* player;
    sf::VideoMode& vm;
    
    //Level Tag
    std::string LevelTagstring;
    sf::Text LevelTagText;
    sf::RectangleShape LevelTagExterior;
        
    //Exp bar
    GUI::ProgressBar* ExpBar;
    
    //Health bar
    sf::Font font;
    GUI::ProgressBar* HPbar;
    
    //Inventory
    
    
    //inventory
    
    
    //COINS
    sf::Sprite monies;
    sf::Texture coinIcon;
    std::string money_string; 
    sf::Text money;
    int max = 99;
    

    void initfont();
    void initLevelTag();
    void initHPbar();
    void initEXPbar();
    void initMONEY();
    void initinventory();
    
public:
    
    PlayerGUI(Player* player, sf::VideoMode& vm);
    virtual ~PlayerGUI();
    
    //Functions
    void updateLevelTag();
    void updateHPbar();
    void updateEXPbar();
    void updateMoney(); 
    void update(const float& dt);
    void renderLevelTag(sf::RenderTarget& target);
    void renderHPbar(sf::RenderTarget& target);
    void renderMoney(sf::RenderTarget& target);
    void renderEXPbar(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
    
    
};

#endif /* PlayerGUI_hpp */
