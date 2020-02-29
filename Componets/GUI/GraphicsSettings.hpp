//
//  GraphicsSettings.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/7/20.
//  Copyright © 2020 Eli Reynolds. All rights reserved.
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
          
          //Functions
          void savetofile(const std::string path);
          void loadfromfile(const std::string path);
          
      };

#endif /* GraphicsSettings_hpp */
