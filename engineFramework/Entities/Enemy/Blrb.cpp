//
//  Blrb.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/5/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "Blrb.hpp"


void Blrb::initvariables()
{
    
}

void Blrb::initanimations()
{
      this->animtioncomponet->add_animation("IDLE", 25.f, 0, 0, 6, 0, 17, 17);
}


Blrb::Blrb(float x, float y, sf::Texture &texturesheet) : Enemy()
{
    
    this->createmovementcomponet(150.f , 2000.f, 500.f);
    this->create_animation_componet(texturesheet);
    this->create_hitbox_componet(this->sprite, 0, 0, 17.f, 17.f);
    this->initanimations();
    this->sprite.setScale(3.f, 3.f);
    this->sprite.setPosition(x,y);
    this->initvariables();
    this->initanimations();
    
}

Blrb::~Blrb()
{
    
}

void Blrb::loseHP(const int HP)
{
    
}

void Blrb::loseEXP(const int EXP)
{
    
}

void Blrb::gainHP(const int HP)
{
    
}

void Blrb::gainEXP(const int EXP)
{

}

void Blrb::updateAnimation(const float &dt)
{
    /*!
       @brief Change the Blrb's animations based on which direction it's walking in
           
       @param const float& dt
        
       @return void
        */
          
          if (this->movementcomponets->getStauts(IDLE))
          {
              
              this->animtioncomponet->play("IDLE", dt, false);
              
          }
}

void Blrb::update(const float &dt, sf::Vector2f &MousePosView)
{
    
       this->movementcomponets->update(dt);
       this->updateAnimation(dt);
       this->hitbox->update();
}

void Blrb::render(sf::RenderTarget &target, sf::Shader *shader, const bool render_hitbox)
{
    if (shader)
      {
          shader->setUniform("hasTexture", true);
          shader->setUniform("light", this->getCenter());
          target.draw(this->sprite, shader);
      }
      

      else if(render_hitbox) {
          this->hitbox->render(target); }
}
