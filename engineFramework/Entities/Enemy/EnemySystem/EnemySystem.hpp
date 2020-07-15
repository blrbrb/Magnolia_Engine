//
//  EnemySystem.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef EnemySystem_hpp
#define EnemySystem_hpp
#include "Enemy.hpp"
#include "Blrb.hpp"

enum EnemyTypes {BLRB = 0};
enum MovementDirections {U = 0, D, L, R};

class EnemySystem
{
public:
    
    //variables
    
    
    
    EnemySystem(std::vector<Enemy*>& ActiveEnemies, std::map<std::string, sf::Texture>& textures);
    virtual ~EnemySystem();
    
    //Accessors
     
    
    //Functions
    void SpawnEnemy(const short type, const float x, const float y, EnemySpawner& enemy_spawner_tile);
    void RemoveEnemy(const int index);
    
    void update(const float& dt);
    
    void render(sf::RenderTarget* target);
    
private:
    
std::map<std::string, sf::Texture>& textures;
    
std::vector<Enemy*>& ActiveEnemies;
    
    
    
};

#endif /* EnemySystem_hpp */
