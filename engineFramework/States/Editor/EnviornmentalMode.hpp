//
//  EnviornmentalMode.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/10/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef EnviornmentalMode_hpp
#define EnviornmentalMode_hpp
#include "EditorModes.hpp"
class EnviornmentalMode : public EditorModes
{
private:
        
        //interface variables
          sf::Text cursortext;
          GUI::TextureSelector* texture_selector;
          sf::RectangleShape select_Rect;
          sf::RectangleShape sidebar;
          sf::RectangleShape sidebar_texture;
          sf::RectangleShape text_container;
          sf::RectangleShape texturesample; 
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
    
    EnviornmentalMode(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata);
    virtual ~EnviornmentalMode();
    
    //Functions
    
    void updateInput(const float& dt);
    void update(const float& dt);
    void updateGUI(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
    
    
};

#endif /* EnviornmentalMode_hpp */
