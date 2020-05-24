//
//  BattleGUI.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 5/17/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "BattleGUI.hpp"


void BattleGUI::initButtons()
{
     this->BUTTONS["ATTACK"] = new GUI::Button(GUI::pixelpercentX(20,this->vm), GUI::pixelpercentY(15, this->vm), GUI::pixelpercentY(61, vm), GUI::pixelpercentX(50, this->vm), &this->font, "Attack", GUI::calcCharSize(this->vm, 100), "red_button01.png", "red_button02.png", "red_button00.png");
     
    this->BUTTONS["ITEM"] = new GUI::Button(GUI::pixelpercentX(20,this->vm), GUI::pixelpercentY(15, this->vm), GUI::pixelpercentY(21, vm), GUI::pixelpercentX(50, this->vm), &this->font, "Item", GUI::calcCharSize(this->vm, 100), "red_button01.png", "red_button02.png", "red_button00.png");
    
    
    
}

void BattleGUI::initcontainer()
{
          this->BattleGUIcontainer.setSize(sf::Vector2f(GUI::pixelpercentX(90, this->vm), GUI::pixelpercentY(30, this->vm)));
          this->BattleGUIcontainer.setFillColor(sf::Color::Black);
          this->BattleGUIcontainer.setOutlineThickness(1.f);
          this->BattleGUIcontainer.setOutlineColor(sf::Color::White);
          this->BattleGUIcontainer.setPosition(GUI::pixelpercentX(5, this->vm), GUI::pixelpercentY(50,this->vm));
          
    
}

void BattleGUI::inittext()
{
    this->enemyleveltag.setFont(this->font);
    this->enemyleveltag.setCharacterSize(12);
    this->enemyleveltag.setFillColor(sf::Color::White);
    this->enemyleveltag.setPosition(100, 100);
    //Note to self, fix this bs later 
    //this->enemyleveltag.setString(this->enemy->getName());
}

void BattleGUI::initfont()
{
    if (!this->font.loadFromFile(resourcePath() + "PressStart2P.ttf"))
       {
           throw std::runtime_error("Error Code 34 || PlayerGUI::PlayerGUI::initfont() || unable to load font from file");
       }
}

void BattleGUI::initenemyHPbar()
{
    this->enemyHP = new GUI::ProgressBar(23.f, 5.f, 10.4, 2.8, 10, this->vm, sf::Color::Red, 150, &this->font);
    
}



BattleGUI::BattleGUI(Player *player, Enemy *enemy, sf::VideoMode& vm) : vm(vm), player(player), enemy(enemy)
{
    
   
    try
    {
        this->initfont();
        this->inittext();
        this->initButtons();
        this->initcontainer();
        this->initenemyHPbar();
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
}


const bool BattleGUI::isButtonPressed(const std::string key)
{
    return this->BUTTONS[key]->isPressed();
    
}



BattleGUI::~BattleGUI()
{
    
}

void BattleGUI::update(const float &dt)
{
    this->updateenemyHPbar();
}

void BattleGUI::updateenemyHPbar()
{
    this->enemyHP->update(this->enemy->attributes->hp);
    
}


void BattleGUI::updatebuttons(const sf::Vector2i MousePos)
{
    for (auto &it : this->BUTTONS)
       {
           it.second->update(MousePos);
       }
}

void BattleGUI::render(sf::RenderTarget &target)
{
    this->renderContainer(target);
    this->renderTag(target);
    this->renderButtons(target);
    this->renderHPBar(target);

}


void BattleGUI::renderContainer(sf::RenderTarget& target)
{
    target.draw(this->BattleGUIcontainer);
    
}

void BattleGUI::renderTag(sf::RenderTarget& target)
{
    target.draw(this->enemyLevelTag);
    
}



void BattleGUI::renderHPBar(sf::RenderTarget& target)
{
    this->enemyHP->render(target);
    
}


void BattleGUI::renderButtons(sf::RenderTarget& target)
{
    for (auto &it : this->BUTTONS)
    {
       it.second->render(target);
    }
    
}
