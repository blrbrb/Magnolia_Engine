//
//  Player.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/28/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include "Entity.hpp"
#include "Sword.hpp"
#include "Inventory.hpp"

class Entity; 

class Player : public Entity
{
private:
    
    //initalizer functions
    void initvariables();
    void initcomponets();
    void initanimations(); 
    void initinventory();
    
    
    
    Sword* sword; 
    
    Inventory* inventory;
    
    //Variables
    bool attacking;
    
    sf::Texture weapon;
    sf::Sprite Weapon; 

public:

    Player(float x, float y, sf::Texture& texturesheet);
    virtual ~Player();
    
    //Accessors
    StatusComponet* getStatusComponet();
    Inventory* getInventory(); 

    //Functions
    
    void loseHP(const int HP);
    void loseEXP(const int EXP);
    void gainHP(const int HP);
    void gainEXP(const int EXP);
    void gainCoins(const int COINS); 
    
    
     void update(const float& dt, sf::Vector2f& MousePosView);
     void updateAnimation(const float& dt);
     void render(sf::RenderTarget& target,sf::Shader* shader = nullptr,const sf::Vector2f light = sf::Vector2f(), const bool render_hitbox = false);

    
};

#endif /* Player_hpp */
