//
//  DialougeSystem.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 6/25/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "DialougeSystem.hpp"


DialougeSystem::DialougeSystem(std::string font_file)
{
   
         
    if (!this->font.loadFromFile(font_file))
    {
        std::cerr << "unable to open font file" << font_file << std::endl;
    }
    this->initfonts(font_file);
    this->initvariables();
    this->inittemplates();
}

DialougeSystem::~DialougeSystem()
{
    //clean memory of text tags
    
    for (auto *textbox : this->boxes)
    {
        delete textbox; 
        
    }
    
    for (auto &textbox : this->templates)
    {
          
        delete textbox.second;
    }
}

void DialougeSystem::addTextbox(unsigned type)
{
    this->boxes.push_back(new Textbox(*this->templates[DEFAULT_TAG]));
}

void DialougeSystem::removeTextbox()
{
    
}

void DialougeSystem::update(const float &dt)
{
    
    
}

void DialougeSystem::render(sf::RenderTarget & target)
{
    for (auto&textbox : this->boxes)
    {
        textbox->render(target);
    }
    
}

void DialougeSystem::initvariables()
{
    
}

void DialougeSystem::inittemplates()
{
    this->templates[DEFAULT_TAG] = new Textbox(this->font, "hello", 0, 0, sf::Color::White, 12,  1000.f, 200.f, 0, 0);
    
}


void DialougeSystem::initfonts(std::string font_file)
{
    
   if (!this->font.loadFromFile(font_file))
       {
           std::cout << "unable to open font file" << font_file << std::endl;
       }
    
}


