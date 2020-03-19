//
//  Enemy.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp
#include "Entity.hpp"
#include "EnemySpawner.hpp"

class Entity;

class Enemy : public Entity
{
public:
    
    Enemy();
    virtual ~Enemy();
    
    //EnemySpawner& enemyspawner; 
    
    //Functions
      virtual void loseHP(const int HP) = 0;
      virtual void gainHP(const int HP) = 0;
   
    
    virtual void update(const float& dt, sf::Vector2f& MousePosView) = 0;
    virtual void updateAnimation(const float& dt) = 0;
    virtual void render(sf::RenderTarget& target,sf::Shader* shader = nullptr,const sf::Vector2f light = sf::Vector2f(), const bool render_hitbox = false) = 0;
    
private:
    //initalizer functions
   virtual void initvariables() = 0;
   virtual void initanimations() = 0;
};

#endif /* Enemy_hpp */
