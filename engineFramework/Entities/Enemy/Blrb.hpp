//
//  Blrb.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/5/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Blrb_hpp
#define Blrb_hpp
#include "Enemy.hpp"
 
class Blrb : public Enemy
{
    
public:
    
    Blrb(float x, float y, sf::Texture& texturesheet);
    virtual ~Blrb();
    
    void loseHP(const int HP);
    void loseEXP(const int EXP);
    void gainHP(const int HP);
    void gainEXP(const int EXP);
    
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& MousePosView);
    void render(sf::RenderTarget& target,sf::Shader* shader = nullptr, const bool render_hitbox = false);
    
private:
    
    void initvariables();
    void initanimations();
    
    
};

#endif /* Blrb_hpp */
