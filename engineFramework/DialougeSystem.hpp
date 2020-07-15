//
//  DialougeSystem.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 6/25/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef DialougeSystem_hpp
#define DialougeSystem_hpp


enum DialougeTypes {DEFAULT_TAG = 0, NPC, EVENT, POSITIVE, NEGATIVE};

class DialougeSystem
{
    
private:
    class Textbox
    {
    private:
        
        float directionY;
        float directionX;
        float life_time;
        float speed;
        
        sf::Text text;
        
    public:
        
        Textbox(sf::Font& font, std::string text, float x, float y, sf::Color color, unsigned char_size, float lifetime, float speed, float dir_x, float dir_y)
        {
            this->text.setFont(font);
            this->text.setPosition(x, y);
            this->text.setFillColor(color);
            this->text.setCharacterSize(char_size);
            this->text.setString(text);
            
            this->directionX = dir_x;
            this->directionY = dir_y;

            this->speed = speed;
            this->life_time = lifetime; 
            
        }
        
        ~Textbox()
        {
            
        }
        
        //Accessor
        inline const bool is_removable() const {return this->life_time <= 0.f;}
        
        //Functions
        void update(const float& dt)
        {
            if(this->life_time >= 0.f)
            {
                this->life_time -= 100.f * dt;
                
                this->text.move(this->directionX * this->speed * dt, this->directionY * this->speed * dt);
            }
        }
        void render(sf::RenderTarget& target)
        {
            target.draw(this->text);
        }
        
    };
    
    sf::Font font;
    
    //internal array of text box elements
    
    std::vector<Textbox*> boxes;
    
    std::map<unsigned, Textbox*> templates; 
     
    void initvariables();
    void inittemplates();
    void initfonts(std::string font_file); 
    
    
    
public:
    
    DialougeSystem(std::string font_file);
    virtual ~DialougeSystem();
    
    void addTextbox(unsigned type);
    void removeTextbox();
    
    void update(const float& dt);
    void render(sf::RenderTarget& target);
    
};

#endif /* DialougeSystem_hpp */
