//
//  BattleState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 4/11/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "BattleState.hpp"


BattleState::BattleState(StateData* state_data, GameStateData* gamestatedata, Player* player, PlayerGUI* PlayerGUI, Enemy* enemy) : State(state_data), Gamestatedata(gamestatedata), player(player), playerGUI(PlayerGUI), enemy(enemy)
{
    this->initbattleGUI();
    this->background.setSize(sf::Vector2f(1400, 1000));
    this->background.setFillColor(sf::Color(120, 120, 120, 250));
    this->initview();
    
    
}

BattleState::~BattleState()
{
    auto it = BUTTONS.begin();
        for (it = BUTTONS.begin(); it != this->BUTTONS.end(); ++it)
       
        {
            delete it->second;
            
        }

}


void BattleState::initview()
{
    this->view.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.F, static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f));

    this->view.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.f,        static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f));
}




    




void BattleState::initbattleGUI()
{
    const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
    
    this->font.loadFromFile(resourcePath() + "PressStart2P.tff");

    
       this->BattleGUIcontainer.setSize(sf::Vector2f(500, 200));
       this->BattleGUIcontainer.setFillColor(sf::Color::Black);
       this->BattleGUIcontainer.setOutlineThickness(1.f);
       this->BattleGUIcontainer.setOutlineColor(sf::Color::White);
       this->BattleGUIcontainer.setPosition(GUI::pixelpercentX(25, vm), GUI::pixelpercentY(25,vm));
       
   this->BUTTONS["ATTACK"] = new GUI::Button(GUI::pixelpercentX(50,vm), GUI::pixelpercentY(75, vm), GUI::pixelpercentY(10, vm), GUI::pixelpercentX(75, vm), &this->font, "Attack", GUI::calcCharSize(vm, 100), "red_button01.png", "red_button02.png", "red_button00.png");

    
    
    
}


void BattleState::updateBattleGUI(const float &dt, const sf::Vector2i MousePos)
{
   
    for (auto &it : this->BUTTONS)
          {
              it.second->update(MousePos);
       
          }
    
}

void BattleState::updateInput(const float& dt)
{
    
    this->updateButtons();
    
    
    
}
void BattleState::updateButtons()
{
    for (auto &it : this-> BUTTONS)
    
     {
         it.second->update(this->MousePosWindow);
         
     }
        
    if(this->BUTTONS["ATTACK"]->isPressed())
       {
           
           std::cout << "attacking!!" << std::endl;
       }

    
}


void BattleState::updatePlayer(const float& dt)
{
    
    
}

void BattleState::updateEnemies(const float& dt)
{
    this->enemy->update(dt, this->MousePosView);
    
}

void BattleState::updatePlayerGUI(const float& dt)
{
     this->playerGUI->update(dt);
}

void BattleState::update(const float &dt)
{
    this->updatePlayer(dt);
    this->updatePlayerGUI(dt);
    this->updateInput(dt);
   
    
}

void BattleState::renderBattleGUI(sf::RenderTarget& target)
{
    
    
 
    target.draw(this->BattleGUIcontainer);
}



void BattleState::renderButtons(sf::RenderTarget& target)
{
    for (auto &it : this->BUTTONS)
       {
           it.second->render(target);
    
       }
    
}


void BattleState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;
    
    target->clear();
    
    this->renderBattleGUI(*target);
    this->renderButtons(*target);
    this->player->render(*target);
    this->enemy->render(*target);
    
    
}

void BattleState::initkeybinds()
{
    
    
}
