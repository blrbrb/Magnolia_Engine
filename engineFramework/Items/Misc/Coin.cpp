//
//  Coin.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/19/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "Coin.hpp"


Coin::Coin(unsigned int value) : Item(value)
{
    this->value = value;
    this->type = ItemTypes::MISC;
    this->texture.loadFromFile("coins.png");
    this->coinsprite.setTexture(texture);        
 
}



Coin::~Coin()
{
    
}

Coin* Coin::clone()
{
    return new Coin(*this);
}

void Coin::render(sf::RenderTarget &target, sf::Shader *shader)
{
    target.draw(this->coinsprite, shader);
}


