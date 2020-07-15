//
//  Apple.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 7/15/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Apple_hpp
#define Apple_hpp
#include "Consumable_Item.hpp"

class Apple : public Consumable_Item
{
public:
    
    Apple(unsigned value);
    virtual ~Apple();
    
    void update();
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
    
private:
    
     void initvariables(); 
};

#endif /* Apple_hpp */
