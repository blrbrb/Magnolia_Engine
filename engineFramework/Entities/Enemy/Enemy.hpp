//
//  Enemy.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Enemy_hpp
#define Enemy_hpp
#include "Entity.hpp"
#include "EnemySpawner.hpp"

class Entity;

class Enemy : public Entity
{
public:
    
    Enemy(EnemySpawner& spawnertile);
    virtual ~Enemy();
    
    
    virtual const StatusComponet* getStatusComponent() const;
    
    virtual void generateAttributes(const unsigned level);
    virtual void update(const float& dt, sf::Vector2f& MousePosView) = 0;
    virtual void updateAnimation(const float& dt) = 0;

    //Functions
    virtual void loseHP(const int hp);
    
    //Accessors
    virtual const bool isDead() const;
    EnemySpawner& getEnemySpawnerTile();
    const unsigned& getGainExp() const;
    
    virtual void render(sf::RenderTarget& target,sf::Shader* shader = nullptr,const sf::Vector2f light = sf::Vector2f(), const bool render_hitbox = false) = 0;
 
protected:

    //child class variables
       std::string name;
    
     
    
private:
    //initalizer functions
   virtual void initvariables() = 0;
   virtual void initanimations() = 0;
   unsigned gainExp;
    
    EnemySpawner& EnemySpawnerTile;
   
};

#endif /* Enemy_hpp */
