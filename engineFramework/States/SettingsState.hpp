//
//  SettingsState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/5/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef SettingsState_hpp
#define SettingsState_hpp
#include "State.hpp"
#include "GUI.hpp"

/// Class with methods that allow the user to change basic settings 
class SettingsState : public State
{
private:
    
        //Functions
         void initkeybinds();
         void initFonts();
         void initGUI();
         void resetGUI();
         void initvariables();
       
    
       //Variables
    sf::Font font;
    sf::RectangleShape background;
    
    sf::Texture backgroundTexture;
    sf::Text option_text;
    std::map<std::string, GUI::Button*> buttons;
    std::map<std::string, GUI::DropDownList*> dropdownlists;
    std::vector<sf::VideoMode> modes;
    
    
    
public:
    
    SettingsState(StateData* state_data);
    virtual ~SettingsState();
    
    //Accessors
    
    
    //Functions
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void update(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
    
};

#endif /* SettingsState_hpp */
