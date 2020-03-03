//
//  Entity.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/23/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp
#include "HitBoxComponet.hpp"
#include "MovementComponets.hpp"
#include "AnimationComponet.hpp"
#include "StatusComponet.hpp"
#include "SkillComponent.hpp"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class SkillComponent;

class Entity {
    
public:
    
    MovementComponets* movementcomponets;
    AnimationComponet* animtioncomponet;
    HitBoxComponet* hitbox;
    StatusComponet* attributes;
    SkillComponent* skillcomponent; 
    sf::Sprite sprite;
    sf::Texture* texture;
    
    //Constructor et Destructor
       Entity();
       virtual ~Entity();
   
     //Modifiers
    virtual void setposition(const float x, const float y);
    void settexture(sf::Texture& texture);
    
    //Accessors
    virtual const sf::Vector2f& getPosition() const;
    virtual const sf::Vector2f getCenter() const; 
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
    virtual const sf::FloatRect getNextPositionBounds(const float& dt) const; 
    
    //Functions
    virtual void move(const float& dt, const float x, const float y);
    virtual void update(const float& dt, sf::Vector2f& MousePosView) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader, const bool render_hitbox) = 0;
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();
    
    
        //Component init functions
        void createmovementcomponet(const float maxVelocity, const float Acceleration, const float Deceleration);
        void create_animation_componet(sf::Texture& texturesheet);
        void create_hitbox_componet(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
        void create_attribute_componet(const unsigned level);
        void create_skill_component(); 
       
    
   
    
private:
    void initvariables(); 
   
    
protected:

   
  
    
};



#endif /* Entity_hpp */
