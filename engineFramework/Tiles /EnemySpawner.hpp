//
//  EnemySpawner.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef EnemySpawner_hpp
#define EnemySpawner_hpp
#include "Tile.hpp"

class Tile;

class EnemySpawner : public Tile
{
    
private:
    
    
    sf::Vector2i gridPosition;
    sf::RectangleShape tile; 
    int Enemytype;
    int Enemyamount;
    int spawn_timer;
    float maxDistance;
    bool spawned;
    
public:
    //construtor and destructor
    EnemySpawner(float x, float y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, int Enemytype, int Enemyamount, int time_to_spawn, int max_distance);
    virtual ~EnemySpawner();
  
    //Accessors
    const bool SetSpawned(const bool spawned);
    const std::string asString() const;
    
    
    void clear();
    void update();
    void render(sf::RenderTarget & target, sf::Shader* shader = NULL, sf::Vector2f PlayerPosition = sf::Vector2f());
    
};

#endif /* EnemySpawner_hpp */

