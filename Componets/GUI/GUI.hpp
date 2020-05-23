/**
///  GUI.hpp
///  engineFramework
///
@author Eli Reynolds on 2/5/20
@copyright © 2020 Eli Reynolds. 
*/

#ifndef GUI_hpp
#define GUI_hpp

#include "ResourcePath.hpp"

///The three possible states for GUI Button elements to be in
enum ButtonStates{IDLE_BUTTON = 0, ///< Button has not been interacted with
    HOVER, ///< User's Mouse is hovering over the Button
    PRESSED ///< The Button has been pressed };
};


///The three possible states for GUI Box elements to be in, similar to
/// @see ButtonStates
enum BoxStates{IDLE_BOX = 0, ///<The box has not been interacted with
    HOVER_BOX, ///< User's Mouse is hovering over the Button
    PRESSED_BOX
    
};
///Namespace containing all of the GUI objects
namespace GUI {



/// Convert a percantage value, to a percentage of the total width of the renderable window space
/// @param percent const float percentage value
/// @param vm A refrence to the sf::VideoMode
/// @returns A new calculated percent
const float pixelpercentX(const float percent, const sf::VideoMode& vm);
/// Convert a percantage value, to a percentage of the total height of the renderable window space
/// @param percent const float percentage value
/// @param vm A refrence to the sf::VideoMode
/// @returns A new calculated percent
   const float pixelpercentY(const float percent, const sf::VideoMode& vm);

/// Calculate a good character size for text based on the total size of the renderable window space
/// @param vm A refrence to the sf::VideoMode
///@returns const unsigned character size
   const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);


///A GUI element designed to handle user input visually, can be customized with text and color
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
    
    /// @brief Construct a GUI button element with user definable colors for fonts, active state, idle state, hover state
    /// @param x float  the X position of the Button
    /// @param y float the Y position of the Button
    /// @param width  the width of the Button
    /// @param height  the height of the Button
    /// @param font  the font for the Button's text
    /// @param text the text to be displayed on the Button
    /// @param character_size  the size of the Button's text
    /// @param idlecolor  the idle Button color
    /// @param hovercolor  the hover color of the Button
    /// @param activecolor  the active color of the Button
    /// @param text_idlecolor  the Button text's idle color
    /// @param text_hovercolor  the Button text's hover color
    /// @param text_activecolor  the Button text's active color
    /// @param Transparent default idle outline color
    /// @param Transparent default   active outline color
    /// @param Transparent default hover outline color
    Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size, sf::Color idlecolor, sf::Color hovercolor, sf::Color activecolor, sf::Color text_idlecolor, sf::Color text_hovercolor, sf::Color text_activecolor,sf::Color outline_activeColor = sf::Color::Transparent, sf::Color outline_idleColor = sf::Color::Transparent, sf::Color outline_hoverColor = sf::Color::Transparent, short unsigned ID = 0);

    
    /// @brief Construct a GUI Button element from a set ot textures
    /// @param x  the X position of the Button
    /// @param y  the Y positon of the Button
    /// @param width  the width of the Button
    /// @param height  the height of the Button
    /// @param font the font
    /// @param text the text for the Button to display
    /// @param character_size the size of the Button's text
    /// @param idle_texture the Button's idle texture
    /// @param active_texture the Button's active texture
    /// @param hover_texture the Button's hover texture
    ///@overload
    Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size, const std::string idle_texture, const std::string active_texture, const std::string hover_texture, short unsigned ID = 0);
    
    
    
    /// @brief Construct a GUI Button element from a set of textures, without any text
    /// @param x the X positon of the Button
    /// @param y the Y position of the Button
    /// @param width the width of the Button
    /// @param height the height of the Button
    /// @param idle_texture the Button's idle texture
    /// @param active_texture the Button's active texture
    /// @param hover_texture the Button's hover texture
    /// @overload
    Button(float x, float y, float width, float height, const std::string idle_texture, const std::string active_texture, const std::string hover_texture, short unsigned ID = 0);
  
    virtual ~Button();
   
    
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i Mousepos);

    
    //Accessors
    /// Retreive wether or not the user has pressed the button
     const bool isPressed() const;
    
    ///Retreive the text on the Button
     const std::string getText() const;
     const short unsigned& getID() const;
   
     
    //Modifiers
    ///Change, or set the Button's text
    void setText(const std::string text);
    ///Change, or set the Button's unique ID
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
    
    /// @brief Construct a GUI Drop Down List element
    ///  @discussion Use a GUI Drop Down List element for user interactions that require a list of options. e.g, a list a resolutions
    ///     in a graphics settings menu, a list of possible dialouge options.
    /// @param x the X position of the Drop Down List
    /// @param y the Y position of the Drop Down List
    /// @param width the width of the Drop Down List
    /// @param height the height of the Drop Down List
    /// @param font the font for the Drop Down Lists's text
    /// @param list the elements to display
    /// @param number_of_elements number of elements to display 
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
    float height;
    float width;
    const float keytimeMax;
    
    sf::RectangleShape bounds;
    sf::RectangleShape selector;
    sf::RectangleShape sidebar;
    sf::Sprite sheet;
    
    sf::Vector2u MousePosGrid;
    sf::IntRect texturerect;
    
    Button* hide;
  
  
    
public:
    
    /// @brief Generate a GUI Texture Selector element
    /// @discussion In general, this is a GUI element designed almost entierly for the editor mode. Allowing the user to select from a png containing many different possible tile types and textures
    /// @param x the X position of the Texture Selector
    /// @param y the Y position of the Texture Selector
    /// @param width the width of the Texture Selector
    /// @param height the height of the Texture Selector
    /// @param gridsize the gridsize
    /// @param texture_sheet the texture sheet for the Texture Selector element to source tile textures from
    /// @param font the font for the Texture Selector to use
    /// @param text a string of text for the Texture Selector
    TextureSelector(float x, float y, float width, float height, float gridsize, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
    
    ~TextureSelector();
    
    //Accessors
    ///Return wether or not the user's mouse is hovering over the Texture selector element
    const bool& getActive() const;
    const bool& getMulitSelect() const;
    ////Return an sf::IntRect refrence to the texture rectangle the user has selected
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
    
    /// @brief Generate a simple GUI Checkbox element
    ///  @discussion use in lists where the user must "check off" options
    /// @param x the X position of the Checkbox on screen
    /// @param y the Y position of the Checkbox on screen
    CheckBox(float x, float y);
    ~CheckBox();
    
    
      void update(const sf::Vector2i Mousepos);
      const bool isPressed() const;
      void render(sf::RenderTarget& target);
    
};

class ProgressBar
{
    
private:
    
    std::string hpbarText;
    sf::Text text;
    float Max_width;
    sf::RectangleShape Interior;
    sf::RectangleShape Exterior;
    int MaxVal; 
    
public:
    /// @brief Construct a GUI ProgressBar element
    /// @discussion Can be used to visuallly display progress percentages in a variety of applications. e.g, a Player's health, loading progress, percentages
    /// @param x the X position of the ProgressBar on screen
    /// @param y the Y position of the ProgressBar on screen
    /// @param width the width of the ProgressBar
    /// @param height the height of the ProgressBar
    /// @param MaxValue the Maximum percentage value for the ProgressBar to display, e.g (blank out of blank)
    /// @param vm the sf::VideoMode
    /// @param inner_color sf::Color, the inner color of the ProgressBar
    /// @param charsize the character size for text above the ProgressBar
    ProgressBar(float x, float y, float width, float height, int MaxValue, sf::VideoMode& vm, sf::Color inner_color, unsigned charsize, sf::Font* font = nullptr);
    
    
    ~ProgressBar();
    
    void update(const int current_value);
    void render(sf::RenderTarget& target);
  
    //Accessors
    const float getWidth();
    ///Return a sf::Vector2f to the size of the ProgressBar
    const sf::Vector2f getSize(); 
};

class Icon
{
public:
    
    /// @brief Construct a simple GUI Icon element
    /// @discussion The Icon element is the simplest form of a Graphical Interface element. This particular Icon is non-clickable, and mainly intended to decorate other GUI elements.
    /// @param x the X position of the Icon element on screen
    /// @param y the Y position of the Icon on screen
    /// @param icon_texture std::string to a texture file to source the icon from
    Icon(float x, float y, const std::string icon_texture);
    virtual ~Icon();
    
    void render(sf::RenderTarget& target);
    
private:
    
    sf::RectangleShape Box;
    sf::Texture icontexture;
    
    
};


}


#endif /* GUI_hpp */
