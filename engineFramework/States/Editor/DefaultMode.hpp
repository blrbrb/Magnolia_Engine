//
//  DefaultMode.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef DefaultMode_hpp
#define DefaultMode_hpp
#include "EditorModes.hpp"
#include "State.hpp"
#include "GUI.hpp"

class State;
class EditorModes;
class StateData;
class EditorStateData; 

class DefaultMode : public EditorModes
{
    
private:
        
        //interface variables
          sf::Text cursortext;
          sf::Text controls;
          GUI::TextureSelector* texture_selector;
          sf::RectangleShape select_Rect;
          sf::RectangleShape sidebar;
          sf::RectangleShape sidebar_texture;
          sf::RectangleShape texturesample;
          sf::RectangleShape texturesample_container; 
          sf::RectangleShape text_container;
          sf::RectangleShape controlsContainer; 
          sf::IntRect TextureRect;
         
     
        //Tile variables
    bool collision;
    short type;
    int layer;
    
    //initalizer functions
    void initvariables();
    void inittext();
    void initGUI(); 
    
    
public:
    
    DefaultMode(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata);
    virtual ~DefaultMode();
    
    //Functions
    
    void updateInput(const float& dt);
    void update(const float& dt);
    void updateGUI(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
    
    
};

#endif /* DefaultMode_hpp */
