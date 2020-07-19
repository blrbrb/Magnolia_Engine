//
//  Tile.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#ifndef Tile_hpp
#define Tile_hpp


#include "GUI.hpp"

enum TileTypes {DEFAULT=0, UNPASSABLE, OBJECT, SPAWNER, LIGHT};
static const char * EnumStrings[] = { "Default", "Unpassable", "Object", "Spawner", "Light", "Stop", "YOU FOOL", "NO" };


class Tile
{
private:
    
    
protected:
    
    sf::Sprite rect;
    short type;
    bool collison_enabled;
    
    
    
public:
    
    Tile();
    Tile( short type, int x, int y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled = false);
    virtual ~Tile();
    
    //Accessors
    virtual const std::string asString() const =0;
    virtual const short& gettype() const;
    virtual const sf::Vector2f& getposition() const;
    virtual const bool& getCollision() const;
    virtual const bool intersects(const sf::FloatRect bounds) const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::Vector2f getCenter() const;
    
    
    //Functions
    virtual void update() =0;
    virtual void render(sf::RenderTarget & target, sf::Shader* shader = NULL,sf::Vector2f LightPosition = sf::Vector2f())=0;
    
};


#endif /* Tile_hpp */
