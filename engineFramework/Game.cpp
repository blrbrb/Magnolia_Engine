//
//  Game.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
// 

#include "Game.hpp"
#include "GameState.hpp"


Game::Game() {
    
   
    this->initVariables();
    this->initGraphicsSettings();
    this->initwindow();
    this->initkeys();
    this->initstatedata();
    this->initstates();
    
    }


Game::~Game() {
    
    delete this -> window;
    
    
    while (!this->states.empty()) {
       delete this->states.top();
        this->states.pop(); }
}

//initalizer functions

void Game::initkeys() {
    
/*!
 @brief  Load the supported input methods (keys,buttons, controllers etc) from the ini file and store them as shared class variables

 @param  void

 @return void

  */
   std::ifstream ifs(resourcePath() + "Supported_Keys.ini");

   if (ifs.is_open())
   {
       std::string key = "";
       int key_value = 0; 
       
       while (ifs >> key >> key_value)
       {
           this->supportedkeys[key] = key_value;
       }
   }

   ifs.close();
    
    for (auto i : this->supportedkeys)
    {
        //std::cout << i.first << " " << i.second << "\n";
    }
}

void Game::initstates() {
    
    this->states.push(new MainMenuState(&this->state_data));
    
}


void Game::initGraphicsSettings() {
    
    this->gfxsettings.loadfromfile(resourcePath() + "Window.ini");
    

    
    
}

void Game::initwindow() {

/*!
 @brief  Initalizes the media layer the application runs on

 @param   void

 @return  void

*/
    
    
    sf::Image icon;
    if(!icon.loadFromFile(resourcePath() + "Blrb.png"))
    {
        
        std::cout << "ERROR CODE GAME::101 || INITWINDOW || UNABLE_TO_LOAD_ICON" << std::endl;
    }
   
    
    if(this->gfxsettings.fullscreen)
        this->window = new sf::RenderWindow(this->gfxsettings.resolution, this->gfxsettings.title, sf::Style::Fullscreen, this->gfxsettings.windowSettings);
    else
        this->window = new sf::RenderWindow(this->gfxsettings.resolution, this->gfxsettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxsettings.windowSettings);
        
        
        
    this->window->setFramerateLimit(this->gfxsettings.framerate_limit);
    this->window->setVerticalSyncEnabled(this->gfxsettings.vsync);
    
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
}

void Game::initstatedata()
{
    this->state_data.window = this->window;
    this->state_data.gfxsettings = &this->gfxsettings;
    this->state_data.supportedkeys = &this->supportedkeys;
    this->state_data.states = &this->states;
    this->state_data.gridsize = this->gridsize;

}





void Game::resizewindow()
{

    
}



void Game::load()
{
    
       
}



void Game::Update()
{
    this->UpdateEvents();
    
    
    if (!this->states.empty())
        {
            if (this->window->hasFocus())
            {
                this->states.top()->update(this->dt);

                if (this->states.top()->getquit())
                {
                    this->states.top()->endstate();
                    delete this->states.top();
                    this->states.pop();
                }
            }
        }
        //Application end
        else
        {
            this->endapplication();
            this->window->close();
        }
    }



void Game::UpdateEvents() {
    
    while (this->window->pollEvent(this->event))
    {
        
        if (this->event.type == sf::Event::Closed) {
            
            this->window->close();
            
        }
    
    }
}

void Game::render() {
    
    
    if (!this->states.empty())
        this->window->clear();
        this->states.top()->render(this->window);
        this->window->display();
    
    
        }
        
void Game::UpdateDT()
{
    
    //Updates the time variable with the time taken for each frame to render
    this-> dt = this -> dtClock.restart().asSeconds();
    std::cout << this->dt  << std::endl;

    
}


void Game::running() {
    
    while (this->window->isOpen()) {
        
      
    
        this->UpdateDT();
            this->Update();
          this->render();
    }
    
} //main loop

void Game::endapplication()
{
    std::cout << "Ending the application..." << std::endl;
}


void Game::initVariables()
{
    this->window = NULL;
    this-> dt = 0.f;
    this->gridsize = 17.f;
    
}






