//
//  State.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 1/22/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef State_hpp
#define State_hpp
#include "Entity.hpp"
#include "GraphicsSettings.hpp"


class Player;
class GraphicsSettings;
class State;



/// Class that passes important global data between states while the application is running.
class StateData
{
    
    
 
public:
    
    StateData() {};
    
   ///The size of each individual tile in a grid.
    float gridsize;
    ///Pointer to the RenderWindow
    sf::RenderWindow* window;
    ///Acessable keys
    std::map<std::string, int>* supportedkeys;
    ///States
    std::stack<State*>* states;
    ///User-defined graphics settings
    GraphicsSettings* gfxsettings;
    
};



class State {

    public:
  
    State(StateData* state_data);
  
    
    virtual ~State();
    
    //public variables
    ///Has the State been quit?
    bool quit;
    ///Has the State been Paused?
    bool paused;
    
    
    //Acessors
    /// Retrieve wether or not the user has requested to end the Application
    const bool& getquit() const;
    /// Retrieve wether or not the minimum allowed time between individual keystrokes has passed
    const bool getkeytime();
    
    
    
    //Modifiers
    ///End the State, and return to either the main menu; or a previous state.
    /// @discussion NOTE: if there is no previou state, or if this function is accessed from the main menu you will get a  bad acess error
    void endstate();
    ///Pause the State
    void Pause_State();
    /// Un-Pause the state
    void Unpause_State();
    

    //Pure Virtual/Template Update functions
    virtual void updateMousePosition(sf::View* view = NULL);
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = NULL) = 0;
    virtual void updatekeytime(const float& dt);
    

protected:
   
    
    sf::RenderWindow* window;
    float gridsize;
    StateData* state_data; 
   
    ///The cursor's position relative to the screen
    sf::Vector2i MousePosScreen;
    /// The cursor's position relative to the window
    sf::Vector2i MousePosWindow;
    /// The cursor's position relative to the view
    sf::Vector2f MousePosView;
    /// The cursor's position relative to the tile grid
    sf::Vector2i MousePosGrid;
    
     /// All useable keyboard keys
    std::map<std::string, int>* supportedkeys;
    /// Keys with a user-supplied map
    std::map<std::string, int> keybinds;

    
    
    virtual void initkeybinds() = 0;
    float keytime;
    float keytime_MAX;
    
 
    //State mechanism
    std::stack<State*>* states; 
    
    ///Texture Asset storage. Saved as a Map container and can be retrieved with a string
    std::map<std::string,sf::Texture> textures;
   
    

    
  
};

#endif /* State_hpp */
