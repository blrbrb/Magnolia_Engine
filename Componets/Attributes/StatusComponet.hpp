//
//  AttributeComponet.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/21/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef AttributeComponet_hpp
#define AttributeComponet_hpp

class StatusComponet
{
    
private:
    //sounds
    sf::SoundBuffer buffer;
    sf::Sound Levelsound;
    
    void initsounds(); 
 
public:
    
        //Leveling 
      int level;
      int exp;
      int expNextlvl;
      int attributepts;
      
      //Multipliers
      int strength;
      int vit;
      int dex;
      int agility;
      int inteligence;
      
      //Status
      int hp;
      int hpMax;
      int damMax;
      int damageMin;
      int accuracy;
      int defense;
      int luck;
    
    //COINS
    int coins; 
      
    
    //const and destruct
    StatusComponet(int level);
    virtual ~StatusComponet();
      
      
    //degub
    std::string debugPrint() const;
      
    //Functions
    void UpdateStats(const bool reset);
    void update();
    void UpdateLevel();
    void createstats();
    
    void Debug_test_Algorithim();
      
    void gainexp(const unsigned exp);
    void gaincoins(const int COINS);
};




#endif /* AttributeComponet_hpp */
