//
//  MovementComponets.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/29/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "MovementComponets.hpp"


MovementComponets::MovementComponets(sf::Sprite& sprite, float maxVelocity, float Acceleration, float Deceleration) : sprite(sprite), maxVelocity(maxVelocity), Acceleration(Acceleration), Deceleration(Deceleration)
{
    this->Velocity.x = 0.f;
    this->Velocity.y = 0.f;
    
    
}

MovementComponets::~MovementComponets()
{
    
}

void MovementComponets::move(const float x ,const float y, const float& dt)
{
    //Acceleration
    //Note, fix clusterfuck of brackets
    
    this->Velocity.x += this->Acceleration * x * dt;
    this->Velocity.y += this->Acceleration  *  y * dt;
    

}


void MovementComponets::update(const float& dt)
{
    /*SLOWS DOWN THE SPRITE*/
    
    if (this->Velocity.x > 0.f) // Check for positive x
    {
        //Max velocity check
        if(this->Velocity.x > maxVelocity)
        {
           this->Velocity.x = this->maxVelocity;
        }
      
        //Deceleration
        this->Velocity.x -= Deceleration * dt;
       
        if(this->Velocity.x < 0.f)
        {
            this->Velocity.x = 0.f;
        }

    }
    else if (this->Velocity.x < 0.f) //Check for negative x
    {
        //Max Velocity Check
        if(this->Velocity.x < -maxVelocity)
        {
            this->Velocity.x = -this->maxVelocity;
        }
        
        //Decelreation
        this->Velocity.x += Deceleration * dt;
        
        if(this->Velocity.x > 0.f)
        {
            this->Velocity.x = 0.f;
        }
    }
    
    if (this->Velocity.y > 0.f) // check for positive y
    {
        //Max velocity check
        if(this->Velocity.y > maxVelocity)
        {
           this->Velocity.y = this->maxVelocity;
        }
      
        //Deceleration
        this->Velocity.y -= Deceleration * dt;
       
        if(this->Velocity.y < 0.f)
        {
            this->Velocity.y = 0.f;
        }
        
        
    }
    else if (this->Velocity.y < 0.f) //Check for negative y
    {
        //Max Velocity Check
        if(this->Velocity.y < -maxVelocity)
        {
            this->Velocity.y = -this->maxVelocity;
        }
        
        //Decelreation
        this->Velocity.y += Deceleration * dt;
        
        if(this->Velocity.y > 0.f)
        {
            this->Velocity.y = 0.f;
        }
    }
    
    //Final Move of the entity, most important expression
    this->sprite.move(this->Velocity * dt);
    
}

const sf::Vector2f& MovementComponets::getvelocity() const
{
    
    return this->Velocity;
    
    
}

//Accessors
// This function returns the state the entity is moving in
//Enum values for every moving State starting at
//    IDLE == 0


const bool MovementComponets::get_moving(const short unsigned state) const
{
    switch(state)
    {
        
        case movements::IDLE:
           
            if(this->Velocity.x == 0.f && this->Velocity.y == 0.f)
            {
                return true;
            }
            
            
            break;
            
        case movements::MOVING:
            
            if (this->Velocity.x !=0 || this->Velocity.y !=0)
               {
                   return true;
               }
               
            break;
            
        case movements::MOVING_LEFT:
           
            if (this->Velocity.x < 0.f)
            {
                return true;
            }
            
            break;
            
        case movements::MOVING_RIGHT:
           
            if(this->Velocity.x > 0.f)
            {
                return true;
            }
            
            break;
            
        case movements::MOVING_UP:
            
            if(this->Velocity.y < 0.f)
            {
                return true;
            }
           
            
            break;
            
        case movements::MOVING_DOWN:
            
            
            if (this->Velocity.y > 0.f)
            {
                return true;
            }
                    break;
    }
    
    return false;
}

const float& MovementComponets::getMaxVelocity() const
{
    
    return this->maxVelocity;
  
}

void MovementComponets::stopVelocity()
{
    this->Velocity.x = 0.f;
    this->Velocity.y = 0.f;
}

void MovementComponets::stopVelocityX()
{
    this->Velocity.x = 0.f;
}

void MovementComponets::stopVelocityY()
{
    this->Velocity.y = 0.f;
}

