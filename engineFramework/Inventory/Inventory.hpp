//
//  Inventory.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/9/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef Inventory_hpp
#define Inventory_hpp
#include "Entity.hpp"

class Item; 
class Entity;
class Player; 

class Inventory
{
private:
    
    //GUI
    
    
    Item** itemarray;
    unsigned number_items;
    unsigned capacity;
    
    void initvariables();
    void expand();
    void freeMemory();
    void nullify(const unsigned from);
    bool ItemAdded; 
  
    
public:
    
    
    Inventory(unsigned capacity);
    virtual ~Inventory();
    
    
    //Functions
    const bool empty() const;
    void clear();
   
 
    const bool loadfromfile(const std::string filename);
    const bool savetofile(const std::string filename);
 
    
    //Accessors
    const unsigned& size() const;
    const unsigned& MaxSize() const;
    
    //Modifiers
    const bool add(Item* item);
    const bool remove(const unsigned index);
    
    
    
    
    
};

#endif /* Inventory_hpp */
