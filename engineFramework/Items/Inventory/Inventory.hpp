//
//  Inventory.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/9/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#ifndef Inventory_hpp
#define Inventory_hpp
#include "Item.hpp"


class Inventory
{
private:
    
    Item** itemarray;
    unsigned number_items;
    unsigned capacity;
    
    void initvariables();
    void expand();
    void freeMemory();
    
    
    
public:
    
    
    Inventory();
    virtual ~Inventory();
    
    
};

#endif /* Inventory_hpp */
