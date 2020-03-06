//
//  State.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
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

//Acessors
const bool State::getkeytime()
{
    /**
    @class State
    @brief Acess the keytime
        @see updatekeytime()
     @sa updatekeytime()
    @discussion You can use this function to create a minimum amount of time that must pass before the user can acess a button, or key again.
    @return const bool
     */
    
    if (this->keytime >= this->keytime_MAX)
    {
        this->keytime = 0.f;
        return true;
    }
    
    return false;
}
    
    

const bool & State::getquit()const
{
    /**
    @class State
    @brief Access wether or not the user has opted to quit the application
    @return const bool
     */
    
    return this->quit;
    
}

void State::endstate()
{
    /**
    @class State
    @brief End the Current State
    @discussion   This function changes the value of the "quit" variable to true, which then is constantly updated by  the game, and accessed by  the getquit() function.
         @see State::getquit()
    @param   void
    @return  void
          */
    this->quit = true;
    
    
}
    
  
void State::updateInput(const float& dt)
{
        
        
}





void State::updateMousePosition(sf::View* view)
{
    /**
    @class State
    @brief Update the MousePositions
    @param sf::View* view
     @sa updatekeytime()
    @discussion You can use this function to access the position of the User's Mouse relative to either the grid, the view, or the window.
    @return void
     */
    
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
    /**
    @class State
    @brief Update the keytime using the delta time variable from the SF clock
        @see update()
        @sa update()
    @return const bool
     */
    if (this->keytime < this->keytime_MAX)
    {
        this->keytime += 10.f * dt;
    }

}



void State::Pause_State()
{
    /**
     @class State
     @brief Pause the current state
        @see Unpause_State()
                    @sa Unpause_State()
     @param   NULL
     @return  a true boolean value for paused
    */
    
    this->paused = true;
}


void State::Unpause_State()
{
    
  /**
   *@brief Unpause the current state
   *@see Pause_State()
   *      @sa Pause_State()
   *@param   NULL
   *
   *@return void
   *
   *@return  a false boolean value for paused
   */
    this->paused = false; 
    
}


