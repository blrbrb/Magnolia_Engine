//
//  EnviornmentalTIle.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/10/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef EnviornmentalTIle_hpp
#define EnviornmentalTIle_hpp
#include "Tile.hpp"

class EnviornmentalTile : public Tile
{
    
public:
    
    EnviornmentalTile(short type, int x, int y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled = false);
    virtual ~EnviornmentalTile();
    
    const short& gettype() const;
    const std::string asString() const;
    
    void render(sf::RenderTarget & target, sf::Shader* shader = NULL, sf::Vector2f PlayerPosition = sf::Vector2f());
    void update(const float& dt);
private:
    
  
    
};

#endif /* EnviornmentalTIle_hpp */
