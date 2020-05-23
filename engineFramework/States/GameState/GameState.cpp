//
//  GameState.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .


#include "GameState.hpp"


GameState::GameState(StateData* state_data)
: State(state_data)
{
    try
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
        this->initenemysystem();
        this->inittilemap();
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what();
        
    }
    
    // this->activEnemies.push_back(new Blrb(500.f, 800.f,this->textures["ENEMY_SHEET"]));
    //this->activEnemies.push_back(new Blrb(100.f, 300.f, this->textures["ENEMY_SHEET"]));
 
}

GameState::~GameState()
{
    
    delete this->player;
    delete this->pMenu;
    delete this->playerGUI;
    delete this->Tilemap;
    delete this->enemysystem;
    
    for (size_t i = 0; i < this->activEnemies.size(); i++ )
    {
        delete this->activEnemies[i];
        
    }
    

}

void GameState::initdeferedrender() {

    if(!this->rendertexture.create(this->state_data->gfxsettings->resolution.width,this->state_data->gfxsettings->resolution.height))
    {
        throw std::runtime_error("unable to create rendertextrue");
    }

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
        std::cout << "ERROR Unable to load core_shader Gamestate line 71" << std::endl;
        
        throw std::runtime_error("ERROR Unable to load core_shader Gamestate line 71");
        
    }
    
    
    
}


void GameState::initview()
{

    this->view.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.F, static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f));

    this->view.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxsettings->resolution.width) / 4.f,        static_cast<float>(this->state_data->gfxsettings->resolution.height) / 4.f));

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


void GameState::initgamestatedata()
{
    this->gamestatedata.keybinds = &this->keybinds;
    this->gamestatedata.font = &this->font;
    
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
   
    srand(static_cast<unsigned>(time(NULL)));
    
    this->updateMousePosition(&this->view);
    this->updateInput(dt);
    this->updatekeytime(dt);
   
    
    if(!this->paused) //Update while unpaused 
     {
         this->updateView(dt);
         this->updatePlayer(dt);
         this->updateEnemies(dt);
         this->updatetilemap(dt);
         this->updateEnemyEncounter();
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
    this->Tilemap->updateTiles(this->player, dt, *this->enemysystem);
    
//Update enemy collision
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

void GameState::updatePlayerInput(const float& dt)
{
   //check for a quit
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        this->player->move(dt, 1.f, 0.f);
        std::cout << "RIGHT" << std::endl;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))) )
    {
        
        this->player->move(dt, -1.f, 0.f);
        std::cout << "LEFT" << std::endl;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    {
        this->player->move(dt, 0.f, -1.f);
        std::cout << "UP" << std::endl;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    {
        
        this->player->move(dt, 0.f, 1.f);
        std::cout << "DOWN" << std::endl;

    }
    
    //hide the player's inventory 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && this->getkeytime())
    {
        this->playerGUI->HideInventory();
    }
    
   
}

void GameState::render(sf::RenderTarget* target) {
  
    if(!target)
        target = this->window;
    
    this->rendertexture.clear();
    
    this->rendertexture.setView(this->view);
    
    this->Tilemap->renderlighttile(this->rendertexture, &this->core_shader);
    
    this->Tilemap->render(this->rendertexture,this->ViewGridPosition, false, &this->core_shader, this->player->getCenter());
    
    this->player->render(this->rendertexture, &this->core_shader, this->player->getCenter(), false);
    
    for (auto *i : this->activEnemies)
       {
           i->render(this->rendertexture, &this->core_shader, i->getCenter(), false);
       }
    
    this->Tilemap->DefferedRender(this->rendertexture, &this->core_shader,this->player->getCenter());
    
    
    this->rendertexture.setView(this->rendertexture.getDefaultView());
    
    this->playerGUI->render(this->rendertexture);
    
    if(this->paused)
    {
        this->rendertexture.setView(this->rendertexture.getDefaultView());
        this->pMenu->render(this->rendertexture);
    }
    
   // this->rendermodes(target);
    
    this->rendertexture.display();
    //this->rendersprite.setTexture(this->rendertexture.getTexture());
    target->draw(this->rendersprite);
}


void GameState::checkforendstate() {
    
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
          
          //return this->quit = true;
        
      }
  //else return this->quit = false;
    
}

void GameState::updatePlayer(const float &dt)
{
    this->updatePlayerInput(dt);
    this->player->update(dt, this->MousePosView);
}

void GameState::updateEnemies(const float &dt)
{
    for (auto *i : this->activEnemies)
         {
             i->update(dt, this->MousePosView);
             i->move_rand(dt, rand() % 3 );
         }
}

void GameState::initenemysystem()
{
    this->enemysystem = new EnemySystem(this->activEnemies, this->textures);
}


void GameState::updateEnemyEncounter()
{

    for (auto *i : this->activEnemies)
    {
        if (i->getGlobalBounds().contains(this->player->getPosition().x, this->player->getPosition().y))
        {
            //enter a battlestate if the player, and enemy positions intersect
            this->state_data->states->push(new BattleState(this->state_data, &this->gamestatedata, this->player, this->playerGUI, i));
        }
        
    }
    
}



