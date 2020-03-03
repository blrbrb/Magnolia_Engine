//
//  EditorModes.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef EditorModes_hpp
#define EditorModes_hpp
#include "State.hpp"


class EditorModes
{
    
private:
    StateData* statedata; 
public:
    
    EditorModes(StateData* statedata);
    virtual ~EditorModes();
    
    
    virtual void updateInput(const float& dt) = 0 ;
    virtual void update(const float& dt) = 0;
    virtual void updateGUI(const float& dt) = 0;
    virtual void renderGUI(sf::RenderTarget& target) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
    
    
};

#endif /* EditorModes_hpp */
