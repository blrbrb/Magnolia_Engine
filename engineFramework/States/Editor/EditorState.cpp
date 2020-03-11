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
    this->initeditorstatedata();
    this->initview();
    this->initFonts();
    this->initkeybinds();
    this->initpausemenu();
    this->initButtons();
    this->inittilemap();
    this->initGUI();
    this->initmodes();
    this->activeMode = EDITOR_MODES::DEFAULT_MODE;
     

}

EditorState::~EditorState() {
    

     auto it = buttons.begin();
     for (it = buttons.begin(); it != this->buttons.end(); ++it)
    
     {
         delete it->second;
      }
    delete this->pMenu;
     
    delete this->Tilemap;
    
  
    
    for (size_t i = 0; i > this->modes.size(); i++)
    {
        delete this->modes[i];
    }
    
    
}

//initalization functions
void EditorState::initvariables()
{
    this->cameraspeed = 200.f; 
    
}


//initalizer functions
void EditorState::initButtons()
{
    
}

void EditorState::inittilemap()
{
    this->Tilemap = new TileMap(this->gridsize, 100, 100, "fuck.png");

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
    this->pMenu->addbutton("Editor_Pause_Load_Button", GUI::calcCharSize(vm), "Load", GUI::pixelpercentX(12.f, vm),
                           GUI::pixelpercentY(6.f, vm), 650.f); 
   
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
                 
                 if (!this->keybinds.at(key))
                 {
                     //std::cout << this->keybinds.at(key);
                 }
             }
         }

         ifs.close();
    
    for (auto i : this->keybinds)
    {
        //std::cout << i.first << " " << i.second << "\n";
        
    }
    
    
    
}

void EditorState::initmodes()
{
    this->modes.push_back(new DefaultMode(this->state_data, this->Tilemap, &this->editorstatedata));
    this->modes.push_back(new EnemyEditorMode(this->state_data, this->Tilemap, &this->editorstatedata));
    this->modes.push_back(new EnviornmentalMode(this->state_data, this->Tilemap, &this->editorstatedata));
    
    this->activeMode = EDITOR_MODES::DEFAULT_MODE;
}

void EditorState::initsidebar()
{
    //config the sidebar
    
  
}

void EditorState::initGUI()
{
     
    

}


/* Initalizer Functions */






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


void EditorState::initeditorstatedata()
{
    //this->editorstatedata.view = &this->view;
     this->editorstatedata.keybinds = &this->keybinds; 
    this->editorstatedata.keytime = &this->keytime;
    this->editorstatedata.ketyimeMax = &this->keytime_MAX;

    this->editorstatedata.mouseposGrid = &this->MousePosGrid;
    this->editorstatedata.mousePosView = &this->MousePosView;
    this->editorstatedata.mousePosWindow = &this->MousePosWindow;
    this->editorstatedata.mousePosScreen= &this->MousePosScreen;
    this->editorstatedata.view = &this->mainview;
    this->editorstatedata.font = &this->font; 
    
    
}

/*Update Functions*/

void EditorState::update(const float& dt) {
    
    this->updateMousePosition(&this->mainview);
    this->updatekeytime(dt);
    this->updateEditorinput(dt);
    
   
   
    if (!this->paused) //Unpaused
    {
        this->updatebuttons();
        this->updateGUI(dt);
        this->updateInput(dt);
        this->updateModes(dt);
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
        
        std::cout << "camera right" << std::endl;
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
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && this->getkeytime())
    {
        if(this->Tilemap->lock_layer)
       this->Tilemap->lock_layer = false;
        
      else
          this->Tilemap->lock_layer = true;
    }
    
    
    /**std::cout << sf::Keyboard::L << std::endl;
    std::cout << "A = "<< " "<< sf::Keyboard::A << std::endl;
    std::cout << "B = "<< " "<< sf::Keyboard::B << std::endl;
    std::cout << "C = "<< " "<< sf::Keyboard::C << std::endl;
    std::cout << "D = "<< " "<< sf::Keyboard::D << std::endl;
    std::cout << "E = "<< " "<< sf::Keyboard::E << std::endl;
    std::cout << "F = "<< " "<< sf::Keyboard::F << std::endl;
    std::cout << "G = "<< " "<< sf::Keyboard::G << std::endl;
    std::cout << "H = "<< " "<< sf::Keyboard::H << std::endl;
    std::cout << "I = "<< " "<< sf::Keyboard::I << std::endl;
    std::cout << "G = "<< " "<< sf::Keyboard::J << std::endl;
    std::cout << "K = "<< " "<< sf::Keyboard::K << std::endl;
    std::cout << "L = "<< " "<< sf::Keyboard::L << std::endl;
    std::cout << "M = "<< " "<< sf::Keyboard::M << std::endl;
    std::cout << "N = "<< " "<< sf::Keyboard::N << std::endl;
    std::cout << "O = "<< " "<< sf::Keyboard::O << std::endl;
    std::cout << "P = "<< " "<< sf::Keyboard::P << std::endl;
    std::cout << "Q = "<< " "<< sf::Keyboard::Q << std::endl;
    std::cout << "R = "<< " "<< sf::Keyboard::R << std::endl;
    std::cout << "S = "<< " "<< sf::Keyboard::S << std::endl;
    std::cout << "T = "<< " "<< sf::Keyboard::T << std::endl;
    std::cout << "U = "<< " "<< sf::Keyboard::U << std::endl;
    std::cout << "V = "<< " "<< sf::Keyboard::V << std::endl;
    std::cout << "W = "<< " "<< sf::Keyboard::W << std::endl;
    std::cout << "X = "<< " "<< sf::Keyboard::X << std::endl;
    std::cout << "Y = "<< " "<< sf::Keyboard::Y << std::endl;
    std::cout << "Z = "<< " "<< sf::Keyboard::Z << std::endl; */
    
    //Zoom the World Builder View in or out
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
    {
        this->mainview.zoom(1.01);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && this->getkeytime())
    {
        this->mainview.zoom(0.5);
    }
   
    
    //inc the current editor mode
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
    {
        
        if (this->activeMode > 0)
        {
            this->activeMode--;
        }
        else
        {
            std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE DOWN!" << "\n";
        }
    }
      
    //dec the current editor mode
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && this->getkeytime())
       {
           if (this->activeMode < this->modes.size() - 1)
           {
               this->activeMode++;
           }
           else
           {
               std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE UP!" << "\n";
           }
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


void EditorState::updateEditorinput(const float& dt)
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getkeytime())
    {
        if (!this->paused)
            this->Pause_State();
        
        else
            this->Unpause_State();
    }
    
    
    
}


void EditorState::updateGUI(const float& dt)
{
    
}


/*Render Functions*/

void EditorState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    //Tilemap Camera (same as game camera)
    this->window->setView(this->mainview);
    this->Tilemap->render(*target, this->MousePosGrid);
        
    //Buttons Camera
    this->window->setView(this->window->getDefaultView());
    this->renderModes(*target);
    //this->renderbuttons(*target);
    
   
    
    if(this->paused)
       {
           this->window->setView(this->window->getDefaultView());
           this->pMenu->render(*target);
       }
    
}

void EditorState::renderGUI(sf::RenderTarget &target)
{
    
   
   
}


void EditorState::renderbuttons(sf::RenderTarget& target)
{
    for (auto &it : this->buttons)
       {
           it.second->render(target);
    
       }
}

void EditorState::updateModes(const float &dt)
{
    this->modes[this->activeMode]->update(dt);
    
}

void EditorState::renderModes(sf::RenderTarget &target)
{
     this->modes[this->activeMode]->render(target);
}



