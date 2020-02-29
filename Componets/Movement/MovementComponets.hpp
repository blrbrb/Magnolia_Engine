//
//  MovementComponets.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/29/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//


#ifndef MovementComponets_hpp
#define MovementComponets_hpp



enum movements {IDLE=0,MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponets {
    
private:
   float maxVelocity;
      
     sf::Vector2f Velocity;
      float Acceleration;
        float Deceleration;
    float directional_velocity;
      
      sf::Sprite& sprite;
    
    
public:
    //Constructors/Destructors
     MovementComponets(sf::Sprite& sprite, float maxVelocity, float Acceleration, float Deceleration);
     virtual ~MovementComponets();
    

    //Functions
     void move(const float x, const float y, const float& dt);
     void update(const float&dt);
     void stopVelocity();
     void stopVelocityX();
     void stopVelocityY();
    
    
    //Accessors
     const sf::Vector2f& getvelocity() const;
     const float& getMaxVelocity() const;
     const bool get_moving(const short unsigned state) const;
    

};
#endif /* MovementComponets_hpp */
