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
    
    Enemy(float x, float y, sf::Texture& texturesheet);
    virtual ~Enemy();
    
    EnemySpawner& enemyspawner; 
    
    //Functions
       void loseHP(const int HP);
       void loseEXP(const int EXP);
       void gainHP(const int HP);
       void gainEXP(const int EXP);
    
    void update(const float& dt, sf::Vector2f& MousePosView);
    void updateAnimation(const float& dt);
    void render(sf::RenderTarget& target,sf::Shader* shader = nullptr, const bool render_hitbox = false);
    
private:
    //initalizer functions
    void initvariables();
   
    void initanimations(); 
};

#endif /* Enemy_hpp */
