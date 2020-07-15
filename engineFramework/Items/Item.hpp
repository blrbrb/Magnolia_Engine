//
//  Item.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Item_hpp
#define Item_hpp

enum ItemTypes{REG = 0, MISC, WEAPON, CONSUMABLE, ENVIORNMENTAL };

class Item
{
    
public:
    

    Item(unsigned value);
    virtual ~Item();
    
    virtual Item* clone() = 0; 
   
    
private:
    

    
protected:
    
    //variables
      unsigned value;
      int type;
    
    
    
};

#endif /* Item_hpp */
