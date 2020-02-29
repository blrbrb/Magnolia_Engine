//
//  GraphicsSettings.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/7/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
//

#include "GraphicsSettings.hpp"

//Constructors/ Destructors

GraphicsSettings::GraphicsSettings()
{
    this->title = "ERROR";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->vsync = false;
    this->windowSettings.antialiasingLevel = 0;
    this->Videomodes = sf::VideoMode::getFullscreenModes();

            
}

//Functions

void GraphicsSettings::savetofile(const std::string path)
         {
            std::ofstream out(resourcePath() + path);
              
             if (out.is_open())
             {
                 out << this->title;
                 out << this->resolution.width << "" << this->resolution.height;
                 out << fullscreen;
                 out << framerate_limit;
                 out << vsync;
                 out << this->windowSettings.antialiasingLevel;
             }
           
           out.close();
             
         }

void GraphicsSettings::loadfromfile(const std::string path)
       {
           std::fstream in(path);
           
           if (in.is_open())
           {
               
               std::getline(in, this->title);
               in >> this->resolution.width >> this->resolution.height;
               in >> fullscreen;
               in >> framerate_limit;
               in >> vsync;
               in >> this->windowSettings.antialiasingLevel;
           }
           
           in.close();
           
       }
