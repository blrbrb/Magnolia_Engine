//
//  SettingsState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/5/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#include "SettingsState.hpp"


//Private Functions


void SettingsState::initvariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
    
    
}


void SettingsState::initkeybinds() {
  
    std::ifstream ifs("Config/SettingsState_Keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedkeys->at(key2);
        }
    }

    ifs.close();
    
 }

void SettingsState::initGUI() {
    
    sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
    
    
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
    
    if (!this->backgroundTexture.loadFromFile(resourcePath() + "EngineLogo.png"))
    {
        std::cout << "ERROR CODE 04: SettingsState::INITBACKGROUND unable to load background" << std::endl;
        throw std::runtime_error("ERROR CODE 04: SettingsState::INITBACKGROUND unable to load background");
    }
    
    this->background.setTexture(&this->backgroundTexture);
    
    
    
    this->buttons["EXIT"] = new GUI::Button(GUI::pixelpercentX(27.1, vm), GUI::pixelpercentY(9, vm), GUI::pixelpercentX(7.1, vm), GUI::pixelpercentY(44, vm), &this->font, "Exit", GUI::calcCharSize(vm), "red_button01.png", "red_button02.png", "red_button00.png");
    
    this->buttons["APPLY"] = new GUI::Button(GUI::pixelpercentX(10, vm), GUI::pixelpercentY(10, vm), GUI::pixelpercentX(7.1, vm), GUI::pixelpercentY(60.5, vm), "grey_box.png", "red_boxCheckmark.png", "grey_box.png");

    std::vector<std::string> modes_str;
    
    for (auto &i : this->modes)
    {
        modes_str.push_back(static_cast<std::string>(std::to_string(i.width) + 'x' + std::to_string(i.height)));
    
        
    }
    
    //std::string list[] = {"1920x1080","720x1080","640x400","400x400"};
    
    this->dropdownlists["RESOLUTION"] = new GUI::DropDownList(GUI::pixelpercentX(75, vm), GUI::pixelpercentY(10, vm), GUI::pixelpercentX(25, vm), GUI::pixelpercentY(25, vm), font, modes_str.data(), 2, 3);
    
    this->option_text.setFont(font);
    
    //text
    this->option_text.setFont(this->font);
    this->option_text.setPosition(sf::Vector2f(GUI::pixelpercentX(7.1, vm), GUI::pixelpercentY(45, vm)));
    this->option_text.setCharacterSize(GUI::calcCharSize(vm, 70));
    this->option_text.setFillColor(sf::Color::White);
    
}

void SettingsState::resetGUI()
{
  /* Clears all of the GUI elements, and re-initalizes the GUI
   *
   *
   *
   *
   * @return void
   */
    
    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); it++)
    {
        delete it->second;
    }
    this->buttons.clear();
    
    auto it2 = this->dropdownlists.begin();
    for(it2 = this->dropdownlists.begin(); it2 != this->dropdownlists.end(); it2++)
    {
        delete it2->second;
    }
    this->dropdownlists.clear();
    

    this->initGUI();
}




void SettingsState::initFonts()
{
    
    
    if (!this->font.loadFromFile(resourcePath() + "PressStart2P.ttf"))
    {
        std::cout << "ERROR CODE 05: SettingsState::initFonts COULD NOT LOAD FONT FROM FILE" << std::endl;
        throw std::runtime_error("ERROR CODE 05: SettingsState::initFonts COULD NOT LOAD FONT FROM FILE");
        
    }

    
}


SettingsState::SettingsState(StateData* state_data) :  State(state_data)
{
    try
    {
        this->initvariables();
        this->initGUI();
        this->initFonts();
        this->initkeybinds();
    }
    
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        
    }
}

SettingsState::~SettingsState()
{
    auto it2 = dropdownlists.begin();
       for (it2 = dropdownlists.begin(); it2 != this->dropdownlists.end(); ++it2)
      
       {
           delete it2->second;
           
       }
}



//Functions 
void SettingsState::update(const float& dt) {
    
    this->updateInput(dt);
    this->updateMousePosition();
    this->updateGUI(dt);
    
}

void SettingsState::updateInput(const float& dt)
{

    
    
}

//Render Functions

void SettingsState::render(sf::RenderTarget* target) {
    
   if (!target)
       target = this->window;

   target->draw(this->background);

    this->renderGUI(*target);
 
    //sf::Text mouseText;
    //mouseText.setPosition(this->MousePosView.x, this->MousePosView.y - 50);
    //mouseText.setFont(this->font);
    //mouseText.setCharacterSize(12);
    //std::stringstream Position;
    //Position << this->MousePosView.x << " " << this->MousePosView.y;
    //mouseText.setString(Position.str());
    //target->draw(mouseText);
}




void SettingsState::renderGUI(sf::RenderTarget& target)
{
    
   for (auto &it : this->buttons)
   {
       it.second->render(target);
   }

    for (auto &it : this->dropdownlists)
   {
       it.second->render(target);
   }
   
}

void SettingsState::updateGUI(const float& dt) {
    
    //GUI element functionality
    
    //button functions
    for (auto &it2 : this-> buttons)
   
    {
        it2.second->update(this->MousePosWindow);
        
    }
    
    //return to main Menu
    if(this->buttons["EXIT"]->isPressed())
    {
        this->endstate();
        
    }
    
    //Apply Changes
    
    if(this->buttons["APPLY"]->isPressed())
    {
        this->state_data->gfxsettings->resolution = this->modes[this->dropdownlists["RESOLUTION"]->getID()];
        
        this->window->create(this->state_data->gfxsettings->resolution, this->state_data->gfxsettings->title,sf::Style::Default);
        
        this->resetGUI();
    }
    
    
    //Drop Down list functions
    
  for (auto &it2 : this-> dropdownlists)
   {
       it2.second->update(this->MousePosWindow, dt);
   }
   
    
}


