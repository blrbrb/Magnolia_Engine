//
//  LightTile.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/14/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "LightTile.hpp"


LightTile::LightTile(short type, int x, int y, float gridsize_f, sf::Texture &texture, const sf::IntRect &texturerect) : Tile(TileTypes::LIGHT, x, y, gridsize_f, texture, texturerect, false)
{
    
    
}

LightTile::~LightTile()
{
    
}

const std::string LightTile::asString() const
{
    std::stringstream out;
       
    out << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top;
       
       
       return out.str();
}




void LightTile::update(const float &dt)
{
    
}

void LightTile::render(sf::RenderTarget &target, sf::Shader *shader, sf::Vector2f LightPosition)
{
    
   if (shader)
   {
       shader->setUniform("LightSource", true);
       shader->setUniform("hasTexture", true);
       shader->setUniform("light2", LightPosition);
       target.draw(this->rect, shader);
      
   }
   
   else
   {
       target.draw(this->rect);
       
   }
   
}

