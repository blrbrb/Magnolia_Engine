//
//  State.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#include "State.hpp"


State::State(StateData* state_data) : quit(false), paused(false) {
    
    this->supportedkeys = state_data->supportedkeys;
    this->state_data = state_data;
    this->states = state_data->states;
    this->window = state_data->window;
    this->keytime = 0.f; 
    this->keytime_MAX = 2.3f;
    this->gridsize = state_data->gridsize;
}

State::~State() {
    
    
}


const bool State::getkeytime()
{
  
    
    if (this->keytime >= this->keytime_MAX)
    {
        this->keytime = 0.f;
        return true;
    }
    
    return false;
}
    
    

const bool & State::getquit()const
{
   
    
    return this->quit;
    
}

void State::endstate()
{
   
    this->quit = true;
    
    
}
    
  
void State::updateInput(const float& dt)
{
        
        
}


void State::updateMousePosition(sf::View* view)
{
    
    
    this->MousePosWindow = sf::Mouse::getPosition();
    this->MousePosScreen = sf::Mouse::getPosition(*this->window);

    if(view)
    this->window->setView(*view);
    
    
    this->MousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    this->MousePosGrid = sf::Vector2i(static_cast<int>(this->MousePosView.x) / static_cast<int>(this->gridsize),
                                      static_cast<int>(this->MousePosView.y) / static_cast<int>(this->gridsize));
   
    this->window->setView(this->window->getDefaultView());
}

void State::updatekeytime(const float& dt)
{
 
    if (this->keytime < this->keytime_MAX)
    {
        this->keytime += 10.f * dt;
    }

}



void State::Pause_State()
{
   
    this->paused = true;
}


void State::Unpause_State()
{
    
  
    this->paused = false; 
    
}


