//
//  PauseMenu.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#ifndef PauseMenu_hpp
#define PauseMenu_hpp

#include "GUI.hpp"



/// The PauseMenu
class PauseMenu
{
    
private:
    
    sf::RectangleShape background;
    sf::RectangleShape container;
    sf::Font& font;
    sf::Text menutext;
    
    std::map<std::string, GUI::Button*> buttons;
    
    
    
public:
    
    
    /// Construct a new PauseMenu
    /// @param vm The VideoMode the PauseMenu will be rendered to
    /// @param font for elements in the PauseMenu to use 
     PauseMenu(sf::VideoMode& vm, sf::Font& font);
     virtual ~PauseMenu();
    
    
    ///Fetch the address to the container holding all of the PauseMenu Buttons
    std::map<std::string, GUI::Button*>& getButtons();
    
    
    /// @brief Fetch a particular button attached to the PauseMenu, and see wether or not it has been pressed
    /// @param key std::string refrence to the button in question
    /// @returns const bool, wether or not the button has been pressed
    const bool isButtonPressed(const std::string& key);
    
    /// @brief addbutton
    ///
    ///  @discussion Construct buttons using the GUI Button constructor, and add them to the PauseMenu. Buttons are pushed back  to an array of Buttons, and stored in a std::map container. It is possible to fetch a particular button using the string assigned to the button on it's construction.
    /// @param key std::string name of the Button
    /// @param charSize @const unsigned
    /// @param text text for the button to display
    /// @param width width of the new button
    /// @param height height of the new button
    /// @param y Y position of the new button on screen
    ///@discussion Currently, it is not possible to control the X axis of the button array's position on screen
    void addbutton(const std::string key, const unsigned charSize, const std::string text, const float width, const float height, const float y);
    

    void update(const sf::Vector2i& MousePos);
    void render(sf::RenderTarget& target);
    
};



#endif /* PauseMenu_hpp */
