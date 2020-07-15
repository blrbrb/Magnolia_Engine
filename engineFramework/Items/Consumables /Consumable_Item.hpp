//
//  Consumable_Item.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 7/15/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Consumable_Item_hpp
#define Consumable_Item_hpp
#include "Item.hpp"

class Consumable_Item : public Item
{
public:
    
    Consumable_Item(unsigned value);
    virtual ~Consumable_Item();
    
    virtual void update() =0;
        
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) =0;
    
protected:
    
    sf::IntRect texture_rect;
    sf::Sprite sprite;
    sf::Texture texturesheet;

private:
    
    void inittexturesheet();
    void initvariables(); 
    
}; 

#endif /* Consumable_Item_hpp */
