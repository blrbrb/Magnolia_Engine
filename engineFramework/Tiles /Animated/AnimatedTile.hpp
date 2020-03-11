//
//  AnimatedTile.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/9/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef AnimatedTile_hpp
#define AnimatedTile_hpp
#include "Tile.hpp"
#include "AnimationComponet.hpp"


class Tile;
class AnimationComponet;

class AnimatedTile : public Tile
{
private:
    
    sf::Sprite rect;
    AnimationComponet* animationcomponet; 
    sf::IntRect AnimationRect;
    sf::Texture texture;
    short type;
    bool collison_enabled;
    
    void initvariables();
    
public:
    
    AnimatedTile(short type, int x, int y, float gridsize_f, sf::Texture& texture, const sf::IntRect& texturerect, bool collision_enabled = false);
    virtual ~AnimatedTile();
    
    //Accessors
    const std::string asString() const;
    const bool& getCollision() const;
    
    //Functions
    void update(const float& dt);
    void render(sf::RenderTarget & target, sf::Shader* shader = NULL, sf::Vector2f PlayerPosition = sf::Vector2f());
    //Modifiers
    
    
};

#endif /* AnimatedTile_hpp */
