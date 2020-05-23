//
//  SkillComponent.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "SkillComponent.hpp"

SkillComponent::SkillComponent()
{
    this->skills.push_back(Skill(SKILLS::HP));
    this->skills.push_back(Skill(SKILLS::SP));
    this->skills.push_back(Skill(SKILLS::DEF));
    this->skills.push_back(Skill(SKILLS::ATK));
    this->skills.push_back(Skill(SKILLS::POW));
}




SkillComponent::~SkillComponent()
{
    
    

}


const int SkillComponent::getSkill(const int skill) const
{
    if(skills.empty() || skill < 0 || skill > this->skills.size())
        throw std::runtime_error("ERROR CODE SkillComponet:42 || Skill does not exist. Cannot gain Exp");
    else
        return this->skills[skill].getlevel();
}

const void SkillComponent::gainExp(const int skill, const int exp)
{
    if(skills.empty() || skill < 0 || skill > this->skills.size())
        std::cout << ("ERROR CODE SkillComponet:42 || Skill does not exist. Cannot gain Exp") << std::endl;
        throw std::runtime_error("ERROR CODE SkillComponet:42 || Skill does not exist. Cannot gain Exp");
       
    if(skills.empty() == true)
        return this->skills[skill].gainexp(exp);

}

