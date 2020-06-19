//
//  MovementComponets.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/29/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "MovementComponets.hpp"


MovementComponets::MovementComponets(sf::Sprite& sprite, float maxVelocity, float Acceleration, float Deceleration) : sprite(sprite), maxVelocity(maxVelocity), Acceleration(Acceleration), Deceleration(Deceleration), movement_time(0), movement_timeMax(7.f)
{
    this->Velocity.x = 0.f;
    this->Velocity.y = 0.f;
    this->Mass = 10.f;
    this->Volume = this->sprite.getLocalBounds().width * this->sprite.getLocalBounds().top;
    this->Density = this->Volume / 25.f;
    
}

MovementComponets::~MovementComponets()
{
    
}

void MovementComponets::Updatephyiscs(const float& dt)
{
    //Acceleration and Deceleration
    this->pastVelX = this->Velocity.x - dt;
    this->pastVelY = this->Velocity.y - dt;

    this->DeltaVelocityX = this->Velocity.x - this->pastVelX;
    this->DeltaVelocityY = this->Velocity.y - this->pastVelY;
    
    this->AccelerationX = this->DeltaVelocityX / dt; 
    this->AccelerationY = this->DeltaVelocityY / dt;
    
    this->Deceleration = this->Acceleration - this->DeltaVelocityX / dt;

    //Force
    this->Force = this->Mass * this->Acceleration;
    
    //Impulse
    this->Impulse = this->Force * dt;
    
    
    //Velocity
    this->Velocity.x = (this->sprite.getPosition().x + dt) - (this->sprite.getPosition().x - dt);
    this->Velocity.y = (this->sprite.getPosition().y + dt) - (this->sprite.getPosition().y - dt);
    
    
    //Momentum
    this->Momentum = this->Mass * this->Velocity;
}

/**
   move the object by supplying an incriment for the X and Y Velocity, and then apply Delta Time.
                   
   @param The X-Velocity and Y-Velocity values to move the object with. Mult by the deltaTime Param, and then combined alongside Y param into a float vector.
   @param
   @param delta Time
   @returns void

*/
void MovementComponets::move(const float x ,const float y, const float& dt)
{
    
    
    this->Velocity.x += this->Acceleration * x * dt;
    this->Velocity.y += this->Acceleration *  y * dt;

}



void MovementComponets::updateMoveTime(const float& dt)
{
    
    if (this->movement_time < this->movement_timeMax)
       {
           this->movement_time += 10.f * dt;
       }

}

void MovementComponets::update(const float& dt)
{
    //update movetime
    
    
    
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


void MovementComponets::move_rand(const float& dt, int seed)
{
    this->updateMoveTime(dt);
    
    switch (seed) {
            
        case 1: 
            
            if(this->getmovetime())
            {
                this->move(0, 4, dt);
            }
            
            break;
            
        case 2:
            
            if(this->getmovetime())
            {
                this->move(0, -4, dt);
            }
                       
            break;
            
            
       case 3:
                       
          if(this->getmovetime())
          {
            this->move(4, 0, dt);
          }
                                  
        break;
            
            
       case 4:
                           
         if(this->getmovetime())
         {
           this->move(-4, 0, dt);
         }
                                      
         break;
        
            
        default:
            break;
    }
    
    
}

/**
           @brief Retrieve wether or not an object is moving in a particular direction
           @param One of the directions, supplied by the directions enumerator; to test the object against.
           @returns a true, or false depending on wether or not the object is moving in the supplied direction

*/
const bool MovementComponets::getStauts(const short unsigned state) const
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

const float & MovementComponets::getAcceleration() const
{
    return this->Acceleration;
}

const bool MovementComponets::getmovetime()
{
    if (this->movement_time >= this->movement_timeMax)
       {
           this->movement_time = 0.f;
           return true;
       }

       return false;
    
}

const sf::Vector2f& MovementComponets::getvelocity() const
{
    return this->Velocity;

}
