//
//  GUI.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/5/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//
#include "GUI.hpp"

/* BEGIN BUTTON */

GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size, sf::Color idlecolor, sf::Color hovercolor, sf::Color activecolor, sf::Color text_idlecolor, sf::Color text_hovercolor, sf::Color text_activecolor, sf::Color outline_activeColor, sf::Color outline_idleColor, sf::Color outline_hoverColor, short unsigned ID)
{
    /*!
     
     @brief Default Constructor for a GUI button element
        
     @param float X
     @param float Y
     @param float width
     @param float height
     @param sf::Font *font
     @param std::string text
     @param unsigned character_size
     @param sf::Color idlecolor
     @param sf::Color hovercolor
     @param sf::Color activecolor
     @param sf::Color text_idlecolor
     @param sf::Color text_hovercolor
     @param sf::Color text_activecolor
     @param sf::Color outline_activecolor
     @param sf::Color outline_idlecolor
     @param sf::Color outline_hoverColor
     @param short  unsigned ID
     
     */
    this->ID = ID;
    
    this->rectangle.setSize(sf::Vector2f(x,y));
    this->rectangle.setPosition(width, height);
    
    this->ButtonState = IDLE_BUTTON;
    
    
    //Configure the text, and font used on the Button interface
    this-> font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idlecolor);
    this->text.setCharacterSize(character_size);
    
    //Configure the Position of the Text on the Button to *roughly* match
    //the center the top left corner is at the center of the button rectangle
    //(Side note) I failed highschool geom. I have no fucking idea why this works, but it does
    
    this->text.setPosition(this->rectangle.getPosition().x + this->rectangle.getPosition().x/ 2.f + 20.f - this->rectangle.getPosition().x / 2.f, this->rectangle.getPosition().y + this->rectangle.getSize().y / 2.f - 20.f);
    
    //Button rect colors
    this->idleColor = idlecolor;
    this->hoverColor = hovercolor;
    this->activeColor = activecolor;
    
    //Button Text colors
    this->text_idlecolor = text_idlecolor;
    this->text_hovercolor = text_hovercolor;
    this->text_activecolor = text_activecolor;
    
    //Button Outline colors
    this->outline_idleColor = outline_idleColor;
    this->outline_hoverColor = outline_hoverColor;
    this->outline_activeColor = outline_activeColor;
    
    
    this->rectangle.setFillColor(this->idleColor);
    this->rectangle.setOutlineColor(outline_idleColor);
    this->rectangle.setOutlineThickness(1.f);

}


GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned int character_size, const std::string idle_texture, const std::string active_texture, const std::string hover_texture, short unsigned ID)
{
    
    this->ID = ID;
       
       this->rectangle.setSize(sf::Vector2f(x,y));
       this->rectangle.setPosition(width, height);
       
       this->ButtonState = IDLE_BUTTON;
       
    this-> font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idlecolor);
    this->text.setCharacterSize(character_size);
    
     this->text.setPosition(this->rectangle.getPosition().x + this->rectangle.getPosition().x/ 2.f + 20.f - this->rectangle.getPosition().x / 2.f, this->rectangle.getPosition().y + this->rectangle.getSize().y / 2.f - 20.f);
    
    try
    {
        if(!this->idle.loadFromFile(resourcePath() + idle_texture))
        {
            throw std::invalid_argument("FATAL ERROR EX_C 21 || GUI::Button Constructor || Unable to find idle texture file");
        }
        if(!this->clicked.loadFromFile(resourcePath() + active_texture))
        {
            throw std::invalid_argument("FATAL ERROR EX_C 22 || GUI::Button Constructor || Unable to find active texture file");
        }
        if(!this->hover_texture.loadFromFile(resourcePath() + hover_texture))
        {
            throw std::invalid_argument("FATAL ERROR EX_C 23 || GUI::Button Constructor || Unable to find hover texture file");
        }
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.exception::what() << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "GUI::BUTTON(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned int" << std::endl << "character_size, const std::string idle_texture, const std::string active_texture, const std::string" << std::endl << "hover_texture, short unsigned ID)" << std::endl;
    }
    
    this->rectangle.setTexture(&idle);
    
    
}

GUI::Button::Button(float x, float y, float width, float height, const std::string idle_texture, const std::string active_texture, const std::string hover_texture, short unsigned ID)
{
    
    /*!
    
    @brief Simplified Constructor for the GUI Button Element.
     
    @discussion Unlike the full constructor, this version initalizes the button rectangle with a texture rather than with a color and also does not include the option to have text.
     Useful for GUI elements that require a texture
       
    @param float X
    @param float Y
    @param float width
    @param float height
  
    @param const_std::string Idle_texture
      @param const_std::string active_texture
      @param const_std::string hover_texture
     
    
    @param short  unsigned ID
    
    */
    
    try
    {
    
        if(!this->idle.loadFromFile(resourcePath() + idle_texture))
        {
            throw std::invalid_argument("FATAL ERROR EX_C 24 || GUI::BUTTON CONSTRUCTOR || Unable to find idle texture");
        }
        
        if(!this->clicked.loadFromFile(resourcePath() + active_texture))
        {
            
            throw std::invalid_argument("FATAL ERROR EX_C 25 || GUI::Button CONSTRUCTOR || Unable to find active texture");
        }
        if(!this->hover_texture.loadFromFile(resourcePath() + hover_texture))
        {
            throw std::invalid_argument("FATAL ERROR EX_C 26 || GUI::Button CONSTRUCTOR || Unable to find hover texture");
        }
           
        this->rectangle.setTexture(&idle);
    
    }
    catch (std::invalid_argument& e)
    {
        
        std::cout << e.what();
    }
    
    this->ID = ID;
          
    this->rectangle.setSize(sf::Vector2f(width, height));
    
          this->rectangle.setPosition(x,y);
          
          this->ButtonState = IDLE_BUTTON;
        
    

     // this->rectangle.setTextureRect(static_cast<sf::IntRect>(this->rectangle.getGlobalBounds())); 
    
}


GUI::Button::~Button()
{
    

    
}

//Functions

void GUI::Button::update(const sf::Vector2i Mousepos) {
    
    this->ButtonState = IDLE_BUTTON; 

    if (this->rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mousepos)))
    {

        this->ButtonState = HOVER;
      
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
          this->ButtonState = PRESSED;
       
        }
    }
        
    switch (this->ButtonState) {

            
        case IDLE_BUTTON: //the Button is not being interacted with by the user
            
            this->rectangle.setTexture(&idle);
            
            //if the button is not given a texture with one of the overload constructors, give it a fill color
            
            if(this->rectangle.getTexture() == NULL)
            {
                this->rectangle.setFillColor(this->idleColor);
                this->text.setFillColor(this->text_idlecolor);
                this->rectangle.setOutlineColor(this->outline_idleColor);
            }
            
            break;
            
        case HOVER: // the user's cursor is hovering over the button
            
            this->rectangle.setTexture(&hover_texture);
            
            if (this->rectangle.getTexture() == NULL)
            {
                this->rectangle.setFillColor(this->hoverColor);
                this->text.setFillColor(this->text_hovercolor);
                this->rectangle.setOutlineColor(this->outline_hoverColor);
            }
            
            break;
            
        case PRESSED: // the button has been interacted with
           
            this->rectangle.setTexture(&clicked);
             
            if (this->rectangle.getTexture() == NULL)
            {
                this->rectangle.setFillColor(this->activeColor);
                this->text.setFillColor(this->text_activecolor);
                this->rectangle.setOutlineColor(this->outline_activeColor);
            }
            
            break;
            
        default:
            //will appear if something is wrong with the initalizaiton of the button texture.
            this->rectangle.setFillColor(sf::Color::Red);
            this->text.setFillColor(sf::Color::Green);
            this->rectangle.setOutlineColor(sf::Color::Blue);
          std::cout << "ERROR CODE BUTTON:210 || GUI::BUTTON::UPDATE || UNABLE TO LOAD BUTTON FROM TEXTURE FILE CHECK BUTTON CONSTRUCTOR" << std::endl;
            break;
    }

}

    

void GUI::Button::render(sf::RenderTarget& target) {

    target.draw(this->rectangle);
    target.draw(this->text);
    
}

//Accessors
// return the bolean for wether or not the user has pressed the button
const bool GUI::Button::isPressed() const {
    
    if (this->ButtonState == PRESSED)
        return true;
    
    
    
   return false;
}

//Debug, fix "returning refrence to local temp. object" warning later

const std::string GUI::Button::getText() const
{
    return this->text.getString();
}

void GUI::Button::setText(const std::string text)
{
    
    this->text.setString(text);
    
    
}

const unsigned short &GUI::Button::getID() const
{
    return this->ID;
}


void GUI::Button::setID(const unsigned short ID)
{
    this->ID = ID;
}







/*END BUTTON*/




/*BEGIN DROPDOWNLIST*/


GUI::DropDownList::DropDownList(float x, float y,float width, float height, sf::Font& font, std::string list[], unsigned number_of_elements, unsigned default_index): font(font), display_list(false), keytime_max(10.f), keytime(2.f)
{
    //number_of_elements = sizeof(list) / sizeof(std::string);
    
  
    this->active_element = new GUI::Button(
    x, y, width, height,
    &this->font, list[default_index], 14, sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
    sf::Color(20, 20, 20, 200), sf::Color(20, 20, 20, 200), sf::Color(20, 20, 20, 200),
    sf::Color::Black, sf::Color::Black, sf::Color::Black);
   
        
    for(unsigned i=0; i < number_of_elements; i++)
    {
        this->list.push_back(new GUI::Button(x, y + ((i+1) * height), width, height, &this->font, list[i], 14, sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
        sf::Color(20, 20, 20, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
        sf::Color::Black, sf::Color::Black, sf::Color::Black,
      i));
        
        
    }
    
  
    
    
}



GUI::DropDownList::~DropDownList()
{
    delete this->active_element;
    
    for (auto *&i : this->list)
    {
        delete i;
    }
    
    
}

void GUI::DropDownList::update(const sf::Vector2i & mousePosWindow, const float& dt)
{
    /*!
     @brief Hide or render the Drop Down element based on wether or not the active element is pressed.
            
     @param const sf::Vector2i& mousePosWindow    The Mouse's position in the window
     
        
     @param const float& Delta Time
     
    @return void
     */
    this->updateketime(dt);

    this->active_element->update(mousePosWindow);

        //Show and hide the list
    if (this->active_element->isPressed() && this->getkeytime())
        {
            if (this->display_list)
                this->display_list = false;
            else
                this->display_list = true;
        }

        if (this->display_list)
        {
            for (auto &i : this->list)
            {
                i->update(mousePosWindow);

                if (i->isPressed() && this->getkeytime())
                {
                    this->display_list = false;
                    this->active_element->setText(i->getText());
                    this->active_element->setID(i->getID());
                }
            }
        }
    }

void GUI::DropDownList::render(sf::RenderTarget& target)
{
    this->active_element->render(target);
    
    if(this->display_list)
        {
           
         for( auto &i : this->list)
          {
             i->render(target);
          }
       
       }
       
    
}


//Accessors

const bool GUI::DropDownList::getkeytime()
{
    if (this->keytime >= this->keytime_max)
    {
        this->keytime = 0.f;
        return true;
    }

    return false;
}

const unsigned short &GUI::DropDownList::getID() const
{
    return this->active_element->getID();
}


void GUI::DropDownList::updateketime(const float& dt)
{
    if (this->keytime < this->keytime_max)
    this->keytime += 10.f * dt;
    
    
    
}

/*END DROPDOWN LIST*/




/* BEGIN TEXTURE SELECTOR*/


GUI::TextureSelector::TextureSelector(float x, float y,float width, float height, float gridsize, const sf::Texture* texture_sheet, sf::Font& font, std::string text) : keytimeMax(2.f), keytime(0.f)
{
    /*!
                @brief Construct's the Texture Selector Element
                @param float x          X position
                @param float y          Y position
                @param float width
                @param float height
                @param float gridsize
                @param const sf::Texture Texture_sheet
                @param sf::Font& font
                @param std::string text
                @return void 
                        
     */
    float offset = gridsize;
    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(x + offset, y);
    this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));
    
    this->sheet.setTexture(*texture_sheet);
    this->sheet.setPosition(x + offset, y);
    
    if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
    {
        this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
    }
    if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
    {
        this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
    }
    
    //Configure the texture selector element
    this->selector.setPosition(x + offset, y);
    this->selector.setSize(sf::Vector2f(17.f, 17.f));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineColor(sf::Color::Green);
    this->selector.setOutlineThickness(1.f);
    
    this->active = false;
    this->gridsize = gridsize;
    
    this->texturerect.width = 17;
    this->texturerect.height = 17;
    this->hidden = false;
    
    this->hide = new GUI::Button(38, 36, x - 10, y - 5, "red_boxCross.png", "grey_box.png", "red_boxTick.png");
   
    
}

//Functions

GUI::TextureSelector::~TextureSelector()
{
    delete this->hide;
}

void GUI::TextureSelector::update(const sf::Vector2i& MousePosWindow, const float& dt)
{
    this->updatekeytime(dt);
    this->hide->update((MousePosWindow));
    
    
    
    if(this->hide->isPressed() && this->getkeytime())
    {
        if(this->hidden == true)
            this->hidden = false;
        
        else
            this->hidden = true;
    }
    
    

    //Update the Selector, if the Texture Selector element is not hidden
    
    if(!this->hidden)
    {
        if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(MousePosWindow)))
          
              this->active = true;
          else
              this->active = false;
          
          if(this->active)
          {
              this->MousePosGrid.x = (MousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(17);
              this->MousePosGrid.y = (MousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(17);
              
              this->selector.setPosition(this->bounds.getPosition().x + this->MousePosGrid.x * 17,
                                         this->bounds.getPosition().y + this->MousePosGrid.y * 17);
              
              //Update the Texture Rectangle
              
              this->texturerect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
              this->texturerect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
              
              
          }
          
    }
    
}

void GUI::TextureSelector::updatekeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
    {
        this->keytime += 10.f * dt;
    }
    
}

void GUI::TextureSelector::render(sf::RenderTarget &target)
{
    if(!this->hidden)
    {
        target.draw(this->bounds);
        target.draw(this->sheet);
        
        if(this->active)
           target.draw(this->selector);
    }
     this->hide->render(target);
   
}


const bool &GUI::TextureSelector::getActive() const
{
    return this->active;
}

const sf::IntRect &GUI::TextureSelector::getTextureRect() const
{
    return this->texturerect;
}

const bool GUI::TextureSelector::getkeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }

    return false;
}


const bool& GUI::TextureSelector::getMulitSelect() const
{
    return this->multi_select;
}

/*END TEXTURE SELECTOR*/




/*BEGIN CHECKBOX*/

GUI::CheckBox::CheckBox(float x, float y)
{
    //HARD CODED CHECK BOX TEXTURES
    this->idle_box.loadFromFile(resourcePath() + "grey_box.png");
    this->active_box.loadFromFile(resourcePath() + "red_boxCheckmark.png");
    
    this->box.setSize(sf::Vector2f(static_cast<float>(this->idle_box.getSize().x), static_cast<float>(this->idle_box.getSize().y)));
    
}

GUI::CheckBox::~CheckBox()
{
    
}

void GUI::CheckBox::update(const sf::Vector2i Mousepos)
{
    
    
    this->BoxState = IDLE_BOX;
        
        if (this->box.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mousepos)))
        {

            this->BoxState = HOVER_BOX;
          
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
              this->BoxState = PRESSED_BOX;
           
            }
           
        }
            
        switch (this->BoxState) {

                
            case IDLE_BUTTON: //the Box is not being interacted with by the user
                
                this->box.setTexture(&idle_box);
                break;
                
            case HOVER: // the user's cursor is hovering over the box
                
                this->box.setTexture(&hover_box);
                break;
                
            case PRESSED: // the button has been interacted with
               
                this->box.setTexture(&active_box);
                break;
                
            default:
                //will appear if something is wrong with the initalizaiton of the checkbox texture.
                this->box.setFillColor(sf::Color::Red);
                this->box.setFillColor(sf::Color::Green);
                this->box.setOutlineColor(sf::Color::Blue);
                std::cout << "ERROR_CODE GUI:630 || CHECKBOX::UPDATE || UNABLE TO LOAD CHECKBOX FROM TEXTURE FILE CHECK CONSTRUCTOR" << std::endl;
                break;
        }

}
    


const bool GUI::CheckBox::isPressed() const
{
    if(this->BoxState == PRESSED_BOX)
        return true;
    
    

    return false;
    
}

void GUI::CheckBox::render(sf::RenderTarget &target) { 
    
}
/*END CHECKBOX */

/*BEGIN MISC*/
const unsigned GUI::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
    /*
    * Calculates the optimal size for text elements based on the current resolution
    *
    * @param   sf::VideoMode& vm   the current resolution stored as a SFML videoMode.
    *
    * @param   const unsigned modifier      a modifer to custimize the size of the text relative to the resolution.
    *
    * @return  unsigned            The calculated ideal text size.
    */
    
    return static_cast<unsigned>((vm.width + vm.height) / modifier);
    
}


const float GUI::pixelpercentX(const float percent, const sf::VideoMode& vm)
{
 
    return std::floor(static_cast<float>(vm.width) * (percent / 100.f));
}

const float GUI::pixelpercentY(const float percent, const sf::VideoMode& vm)
{
    
    
     return std::floor(static_cast<float>(vm.height) * (percent / 100.f));
}


GUI::ProgressBar::ProgressBar(float x, float y, float width, float height, int MaxValue, sf::VideoMode& vm, sf::Color inner_color, unsigned charSize, sf::Font* font)
{
    float widthh = GUI::pixelpercentX(width, vm);
    float heightt = GUI::pixelpercentY(height, vm);
    float xx = GUI::pixelpercentX(x, vm);
    float yy = GUI::pixelpercentY(y, vm);
    
    
    this->MaxVal = MaxValue;
    this->Max_width = width;
    
    this->Exterior.setSize(sf::Vector2f(widthh, heightt));
    this->Exterior.setFillColor(sf::Color(50,50,50,200));
    this->Exterior.setPosition(xx,yy);
    
    this->Interior.setSize(sf::Vector2f(widthh, heightt));
    this->Interior.setFillColor(inner_color);
    this->Interior.setPosition(this->Exterior.getPosition());

    if(font)
    {
        this->text.setFont(*font);
    
    this->text.setCharacterSize(GUI::calcCharSize(vm, charSize));
        this->text.setPosition(this->Interior.getPosition().x + GUI::pixelpercentX(1.4, vm), this->Interior.getPosition().y + GUI::pixelpercentY(2, vm));
    }
}


GUI::ProgressBar::~ProgressBar()
{
    
    
    
    
}



void GUI::ProgressBar::update(const int current_value)
{
    float percent = static_cast<float>(current_value) /
                    static_cast<float>(MaxVal);
    
    
    this->Interior.setSize(sf::Vector2f(static_cast<float>(std::floor(this->Max_width * percent)), this->Interior.getSize().y));
    
    this->hpbarText = std::to_string(current_value) + "/" +
                     std::to_string(MaxVal);
    this->text.setString(hpbarText);
}


void GUI::ProgressBar::render(sf::RenderTarget& target)
{
    target.draw(this->Exterior);
    target.draw(this->Interior);
    target.draw(this->text);

}


const float GUI::ProgressBar::getWidth()
{
    return this->Max_width;
}

const sf::Vector2f GUI::ProgressBar::getSize()
{
    return this->Interior.getSize(); 
}

/* END PROGRESSBAR */


/*BEGIN ICON*/
 

GUI::Icon::Icon(float x, float y, const std::string icon_texture)
{
    
    this->icontexture.loadFromFile(resourcePath() + icon_texture);
    this->Box.setTexture(&icontexture);
    this->Box.setSize(sf::Vector2f(64, 64));
    this->Box.setPosition(x, y);

}


GUI::Icon::~Icon()
{
    
    
    
    
}


void GUI::Icon::render(sf::RenderTarget& target)
{
    
    target.draw(this->Box);
    
}
