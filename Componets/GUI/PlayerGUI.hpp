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
#include "Inventory.hpp"


class Player;
class Inventory;



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
    
    std::vector<sf::RectangleShape> Itemboxes;
    //inventory
    
    
    //COINS
    sf::Sprite monies;
    sf::Texture coinIcon;
    std::string money_string; 
    sf::Text money;
    int max = 99;
    int maxItems;
    int currentSize; 
    

    void initfont();
    void initLevelTag();
    void initHPbar();
    void initEXPbar();
    void initMONEY();
    void initinventory();
    void initvariables();
  
    
public:
    
    PlayerGUI(Player* player, sf::VideoMode& vm);
    virtual ~PlayerGUI();
    
    //Functions
    void updateLevelTag();
    void updateHPbar();
    void updateEXPbar();
    void updateMoney();
    void updateInventory();
    void update(const float& dt);
    void renderLevelTag(sf::RenderTarget& target);
    void renderHPbar(sf::RenderTarget& target);
    void renderMoney(sf::RenderTarget& target);
    void renderEXPbar(sf::RenderTarget& target);
    void renderInventory(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
    
    
};





//end namespace PlayerGUI


#endif /* PlayerGUI_hpp */
