//
//  Enemy.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "Enemy.hpp"


Enemy::Enemy(float x, float y, sf::Texture& texturesheet) : enemyspawner(enemyspawner)
{
      this->createmovementcomponet(150.f , 2000.f, 500.f);
      this->create_animation_componet(texturesheet);
      this->create_hitbox_componet(this->sprite, 0, 0, 17.f, 17.f);
      this->initanimations();
      this->sprite.setScale(3.f, 3.f);
      this->sprite.setPosition(x,y);
    
}

Enemy::~Enemy()
{
    
}




void Enemy::initanimations()
{
    
    this->animtioncomponet->add_animation("IDLE", 25.f, 0, 0, 6, 0, 17, 17);

}
    

void Enemy::updateAnimation(const float& dt)
{
    /*!
    @brief Change the Enemy's animations based on which direction they're walking in
        
    @param const float& dt
     
    @return void
     */
       
       if (this->movementcomponets->get_moving(IDLE))
       {
           
           this->animtioncomponet->play("IDLE", dt, false);
           
       }

      
        
}




void Enemy::update(const float& dt, sf::Vector2f& MousePosView)
{
   
   
    this->movementcomponets->update(dt);
    this->updateAnimation(dt);
    
    this->hitbox->update();
    
  
    
   
}

void Enemy::render(sf::RenderTarget &target, sf::Shader* shader,const bool render_hitbox)
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
