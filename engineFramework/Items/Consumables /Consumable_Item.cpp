//
//  Consumable_Item.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 7/15/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "Consumable_Item.hpp"

Consumable_Item::Consumable_Item(unsigned value) :Item(value)
{
    this->initvariables(); 

}

void Consumable_Item::initvariables()
{
    

    this->inittexturesheet();
    this->type = ItemTypes::CONSUMABLE;
    

}


void Consumable_Item::inittexturesheet()
{
    this->texturesheet.loadFromFile("/Resources/item_sheet.png");  
}


Consumable_Item::~Consumable_Item()
{
    
    
    
}
