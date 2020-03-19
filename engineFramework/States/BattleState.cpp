//
//  BattleState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/6/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "BattleState.hpp"


BattleState::BattleState(StateData *state_data) : State(state_data)
{
    this->initview();
    this->initfonts();
    this->inittextures();
    this->inittextures();
    
}

BattleState::~BattleState()
{
    
}

void BattleState::render(sf::RenderTarget *target)
{
    target->draw(this->background);
}

void BattleState::update(const float &dt)
{
    
}

void BattleState::updatePlayerInput(const float &dt)
{

}

void BattleState::updatePlayerGUI(const float &dt)
{
    
}

void BattleState::initkeybinds()
{
    
}

void BattleState::initbackground()
{
    
}

void BattleState::initdeferedrender()
{
    
}

void BattleState::initview()
{
    this->view.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width), static_cast<float>(this->state_data->gfxsettings->resolution.height)));

    this->view.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 2.f,        static_cast<float>(this->state_data->gfxsettings->resolution.height) / 2.f));
}

void BattleState::inittextures()
{
    
 if (!this->textures["PLAYER_SHEET"].loadFromFile(resourcePath() + "Hero.png"))
    {
        std::cout << "ERROR_C 02: GAMESTATE::INITTEXTURES Could Not Load PLAYER_SHEET textures" << std::endl;
        throw std::runtime_error("ERROR CODE 02: GAMESTATE::INITTEXTURES Could Not Load PLAYER_SHEET textures");
    }
}

void BattleState::initplayers()
{
    this->player = new Player(100,50, this->textures["PLAYER_SHEET"]);
}

void BattleState::initfonts()
{
    
}

void BattleState::initpausemenu()
{
    
}

void BattleState::initshaders()
{
    
}

void BattleState::updateInput(const float &dt)
{
    
}


