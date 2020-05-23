//
//  Game.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
// 

#ifndef Game_hpp
#define Game_hpp

#include "States/MainMenuState.hpp"



class Game {
public:
    
    
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
    
    ///All of the mappable keyboard keys for user input.
    std::map<std::string, int> supportedkeys;
    

    sf::RenderWindow* window;
    sf::Event event;
    float gridsize; 
    bool fullscreen;
    
    sf::Clock dtClock;
    ///Delta Time
    float dt;
    ///Elapsed Time 
    float elapsedTime;
    
    ///The State Mechanism, stored in a stack of "State" objects
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
