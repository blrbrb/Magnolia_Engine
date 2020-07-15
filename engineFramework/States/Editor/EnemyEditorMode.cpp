//
//  EnemyEditorMode.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/4/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
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
                                     std::cout << "Grid space is already assigned to a tile, disable layer locking to place more than one tile on a Grid space" << std::endl;
                                 }
                               
                           }
                         //else if adding tiles is not locked to one layer
                           else if (!this->tilemap->lock_layer)
                            {
                        
                                this->tilemap->addTile(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, 0, this->TextureRect, this->Enemytype, this->Enemyamount, this->spawn_timer, this->maxDistance);
                                
                                std::cout << "Spawner Tile Added" << std::endl;
                               
                            }

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
                                   std::cout << "Grid space has already been assigned a tile , disable layer locking to place more than one tile on a Grid space" << std::endl;
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
            
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && this->getkeytime())
    {
        if (this->Enemyamount > 0)
            this->Enemyamount--;
              
    }
        
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->getkeytime())
    {
        
        if (this->Enemyamount < 100)
            this->Enemyamount++;
        else
            this->Enemyamount = 0;
    }
    
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) && this->getkeytime())
    {
        
        if (this->spawn_timer > 0)
                this->spawn_timer--;
    }
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && this->getkeytime())
    {
        
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
    target.draw(this->controlsContainer);
    target.draw(this->controls); 
}

void EnemyEditorMode::render(sf::RenderTarget &target)
{
      this->renderGUI(target);
}

void EnemyEditorMode::initGUI()
{
     sf::VideoMode vm = statedata->gfxsettings->resolution;
    
       this->sidebar.setSize(sf::Vector2f(64.f, static_cast<float>(this->statedata->gfxsettings->resolution.height)));
       this->sidebar.setFillColor(sf::Color(50,50,50, 100));
       this->sidebar.setOutlineColor(sf::Color(200,200,200,150));
       this->sidebar.setOutlineThickness(1.f);
       
        //config the selection rectangle
        this->select_Rect.setSize(sf::Vector2f(statedata->gridsize, statedata->gridsize));
        this->select_Rect.setFillColor(sf::Color::White);
    
        //init the box to display controls information to the user
        this->controlsContainer.setSize(sf::Vector2f(GUI::pixelpercentX(22.57, vm), GUI::pixelpercentY(30, vm)));
        this->controlsContainer.setFillColor(sf::Color(50,50,50,100));
        this->controlsContainer.setPosition(GUI::pixelpercentX(77.4, vm), GUI::pixelpercentY(30, vm));
        this->controlsContainer.setOutlineThickness(1.f);
        this->controlsContainer.setOutlineColor(sf::Color(200, 200, 200, 150));
         
        //init the box for the cursor text to be displayed in
        this->text_container.setSize(sf::Vector2f(GUI::pixelpercentX(22.57, vm), (GUI::pixelpercentY(30, vm))));
        this->text_container.setFillColor(sf::Color(50,50,50,100));
        this->text_container.setPosition(GUI::pixelpercentX(77.4, vm), GUI::pixelpercentY(0, vm));
        this->text_container.setOutlineThickness(1.f);
        this->text_container.setOutlineColor(sf::Color(200, 200, 200, 150));
        
    
}

void EnemyEditorMode::initvariables()
{
    this->Enemytype = 1;
    this->Enemyamount = 1;
    this->spawn_timer = 60;
    this-> maxDistance = 1000.f;
    this->type = 1;
      
}

void EnemyEditorMode::inittext()
{
    sf::VideoMode vm = statedata->gfxsettings->resolution;
        
          //init the cursor text
           this->cursortext.setFont(*this->editorstatedata->font);
           this->cursortext.setFillColor(sf::Color::White);
           this->cursortext.setCharacterSize(GUI::calcCharSize(vm, 140));
           this->cursortext.setOutlineThickness(1.f);
           this->cursortext.setPosition(GUI::pixelpercentX(78.4, vm), GUI::pixelpercentX(3, vm));
        
    
          //init the text describing the controls to the user
          this->controls.setCharacterSize(GUI::calcCharSize(vm, 140));
          this->controls.setFillColor(sf::Color::White);
          this->controls.setFont(*this->editorstatedata->font);
          this->controls.setPosition(GUI::pixelpercentX(78.4, vm), GUI::pixelpercentY(33, vm));
          this->controls.setString("CONTROLS \n+ Enemies: Up \n - Enemies: Down \n + Spawn Time: J \n - Spawn Time: K");
     
}



