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

void EnemySystem::create(short type, const float x, const float y)
{
    switch (type)
    {
        case EnemyTypes::BLRB:
            this->ActiveEnemies.push_back(new Blrb(x, y, this->textures["ENEMY_SHEET"]));
            break;
            
        default:
            std::cout << "LMAO you FUCKING idiot. YOU FUCKED IT UP YOur LIFE IS MEANINGLESS. GET A REAL FUCKING JOB AND STOP SITTING AROUNG MESSING WITH YOUR GAMES ALL DAY ELI. FUCK AROUND TIME IS OVER ~ Dad" << std::endl;
             break;
   
    }
    
}

void EnemySystem::update(const float &dt)
{
   
    
}

void EnemySystem::render(sf::RenderTarget *target)
{

    
    
}













