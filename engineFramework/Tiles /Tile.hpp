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

enum TileTypes {DEFAULT=0, UNPASSABLE, OBJECT, GRASS, DIRT, WATER, METAL, STONE, SAND, WOOD, SPAWNER, ANIMATED};

class Tile
{
private:
    
    
protected:
    
    sf::Sprite rect;
    short type;
    bool collison_enabled; 
    
    
public:
    
    Tile();
    Tile(short type, int x, int y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled = false );
    virtual ~Tile();
    
    //Accessors
    virtual const std::string asString() const =0;
    virtual const short& gettype() const;
    virtual const sf::Vector2f& getposition() const;
    virtual const bool& getCollision() const;
    virtual const bool intersects(const sf::FloatRect bounds) const;
    virtual const sf::FloatRect getGlobalBounds() const;
    
    //Functions
    virtual void update(const float& dt) =0;
    virtual void render(sf::RenderTarget & target, sf::Shader* shader = NULL, sf::Vector2f PlayerPosition = sf::Vector2f())=0;
    
};


#endif /* Tile_hpp */
