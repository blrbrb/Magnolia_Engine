//
//  AnimationComponet.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/30/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef AnimationComponet_hpp
#define AnimationComponet_hpp

/**
    
 @brief When applied to an object, can be used to stitch a spritesheet into a working animation
 
 
 */
class AnimationComponet {
    
public:
    
   
    AnimationComponet(sf::Sprite& sprite, sf::Texture& texturesheet);
    virtual ~AnimationComponet();
    
    /**
        @brief Is called in order to add an animation to an object. The new animation is stored in a map container, and can be fetched with the play animation function
        @param A string naming the animation, how fast to play the animation, the start X frame, the Start Y frame, the End X frame, the End Y Frame, the width of the Frame(s), the height of the Frame(s)
        @returns void
     
     */
     void add_animation(const std::string& key,float animationtimer,int start_x, int start_y, int end_x, int end_y, int width, int height);
    
    /**
                @brief Play the animation
                @param the name of the animation, delta time, (bool) priority
                @returns a constant boolean value representing wether or not the animation has finished playing
     */
     const bool& play(const std::string& key, const float& dt, const bool priority = false);
     const bool& play(const std::string& key, const float& dt, const float& speed, const float& speed_max, const bool priority = false);
     void update(const float& dt);
    
    //Accessors
     const bool& getDone(const std::string key);
    
    
    
    
private:
    class Animation {
   
    
        
    public:
        sf::Sprite& sprite;
        sf::Texture& texturesheet;
        sf::IntRect startRect;
        sf::IntRect currentrect;
        sf::IntRect endRect;
        bool done;
        int width;
        int height;
        float animationtimer;
        float timer;
        
        float speed;
        
        Animation(sf::Texture& texturesheet, sf::Sprite& sprite, float animationtimer, int start_x, int start_y, int end_x, int end_y, int width, int height):
      sprite(sprite), texturesheet(texturesheet), width(width), height(height), animationtimer(animationtimer), timer(0.f), done(false)
        {
            this->width = width;
            this->height = height;
            
            this->startRect = sf::IntRect(start_x * width, start_y * height, width, height);
            this->currentrect = startRect;
            this->endRect = sf::IntRect(end_x * width, end_y * height, width, height);
          
            
            this->sprite.setTexture(this->texturesheet, true);
            this->sprite.setTextureRect(this->startRect);
            
        }
        
        
        //*Functions*
        
         const bool& play(const float& dt)
        {
            this->done = false;
            this->timer += 100.f * dt;
            
            if (this->timer >= this->animationtimer)
            {
                //clear the timer
                this->timer = 0.f;
                
                //start the animation
                if (this->currentrect != this->endRect)
                {
                    this->currentrect.left += this->width;
                }
    
                    
                else //restart the animation
                {
                    this->done = true;
                    this->currentrect.left = this->startRect.left;
                }
                
                
                this->sprite.setTextureRect(this->currentrect);
            }
            return this->done;
        }
        
        ///Overloaded play function with user-definable animation speed parameters
         const bool& play(const float&dt, float speed_percent)
        {
            
            if(speed_percent < 0.f)
            {
                speed_percent = 0.5f;
            }
            
            this->done = false;
            this->timer += speed_percent * 100.f * dt;
                    
                    if (this->timer >= this->animationtimer)
                    {
                        //clear the timer
                        this->timer = 0.f;
                        
                        //start the animation
                        if (this->currentrect != this->endRect)
                        {
                            this->currentrect.left += this->width;
                        }
            
                            
                        else //restart the animation
                        {
                            this->currentrect.left = this->startRect.left;
                            this->done = true;
                        }
                        
                        
                        this->sprite.setTextureRect(this->currentrect);
                    }
            return this->done;
        }

       
         void reset()
        {
            this->timer = 0.f;
            this->currentrect = this->startRect;
            
            
        }
        
        //*End Functions*
               
        //*Accessors*
                   
               const bool& getDone() const
               {
                   return this->done;
                
               }
        
        //*End Accessors*
    };
    
    sf::Sprite& sprite;
    sf::Texture& texturesheet;
    std::map<std::string, Animation*> animations;
    Animation* lastAnimation;
    Animation* priorityAnimation;
    
};

#endif /* AnimationComponet_hpp */
