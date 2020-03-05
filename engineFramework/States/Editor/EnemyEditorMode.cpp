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
    
    
    
}

EnemyEditorMode::~EnemyEditorMode()
{
    
}

void EnemyEditorMode::updateInput(const float &dt)
{
    
    
    
}

void EnemyEditorMode::update(const float &dt)
{
    this->updateGUI(dt);
    this->updateInput(dt);
}

void EnemyEditorMode::updateGUI(const float &dt)
{
    sf::VideoMode vm = this->statedata->gfxsettings->resolution;
     
     this->texture_selector->update(*this->editorstatedata->mousePosWindow, dt);
     
     if(!this->texture_selector->getActive())
     {
           //set the selection rectangle position
         this->select_Rect.setTextureRect(this->TextureRect);
         this->select_Rect.setPosition(this->editorstatedata->mouseposGrid->x * this->statedata->gridsize, this->editorstatedata->mouseposGrid->y * this->statedata->gridsize);
         
     }
     

     //set the cursor text
     std::stringstream cursor_text;
     cursor_text << this->editorstatedata->mousePosView->x << " " << this->editorstatedata->mousePosView->y
     << "\n" << this->editorstatedata->mouseposGrid->x << " " << this->editorstatedata->mouseposGrid->y
     << "\n" << this->TextureRect.left << " " << this->TextureRect.top << "Collision: " << this->collision
     << "\n" << "type" << this->type
     << "\n" << "Tiles:" << this->tilemap->getLayerSize(this->editorstatedata->mouseposGrid->x, this->editorstatedata->mouseposGrid->y, this->layer);
     
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

     this->cursortext.setString(cursor_text.str());
     
    }
    

void EnemyEditorMode::renderGUI(sf::RenderTarget &target)
{
    if (!this->texture_selector->getActive())
    {
        target.setView(*this->editorstatedata->view);
        target.draw(this->select_Rect);
        
    }
    
    target.setView(this->statedata->window->getDefaultView());
    this->texture_selector->render(target);
    target.draw(this->sidebar);
    target.draw(this->cursortext);
    target.draw(this->text_container);
    
    target.setView(*this->editorstatedata->view);
    
    
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
         this->select_Rect.setTexture(tilemap->getTileSheet());
        
        
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
    this->TextureRect = sf::IntRect(0, 0, 17, 17);
    this->collision = false;
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



