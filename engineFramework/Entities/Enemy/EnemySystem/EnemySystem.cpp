//
//  EnemySystem.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "EnemySystem.hpp"


EnemySystem::EnemySystem(std::vector<Enemy *> &ActiveEnemies, std::map<std::string, sf::Texture> &textures) : textures(textures), ActiveEnemies(ActiveEnemies)
{
    
    this->textures = textures;
    this->ActiveEnemies = ActiveEnemies;
   
    
    
    
}

EnemySystem::~EnemySystem()
{
    
}

void EnemySystem::SpawnEnemy(const short type, const float x, const float y, EnemySpawner& enemy_spawner_tile)
{
    switch (type)
    {
        case EnemyTypes::BLRB:
            this->ActiveEnemies.push_back(new Blrb(x, y, this->textures["ENEMY_SHEET"], enemy_spawner_tile));
            enemy_spawner_tile.increaseEnemyCounter();
            
            break;
            
        default:
            
            throw std::invalid_argument("EnemySystem::SpawnEnemy" "Const Short Enemy Type: "  + std::to_string(type) + " is not a valid enemy type" );
             break;
   
    }
    
}


void EnemySystem::RemoveEnemy(const int index)
{
    this->ActiveEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();
    delete this->ActiveEnemies[index];
    this->ActiveEnemies.erase(this->ActiveEnemies.begin() + index);
    
}

void EnemySystem::update(const float &dt)
{
   
    
}

void EnemySystem::render(sf::RenderTarget *target)
{

    
    
}













