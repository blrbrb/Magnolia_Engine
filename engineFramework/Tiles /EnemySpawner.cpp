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
    this->tile.setSize(sf::Vector2f(30, 30));
    this->type = type;
    this->Enemyamount = Enemyamount;
    this->spawn_timer = time_to_spawn;
    this->maxDistance = max_distance;
    this->spawned = false; 
}

EnemySpawner::~EnemySpawner()
{
    
    

}

void EnemySpawner::clear()
{
    
}

void EnemySpawner::update()
{
    
}

void EnemySpawner::render(sf::RenderTarget &target, sf::Shader* shader, sf::Vector2f PlayerPosition)
{
    target.draw(this->tile);
}

const std::string EnemySpawner::asString() const 
{
    std::stringstream ss;
    
    ss << this->type << "" << this->rect.getTextureRect().left << "" << this->rect.getTextureRect().top << "" << this->Enemytype
    << "" << this->Enemyamount << "" << this->spawn_timer << "" << this->maxDistance;
    
    return ss.str();
    
}

const bool EnemySpawner::SetSpawned(const bool spawned)
{
    this->spawned = spawned;
}


