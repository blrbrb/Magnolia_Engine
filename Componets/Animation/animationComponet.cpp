//
//  AnimationComponet.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/30/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "AnimationComponet.hpp"


AnimationComponet::AnimationComponet(sf::Sprite& sprite, sf::Texture& texturesheet) :
sprite(sprite), texturesheet(texturesheet), lastAnimation(NULL), priorityAnimation(NULL)
{

    
   
    
}

AnimationComponet::~AnimationComponet()
{
    
    for (auto &i : this->animations)
    {
        delete i.second;
        
    }
    
}

//*Functions*
void AnimationComponet::add_animation(const std::string& key, float animationtimer,int start_x, int start_y, int end_x, int end_y, int width, int height)
{
   
   
    this->animations[key] = new Animation(this->texturesheet, this->sprite, animationtimer, start_x, start_y,  end_x, end_y, width, height);
    

    
}

const bool& AnimationComponet::play(const std::string& key, const float& dt, const bool priority )
{
    
    if(this->priorityAnimation) //*if a priority animation exists, play it first
    {
        
        if (this->priorityAnimation == this->animations[key])
        {
          
          if (this->lastAnimation != this->animations[key])
          {
              
              if (this->lastAnimation == NULL)
                  this->lastAnimation = this->animations[key];
              
              
              else
              {
                  this->lastAnimation->reset();
                  this->lastAnimation = this->animations[key];
              }
          }
            //if the priority animation is finished 
            if(this->animations[key]->play(dt))
            {
                this->priorityAnimation = NULL;
            }
            
        }
        
    }
    
    else // Play an animation if no other priority animations exist
    {
        if (priority)
        {
            this->priorityAnimation = this->animations[key];
        }
        
    if (this->lastAnimation != this->animations[key])
    {
        
        if (this->lastAnimation == NULL)
            this->lastAnimation = this->animations[key];
        
        
        else
        {
            this->lastAnimation->reset();
            this->lastAnimation = this->animations[key];
        }
    }
    
        this->animations[key]->play(dt);
        
    }
    return this->animations[key]->getDone();
}

const bool& AnimationComponet::play(const std::string& key, const float& dt, const float& speed, const float& speed_max, const bool priority)
{
    if(this->priorityAnimation) //*if a priority animation exists, play it first
    {
           
           if (this->priorityAnimation == this->animations[key])
           {
             
             if (this->lastAnimation != this->animations[key])
             {
                 
                 if (this->lastAnimation == NULL)
                     this->lastAnimation = this->animations[key];
                 else
                 {
                     this->lastAnimation->reset();
                     this->lastAnimation = this->animations[key];
                 }
             }

                    
        
            if(animations[key]->play(dt, abs(speed / speed_max)))
               {
                this->priorityAnimation = NULL;
               }
            }
        }
               
        else
        {
            //if there is a priority animation, set true 
            if (priority)
            {
                this->priorityAnimation = this->animations[key];
            }
            
    if (this->lastAnimation != this->animations[key])
    {
        if (this->lastAnimation == NULL)
            this->lastAnimation = this->animations[key];
        
        
        else
        {
            this->lastAnimation->reset();
            this->lastAnimation = this->animations[key];
        }
    }
    
    this->animations[key]->play(dt, abs(speed / speed_max));
    
}
    return this->animations[key]->getDone();
}
//*End Functions*

//*Accessors*
const bool& AnimationComponet::getDone(const std::string key)
{
    return this->animations[key]->getDone();
    
}
