//
//  EnemyEditorMode.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/4/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef EnemyEditorMode_hpp
#define EnemyEditorMode_hpp
#include "EditorModes.hpp"

class EnemyEditorMode : public EditorModes
{
public:
    
    EnemyEditorMode(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata);
    virtual ~EnemyEditorMode();
    
    
    void updateInput(const float& dt);
    
    void update(const float& dt);
    
    void updateGUI(const float& dt);
    
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
    
    
private:
        //GUI variables
        sf::Text cursortext;
         GUI::TextureSelector* texture_selector;
         sf::RectangleShape select_Rect;
         sf::RectangleShape sidebar;
         sf::RectangleShape sidebar_texture;
         sf::RectangleShape text_container;
         sf::IntRect TextureRect;
    
    int layer;
    int type; 
    //Tile variables
     
    int Enemytype;
    int Enemyamount;
    int spawn_timer;
    float maxDistance;
    
    //initalizer functions
    void initGUI();
    void initvariables();
    void inittext();
    
    
    
};

#endif /* EnemyEditorMode_hpp */
