//
//  Tile.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
// 

#ifndef Tile_hpp
#define Tile_hpp


#include "GUI.hpp"

enum TileTypes {DEFAULT=0, UNPASSABLE, OBJECT};

class Tile
{
private:
    
    
protected:
    
    sf::Sprite rect;
    short type;
    bool collison_enabled; 
  
    
public:
    Tile();
    Tile(int x, int y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();
    
    //Accessors
    const std::string asString() const;
    const short& gettype() const;
    const sf::Vector2f& getposition() const;
    const bool& getCollision() const;
    const bool intersects(const sf::FloatRect bounds) const;
    const sf::FloatRect getGlobalBounds() const; 
    
    //Functions
    void update();
    void render(sf::RenderTarget & target, sf::Shader* shader = NULL, sf::Vector2f PlayerPosition = sf::Vector2f());
    
};



#endif /* Tile_hpp */
