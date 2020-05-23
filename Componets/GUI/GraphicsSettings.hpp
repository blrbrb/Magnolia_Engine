//
//  GraphicsSettings.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/7/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef GraphicsSettings_hpp
#define GraphicsSettings_hpp

class GraphicsSettings
      {
      private:
          
          
      public:
          //Variables
          std::string title;
          sf::VideoMode resolution;
          std::vector<sf::VideoMode> Videomodes;
          sf::ContextSettings windowSettings;
          bool fullscreen;
          bool vsync;
          unsigned framerate_limit;
          
          //Constructors/Destructors
          GraphicsSettings();
          
          
          
          /// savetofile
          /// @brief Save the current graphics settings to a file to acess later.
          /// @param path to the file to write on
          void savetofile(const std::string path);
          
          /// loadfromfile
          /// @brief Load saved graphics settings from a file.
          /// @param path to the file to read from
          void loadfromfile(const std::string path);
          
      };

#endif /* GraphicsSettings_hpp */
