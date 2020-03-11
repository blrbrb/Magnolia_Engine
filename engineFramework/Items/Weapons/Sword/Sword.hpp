//
//  Sword.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Sword_hpp
#define Sword_hpp
#include "Weapon.hpp"

class Weapon;

class Sword : public Weapon
{
public:
    
    Sword(unsigned value, std::string texture_file); 
    virtual ~Sword();
    
    //Functions
    virtual void update(const sf::Vector2f& MousePosView, const sf::Vector2f center);
    virtual void render(sf::RenderTarget& target, sf::Shader * shader = nullptr);
    
    virtual Sword* clone();
    
private:
    
};

#endif /* Sword_hpp */
