//
//  Apple.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 7/15/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "Apple.hpp"

Apple::Apple(unsigned int value) : Consumable_Item(value)
{
    this->initvariables(); 
    this->value = 3;
}

void Apple::initvariables()
{
    this->texture_rect.top = 0;
    this->texture_rect.left = 17;
    this->texture_rect.height = 0;
    this->texture_rect.width = 17;
    
    this->sprite.setTextureRect(this->texture_rect);
}

Apple::~Apple()
{

}

void Apple::update()
{
    
}

void Apple::render(sf::RenderTarget &target, sf::Shader *shader)
{
    if (shader)
              target.draw(this->sprite, shader);
          else
              target.draw(this->sprite);
}
