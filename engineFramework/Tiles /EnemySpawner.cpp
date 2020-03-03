//
//  EnemySpawner.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "EnemySpawner.hpp"


EnemySpawner::EnemySpawner(int x, int y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, sf::Vector2i &grid_position, int type, int Enemyamount, int time_to_spawn, float max_distance) : Tile(x, y, gridsize_f, texture, texturerect, false, TileTypes::SPAWNER)
{
    this->tile.setSize(sf::Vector2f(30, 30));
    this->tile.setFillColor(sf::Color::White);
    this->gridPosition = grid_position;
    this->type = type;
    this->Enemyamount = Enemyamount;
    this->spawn_timer = time_to_spawn;
    this->maxDistance = max_distance;
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
