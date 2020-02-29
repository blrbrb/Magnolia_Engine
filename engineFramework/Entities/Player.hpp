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

class Entity; 

class Player : public Entity
{
private:
    //initalizer functions
    void initvariables();
    void initcomponets();
    
    //Variables
    bool attacking;
    


public:

    Player(float x, float y, sf::Texture& texturesheet);
    virtual ~Player();
    
    //Accessors
    StatusComponet* getStatusComponet(); 

    //Functions
    
    void loseHP(const int HP);
    void loseEXP(const int EXP);
    void gainHP(const int HP);
    void gainEXP(const int EXP);
    
    
     void update(const float& dt);
     void updateAnimation(const float& dt);
     void render(sf::RenderTarget& target,sf::Shader* shader = NULL, const bool render_hitbox = false);

    
};

#endif /* Player_hpp */
