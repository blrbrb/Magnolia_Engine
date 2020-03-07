//
//  EnemySystem.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/6/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef EnemySystem_hpp
#define EnemySystem_hpp
#include "Enemy.hpp"
#include "Blrb.hpp"

enum EnemyTypes {BLRB = 0};

class EnemySystem
{
public:
    
    EnemySystem(std::vector<Enemy*>& ActiveEnemies, std::map<std::string, sf::Texture>& textures);
    virtual ~EnemySystem();
    
    
    void create(short type, const float x, const float y);
    void update(const float& dt);
    void render(sf::RenderTarget* target);
    
private:
    
std::map<std::string, sf::Texture>& textures;
std::vector<Enemy*>& ActiveEnemies;
    
    
    
};

#endif /* EnemySystem_hpp */
