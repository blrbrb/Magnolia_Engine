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
    for (size_t i = 0; i > this->capacity; i++)
    {
        delete this->itemarray[i];
    }
    delete[] this->itemarray; 
}

void Inventory::initvariables()
{
    this->number_items = 0;
    this->itemarray = new Item*[this->capacity];
    this->nullify(0);

}

Inventory::Inventory(unsigned capacity)
{
    this->capacity = capacity;
    
    this->initvariables();
}

Inventory::~Inventory()
{
    
    this->freeMemory(); 
}


void Inventory::nullify(const unsigned from)
{
    for (size_t i = from; i < this->capacity; i++)
      {
          this->itemarray = nullptr;
      
      }
}


void Inventory::clear()
{
    for (size_t i = 0; i < this->number_items; i++)
         {
             delete this->itemarray[i];
         }

    this->number_items = 0;
    
    this->nullify(0);
}

const bool Inventory::empty() const
{
    return this->number_items == 0;
}

const unsigned int &Inventory::size() const
{
    return this->number_items;
}

const unsigned int &Inventory::MaxSize() const
{
    return this->capacity;
}

const bool Inventory::add(Item *item)
{
    if (this->number_items < this->capacity)
    {
        this->itemarray[this->number_items++] = item->clone();
        return true;
        this->ItemAdded = true; 
    }
    return false;
}

const bool Inventory::remove(const unsigned int index)
{
    if (this->number_items > 0)
    {
        if(index < 0 || index >= this->capacity)
            return false;
        
        delete this->itemarray[index];
        this->itemarray[index] = nullptr;
        --this->number_items; 
        return true; 
    }
    return false; 
}

const bool Inventory::loadfromfile(const std::string filename)
{
    
}

const bool Inventory::savetofile(const std::string filename)
{
    
}

