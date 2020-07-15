//
//  Potion.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 7/15/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Potion_hpp
#define Potion_hpp
#include "Consumable_Item.hpp"

class Potion : public Consumable_Item
{
public:
    
    
    Potion(unsigned value);
    virtual ~Potion();
    
    
    void update();
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
    
private:
    
    void initvariables(); 
    
};

#endif /* Potion_hpp */
