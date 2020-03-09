//
//  Inventory.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/9/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "Inventory.hpp"

void Inventory::freeMemory()
{
    
    
}

void Inventory::initvariables()
{
    
    
}

Inventory::Inventory()
{
    this->capacity = 10;
    this->number_items = 0;
    this->itemarray = new Item*[this->capacity];
    
    
    for (size_t i = 0; i < this->capacity; i++)
    {
        this->itemarray = nullptr;
    
    }
    
}

Inventory::~Inventory()
{
    
    
}
