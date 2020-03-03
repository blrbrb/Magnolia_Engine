//
//  Sword.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "Sword.hpp"

Sword::Sword()
{
    if (this->weaponTexture.loadFromFile("sword.png"))
    {
        std::cout << "unable to load sword texture in Sword.cpp. Sword/Sword.png"  << std::endl;
    }
    
    this->weaponSprite.setTexture(this->weaponTexture);
}



Sword::~Sword()
{
    
    
    
}



void Sword::update(const sf::Vector2f &MousePosView, const sf::Vector2f center)
{
    this->weaponSprite.setPosition(center);
    
    float dx = MousePosView.x - weaponSprite.getPosition().x;
    float dy = MousePosView.y - weaponSprite.getPosition().y;
    
    const float PI = 3.14159265;
    float deg = atan2(dy,dx) * 180 / PI;
    
    this->weaponSprite.setRotation(deg + 90.f);
    
    
}

void Sword::render(sf::RenderTarget &target, sf::Shader* shader)
{
    if (shader)
        target.draw(this->weaponSprite, shader);
    else
        target.draw(this->weaponSprite);
    
}
