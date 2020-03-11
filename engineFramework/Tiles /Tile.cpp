//
//  Tile.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
// 

#include "Tile.hpp"
#include "PrefixHeader.pch"

Tile::Tile()
{
    this->collison_enabled = false;
    this->type = 0;
    
}

                                                                                        
Tile::Tile(short type, int x, int y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled)
{
    //this->rect.setSize(sf::Vector2f(gridsize_f, gridsize_f));
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    
    this->rect.setTexture(texture);
    this->rect.setScale(2, 2);
    this->rect.setPosition(static_cast<float>(x) * gridsize_f, static_cast<float>(y) * gridsize_f);
    this->rect.setTextureRect(texturerect);
    
    this->collison_enabled = collision_enabled;
    this->type = type;
    

}


Tile::~Tile()
{
    

}

//Functions

void Tile::update(const float& dt)
{
    //this->rect.setColor(sf::Color::Blue);
    
}


void Tile::render(sf::RenderTarget &target, sf::Shader* shader, sf::Vector2f PlayerPosition)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("light", PlayerPosition);
        target.draw(this->rect, shader);
    }
    
    else
    {
        target.draw(this->rect);
        
    }
    
    }



const sf::Vector2f &Tile::getposition() const
{
    return this->rect.getPosition(); 
}

const bool& Tile::getCollision() const
{
    return this->collison_enabled;
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
    return this->rect.getGlobalBounds().intersects(bounds);
}

const sf::FloatRect Tile::getGlobalBounds() const
{ 
    return this->rect.getGlobalBounds();
}

const short& Tile::gettype() const
{
    return this->type;

}
