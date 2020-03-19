//
//  PlayerGUI.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/24/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "PlayerGUI.hpp"



PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm) : vm(vm)
{
    this->player = player;
    this->initfont();
    this->initLevelTag(); 
    this->initHPbar();
    this->initEXPbar();
}


PlayerGUI::~PlayerGUI()
{
    delete this->HPbar;
    delete this->ExpBar;
    
}

void PlayerGUI::initMONEY()
{
    this->coinIcon.loadFromFile("hero.png");
    this->monies.setTexture(coinIcon);
    this->monies.setPosition(500, 100);
    this->money.setCharacterSize(10);
    this->money.setPosition(500, 100);
}

void PlayerGUI::initHPbar()
{
    this->HPbar = new GUI::ProgressBar(1.f, 8.3, 10.4, 2.8, this->player->attributes->hpMax, this->vm, sf::Color::Red, 150, &this->font);
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
    this->updateHPbar();
    this->updateEXPbar();
    this->updateInventory();
}


void PlayerGUI::updateInventory()
{
    this->currentSize = this->player->getInventory()->size();
    
    this->Itemboxes.resize(this->currentSize);
    
        for (int x =0; x <= this->currentSize; x++)
        {
               this->Itemboxes.push_back(sf::RectangleShape());
               this->Itemboxes[x].setSize(sf::Vector2f(64, 64));
               this->Itemboxes[x].setFillColor(sf::Color::Red);
               this->Itemboxes[x].setPosition(400, 400);
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
    
    this->money_string = std::to_string(this->player->getStatusComponet()->coins);
    this->money.setString(money_string);
    
    this->money.setPosition(200, 220);
    
}

void PlayerGUI::renderMoney(sf::RenderTarget& target)
{
    target.draw(this->monies);
    target.draw(this->money);
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
    for(size_t i2 =this->Itemboxes.size(); i2 < this->currentSize; i2++)
    {
        //target.draw(this->Itemboxes[i2]);
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




