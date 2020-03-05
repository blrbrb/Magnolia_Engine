//
//  EditorModes.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "EditorModes.hpp"

EditorModes::EditorModes(StateData* statedata, TileMap* tilemap, EditorStateData* editorstatedata) : statedata(statedata), tilemap(tilemap), editorstatedata(editorstatedata)
{
    
    

}


EditorModes::~EditorModes()
{
    
    
    
    
    
    
    
    
}


void EditorModes::updateInput(const float& dt)
{
    
}

void EditorModes::update(const float &dt)
{
    
}

void EditorModes::updateGUI(const float &dt)
{
    
}

void EditorModes::renderGUI(sf::RenderTarget &target)
{

}

void EditorModes::render(sf::RenderTarget & target)
{
    
}

const bool EditorModes::getkeytime()
{
    /**
    @class EditorModes
    @brief Acess the keytime
        @see updatekeytime()
     @sa updatekeytime()
    @discussion You can use this function to create a minimum amount of time that must pass before the user can acess a button, or key again.
    @return const bool
     */
    
    if (*this->editorstatedata->keytime >= *this->editorstatedata->ketyimeMax)
    {
        *this->editorstatedata->keytime = 0.f;
        return true;
    }
    
    return false;
}
