//
//  Player.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/28/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "Player.hpp"

//Constructors, Destructors

Player::Player(float x, float y, sf::Texture& texturesheet)
{
    
    
    this->initcomponets();
    this->initinventory(); 
    this->setposition(x, y);

    this->create_animation_componet(texturesheet);
    this->initanimations();
    //this->sprite.setScale(2, 2);

}

Player::~Player()
{
    
    delete this->inventory; 
    delete this->sword; 
    
}


//initalizer functions

void Player::initcomponets()
{
    this->createmovementcomponet(50.f ,2000.f, 200.f);     //current dimensions of hero.png 16x16 plus scale = 64x64
    this->create_hitbox_componet(this->sprite, 5, 5, 55.f, 60.f);    //Note: is lower because cropped for more accurate collision
    this->create_attribute_componet(1);
    this->create_skill_component();
    this->sword = new Sword(2, "sword.png");
    

}

void Player::initinventory()
{
    this->inventory = new Inventory(100);
}




void Player::initvariables()
{
    this->attacking = false; 
}

void Player::initanimations()
{
    
    this->animtioncomponet->add_animation("IDLE_LEFT", 10.f, 4, 0, 4, 0, 16, 16);
    this->animtioncomponet->add_animation("WALK_RIGHT", 10.f, 4, 1, 7, 1, 16, 16);
    this->animtioncomponet->add_animation("WALK_LEFT", 10.f, 0, 1, 3, 1, 16, 16);
    this->animtioncomponet->add_animation("WALK_DOWN", 10.f, 4, 0, 7, 0, 16, 16);
    this->animtioncomponet->add_animation("WALK_UP", 10.f, 0, 0, 3, 0, 16, 16);
    
    //lol
    this->animtioncomponet->add_animation("PISSING_PANTS", 10.f, 0, 0, 5, 0, 16, 16);
    
}
    

void Player::updateAnimation(const float& dt)
{
    /*!
    @brief Change the player's animations based on which direction they're walking in
        
    @param const float& dt
     
    @return void
     */
       
       this->movementcomponets->update(dt);
       
       if (this->movementcomponets->getStauts(IDLE))
       {
           
       this->animtioncomponet->play("IDLE_LEFT", dt);
           
       }

       else if(this->movementcomponets->getStauts(MOVING_RIGHT))
       {
           this->animtioncomponet->play("WALK_RIGHT", dt);
           
       }
       
       else if (this->movementcomponets->getStauts(MOVING_LEFT))
       {
           this->animtioncomponet->play("WALK_LEFT", dt);
           
       }
       
       else if (this->movementcomponets->getStauts(MOVING_DOWN))
       {
           
           this->animtioncomponet->play("WALK_DOWN", dt);
           
       }
       
       else if (this->movementcomponets->getStauts(MOVING_UP))
       {
           this->animtioncomponet->play("WALK_UP", dt);
       }

}




void Player::update(const float& dt, sf::Vector2f& MousePosView)
{
    //debug. Exp gain test
    
    this->attributes->update();
    this->attributes->UpdateStats(true);
    
    this->movementcomponets->update(dt);
    
    this->updateAnimation(dt);
    
    this->hitbox->update();
    
   
    
   
}





void Player::render(sf::RenderTarget &target, sf::Shader* shader,const sf::Vector2f light, const bool render_hitbox)
{
    
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("light", light);
        target.draw(this->sprite, shader);
        this->sword->render(target, shader);
       
    }

    else if(render_hitbox) {
        this->hitbox->render(target); }
    
}

StatusComponet *Player::getStatusComponet()
{
    return this->attributes;
}


Inventory* Player::getInventory()
{
    return this->inventory; 
}


void Player::loseHP(const int HP)
{
    
    this->attributes->hp -= HP;
    
    if(this->attributes->hp < 0)
        this->attributes->hp = 0;
}



void Player::loseEXP(const int EXP)
{
    this->attributes->exp -= EXP;
       
       if(this->attributes->exp < 0)
           this->attributes->exp = 0;
}



void Player::gainHP(const int HP)
{
    this->attributes->hp += HP;
    
    if(this->attributes->hp > this->attributes->hpMax)
        this->attributes->hp = this->attributes->hpMax;
}



void Player::gainEXP(const int EXP)
{
    this->attributes->gainexp(EXP);
}


void Player::gainCoins(const int COINS)
{
    this->attributes->gaincoins(COINS);
}
