//
//  Coin.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/19/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Coin_hpp
#define Coin_hpp
#include "Item.hpp"
 
class Coin : public Item
{
    
public:
    
    Coin(unsigned value);
    virtual ~Coin();
    
    //Functions

    virtual Coin* clone();
    virtual void render(sf::RenderTarget& target, sf::Shader * shader = nullptr);
    
private:
    
    sf::Texture texture;
    sf::Sprite coinsprite; 
    
};

#endif /* Coin_hpp */
