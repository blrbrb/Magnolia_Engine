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
    float EXPbarMaxWidth;
    std::string EXPstring;
    sf::Text EXPbarText;
    sf::RectangleShape EXPbarExterior;
    sf::RectangleShape EXPbarInterior;
    
    //Health bar
    float hpbarMaxWidth;
    std::string HPString; 
    sf::Text HPbarText; 
    sf::Font font;
    sf::RectangleShape HPbarExterior;
    sf::RectangleShape HPbarInterior;
    
 
    

    void initfont();
    void initLevelTag();
    void initHPbar();
    void initEXPbar(); 
    
public:
    
    PlayerGUI(Player* player, sf::VideoMode& vm);
    virtual ~PlayerGUI();
    
    //Functions
    void updateLevelTag();
    void updateHPbar();
    void updateEXPbar();
    void update(const float& dt);
    void renderLevelTag(sf::RenderTarget& target);
    void renderHPbar(sf::RenderTarget& target);
    void renderEXPbar(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
    
    
};

#endif /* PlayerGUI_hpp */
