//
//  Potion.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 7/15/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "Potion.hpp"


Potion::Potion(unsigned value) : Consumable_Item(value)
{
    this->value = 2; 
    this->initvariables();
    
}

void Potion::initvariables()
{
    this->texture_rect.top = 0;
    this->texture_rect.left = 0;
    this->texture_rect.width = 0;
    this->texture_rect.height = 0;
    
    this->sprite.setTextureRect(this->texture_rect);

}

Potion::~Potion()
{
    
    
    
}

void Potion::update()
{
    
}

void Potion::render(sf::RenderTarget& target, sf::Shader* shader)
{
    
    if (shader)
           target.draw(this->sprite, shader);
       else
           target.draw(this->sprite);
    
}
