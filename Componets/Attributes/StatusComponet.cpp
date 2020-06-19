//
//  AttributeComponet.cppe
//  engineFramework
//
//  Created by Eli Reynolds on 2/21/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "StatusComponet.hpp"


///me secret leveling formular
//
//(50/3) x (y+1^3) - 6 x (y^2) + (y+1) x 17 - 12;
//
//
//
StatusComponet::StatusComponet(int level)
{
    //init leveling variables
    this->level = level;
    this->exp = 0;                                      
    this->expNextlvl =static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) -12));
    
    this->attributepts = 2;
     
    //init stats
    this->vit = 1;
    this->inteligence = 1;
    this->dex = 1;
    this->strength = 1;
    this->agility = 1;
    this->initsounds();
    this->UpdateStats(true);
    
    
    this->UpdateLevel();
    this->UpdateStats(true);
    
    //init money
    this->coins = 0; 
    
}

StatusComponet::~StatusComponet()
{
   
}

void StatusComponet::initsounds()
{
    this->buffer.loadFromFile(resourcePath() + "LevelUp.wav");
    this->Levelsound.setBuffer(buffer);
}


void StatusComponet::UpdateStats(const bool reset)
{
    //Calc to determine the Player's health points
    ////Form: x = y*9 + y + z/2 + xn / 5;
    
    //Calc to determien the Player's min damage
    ///Form: x = y2 + y/4 + xn / 5;
    
    //Calc to determine the Player;s Maximum damage
    ///Form: x = y2 + y/2 + xn / 5;
    
    //Calc to determine the Player's defense
    ///x = y2 + y/4 + xn/5;
    
    this->hpMax = this->vit * 9 + this->vit + this->strength / 2 + this->inteligence / 5;
    this->damageMin = this->strength * 2 + this->strength / 4 + this->inteligence / 5;
    this->damMax = this->strength * 2 + this->strength / 2 + this->inteligence / 5;
    this->defense = this->agility * 2 + this->agility / 4 + this->inteligence / 5;
    this->luck = this->inteligence * 2 + this->inteligence / 5;
    
    if(reset)
    {
        this->hp = this->hpMax;
    }
    
}



void StatusComponet::update()
{
    this->UpdateLevel();
}



void StatusComponet::createstats()
{
    
}



void StatusComponet::UpdateLevel()
{
    
    if (this->exp >= this->expNextlvl)
    {
        this->Levelsound.play();
        
        ++this->level;
        this->exp -= this->expNextlvl;
        this->expNextlvl = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) -12));
        //Formula Proof
        // x  = (50/30) * (y^3) - 6 * (y-^2)  +  (y * 17) - 12
        ++this->attributepts;
        
    }
    
}

std::string StatusComponet::debugPrint() const
{
    std::stringstream st;
    
    st << "Level:" << this->level << "\n"
    << "Exp:" << this->exp << "\n"
    << "Exp Next:" << this->expNextlvl << "\n"
    << "Attribute Pts:" << this->attributepts << "\n";
    
    
    return st.str();
    
}

const bool StatusComponet::isdead() const
{
    return this->hp <= 0;
    
}

//Modifiers
//Begin

void StatusComponet::loseHP(const int hp)
{
    this->hp -= hp;

    if (this->hp < 0)
        this->hp = 0;
}

void StatusComponet::gainHP(const int hp)
{
    this->hp += hp;

    if (this->hp > this->hpMax)
        this->hp = this->hpMax;
}

void StatusComponet::loseEXP(const int exp)
{
    this->exp -= exp;

    if (this->exp < 0)
        this->exp = 0;
}

void StatusComponet::gainEXP(const int exp)
{
    this->exp += exp;

    this->UpdateLevel();
}
