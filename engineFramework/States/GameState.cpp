//
//  GameState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.


#include "GameState.hpp"


GameState::GameState(StateData* state_data)
: State(state_data)
{
    this->initdeferedrender();
    this->initview();
    this->initkeybinds();
    this->initfonts();
    this->inittextures();
    this->initpausemenu();
    this->initshaders();
    this->initplayers();
    this->initplayerGUI();
    this->inittilemap();
    
   // this->activEnemies.push_back(new Blrb(500.f, 800.f,this->textures["ENEMY_SHEET"]));
    //this->activEnemies.push_back(new Blrb(100.f, 300.f, this->textures["ENEMY_SHEET"]));
 
}

GameState::~GameState() {
    
    delete this->player;
    delete this->pMenu;
    delete this->playerGUI;
    delete this->Tilemap;
    
    for (size_t i = 0; i < this->activEnemies.size(); i++ )
    {
        delete this->activEnemies[i];
        
    }
    
   
    
}

void GameState::initdeferedrender() {

    this->rendertexture.create(this->state_data->gfxsettings->resolution.width,this->state_data->gfxsettings->resolution.height);

    this->rendersprite.setTexture(this->rendertexture.getTexture());
    this->rendersprite.setTextureRect(
        sf::IntRect(
            0,
            0,
                    this->state_data->gfxsettings->resolution.width,
                    this->state_data->gfxsettings->resolution.height
        )
    );
}



void GameState::initshaders()
{
    if(!this->core_shader.loadFromFile( resourcePath() + "vertex_shader.vert", resourcePath() + "fragment_shader.frag"))
    {
        std::cout << "ERROR" << std::endl; 
    }
}


void GameState::initview()
{
    this->view.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width), static_cast<float>(this->state_data->gfxsettings->resolution.height)));

    this->view.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 2.f,        static_cast<float>(this->state_data->gfxsettings->resolution.height) / 2.f));
}


void GameState::initkeybinds() {
  
    std::ifstream ifs("Config/GameState_Keys.ini");

      if (ifs.is_open())
      {
          std::string key = "";
          std::string key2 = "";

          while (ifs >> key >> key2)
          {
              this->keybinds[key] = this->supportedkeys->at(key2);
          }
      }
   
    for (auto i : this->keybinds)
     {
        
         std::cout << i.first << " " << i.second << "\n";
         
     }
   
      ifs.close();
  }

void GameState::initplayerGUI()
{
    this->playerGUI = new PlayerGUI(this->player, this->state_data->gfxsettings->resolution);
    this->buffer.loadFromFile(resourcePath() + "Beep.wav");
    this->sound.setBuffer(buffer);
}


void GameState::inittextures()
{
    if (!this->textures["PLAYER_SHEET"].loadFromFile(resourcePath() + "Hero.png"))
    {
        std::cout << "ERROR_C 02: GAMESTATE::INITTEXTURES Could Not Load PLAYER_SHEET textures" << std::endl;
        throw std::runtime_error("ERROR CODE 02: GAMESTATE::INITTEXTURES Could Not Load PLAYER_SHEET textures");
    }
    
    if (!this->textures["ENEMY_SHEET"].loadFromFile(resourcePath() + "Blrb.png"))
    {
        std::cout << "ERROR_C 02: GAMESTATE::INITTEXTURES Could Not Load ENEMY_SHEET textures" << std::endl;
        throw std::runtime_error("ERROR CODE 02: GAMESTATE::INITTEXTURES Could Not Load ENEMY_SHEET textures");
    }
    
}

void GameState::initfonts()
{
    if (!this->font.loadFromFile(resourcePath() + "PressStart2P.ttf"))
       {
           std::cout << "ERROR_C_03: GameState::initFonts COULD NOT LOAD FONT FROM FILE" << std::endl;
           throw std::runtime_error("ERROR_C_03: GameState::initFonts COULD NOT LOAD FONT FROM FILE");
       }
}



void GameState::initplayers()
{
    this->player = new Player(100,50, this->textures["PLAYER_SHEET"]);
    
}

void GameState::initpausemenu()
{
    const sf::VideoMode& vm = this->state_data->gfxsettings->resolution;
    
    this->pMenu = new PauseMenu(this->state_data->gfxsettings->resolution, this->font);
    
    this->pMenu->addbutton("Pause_Quit_Button",GUI::calcCharSize(vm),"Quit",GUI::pixelpercentX(13.f, vm), GUI::pixelpercentY(6.f, vm), 200.f);
}

void GameState::inittilemap()
{
    this->Tilemap = new TileMap(this->state_data->gridsize, 100, 100, "TileMap.png");
    this->Tilemap->loadfromfile("Config/text.slmp");
}


void GameState::update(const float& dt) {
   
    this->updateMousePosition(&this->view);
    this->updateInput(dt);
    this->updatekeytime(dt);
    
    if(!this->paused) //Update while unpaused 
     {
        this->updateView(dt);
        this->updatePlayerInput(dt);
        //important to update the player BEFORE the tilemap
        this->player->update(dt, this->MousePosView);
        for (auto *i : this->activEnemies)
        {
                  i->update(dt, this->MousePosView);
        }
         this->updatetilemap(dt);
         this->updatePlayerGUI(dt);
        
         
     }
   
    else // Update while Paused
     {
         this->pMenu->update(this->MousePosWindow);
         this->updatebuttons();
     }
}

void GameState::updateInput(const float& dt)
{
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getkeytime())
     {
         if (!this->paused)
             this->Pause_State();
         else
             this->Unpause_State();
     }
}

void GameState::updatetilemap(const float& dt)
{
    this->Tilemap->updateWorldBoundsCollision(this->player, dt);
    this->Tilemap->updateTileCollision(this->player, dt);
    this->Tilemap->update(this->player, dt);
    
    if(this->Tilemap->isEntityColliding == true)
    {
        this->sound.play();
    
    }
    
    for (auto *i : this->activEnemies)
    {
        this->Tilemap->updateWorldBoundsCollision(i, dt);
        this->Tilemap->updateTileCollision(i, dt);
        
    }

    
}



void GameState::updatebuttons()
{
    if(this->pMenu->isButtonPressed("Pause_Quit_Button"))
    {
        this->endstate();
    }
}

void GameState::updateView(const float &dt)
{
    /**
                @brief Function that updates the area of the tilemap, or current level visible to the player at any one point
                @param const float detlaTime
                @returns void
     
     */
    
    
    this->view.setCenter(std::floor(this->player->getPosition().x + static_cast<float>(this->state_data->gfxsettings->resolution.width / 20)), std::floor(this->player->getPosition().y +                                                                        static_cast<float>(this->state_data->gfxsettings->resolution.height / 20)));
    
    
    
    
    if(this->Tilemap->getMaxSize().x >= this->view.getSize().x)
    {
        
        if(this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
        {
            this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
        
        else if(this->view.getCenter().x + this->view.getSize().x / 2.f > 10000.f)
        {
            this->view.setCenter(3000.f - this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
        
    }
    
    
    if(this->Tilemap->getMaxSize().y >= this->view.getSize().y)
    {
    
        if (this->view.getCenter().y - this->view.getSize().y / 2.f  < 0.f)
        {
            this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
        }
        
        else if (this->view.getCenter().y + this->view.getSize().y / 2.f > 10000.f)
        {
            this->view.setCenter(this->view.getCenter().x, 10000.f - this->view.getSize().y / 2.f);
        }
        
    }
    

    //Update the GridPosition view
    this->ViewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->state_data->gridsize);
    
    this->ViewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->state_data->gridsize);
}

void GameState::updatePlayerGUI(const float &dt)
{
    this->playerGUI->update(dt);
}

void GameState::updatePlayerInput(const float& dt) {
   //check for a quit
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        this->player->move(dt, 1.f, 0.f);
        std::cout << "RIGHT" << std::endl;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))) ) {
        
        this->player->move(dt, -1.f, 0.f);
        std::cout << "LEFT" << std::endl;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
        this->player->move(dt, 0.f, -1.f);
        std::cout << "UP" << std::endl;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
        
        this->player->move(dt, 0.f, 1.f);
        std::cout << "DOWN" << std::endl;
        if(this->getkeytime())
            this->player->loseHP(1);
    }
    
   

}

void GameState::render(sf::RenderTarget* target) {
  
    if(!target)
        target = this->window;
    
    this->rendertexture.clear();
    
    this->rendertexture.setView(this->view);
    
    
    this->Tilemap->render(this->rendertexture,this->ViewGridPosition, false, &this->core_shader, this->player->getPosition());
    
     this->player->render(this->rendertexture, &this->core_shader, false);
    
    for (auto *i : this->activEnemies)
       {
           i->render(this->rendertexture, &this->core_shader, true);
       }
    
    this->Tilemap->DefferedRender(this->rendertexture, &this->core_shader,this-> player->getPosition());
    
    
    this->rendertexture.setView(this->rendertexture.getDefaultView());
    this->playerGUI->render(this->rendertexture);
    
    if(this->paused)
    {
        this->rendertexture.setView(this->rendertexture.getDefaultView());
        this->pMenu->render(this->rendertexture);
    }
    
    this->rendertexture.display();
    //this->rendersprite.setTexture(this->rendertexture.getTexture());
    target->draw(this->rendersprite);
}



void GameState::checkforendstate() {
    
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
          
          return this->quit = true;
        
      }
  else return this->quit = false;
    
}

void GameState::updatePlayer(const float &dt) { 
    <#code#>;
}

void GameState::updateEnemies(const float &dt) { 
    <#code#>;
}










