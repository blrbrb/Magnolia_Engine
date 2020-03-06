//
//  NormalTile.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/6/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "NormalTile.hpp"


NormalTile::NormalTile(short type, int x, int y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled) : Tile(type, x, y, gridsize_f,texture, texturerect, collision_enabled)
{
    
    
    
    
}

NormalTile::~NormalTile()
{
    
}


const sf::FloatRect NormalTile::getGlobalBounds() const
{
    return this->rect.getGlobalBounds();
}

const std::string NormalTile::asString() const
{
    std::stringstream out;
       
       out << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->collison_enabled << " " << this->type;
       
       
       return out.str();
}

void NormalTile::update()
{
    
}

void NormalTile::render(sf::RenderTarget &target, sf::Shader *shader, sf::Vector2f PlayerPosition)
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