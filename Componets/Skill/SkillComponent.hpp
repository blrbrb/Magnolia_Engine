//
//  SkillComponent.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef SkillComponent_hpp
#define SkillComponent_hpp

enum SKILLS {HP = 0, ATK, POW, DEF, SPEED, SP };

class SkillComponent
{
public:
    
    SkillComponent();
    virtual ~SkillComponent();
    
   const int getSkill(const int skill) const;
   const void gainExp(const int skill, const int exp);
    
private:
    class Skill
    {
    private:
        int type;
        int level;
        int exp;
        int expNext;
        int levelCap;
        
    public:
        
        Skill(int type)
        {
            this->type = type;
            this->level = 1;
            this->levelCap = 99;
            this->exp = 0;
            this->expNext = 100;
        }
        
        ~Skill() {}
        
        
        //Accessors
        inline const int & getType() const {return this->type;}
        inline const int & getlevel() const {return this->level;}
        inline const int & getexp() const {return this->exp;}
        inline const int & getExpNext() const {return this->expNext;}
        
        //Modifiers
         void gainexp(const int exp)
        {
            this->exp += exp;
            this->updateLevel();
        }
        
        void LoseExp(const int exp){this->exp -= exp;}
        
        
        void setLevel(const int level){this->level = level;}
        void setLevelCap(const int levelCap) {this->levelCap = levelCap;}
        
        //functions
        
        void updateLevel(const bool up = true)
        {
            if (up)
            {
                if (this->level < this->levelCap)
                {

                    while (this->exp >= this->expNext)
                    {
                        if (this->level < this->levelCap)
                        {
                            this->level++;
                            this->expNext = static_cast<int>(std::pow(this->level, 2)) + this->level * 10 + this->level * 2 + this->level;
                        }
                    }
                    
                }
            }
            else
            {
                if(this->level > 0)
                {
                    while(this->exp < 0)
                    {
                        if (this->level > 0)
                        {
                            this->level--;
                            this->expNext = static_cast<int>(std::pow(this->level, 2)) + this->level * 10 + this->level * 2 + this->level;
                        }
                    }
                }
                
            }
        }
        
        
        
        
        
        void update()
        {
           
            
        }
        
    };
    
    std::vector<Skill> skills;
    
};

#endif /* SkillComponent_hpp */
