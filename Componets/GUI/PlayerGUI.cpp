//
//  PlayerGUI.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/24/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//


#include "PlayerGUI.hpp"

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm) : vm(vm)
{
    this->player = player;
    this->initfont();
    this->initLevelTag(); 
    this->initHPbar();
    this->initEXPbar();
    this->initMONEY();
    this->initinventory();
    this->hidden = true;
}


PlayerGUI::~PlayerGUI()
{
    delete this->HPbar;
    delete this->ExpBar;
    
}



void PlayerGUI::initMONEY()
{
    this->Coins = new GUI::Icon(GUI::pixelpercentX(92, vm), GUI::pixelpercentY(0, vm), "coins.png");
    this->CurrentCoins.setCharacterSize(GUI::calcCharSize(vm, 100));
    this->CurrentCoins.setFillColor(sf::Color::White);
    this->CurrentCoins.setFont(font);
    this->CurrentCoins.setPosition(GUI::pixelpercentX(96, vm), GUI::pixelpercentY(2, vm));
}

void PlayerGUI::initHPbar()
{
    this->HPbar = new GUI::ProgressBar(1.f, 8.3, 10.4, 2.8, this->player->getStatusComponet()->hpMax, this->vm, sf::Color::Red, 150, &this->font);
    
}

void PlayerGUI::initLevelTag()
{
    
        float width = GUI::pixelpercentX(2.1, vm);
        float height = GUI::pixelpercentY(3, vm);
        float x = GUI::pixelpercentX(1.4, vm);
        float y = GUI::pixelpercentY(2, vm);
      
        this->LevelTagExterior.setSize(sf::Vector2f(width, height));
        this->LevelTagExterior.setFillColor(sf::Color(50,50,50,200));
        this->LevelTagExterior.setPosition(x,y);
    
        this->LevelTagText.setFont(this->font);
        this->LevelTagText.setCharacterSize(GUI::calcCharSize(vm, 100));
        this->LevelTagText.setPosition(GUI::pixelpercentX(1.4, vm), GUI::pixelpercentY(1.4, vm));
    
}

void PlayerGUI::initEXPbar()
{
    this->ExpBar = new GUI::ProgressBar(1.f, 16.6, 10.4, 2.8, this->player->attributes->expNextlvl, this->vm,sf::Color::Green, 150, &this->font);
}

void PlayerGUI::initinventory()
{
    this->player->getInventory()->clear();

}

void PlayerGUI::initfont()
{
    this->font.loadFromFile(resourcePath() + "PressStart2P.ttf");
}

void PlayerGUI::update(const float &dt)
{
    this->updateLevelTag();
    this->updateMoney();
    this->updateHPbar();
    this->updateEXPbar();
    this->updateInventory();
}


void PlayerGUI::updateInventory()
{
    //update the size of the inventory
    this->currentSize = this->player->getInventory()->MaxSize();
       
          this->Itemboxes.resize(this->currentSize);
          float X= GUI::pixelpercentX(50, vm);
          float Y = GUI::pixelpercentY(50, vm);
          
              for (int x =0; x <= this->currentSize; x++)
              {
                  X += GUI::pixelpercentX(6,vm);
                  
                  
                  if(X >= GUI::pixelpercentX(100, vm) || Y >= GUI::pixelpercentY(100, vm))
                  {
                     Y += GUI::pixelpercentY(8, vm);
                     X = GUI::pixelpercentX(0, vm);

                  }
        
                     this->Itemboxes.push_back(sf::RectangleShape());
                     this->Itemboxes.at(x).setSize(sf::Vector2f(64, 64));
                     this->Itemboxes.at(x).setFillColor(sf::Color(50,50,50,200));
                     this->Itemboxes.at(x).setOutlineColor(sf::Color::White);
                     this->Itemboxes.at(x).setOutlineThickness(1.f);
                     this->Itemboxes.at(x).setPosition(X, Y);
                            
                  
              }
       
    
   
}

void PlayerGUI::updateHPbar()
{
    this->HPbar->update(this->player->attributes->hp);
}

void PlayerGUI::updateEXPbar()
{
    this->ExpBar->update(this->player->attributes->exp);
}

void PlayerGUI::updateLevelTag()
{
    this->LevelTagstring = std::to_string(this->player->getStatusComponet()->level);
    this->LevelTagText.setString(LevelTagstring);
    
}

void PlayerGUI::updateMoney()
{
    
    this->coins_string = std::to_string(this->player->getStatusComponet()->coins);
    this->CurrentCoins.setString(coins_string);
    
}

void PlayerGUI::renderMoney(sf::RenderTarget& target)
{
    this->Coins->render(target);
    target.draw(this->CurrentCoins);
}


void PlayerGUI::renderLevelTag(sf::RenderTarget& target)
{
    target.draw(this->LevelTagExterior);
    target.draw(this->LevelTagText);
}

void PlayerGUI::renderHPbar(sf::RenderTarget& target)
{
    this->HPbar->render(target);
}

void PlayerGUI::renderInventory(sf::RenderTarget& target)
{
    if(this->hidden == false)
    {
        for(size_t i2 =0; i2 < Itemboxes.size(); i2++)
        {
            target.draw(this->Itemboxes[i2]);
        }
    }
    else if(this->hidden == true)
    {
        
        
    }
    
}


void PlayerGUI::renderEXPbar(sf::RenderTarget& target)
{
    this->ExpBar->render(target);
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    this->renderMoney(target);
    this->renderLevelTag(target);
    this->renderEXPbar(target);
    this->renderHPbar(target);
    this->renderInventory(target);
}


//Accessors

const bool PlayerGUI::getInventoryHidden()
{
    return this->hidden;
}


//Modifers

void PlayerGUI::HideInventory()
{
    if(this->hidden == true)
        this->hidden = false;
    
    else
        this->hidden = true;
}


