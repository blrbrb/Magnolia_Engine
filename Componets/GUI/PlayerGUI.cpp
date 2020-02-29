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


PlayerGUI::~PlayerGUI() { 
    
}

void PlayerGUI::initHPbar()
{
    
    float width = GUI::pixelpercentX(21.4, vm);          //300.f;
    float height = GUI::pixelpercentY(1.5, vm);
    float x = GUI::pixelpercentX(1.4, vm);
    float y = GUI::pixelpercentY(6.0, vm);
    this->hpbarMaxWidth = width;
    
   
    this->HPbarExterior.setSize(sf::Vector2f(width, height));
    this->HPbarExterior.setFillColor(sf::Color(50,50,50,200));
    this->HPbarExterior.setPosition(x,y);
    
    this->HPbarInterior.setSize(sf::Vector2f(width, height));
    this->HPbarInterior.setFillColor(sf::Color(250,20,20,200));
    this->HPbarInterior.setPosition(this->HPbarExterior.getPosition());
    
    this->HPbarText.setFont(this->font);
    this->HPbarText.setCharacterSize(GUI::calcCharSize(vm, 100));
    this->HPbarText.setPosition(this->HPbarInterior.getPosition().x + GUI::pixelpercentX(1.4, vm), this->HPbarInterior.getPosition().y + GUI::pixelpercentY(2, vm));
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
        this->LevelTagText.setPosition(this->EXPbarInterior.getPosition().x + GUI::pixelpercentX(1.4, vm), this->EXPbarInterior.getPosition().y + GUI::pixelpercentY(2, vm));
    
}


void PlayerGUI::initEXPbar()
{

    float width = GUI::pixelpercentX(21.4, vm);
    float height = GUI::pixelpercentY(1.5, vm);
    float x = GUI::pixelpercentX(1.4, vm);
    float y = GUI::pixelpercentY(12, vm);
    this->EXPbarMaxWidth = width;
       
      
    this->EXPbarExterior.setSize(sf::Vector2f(width, height));
    this->EXPbarExterior.setFillColor(sf::Color(50,50,50,200));
    this->EXPbarExterior.setPosition(x,y);
       
    this->EXPbarInterior.setSize(sf::Vector2f(width, height));
    this->EXPbarInterior.setFillColor(sf::Color(20,250,20,200));
    this->EXPbarInterior.setPosition(this->EXPbarExterior.getPosition());
       
    this->EXPbarText.setFont(this->font);
    this->EXPbarText.setCharacterSize(GUI::calcCharSize(vm, 100));
    this->EXPbarText.setPosition(this->EXPbarInterior.getPosition().x + GUI::pixelpercentX(1.4, vm), this->EXPbarInterior.getPosition().y + GUI::pixelpercentY(2, vm));
    
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
}

void PlayerGUI::updateHPbar()
{
    float percent = static_cast<float>(this->player->getStatusComponet()->hp) /
                    static_cast<float>(this->player->getStatusComponet()->hpMax);
    
    
    this->HPbarInterior.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpbarMaxWidth * percent)), this->HPbarInterior.getSize().y));
    
    this->HPString = std::to_string(this->player->getStatusComponet()->hp) + "/" +
                     std::to_string(this->player->getStatusComponet()->hpMax);
    
    this->HPbarText.setString(HPString);
}

void PlayerGUI::updateEXPbar()
{
    
    float percent = static_cast<float>(this->player->getStatusComponet()->exp) /
                       static_cast<float>(this->player->getStatusComponet()->expNextlvl);
       
       
       this->EXPbarInterior.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpbarMaxWidth * percent)), this->HPbarInterior.getSize().y));
       
    this->EXPstring = std::to_string(this->player->getStatusComponet()->exp) + "/" +
                        std::to_string(this->player->getStatusComponet()->expNextlvl);
       
    this->EXPbarText.setString(EXPstring);
}

void PlayerGUI::updateLevelTag()
{
    
    this->LevelTagstring = std::to_string(this->player->getStatusComponet()->level);
       
    this->LevelTagText.setString(LevelTagstring);
    
}




void PlayerGUI::renderLevelTag(sf::RenderTarget& target)
{
    target.draw(this->LevelTagExterior);
    target.draw(this->LevelTagText);
}

void PlayerGUI::renderHPbar(sf::RenderTarget& target)
{
    target.draw(this->HPbarExterior);
    target.draw(this->HPbarInterior);
    target.draw(this->HPbarText);
    
    
}


void PlayerGUI::renderEXPbar(sf::RenderTarget& target)
{
       target.draw(this->EXPbarExterior);
       target.draw(this->EXPbarInterior);
       target.draw(this->EXPbarText);
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    this->renderLevelTag(target);
    this->renderEXPbar(target);
    this->renderHPbar(target);
}

