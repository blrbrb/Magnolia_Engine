//
//  State.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef State_hpp
#define State_hpp
#include "Entity.hpp"
#include "GraphicsSettings.hpp"


class Player;
class GraphicsSettings;
class State;


class StateData
{
    
    
 
public:
    StateData() {};
    
    //Variables
    float gridsize;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedkeys;
    std::stack<State*>* states;
    GraphicsSettings* gfxsettings;
    
};



class State {

    public:
    //Constructors and Destructors
    State(StateData* state_data);
  
    
    virtual ~State();
    
    //public variables
    bool quit;
    bool paused;
    
    
    //Acessors
    const bool& getquit() const;
    const bool getkeytime();

    
    
    //Modifiers
    void endstate();
    void Pause_State();
    void Unpause_State();
    

    //Pure Virtual Template Update functions
    virtual void updateMousePosition(sf::View* view = NULL);
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = NULL) = 0;
    virtual void updatekeytime(const float& dt);
    

protected:
   
    //All states inherit these values through the StateData subclass
    //Debug, will problably remove later duplicate data.
    sf::RenderWindow* window;
    float gridsize;
    StateData* state_data; 
   
    //Global Mouse Position Accessors
    sf::Vector2i MousePosScreen;
    sf::Vector2i MousePosWindow;
    sf::Vector2f MousePosView;
    sf::Vector2i MousePosGrid;
    
    //Keybinds, keylogging, input update, controllers
    std::map<std::string, int>* supportedkeys;
    std::map<std::string, int> keybinds;

    
    //keybinds, buttontime
    virtual void initkeybinds() = 0;
    float keytime;
    float keytime_MAX;
    
 
    //State mechanism
    std::stack<State*>* states; 
    
    //Asset storage
    std::map<std::string,sf::Texture> textures;
   
    

    
  
};

#endif /* State_hpp */
