//
//  HitBoxComponet.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/1/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef HitBoxComponet_hpp
#define HitBoxComponet_hpp



class HitBoxComponet
{
public:
    
    //Constructors/Destructors 
    HitBoxComponet(sf::Sprite& sprite,float offset_x, float offset_y, float width, float height);
    virtual ~HitBoxComponet(); 
    
    
    //Functions
    void update();
    void render(sf::RenderTarget& target);
    bool intersects(const sf::FloatRect& rect);
    
    //Modifiers
    
    void setposition(const sf::Vector2f positon);
    void setposition(const float x, const float y);
    
    //Accessors
    const sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity); 
    
    
    
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
    float offsetX;
    float offsetY;
    sf::FloatRect nextpos;
    
};

#endif /* HitBoxComponet_hpp */
