//
//  Player.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/28/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Player_hpp
#define Player_hpp
#include "Entity.hpp"
#include "Sword.hpp"
#include "Inventory.hpp"

class Entity; 

class Player : public Entity
{
private:
    
    //initalizer functions
    void initvariables();
    void initcomponets();
    void initanimations(); 
    void initinventory();
    
    
    
    Sword* sword; 
    
    Inventory* inventory;
    
    //Variables
    bool attacking;
    
    
    sf::Texture weapon;
    sf::Sprite Weapon; 

public:

    Player(float x, float y, sf::Texture& texturesheet);
    virtual ~Player();
    
    //Accessors
    ///Retrieve a pointer to the Player's status component through Entity
    StatusComponet* getStatusComponet();
    ///Retrieve a pointer to the Player's Inventory
    Inventory* getInventory();
    

    //Functions
    
    /// Take away HP points from the Player's Status Component
    ///  @param HP const int amount of HP to reduce
    void loseHP(const int HP);
    
    /// Take away EXP points from the Player's Status Component
    /// @param EXP const int amount of EXP to reduce
    void loseEXP(const int EXP);
    
    /// Give HP points to the Player's Status Component
    /// @param HP const int amount of HP to give
    void gainHP(const int HP);
    
    /// Give EXP points to the Player's Status Component
    ///  @param EXP const int amount of EXP to give
    void gainEXP(const int EXP);
    
    /// Give coins to the Player's Status Component
    /// @param COINS const int amount of coins to give
    void gainCoins(const int COINS); 
    
    
    ///  Update the Player
    /// @param dt Delta-Time
    /// @param MousePosView sf::Vector2f, the mouse's position relative to the view
     void update(const float& dt, sf::Vector2f& MousePosView);
    
    /// Update the Player's animation component
    /// @param dt Delta-Time
     void updateAnimation(const float& dt);
    
    /// Render the entity to either an OpenGL object, or an sf::RenderTarget
    /// @param target the intended target to render to
     void render(sf::RenderTarget& target,sf::Shader* shader = nullptr,const sf::Vector2f light = sf::Vector2f(), const bool render_hitbox = false);

    
};

#endif /* Player_hpp */
