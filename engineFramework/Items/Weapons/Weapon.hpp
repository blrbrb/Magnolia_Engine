//
//  Weapon.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Weapon_hpp
#define Weapon_hpp
#include "Item.hpp"
class Item;


class Weapon : public Item
{
public:
    
    Weapon(unsigned value, std::string texture_file);
    virtual ~Weapon();
    
    virtual void update(const sf::Vector2f& MousePosView, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
    virtual Weapon* clone() = 0;
    
    //Accessors
  
    
protected:
    
    sf::Sprite weaponSprite;
    sf::Texture weaponTexture; 
    
    void initvariables();
    
    int damageMin;
    int damageMax;
    int range;
    
private:
    
};

#endif /* Weapon_hpp */
