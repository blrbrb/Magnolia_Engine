//
//  Entity.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/23/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "Entity.hpp"

Entity::Entity() {
    
    this->initvariables();
    
}


const sf::Vector2f &Entity::getPosition() const
{
    /*!
                @brief  Fetch the position of the entity relative to the window
    
                @param  void
     
                @return const sf::Vector2f&     The position of the entity

     */
    
    
    
    if(this->hitbox) {
        return this->sprite.getPosition(); }
    
    return this->sprite.getPosition();
        
}


const sf::Vector2f Entity::getCenter() const
{
    /*!
     @brief Fetch the center of the entity's sprite
     
     @param void
     
     @return const sf::Vector2f     The Center
     
     */
    
  if (this->hitbox)
      return this->hitbox->getPosition() +
      sf::Vector2f
      (
          this->hitbox->getGlobalBounds().width / 2.f,
          this->hitbox->getGlobalBounds().height / 2.f
      );

  return
      this->sprite.getPosition() +
      sf::Vector2f
      (
          this->sprite.getGlobalBounds().width / 2.f,
          this->sprite.getGlobalBounds().height / 2.f
      );
}

// Apply the final movements and animations to the entity
void Entity::update(const float& dt) {
   
    if (this->movementcomponets)
    {
        this->movementcomponets->update(dt);
    }
    
}

Entity::~Entity() {
    
    delete this->hitbox;
    delete this-> movementcomponets;
    delete this->animtioncomponet;
    delete this->attributes;
}

void Entity::initvariables()
{
    this->texture = NULL;
    this->hitbox = NULL;
    this->movementcomponets = NULL;
    
}

void Entity::settexture(sf::Texture& texture)
{
    this->texture = &texture;
    this->sprite.setTexture(texture);
    
}

void Entity::createmovementcomponet(const float maxVelocity, const float Acceleration, const float Deceleration)
{
    
    this->movementcomponets = new MovementComponets(this->sprite, maxVelocity, Acceleration, Deceleration);
    
}

void Entity::create_animation_componet(sf::Texture& texturesheet)
{
    
    this->animtioncomponet = new AnimationComponet(this->sprite, texturesheet);
    
    
}



void Entity::setposition(const float x, const float y)
{
    if(this->hitbox) {
        this->sprite.setPosition(x, y); }

    else {
        
        this->sprite.setPosition(x, y); }
}


void Entity::render(sf::RenderTarget& target,sf::Shader* shader, const bool render_hitbox)
{
    
}

void Entity::move(const float& dt, const float x, const float y) {
    
    if(this->hitbox)
        this->movementcomponets->move(x, y, dt);
        
    else
        this->sprite.setPosition(x, y);
    
}

void Entity::create_attribute_componet(const unsigned level)
{
    this->attributes = new StatusComponet(level);
    
}


void Entity::create_hitbox_componet(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{

    this->hitbox = new HitBoxComponet(sprite, offset_x, offset_y, width, height);
    
    
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    if(this->hitbox)
        return this->hitbox->getGlobalBounds();
    else 
    return this->sprite.getGlobalBounds();
    
    
    
    
    
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
    if(this->hitbox)
        return sf::Vector2i(static_cast<int>(this->hitbox->getPosition().x) / gridSizeI, static_cast<int>(this->hitbox->getPosition().y) / gridSizeI);
    
    else
        return
        sf::Vector2i(static_cast<int>(this->sprite.getPosition().x) / gridSizeI, static_cast<int>(this->sprite.getPosition().y) / gridSizeI);
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
    if(this->hitbox && this->movementcomponets)
        return this->hitbox->getNextPosition(this->movementcomponets->getvelocity() * dt);
    
    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

void Entity::stopVelocity()
{
    if (this->movementcomponets)
        this->movementcomponets->stopVelocity();
}

void Entity::stopVelocityX()
{
    if (this->movementcomponets)
        this->movementcomponets->stopVelocityX();
}

void Entity::stopVelocityY()
{
    if (this->movementcomponets)
        this->movementcomponets->stopVelocityY();
}






