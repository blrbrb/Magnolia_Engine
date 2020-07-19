//
//  BattleState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 4/11/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "BattleState.hpp"


BattleState::BattleState(StateData* state_data, GameStateData* gamestatedata, Player* player, class PlayerGUI* PlayerGUI, Enemy* enemy) : State(state_data), Gamestatedata(gamestatedata), player(player), PlayerGUI(PlayerGUI), enemy(enemy), eventtimeMax(50.f)
{

    try
    {
        this->initVariables();
        this->initrender();
        this->initview();
        this->initpausemenu();
        this->initplayerGUI();
    }
    
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl; 
    }
    
    //Player always takes first turn
    this->PlayerTurn = true;
    
    
}

BattleState::~BattleState()
{
    
    delete this->battleGUI;
    delete this->pMenu;
   
  

}


void BattleState::initVariables()
{
    this->eventtime = 0.f;

}


void BattleState::initrender()
{
    

        if(!this->rendertexture.create(this->state_data->gfxsettings->resolution.width,this->state_data->gfxsettings->resolution.height))
        {
            throw std::runtime_error("unable to create rendertextrue");
        }

        this->rendersprite.setTexture(this->rendertexture.getTexture());
       
        this->rendersprite.setTextureRect(
            sf::IntRect(
                0,
                0,
                        this->state_data->gfxsettings->resolution.width,
                        this->state_data->gfxsettings->resolution.height
            )
      
                                                                            );
        
}



void BattleState::initview()
{
    this->view.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.F, static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f));

    this->view.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.f,        static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f));
}

void BattleState::initpausemenu()
{
    
    const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
       
    this->pMenu = new PauseMenu(this->state_data->gfxsettings->resolution, this->font);
       
    this->pMenu->addbutton("Pause_Quit_Button",GUI::calcCharSize(vm),"Quit",GUI::pixelpercentX(13.f, vm), GUI::pixelpercentY(6.f, vm), 200.f);
    
}


void BattleState::updateBattleGUI(const float &dt)
{
    this->battleGUI->update(dt);
}

void BattleState::updatePauseMenu()
{
        if(this->pMenu->isButtonPressed("Pause_Quit_Button"))
        {
            this->endstate();
        }
}

void BattleState::updateInput(const float& dt)
{
    
    this->updateButtons(dt);

    
    
    
}
void BattleState::updateButtons(const float& dt)
{
    this->battleGUI->updatebuttons(this->MousePosScreen);
    

    if(this->battleGUI->isButtonPressed("ATTACK") && this->getEventtime())
    {
        
        this->PlayerAttack();
        this->enemy->animtioncomponet->play("ATTACKED", dt);
        
            if(this->PlayerTurn)
                this->PlayerTurn = false;
            else
                this->PlayerTurn = true;
        
    }
    
    
    

}



void BattleState::PlayerAttack()
{
    
    this->enemy->loseHP(this->player->attributes->strength * this->player->attributes->attributepts);
    
}



void BattleState::updateEnemies(const float& dt)
{
    this->enemy->update(dt, this->MousePosView);
    this->enemy->sprite.setScale(10, 10);
    
    if(this->PlayerTurn == false)
    {
        
        this->player->getStatusComponet()->loseHP(this->enemy->attributes->strength);
        
        if(!this->PlayerTurn)
            this->PlayerTurn = true;
        else
            this->PlayerTurn = false;
    }
    
    if(this->enemy->isDead())
    {
        this->player->attributes->gainEXP(this->enemy->getGainExp());
        this->states->pop();
    }
   
}

void BattleState::updatePlayerGUI(const float& dt)
{
    this->PlayerGUI->update(dt);
}






void BattleState::updateeventtime(const float& dt)
{
    if (this->eventtime < this->eventtimeMax)
    {
        this->eventtime += 10.f * dt;
    }
}



void BattleState::update(const float &dt)
{
    
    this->updateeventtime(dt);
    this->updateMousePosition();
    this->updatePlayerGUI(dt);
  

    
    
    if(!this->paused) //Update while unpaused
      {
          if(this->PlayerTurn) //Update while it's the player's turn
          {
            this->updateBattleGUI(dt);
            this->updateInput(dt);
              
          }
    
          this->updateEnemies(dt);
        
      }
    
     else // Update while Paused
      {
          this->pMenu->update(this->MousePosWindow);
      }
    

}



void BattleState::renderBattleGUI(sf::RenderTarget& target)
{
   
    this->battleGUI->render(target);
}


void BattleState::render(sf::RenderTarget *target)
{
    
    this->rendertexture.clear();
    this->renderBattleGUI(this->rendertexture);
    this->PlayerGUI->render(this->rendertexture);
    
    if(this->enemy)
    {
        this->enemy->render(this->rendertexture);
    }
    
    if(this->paused)
    {
        this->rendertexture.setView(this->rendertexture.getDefaultView());
        this->pMenu->render(this->rendertexture);
    }
  
    
    this->rendertexture.display();
    

    target->draw(this->rendersprite);
    
}

void BattleState::initkeybinds()
{
    
    
}

void BattleState::GiveEnemyDamage(const float& dt)
{
    
    this->enemy->animtioncomponet->play("ATTACKED", dt);
    this->enemy->loseHP(2);
    
}


void BattleState::initplayerGUI()
{
    sf::VideoMode &vm = this->state_data->gfxsettings->resolution;
    
    this->battleGUI = new BattleGUI(this->player, this->enemy, vm);
}



const bool BattleState::getEventtime()
{
    if (this->eventtime >= this->eventtimeMax)
        {
            this->eventtime = 0.f;
            return true;
        }

        return false;
    
}
