//
//  EditorState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/1/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "EditorState.hpp"

EditorState::EditorState(StateData* state_data)
: State(state_data)
{
    
    this->initvariables();
    this->initview();
    this->initkeybinds();
    this->initFonts();
    this->inittext();
    this->initbackground();
    this->inittilemap();
    this->initpausemenu();
    
    this->initGUI();

}

EditorState::~EditorState() {
    

     auto it = buttons.begin();
     for (it = buttons.begin(); it != this->buttons.end(); ++it)
    
     {
         delete it->second;
      }
    delete this->pMenu;
     
    delete this->Tilemap;
    
    delete this->texture_selector;
    
    
}

//initalization functions
void EditorState::initvariables()
{
    this->TextureRect = sf::IntRect(0, 0, 17, 17);
    this->collision = false;
    this->type = TileTypes::DEFAULT;
    this->cameraspeed = 200.f;
    this->layer = 0;
    
}


//initalizer functions


void EditorState::inittilemap()
{
    this->Tilemap = new TileMap(this->gridsize, 100, 100, "TileMap.png");

}

void EditorState::initview()
{
    this->mainview.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width), static_cast<float>(this->state_data->gfxsettings->resolution.height)));
    
    
    this->mainview.setCenter(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 2.f,
                             static_cast<float>(this->state_data->gfxsettings->resolution.height) / 2.f);
}


void EditorState::initpausemenu()
{
    
     const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
    
    this->pMenu = new PauseMenu(this->state_data->gfxsettings->resolution, this->font);
    
    this->pMenu->addbutton("Editor_Pause_Quit_Button", GUI::calcCharSize(vm), "Quit", GUI::pixelpercentX(12.f, vm), GUI::pixelpercentY(6.f, vm), 150.f);
    this->pMenu->addbutton("Editor_Pause_Save_Button", GUI::calcCharSize(vm), "Save", GUI::pixelpercentX(12.f, vm), GUI::pixelpercentY(6.f, vm), 400.f);
    this->pMenu->addbutton("Editor_Pause_Load_Button", GUI::calcCharSize(vm), "Load", GUI::pixelpercentX(12.f, vm), GUI::pixelpercentY(6.f, vm), 650.f);
   
}

void EditorState::updatepausemenubuttons()
{
    
    //Quit: Back to Main
    if(this->pMenu->isButtonPressed("Editor_Pause_Quit_Button"))
    {
            this->endstate();
    }

    
    //Save the TileMap
    if(this->pMenu->isButtonPressed("Editor_Pause_Save_Button"))
    {
     
        this->Tilemap->savetofile("Config/text.slmp");

    }
    
    //Load the TileMap
    if(this->pMenu->isButtonPressed("Editor_Pause_Load_Button"))
    {
       
        this->Tilemap->loadfromfile("Config/text.slmp");

    }


    
}

void EditorState::initkeybinds()
{
  
    std::ifstream ifs("Config/EditorState_Keys.ini");

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

void EditorState::initsidebar()
{
    //config the sidebar
    this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->state_data->gfxsettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50,50,50, 100));
    this->sidebar.setOutlineColor(sf::Color(200,200,200,150));
    this->sidebar.setOutlineThickness(1.f);
  
}

void EditorState::initGUI()
{
     
    this->initsidebar();
    
    //config the selection rectangle
    this->select_Rect.setSize(sf::Vector2f(this->state_data->gridsize, this->state_data->gridsize));
     this->select_Rect.setTexture(this->Tilemap->getTileSheet());
    
    
    //this->select_Rect.setFillColor(sf::Color::Transparent);
    //this->select_Rect.setOutlineColor(sf::Color::Green);
    //this->select_Rect.setOutlineThickness(2);
    
    //Config the TextureSelector from GUI.hpp
    this->texture_selector = new GUI::TextureSelector(20.f, 20.f, 543.f, 560.f, this->state_data->gridsize, this->Tilemap->getTileSheet(), this->font, "X");
    
   
    
    this->buffer.loadFromFile(resourcePath() + "Beep.wav");
    this->UI_invalid.setBuffer(buffer);

}


/* Initalizer Functions */

void EditorState::inittext()
{
    sf::VideoMode vm = this->state_data->gfxsettings->resolution;
    
    
       this->cursortext.setFont(this->font);
       this->cursortext.setFillColor(sf::Color::White);
       this->cursortext.setCharacterSize(GUI::calcCharSize(vm, 100));
       this->cursortext.setOutlineThickness(1.f);
       this->cursortext.setPosition(GUI::pixelpercentX(73.4, vm), GUI::pixelpercentX(3, vm));
    
        
    
       this->text_container.setSize(sf::Vector2f(400.f, 200.f));
       this->text_container.setFillColor(sf::Color(50,50,50,100));
       this->text_container.setPosition(GUI::pixelpercentX(71.4, vm), GUI::pixelpercentY(0, vm));
       this->text_container.setOutlineThickness(1.f);
       this->text_container.setOutlineColor(sf::Color(200, 200, 200, 150));
}





void EditorState::initFonts() {
    
    if (!this->font.loadFromFile(resourcePath() + "PressStart2P.ttf"))
    {
        std::cout <<  "ERROR CODE 01: EditorState::initFonts COULD NOT LOAD FONT FROM FILE" << std::endl;
        throw std::runtime_error("ERROR CODE 01: EditorState::initFonts COULD NOT LOAD FONT FROM FILE");
        
    }
    
}


void EditorState::initbackground()
{

    
    
    
}

/*Update Functions*/

void EditorState::update(const float& dt) {
    
    this->updateMousePosition(&this->mainview);
    this->updatekeytime(dt);
    this->updateInput(dt);
    
   
    if (!this->paused) //Unpaused
    {
        
        this->updatebuttons();
        this->updateGUI(dt);
        this->updateEditorinput(dt);
        
    }
    else //Paused
    {
        this->pMenu->update(this->MousePosWindow);
        this->updatepausemenubuttons();
       
    }
    
}


void EditorState::updateInput(const float& dt) {
    
    //Scroll the World Builder View 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
    {
        this->mainview.move(this->cameraspeed * dt, 0.f);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
    {
        this->mainview.move(-this->cameraspeed * dt, 0.f);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
    {
        this->mainview.move(0.f, -this->cameraspeed * dt);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
    {
        this->mainview.move(0.f, this->cameraspeed * dt);
    }
    
    
    
    //Zoom the World Builder View in or out
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
    {
        this->mainview.zoom(1.01);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
    {
        this->mainview.zoom(0.8);
    }
   

    //Pause
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getkeytime())
    {
        if (!this->paused)
            this->Pause_State();
        
        else
            this->Unpause_State();
    }
    
    
    
    
}

void EditorState::updateEditorinput(const float &dt)
{
    /*!
                @class EditorState
                @brief Update the user's Input while inside the editor state
                @param const float deltaTime
                @return void
     */
    
   
    if((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PLACE"))) && this->getkeytime()))
    {
    //if the user's mouse is not on the sidebar
        
    if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->MousePosWindow)))
    {
        //if the texure selector is not active
         if(!this->texture_selector->getActive())
         {
                 if(this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->layer) != -1)
                 {
                     //if adding tiles is locked to one layer
                       if (this->Tilemap->lock_layer)
                       {
                            if (this->Tilemap->TileEmpty(MousePosGrid.x, MousePosGrid.y, 0))
                             {
                                 this->Tilemap->addTile(MousePosGrid.x, MousePosGrid.y, 0, this->TextureRect, collision, type);
                             }
                             else
                             {
                                 this->Tilemap->addTile(MousePosGrid.x, MousePosGrid.y, 0, this->TextureRect, collision, type);
                             }
                             
                       }
                 }
             
                //else play UI invalid sound for invalid tile placement
             
                 else if(this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->layer) == -1)
                 {
                     this->UI_invalid.play();
                 }
         }
         //else set the selection rect to the texture the user's mouse is on in the texture selector
        else
        {
            this->TextureRect = this->texture_selector->getTextureRect();
                     
        }
     }
    
        
     
  }
    

    
    //Remove a tile
    else if ((sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("REMOVE"))) && this->getkeytime()))
 {
     //if the user's mouse is not on the sidebar
     if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->MousePosWindow)))
      {
          //if the user's mouse is not inside the texture selector
         if(!this->texture_selector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->MousePosWindow)))
          {
              //if the cursor is over a valid tile, ok to place
              if(this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->layer) != -1)
              {
                  
                  this->Tilemap->RemoveTile(this->MousePosGrid.x, this->MousePosGrid.y, 0);
              }
              
              //else play UI invalid sound
              else if(this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->layer) == -1)
              {
                  this->UI_invalid.play();
              }
          }
        
            else
             {
             
             }
      }
        
 }
    
  
    
    //Toggle Collision on Tiles
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getkeytime())
    {
        if(this->collision)
            this->collision = false;
        else
            this->collision = true;
    }
    
    
    //Toggle Type of Tile to increase or decrease
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TYPE_INCREASE"))) && this->getkeytime())
    {
        ++this->type;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TYPE_DECREASE"))) && this->getkeytime())
    {
        if(this->type > 0)
        --this->type;
    }
    
    
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
    {
        if(this->Tilemap->lock_layer)
        this->Tilemap->lock_layer = false;
        
      else
          this->Tilemap->lock_layer = true;
    }
    

}


void EditorState::updatebuttons()
{
    /*!
    @class EditorState
    @brief Update the user's Input for buttons
    @param void
    @return void
    */
    
    for (auto &it : this-> buttons)
    {
        it.second->update(this->MousePosWindow);
    }
    
}


void EditorState::updateGUI(const float& dt)
{
    sf::VideoMode vm = this->state_data->gfxsettings->resolution;
    
    this->texture_selector->update(this->MousePosWindow, dt);
    
    if(!this->texture_selector->getActive())
    {
          //set the selection rectangle position
        this->select_Rect.setTextureRect(this->TextureRect);
        this->select_Rect.setPosition(this->MousePosGrid.x * this->state_data->gridsize, this->MousePosGrid.y * this->state_data->gridsize);
        
    }
    

    //set the cursor text
    
    
    std::stringstream cursor_text;
    cursor_text << this->MousePosView.x << " " << this->MousePosView.y
    << "\n" << this->MousePosGrid.x << " " << this->MousePosGrid.y
    << "\n" << this->TextureRect.left << " " << this->TextureRect.top << "Collision: " << this->collision
    << "\n" << "type" << this->type
    << "\n" << "Tiles:" << this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->layer);
    
    //If the cursor is on a valid tile, the text color is white
    if (this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->layer) != -1)
    {
        this->cursortext.setFillColor(sf::Color::White);
    }
    
    //if the cursor is not on a valid tile, the text color is red
    else if (this->Tilemap->getLayerSize(this->MousePosGrid.x, this->MousePosGrid.y, this->layer) == -1 )
    {
        this->cursortext.setFillColor(sf::Color::Red);
    }

    this->cursortext.setString(cursor_text.str());
    
   }




/*Render Functions*/

void EditorState::render(sf::RenderTarget* target) {
    
    if (!target)
        target = this->window;
    
    //Tilemap Camera (same as game camera)
    this->window->setView(this->mainview);
    this->Tilemap->render(*target, this->MousePosGrid);
    
    //Buttons Camera
    this->window->setView(this->window->getDefaultView());
    this->renderbuttons(*target);
    
    this->renderGUI(*target);
    
    
    if(this->paused)
    {
        this->window->setView(this->window->getDefaultView());
        this->pMenu->render(*target);
    }
    

    //render the Scroller text
   
    
    //render the gui sidebar
   
    
}

void EditorState::renderGUI(sf::RenderTarget &target)
{
    if (!this->texture_selector->getActive())
    {
        target.setView(this->mainview);
        target.draw(this->select_Rect);
        
    }
    
    target.setView(this->window->getDefaultView());
    this->texture_selector->render(target);
    target.draw(this->sidebar);
    target.draw(this->cursortext);
    target.draw(this->text_container);
    
    target.setView(this->mainview);
    
    


}


void EditorState::renderbuttons(sf::RenderTarget& target)
{
    for (auto &it : this->buttons)
       {
           it.second->render(target);
    
       }
}

