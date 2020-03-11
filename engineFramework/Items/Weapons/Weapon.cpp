//
//  Weapon.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "Weapon.hpp"

void Weapon::initvariables()
{
    
    this->range = 5;
    this->damageMax = 5;
    this->damageMin = 1;
    
}

Weapon::Weapon(unsigned value, std::string texture_file) : Item(value)
{
    this->type = ItemTypes::WEAPON;
    this->initvariables();
    if (this->weaponTexture.loadFromFile(texture_file))
    {
        std::cout << "unable to load texture "  << std::endl;
    }
    
    this->weaponSprite.setTexture(this->weaponTexture);
}

Weapon::~Weapon()
{ 
    
}

