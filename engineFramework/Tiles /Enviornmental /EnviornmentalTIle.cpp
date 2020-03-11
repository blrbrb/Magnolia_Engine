//
//  EnviornmentalTIle.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/10/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "EnviornmentalTIle.hpp"


EnviornmentalTile::EnviornmentalTile(short type, int x, int y, float gridsize_f, sf::Texture &texture, const sf::IntRect &texturerect, bool collision_enabled) : Tile(TileTypes::OBJECT, x, y, gridsize_f,texture, texturerect, collision_enabled)
{
    this->rect.setTexture(texture);
    this->rect.setScale(5, 5);
}

EnviornmentalTile::~EnviornmentalTile()
{
    
}

const short &EnviornmentalTile::gettype() const
{
    return this->type; 
}

const std::string EnviornmentalTile::asString() const
{
    std::stringstream out;
       
    out << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->collison_enabled;
       
       
       return out.str();
}

void EnviornmentalTile::render(sf::RenderTarget &target, sf::Shader *shader, sf::Vector2f PlayerPosition)
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

void EnviornmentalTile::update(const float &dt)
{
    
}
