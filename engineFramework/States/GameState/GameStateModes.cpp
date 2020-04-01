//
//  GameStateModes.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/21/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "GameStateModes.hpp"


GameStateModes::GameStateModes(StateData *satedata, GameStateData *gamestatedata) :statedata(satedata), gamestatedata(gamestatedata)
{
    
    
    
}

GameStateModes::~GameStateModes()
{
    
}



const bool GameStateModes::getkeytime()
{
       if (*this->gamestatedata->keytime >= *this->gamestatedata->ketyimeMax)
        {
            *this->gamestatedata->keytime = 0.f;
            return true;
        }
        
        return false;
}
