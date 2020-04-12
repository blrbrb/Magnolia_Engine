//
//  BattleState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 4/11/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "BattleState.hpp"


BattleState::BattleState(StateData *state_data) : State(state_data)
{
    
}

BattleState::~BattleState()
{
    
}

void BattleState::updateInput(const float &dt)
{

}

void BattleState::update(const float &dt)
{
    this->tester.setSize(sf::Vector2f(1000, 1000));
    this->tester.setFillColor(sf::Color::Red);
}

void BattleState::render(sf::RenderTarget *target)
{
    target->draw(this->tester);
}

void BattleState::initkeybinds()
{
    
    
}
