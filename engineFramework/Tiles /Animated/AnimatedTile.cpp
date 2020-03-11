//
//  AnimatedTile.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/9/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "AnimatedTile.hpp"


void AnimatedTile::initvariables()
{
    this->texture.loadFromFile("hero.png");
    this->animationcomponet = new AnimationComponet(this->rect, texture);
    this->animationcomponet->add_animation("IDLE", 10, 0, 0, 0, 0, 0, 0);
    this->rect.setTexture(texture);
}

AnimatedTile::AnimatedTile(short type, int x, int y, float gridsize_f, sf::Texture &texture, const sf::IntRect &texturerect, bool collision_enabled) : Tile(TileTypes::ANIMATED,x, y, gridsize_f, texture, texturerect, false )
{
    
    this->initvariables(); 

    
}

AnimatedTile::~AnimatedTile()
{
    delete this->animationcomponet;
}

const std::string AnimatedTile::asString() const
{
    
}

const bool &AnimatedTile::getCollision() const
{

    
}

void AnimatedTile::update(const float& dt)
{
    this->animationcomponet->play("IDLE", dt);
}

void AnimatedTile::render(sf::RenderTarget &target, sf::Shader *shader, sf::Vector2f PlayerPosition)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("light", PlayerPosition);

        target.draw(this->rect, shader);
    }
    else
        target.draw(this->rect);
    
}
