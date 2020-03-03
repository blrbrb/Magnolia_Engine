//
//  EditorState.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/1/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
// 

#ifndef EditorState_hpp
#define EditorState_hpp
#include "State.hpp"
#include "GUI.hpp"
#include "PauseMenu.hpp"
#include "TileMap.hpp"
#include "EditorModes.hpp"


class State;
class EditorModes;
class PauseMenu;
class TileMap; 


class EditorState : public State
{
    public:
        EditorState(StateData* state_data);
    
        virtual ~EditorState();
        
    
        //Functions
        void updateInput(const float& dt);
        void updateEditorinput(const float& dt);
        void update(const float& dt);
        void updatebuttons();
        void updateGUI(const float& dt);
        void updatepausemenubuttons();
        void renderbuttons(sf::RenderTarget& target);
        void renderGUI(sf::RenderTarget& target);
        void render(sf::RenderTarget* target = nullptr);
            
private:
    
        //Private initalizer Functions
        void initkeybinds();
        void initview();
        void initFonts();
        void initButtons();
        void initbackground();
        void initvariables();
        void initpausemenu();
        void inittext();
        void inittilemap();
        void initsidebar();
        void initGUI();
         
        //Text
        sf::Font font;
        sf::Text cursortext;
    
        //Pause Menu
        PauseMenu* pMenu;
    
        //TileMap
        TileMap* Tilemap;
    
        //GUI
        GUI::TextureSelector* texture_selector; 
        sf::RectangleShape select_Rect;
        sf::RectangleShape sidebar;
        sf::RectangleShape sidebar_texture;
        sf::RectangleShape text_container;  
        sf::IntRect TextureRect;
        std::map<std::string, GUI::Button*> buttons;
       
        //Sounds
        sf::SoundBuffer buffer;
        sf::Sound UI_invalid;
    
        //Camera
        sf::View mainview;

    bool collision;
    short type;
    float cameraspeed;
    int layer; 
    
 
   
};
    

#endif /* EditorState_hpp */
