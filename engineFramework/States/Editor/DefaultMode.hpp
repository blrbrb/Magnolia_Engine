//
//  DefaultMode.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/3/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef DefaultMode_hpp
#define DefaultMode_hpp
#include "EditorModes.hpp"
#include "State.hpp"

class State;
class EditorModes;
class StateData;


class DefaultMode : public EditorModes
{
    
private:
   
public:
    
    DefaultMode(StateData* statedata);
    virtual ~DefaultMode();
    
    
};

#endif /* DefaultMode_hpp */
