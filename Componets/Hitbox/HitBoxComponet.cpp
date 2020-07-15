//
//  HitBoxComponet.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/1/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "HitBoxComponet.hpp"


HitBoxComponet::HitBoxComponet(sf::Sprite& sprite,float offset_x, float offset_y, float width, float height) : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{

    

    this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
    
    
    
    this->hitbox.setSize(sf::Vector2f(width, height));
   
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(sf::Color::Green);
   
    this->nextpos.left = 0.f;
    
    this->nextpos.top = 0.f;
    this->nextpos.width = width;
    this->nextpos.height = height; 
  
}


HitBoxComponet::~HitBoxComponet()
{

    
    
    
}

void HitBoxComponet::update()
{
    
    this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
   
    
}

void HitBoxComponet::render(sf::RenderTarget& target)
{
    
    target.draw(this->hitbox);
   
    
}

bool HitBoxComponet::intersects(const sf::FloatRect& rect)
{
  
    
    return this->hitbox.getGlobalBounds().intersects(rect);
  
    
}

void HitBoxComponet::setposition(const sf::Vector2f positon)
{
    this->hitbox.setPosition(positon);
    this->sprite.setPosition(positon.x - this->offsetX, positon.y - this->offsetY);
}

void HitBoxComponet::setposition(const float x, const float y)
{
    this->hitbox.setPosition(x, y);
    this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
  
}

const sf::FloatRect HitBoxComponet::getGlobalBounds() const
{
    
    return this->hitbox.getGlobalBounds(); 
    
    
}

const sf::FloatRect& HitBoxComponet::getNextPosition(const sf::Vector2f &velocity)
{
    
    this->nextpos.left = this->hitbox.getPosition().x + velocity.x;
    this->nextpos.top = this->hitbox.getPosition().y + velocity.y;

    return this->nextpos;
}


const sf::Vector2f& HitBoxComponet::getPosition() const
{
    return this->hitbox.getPosition();
}




