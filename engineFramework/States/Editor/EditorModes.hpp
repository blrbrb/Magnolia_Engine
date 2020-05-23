//
//  EditorModes.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef EditorModes_hpp
#define EditorModes_hpp
#include "State.hpp"
#include "TileMap.hpp"

class State;
class StateData;
class TileMap; 


class EditorStateData
{
public:
    
    EditorStateData() {};
    
    
    sf::View* view;
    
    float* keytime;
    float* ketyimeMax;
    
    std::map<std::string, int>* keybinds;
    sf::Vector2i* mousePosScreen;
    sf::Vector2i* mousePosWindow;
    sf::Vector2f* mousePosView;
    sf::Vector2i* mouseposGrid;
    sf::Font* font;
    
};


class EditorModes
{
    
protected:
    
    TileMap* tilemap;
    StateData* statedata;
    EditorStateData* editorstatedata;
    
public:
    
    EditorModes(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata);
    virtual ~EditorModes();
    
    const bool getkeytime();
    
    virtual void updateInput(const float& dt) = 0 ;
    virtual void update(const float& dt) = 0;
    virtual void updateGUI(const float& dt) = 0;
    virtual void renderGUI(sf::RenderTarget& target) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
    
    
};

#endif /* EditorModes_hpp */
