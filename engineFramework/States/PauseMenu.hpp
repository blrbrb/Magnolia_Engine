//
//  PauseMenu.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/3/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
// 

#ifndef PauseMenu_hpp
#define PauseMenu_hpp

#include "GUI.hpp"



class PauseMenu
{
    
private:
    
    sf::RectangleShape background;
    sf::RectangleShape container;
    sf::Font& font;
    sf::Text menutext;
    
    std::map<std::string, GUI::Button*> buttons;
    
    
    
public:
    //Constructors and Destructors
     PauseMenu(sf::VideoMode& vm, sf::Font& font);
     virtual ~PauseMenu();
    
    //Accessor
    std::map<std::string, GUI::Button*>& getButtons();
    
    //Functions
    const bool isButtonPressed(const std::string& key);
   
    void addbutton(const std::string key, const unsigned charSize, const std::string text, const float width, const float height, const float y);
    

    void update(const sf::Vector2i& MousePos);
    void render(sf::RenderTarget& target);
    
};



#endif /* PauseMenu_hpp */
