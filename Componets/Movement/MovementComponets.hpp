//
//  MovementComponets.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/29/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//


#ifndef MovementComponets_hpp
#define MovementComponets_hpp 


/**
    @brief Supported Directional Velocities
            
    @discussion These enumerations are used  to determine the direction that an object is headed.
 
 */
enum movements {
    IDLE=0, ///< The object's X and Y velocities both equal zero
    MOVING, ///< The object has an non-zero X and or Y velocity
    MOVING_LEFT, ///< The object's X velocity is less than zero
    MOVING_RIGHT,///<The object's X velocity is greater than zero
    MOVING_UP, ///<The object's Y velocity is less than zero
    MOVING_DOWN ///<The object's Y velocity is greater than zero
    
};

/**
    @brief This class  is attached to in game objects that move, and then called when physical  transformations need to be updated. It is important to remember that
                       there is no global physics engine, and the methods in this class must be used on every entiy intended to be non-stationary

 
 */



class MovementComponets {
    
private:

    ///The Velocity of the object
    sf::Vector2f Velocity;
    ///the Position of the Object
    sf::Vector2f Position;
    ///The momentum of the object
    sf::Vector2f Momentum;

    float AccelerationX;
    float AccelerationY;
    float Acceleration; 
    float Volume; 
    float Force;
    float Linear_Inertia;
    float Power;
    float Work;
    float Deceleration;
    float directional_velocity;
    float Impulse;
    float maxVelocity;

   
    
    float DeltaVelocityX;
    float DeltaVelocityY;
    float pastVelX;
    float pastVelY;
    
    
    float movement_time;
    float movement_timeMax;
    
    ///Max random movement seed;
     float rand_max;

    
    sf::Sprite& sprite;
    
    
public:
    
    
    /// MovementComponets
    /// @discussion Construct a movement component for an entity.
    /// @coclass Entity
    /// @param sprite the entity's sprite
    /// @param maxVelocity set a maximum velocity
    /// @param Acceleration set a rate of acceleration
    /// @param Deceleration set a rate of deceleration
     MovementComponets(sf::Sprite& sprite, float maxVelocity, float Acceleration, float Deceleration);
     virtual ~MovementComponets();
    

  
    
    
     void move(const float x, const float y, const float& dt);
    

     void update(const float&dt);
    
    /// move_rand
    /// @discussion Move the entity at a random interval, in a random direction
    /// @param dt Delta-Time
    /// @param seed rand
     void move_rand(const float& dt, int seed);
    
     void updateMoveTime(const float& dt);
    
    /// Bring the enttiy to a complete stop
     void stopVelocity();
    ///Bring the entity's X velocity to a complete stop
     void stopVelocityX();
    ///Bring the entity's Y velocity to a complete stop
     void stopVelocityY();
    
    
    //Accessors
    /// Fetch the current velocity of the entity
     const sf::Vector2f& getvelocity() const;
    ///Fetch the maximum possible velocity of the entity
     const float& getMaxVelocity() const;
    ///Fetch the acceleration of the entity
     const float& getAcceleration() const;
    ///@brief getStatus
    ///@discussion  Fetch wether or not the entity is moving in a particular direction
    ///@param state the direction to check
     const bool getStauts(const short unsigned state) const;
    
    
     const bool getmovetime();
     
    
};
#endif /* MovementComponets_hpp */
