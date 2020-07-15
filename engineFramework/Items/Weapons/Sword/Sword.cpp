//
//  Sword.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "Sword.hpp"

Sword::Sword(unsigned value, std::string texture_file) : Weapon(value, texture_file)
{ 
    this->initvariables(); 
}

void Sword::initvariables()
{
    this->type = ItemTypes::WEAPON;
    this->value = 1;
    
}


Sword::~Sword()
{
    
    
    
}


void Sword::update(const sf::Vector2f position)
{
    this->weaponSprite.setPosition(position.x, position.y);
}

void Sword::render(sf::RenderTarget &target, sf::Shader* shader)
{
    if (shader)
        target.draw(this->weaponSprite, shader);
    else
        target.draw(this->weaponSprite);
    
}

Sword *Sword::clone()
{
    return new Sword(*this);
}

