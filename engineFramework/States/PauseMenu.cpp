
//  PauseMenu.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/3/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "PauseMenu.hpp"


PauseMenu::PauseMenu(sf::VideoMode& vm,sf::Font& font) :
font(font)

{
    
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));
    this->background.setFillColor(sf::Color(20, 20, 20, 100));
    this->container.setSize(sf::Vector2f(static_cast<float>(vm.width) / 0.5 ,static_cast<float>(vm.height) - GUI::pixelpercentY(9.3,vm)));
    this->container.setFillColor(sf::Color(20,20,20,200));
    this->container.setPosition(static_cast<float>(vm.width / 2.f) - this->container.getSize().x / 2.f, 0.f);
    
   //init MenuText
    this->menutext.setFont(font);
    this->menutext.setFillColor(sf::Color(255, 255, 255, 200));
    this->menutext.setCharacterSize(GUI::calcCharSize(vm));
    this->menutext.setString("PAUSED");
    this->menutext.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menutext.getGlobalBounds().width / 2.f,
                               this->container.getPosition().y + GUI::pixelpercentY(4,vm ));
    
    
}

PauseMenu::~PauseMenu()
{
    auto it = buttons.begin();
       for (it = buttons.begin(); it != this->buttons.end(); ++it)
      
       {
           delete it->second;
       }
}

void PauseMenu::update(const sf::Vector2i& MousePos)
{
    for (auto &i :this->buttons)
    {
           i.second->update(MousePos);
    }
    
   
    
}

void PauseMenu::render(sf::RenderTarget& target)
{
    
    target.draw(background);
    target.draw(container);
    
    for (auto &i : this->buttons)
    {
        i.second->render(target);
        
        
    }
   
    target.draw(this->menutext);
}

std::map<std::string, GUI::Button*>& PauseMenu::getButtons()
{
   
    return this->buttons;

}

void PauseMenu::addbutton(const std::string key, const unsigned charSize, const std::string text,const float width, const float height, const float y)
{
     float x = this->container.getPosition().x / 4.f  + this->container.getSize().x / 4.f;
    

    this->buttons[key] = new GUI::Button(width, height, x, y, &this->font, text, charSize, "red_button06.png", "red_button07.png", "red_button07.png");
  
    
   
    
}
const bool PauseMenu::isButtonPressed(const std::string& key)
{
    return this->buttons[key]->isPressed();
    
    
}

