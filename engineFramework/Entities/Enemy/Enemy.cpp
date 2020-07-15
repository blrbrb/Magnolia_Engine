//
//  Enemy.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "Enemy.hpp"


Enemy::Enemy(EnemySpawner& spawnertile) :EnemySpawnerTile(spawnertile)
{
   
   
}

Enemy::~Enemy()
{
    
}

void Enemy::initvariables()
{
    this->gainExp = 10;
}

void Enemy::initanimations()
{
    
}



void Enemy::generateAttributes(const unsigned level)
{
    this->gainExp = level * (rand() % 5 + 1);
}

void Enemy::loseHP(const int hp)
{
    if (this->attributes)
    {
        this->attributes->loseHP(hp);
    }

}
const unsigned & Enemy::getGainExp() const
{
    return this->gainExp;
}


EnemySpawner & Enemy::getEnemySpawnerTile()
{
        return this->EnemySpawnerTile;
}


const bool Enemy::isDead() const
{
    if (this->attributes)
    {
        return this->attributes->isdead();
    }

    return false;
}

const StatusComponet * Enemy::getStatusComponent() const
{
    if (this->attributes)
        return this->attributes;
    else
    {
        std::cout << "ERROR::ENEMY::STATUSCOMPONENT IS NOT INITIALIZED" << "\n";
        return nullptr;
    }
}

void Enemy::updateAnimation(const float& dt)
{
   

      
        
}




void Enemy::update(const float& dt, sf::Vector2f& MousePosView)
{
   
  
    
  
    
    
}

void Enemy::render(sf::RenderTarget &target, sf::Shader* shader,const sf::Vector2f light,const bool render_hitbox)
{
  
    
}

