//
//  EnemyEditorMode.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/4/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "EnemyEditorMode.hpp"


EnemyEditorMode::EnemyEditorMode(StateData *statedata, TileMap *tilemap, EditorStateData *editorstatedata) : EditorModes(statedata, tilemap, editorstatedata)
{
    this->initvariables();
    this->inittext();
    this->initGUI();
    
}

EnemyEditorMode::~EnemyEditorMode()
{
    
}

void EnemyEditorMode::updateInput(const float &dt)
{
    if((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getkeytime()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("PLACE"))) && this->getkeytime()))
        {
                 if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) != -1)
                     {
                         //if adding tiles is locked to one layer
                           if (this->tilemap->lock_layer)
                           {
                                if (this->tilemap->TileEmpty(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer))
                                 {
                                     this->tilemap->addTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, this->TextureRect, this->Enemytype, this->Enemyamount, this->spawn_timer, this->maxDistance);
                                     
                                        std::cout << "LOCKED: Spawner Added" << std::endl;
                                 }
                                 else
                                 {
                                     std::cout << "Tile is already assigned to space, disable layer locking to place more than one tile on a spot" << std::endl;
                                 }
                               
                           }
                         //else if adding tiles is not locked to one layer
                           else if (!this->tilemap->lock_layer)
                            {
                        
                                this->tilemap->addTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, this->TextureRect, this->Enemytype, this->Enemyamount, this->spawn_timer, this->maxDistance);
                                
                                std::cout << "Tile Added" << std::endl;
                               
                            }

                     }
                 
                    //else play UI invalid sound for invalid tile placement
                 
                 
             
             //else set the selection rect to the texture the user's mouse is on in the texture selector
            else
            {
                this->TextureRect = this->texture_selector->getTextureRect();
                         
            }
        }
    
        
        //Remove a tile
    else if ((sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getkeytime()) ||  (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorstatedata->keybinds->at("REMOVE"))) && this->getkeytime()))
     {
         
            if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) != -1)
                  {
                      
                      if (this->tilemap->lock_layer)
                         {
                              if (!this->tilemap->TileEmpty(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer))
                               {
                                   if(this->tilemap->checktype(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, TileTypes::SPAWNER))
                                   {
                                         this->tilemap->RemoveTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, TileTypes::SPAWNER );
                                       
                                   }
                                   std::cout << "LOCKED: Tile Removed" << std::endl;
                               }
                               else
                               {
                                   std::cout << "Tile is already assigned to space, disable layer locking to place more than one tile on a spot" << std::endl;
                               }
                             
                         }
                        //else if adding tiles is not locked to one layer
                         else if (!this->tilemap->lock_layer)
                          {
                      
                              this->tilemap->RemoveTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer, TileTypes::SPAWNER);
                              
                              std::cout << "Tile Removed" << std::endl;
                              
                          }
                      
                    
                  }
                  
                  //else play UI invalid sound
                  else if(this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) == -1)
                  {
                      
                  }
              
            
                else
                 {
                 
                 }
          }
            
        
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->getkeytime())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->Enemyamount > 0)
                this->Enemyamount--;
        }
        
        if (this->Enemyamount < 100)
            this->Enemyamount++;
        else
            this->Enemyamount = 0;
    }
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && this->getkeytime())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->spawn_timer > 0)
                this->spawn_timer--;
        }
        
        if (this->spawn_timer < 1000)
            this->spawn_timer++;
        
        else
            this->spawn_timer = 0;
    }
    
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) && this->getkeytime())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->type > 0)
                this->type--;
        }
    
         if (this->Enemytype < 10000)
             this->Enemyamount++;
        else
            this->Enemyamount=0;
    }
}


    


void EnemyEditorMode::update(const float &dt)
{
    this->updateGUI(dt);
    this->updateInput(dt);
}

void EnemyEditorMode::updateGUI(const float &dt)
{
    sf::VideoMode vm = this->statedata->gfxsettings->resolution;
     

           //set the selection rectangle position
     
         this->select_Rect.setPosition(this->editorstatedata->mouseposGrid->x * this->statedata->gridsize, this->editorstatedata->mouseposGrid->y * this->statedata->gridsize);
         
    
     

     //set the cursor text
     std::stringstream cursor_text;
     cursor_text <<
    "\n" << "Enemy Type: " << this->Enemytype <<
    "\n" << "Enemy Amount: " << this->Enemyamount <<
    "\n" << "Time to Spawn: " << this->spawn_timer <<
    "\n" << "Max Distance: " << this->maxDistance;

    this->cursortext.setString(cursor_text.str());
     
     //If the cursor is on a valid tile, the text color is white
     if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) != -1)
     {
         this->cursortext.setFillColor(sf::Color::White);
     }
     
     //if the cursor is not on a valid tile, the text color is red
     else if (this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer) == -1 )
     {
         this->cursortext.setFillColor(sf::Color::Red);
     }


    }
    

void EnemyEditorMode::renderGUI(sf::RenderTarget &target)
{
    
     target.setView(*this->editorstatedata->view);
     target.draw(this->select_Rect);
   
   
    
    target.setView(this->statedata->window->getDefaultView());
    target.draw(this->sidebar);
    target.draw(this->cursortext);
    target.draw(this->text_container);
}

void EnemyEditorMode::render(sf::RenderTarget &target)
{
      this->renderGUI(target);
}

void EnemyEditorMode::initGUI()
{
       this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->statedata->gfxsettings->resolution.height)));
       this->sidebar.setFillColor(sf::Color(50,50,50, 100));
       this->sidebar.setOutlineColor(sf::Color(200,200,200,150));
       this->sidebar.setOutlineThickness(1.f);
       
        //config the selection rectangle
       this->select_Rect.setSize(sf::Vector2f(statedata->gridsize, statedata->gridsize));
        this->select_Rect.setFillColor(sf::Color::White);
        
        
        //this->select_Rect.setFillColor(sf::Color::Transparent);
        //this->select_Rect.setOutlineColor(sf::Color::Green);
        //this->select_Rect.setOutlineThickness(2);
  
        
        //Config the TextureSelector from GUI.hpp
        this->texture_selector = new GUI::TextureSelector(20.f, 20.f, 543.f, 560.f, this->statedata->gridsize, this->tilemap->getTileSheet(), *this->editorstatedata->font, "X");
        
       
        
       // this->buffer.loadFromFile(resourcePath() + "Beep.wav");
        //this->UI_invalid.setBuffer(buffer
}

void EnemyEditorMode::initvariables()
{
    this->Enemytype = 1;
    this->Enemyamount = 1;
    this->spawn_timer = 1;
    this-> maxDistance = 5;
    this->layer = 0;
    this->type = TileTypes::SPAWNER; 
      
}

void EnemyEditorMode::inittext()
{
    sf::VideoMode vm = statedata->gfxsettings->resolution;
        
        
           this->cursortext.setFont(*this->editorstatedata->font);
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



