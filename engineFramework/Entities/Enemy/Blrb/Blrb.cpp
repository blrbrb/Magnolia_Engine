//
//  Blrb.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/5/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "Blrb.hpp"


void Blrb::initvariables()
{
    this->create_attribute_componet(1);
    this->createmovementcomponet(150.f , 2000.f, 500.f);
    this->create_hitbox_componet(this->sprite, 0, 0, 17.f, 17.f);
    
    
}

void Blrb::initanimations()
{
     this->animtioncomponet->add_animation("IDLE", 25.f, 0, 0, 6, 0, 17, 17);
     this->animtioncomponet->add_animation("LEFT", 25.f, 0, 0, 6, 0, 17, 17);
     this->animtioncomponet->add_animation("RIGHT", 25.f, 0, 0, 6, 0, 17, 17);
     this->animtioncomponet->add_animation("UP", 25.f, 0, 3, 6, 0, 17, 17);
     this->animtioncomponet->add_animation("DOWN", 25.f, 0, 4, 6, 0, 17, 17);
     this->animtioncomponet->add_animation("ATTACKED", 25.f, 0, 2, 6, 0, 17, 17);
    

}


Blrb::Blrb(float x, float y, sf::Texture &texturesheet, EnemySpawner& enemyspawner) : Enemy(enemyspawner)
{
    this->initvariables();
    this->create_animation_componet(texturesheet);
    this->initanimations();
    this->create_skill_component();
    //this->sprite.setScale(2.f, 2.f);
    this->sprite.setPosition(x,y);

}



Blrb::~Blrb()
{
    
}

void Blrb::updateAnimation(const float &dt)
{
   
          if (this->movementcomponets->getStauts(IDLE))
          {
              
              this->animtioncomponet->play("IDLE", dt, false);
              
          }

            if (this->movementcomponets->getStauts(MOVING_LEFT))
            {
                 
               this->animtioncomponet->play("LEFT", dt, false);
                 
            }
    
   
    if (this->movementcomponets->getStauts(MOVING_UP))
    {
        
        this->animtioncomponet->play("UP", dt, false);
        
    }
    
    if (this->movementcomponets->getStauts(MOVING_DOWN))
    {
        
        this->animtioncomponet->play("DOWN", dt, false);
        
    }
    
    if (this->movementcomponets->getStauts(MOVING_RIGHT))
    {
        
        this->animtioncomponet->play("RIGHT", dt, false);
        
    }
        
}




void Blrb::update(const float &dt, sf::Vector2f &MousePosView)
{
       this->movementcomponets->update(dt);
       this->attributes->update();
       this->attributes->UpdateStats(false);
       this->updateAnimation(dt);
       this->hitbox->update();
}





void Blrb::render(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f light, const bool render_hitbox)
{
    if (shader)
      {
          shader->setUniform("hasTexture", true);
          shader->setUniform("light", light);
         
          target.draw(this->sprite, shader);
      }
    
    else if (!shader)
    {
        
        target.draw(this->sprite);
    }
      
      if(render_hitbox) {
          this->hitbox->render(target); }
}


StatusComponet* Blrb::getStatusComponent()
{
    
    return this->attributes;
}
