//
//  EnemySpawner.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "EnemySpawner.hpp"


EnemySpawner::EnemySpawner(float x, float y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, int type, int Enemyamount, int time_to_spawn, int max_distance) : Tile(TileTypes::SPAWNER, x, y, gridsize_f, texture, texturerect, false)
{
    //Init variables
    this->Enemy_type = type;
    this->Enemy_amount = Enemyamount;
    this->spawn_timer = time_to_spawn;
    this->maxDistance = max_distance;
    this->Spawned = false;
}

EnemySpawner::~EnemySpawner()
{
    
    

}

void EnemySpawner::clear()
{
    
}

void EnemySpawner::update(const float& dt)
{
    
}

void EnemySpawner::render(sf::RenderTarget &target, sf::Shader* shader, sf::Vector2f PlayerPosition)
{
  if (shader)
  {
      shader->setUniform("hasTexture", true);
      shader->setUniform("lightPos", PlayerPosition);

      target.draw(this->rect, shader);
  }
  else
      target.draw(this->rect);
}

const std::string EnemySpawner::asString() const 
{
    std::stringstream ss;
    
    ss << this->type << " " << this->rect.getTextureRect().left << " " << this->rect.getTextureRect().top << " " << this->Enemy_type
    << " " << this->Enemy_amount << " " << this->spawn_timer << " " << this->maxDistance;
    
    //std::cout << ss.str() << std::endl;
    
    return ss.str();
    
}

const bool EnemySpawner::SetSpawned(const bool spawned)
{
    this->Spawned = spawned;
}

const bool &EnemySpawner::getSpawned() const
{
    return this->Spawned; 
}



