//
//  Entity.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/23/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Entity_hpp
#define Entity_hpp
#include "HitBoxComponet.hpp"
#include "MovementComponets.hpp"
#include "AnimationComponet.hpp"
#include "StatusComponet.hpp"
#include "SkillComponent.hpp"
#include "Item.hpp"


class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class SkillComponent;

class Entity {
    
public:
    
    ///The Movement Component
    MovementComponets* movementcomponets;
    ///The Animation Component
    AnimationComponet* animtioncomponet;
    /// The Hitbox Component
    HitBoxComponet* hitbox;
    ///The Status Component
    StatusComponet* attributes;
    /// The Skill Component 
    SkillComponent* skillcomponent;
    ///The entity's sprite
    sf::Sprite sprite;
    ///the texture used to generate the entity's sprite
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
    virtual const float getDistance(const Entity& entity) const;
    
    //Functions
    ///  Move the entity in a particular direction
    /// @param dt const float Delta-Time
    /// @param x   const float X-Acceleration
    /// @param y const float Y-Acceleration
    virtual void move(const float& dt, const float x, const float y);
    ///  Move the entity at a random interval, in random directions
    /// @param dt Delta-Time
    /// @param seed a Seed
    virtual void move_rand(const float& dt, int seed);
    
    virtual void update(const float& dt, sf::Vector2f& MousePosView) = 0;
    
    virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light, const bool render_hitbox) = 0;
    
    ///  Bring the Entity to a complete stop
    virtual void stopVelocity();
    ///  Stop the X Velocity of the Entity
    virtual void stopVelocityX();
    /// Stop the Y Velocity of the Entity
    virtual void stopVelocityY();
    
    
    //Component init functions
    ///  @brief Generate the movement component for the Entity,
    ///   This component will be used to determine all physics interactions between objects and the entity / other entites
    ///
    /// @param maxVelocity The maximum overall speed the entity should be able to reach
    /// @param Acceleration The rate of acceleration the entity should have
    /// @param Deceleration The rate of deceleration the entity should have
    
    void createmovementcomponet(const float maxVelocity, const float Acceleration, const float Deceleration);
    
    /// Generate the animation component for the entity
    /// @param texturesheet A texturesheet to split into an animation
    void create_animation_componet(sf::Texture& texturesheet);
    
    /// Generate the entity's hitbox
    /// @param sprite The sprite used to represent the entity on screen
    /// @param offset_x The X offset for the hitbox
    /// @param offset_y The Y-offset for the hitbox
    /// @param width The width of the hitbox
    /// @param height The height of the hitbox
    void create_hitbox_componet(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    
    /// Generate the Leveling, Status, etc values for the entity
    /// @param level const unsigned level to start the entity out on
    void create_attribute_componet(const unsigned level);
    
    /// Genertate the entity's skill component.
    void create_skill_component();
       
    
   
    
private:
    void initvariables();
    

    
protected:

   
  
    
};



#endif /* Entity_hpp */
