//
//  Game.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
// 

#ifndef Game_hpp
#define Game_hpp

#include "States/MainMenuState.hpp"



class Game {
public:
    
    //Constructor et Destructor
     Game();
    ~Game();
    
    //Misc
    void endapplication();
    void resizewindow(); 
    
    
    //Final Render
    void render();
    
    //To Main loop
    void running();
    
    //Update Functions 
    void UpdateEvents();
    void UpdateDT();
    void Update();
    
    
    
    
    
private:
    
    //private game variables
    std::map<std::string, int> supportedkeys;
    

    sf::RenderWindow* window;
    sf::Event event;
    float gridsize; 
    bool fullscreen;
    
    sf::Clock dtClock;
    float dt;
    float elapsedTime;
    
    
    
    std::stack<State*> states;
    StateData state_data;
    GraphicsSettings gfxsettings;

    //init functions
    void load();
    void initwindow();
    void initstates();
    void initkeys();
    bool initJoySticks();
    void initVariables();
    void initGraphicsSettings();
    void initstatedata();
    
};


#endif /* Game_hpp */
