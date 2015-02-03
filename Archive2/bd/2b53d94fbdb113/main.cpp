struct Job {
int health_gain;
//int mana_gain;

int threat_shed = 0;
int threat_gain = 0;

bool sword_mastery = false;
bool axe_mastery = false;
bool dagger_mastery = false;
bool hammer_mastery = false;
bool bow_mastery = false;
bool staff_mastery = false;
bool shield_mastery = false;

bool wear_heavy = false;
bool wear_light = true ;

//berserker secret
bool twoh_mastery = false;

/*
bool spell_apprentice;
bool spell_journeyman;
bool spell_master;
*/

};

int main()
{
    Job warrior;
    warrior.health_gain = 10;
    warrior.threat_gain = 3;
    warrior.sword_mastery = true;
    warrior.axe_mastery = true;
    warrior.bow_mastery = true;
    warrior.staff_mastery = true;
    warrior.hammer_mastery = true;
    warrior.dagger_mastery = true;
    warrior.wear_heavy = true;
    
    //rogue
    Job rogue;
    rogue.health_gain = 7;
    rogue.threat_shed = 3;
    rogue.sword_mastery = true;
    rogue.dagger_mastery = true;
    
    //knight
    Job knight;
    knight.health_gain = 20;
    knight.threat_gain = 5;
    knight.sword_mastery = true;
    knight.hammer_mastery = true;
    knight.shield_mastery = true;
    knight.wear_heavy = true;
    knight.wear_light = false;
    
    //berserker
    Job berserker;
    berserker.health_gain = 20;
    berserker.threat_gain = 3;
    berserker.axe_mastery = true;
    berserker.sword_mastery = true;
    berserker.hammer_mastery = true;
    berserker.twoh_mastery = true;
    
    
    //Range
    Job ranger;
    ranger.health_gain = 5;
    ranger.bow_mastery = true;
    ranger.dagger_mastery = true;

    return 0;
}