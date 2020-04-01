//
//  DefaultGameState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/25/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "DefaultGameState.hpp"


DefaultGameState::DefaultGameState(StateData *statedata, GameStateData *gamestatedata)  :GameStateModes(statedata, gamestatedata)
{
    
}

DefaultGameState::~DefaultGameState()
{
    
}

void DefaultGameState::updateInput(const float &dt)
{
    
}

void DefaultGameState::update(const float &dt)
{
    std::cout << "Working!!" << std::endl; 
    
}

void DefaultGameState::updateGUI(const float &dt)
{
    
}

void DefaultGameState::renderGUI(sf::RenderTarget &target)
{
    
}

void DefaultGameState::render(sf::RenderTarget &target)
{
    
}


void DefaultGameState::updatePlayerInput(const float &dt)
{
    
}

void DefaultGameState::updatePlayerGUI(const float &dt)
{
    
}

void DefaultGameState::updatePlayer(const float &dt)
{
    
}

void DefaultGameState::updateEnemies(const float &dt)
{
    
}

void DefaultGameState::updateEnemyEncounter()
{
    
}


