//
//  GUI.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/5/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef GUI_hpp
#define GUI_hpp
#include "ResourcePath.hpp"

enum ButtonStates{IDLE_BUTTON = 0 , HOVER, PRESSED };
enum BoxStates{IDLE_BOX= 0, HOVER_BOX, PRESSED_BOX};

namespace GUI {


//Functions
   const float pixelpercentX(const float percent, const sf::VideoMode& vm);
   const float pixelpercentY(const float percent, const sf::VideoMode& vm);
   const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);



class Button {

private:
   
    short unsigned ButtonState;
    short unsigned ID;
    sf::RectangleShape rectangle;
    sf::FloatRect ButtonBounds; 
    sf::Texture idle;
    sf::Texture clicked; 
    sf::Texture hover_texture;
    sf::Font *font;
    sf::Text text;
    
    //degug colors remove later
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    //debug colors removce later
    sf::Color outline_idleColor;
    sf::Color outline_hoverColor;
    sf::Color outline_activeColor;
    //debug colors remove later
    sf::Color text_idlecolor;
    sf::Color text_hovercolor;
    sf::Color text_activecolor;
    
    bool hover;
    bool pressed;
    
public:
    
    Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size, sf::Color idlecolor, sf::Color hovercolor, sf::Color activecolor, sf::Color text_idlecolor, sf::Color text_hovercolor, sf::Color text_activecolor,sf::Color outline_activeColor = sf::Color::Transparent, sf::Color outline_idleColor = sf::Color::Transparent, sf::Color outline_hoverColor = sf::Color::Transparent, short unsigned ID = 0);

   
    Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size, const std::string idle_texture, const std::string active_texture, const std::string hover_texture, short unsigned ID = 0);
    
    
   
    Button(float x, float y, float width, float height, const std::string idle_texture, const std::string active_texture, const std::string hover_texture, short unsigned ID = 0);
  
    virtual ~Button();
   
    
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i Mousepos);

    
    //Accessors
     const bool isPressed() const;
     const std::string& getText() const;
     const short unsigned& getID() const;
   
     
    //Modifiers
    void setText(const std::string text);
    void setID(const short unsigned ID);
    

};


class DropDownList
{
private:
    float keytime;
    float keytime_max;
    
    GUI::Button* active_element;
    std::vector<GUI::Button*> list;
    sf::Font& font;
    
    
public:

    DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned number_of_elements, unsigned default_index = 0);
    ~DropDownList();
    
    //Accessors
    const bool getkeytime();
    bool display_list;
    const unsigned short& getID() const;
    
    //Functions
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i& MouseposWindow, const float& dt);
    void updateketime(const float& dt);
    
};

class TextureSelector
{
private:
    bool active;
    bool hidden;
    bool multi_select; 
    float gridsize;
    float keytime;
    const float keytimeMax;
    
    sf::RectangleShape bounds;
    sf::RectangleShape selector;
    sf::RectangleShape sidebar;
    sf::Sprite sheet;
    
    sf::Vector2u MousePosGrid;
    sf::IntRect texturerect;
    
    Button* hide;
  
  
    
public:
    //constructor and destructor
    TextureSelector(float x, float y, float width, float height, float gridsize, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
    ~TextureSelector();
    
    //Accessors
    const bool& getActive() const;
    const bool& getMulitSelect() const; 
    const sf::IntRect& getTextureRect() const;
    const bool getkeytime();
    
    
    
    //Functions
    void update(const sf::Vector2i& MousePosWindow, const float& dt);
    void updatekeytime(const float& dt);
    void render(sf::RenderTarget &target);
    
};

class CheckBox
{
    
private:
    short unsigned BoxState;
    sf::Texture idle_box;
    sf::Texture hover_box; 
    sf::Texture active_box;
    sf::RectangleShape box;
    bool checked;
    bool hovering;
    
public:
    
    CheckBox(float x, float y);
    ~CheckBox();
    
    
      void update(const sf::Vector2i Mousepos);
      const bool isPressed() const;
      void render(sf::RenderTarget& target);
    
};

}


#endif /* GUI_hpp */
