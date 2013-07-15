#include <iostream>
#include <cstring>

#define CONF_LENGTH_MAX 30

int replace_configuration_keyword(char* argConf, char* argCouplesKeywordConf, size_t argConfSize) {

    char *saveptr_couples_keyword_conf = NULL, *couple_keyword_conf = NULL;
    char *couple_keyword_conf_duplicated = NULL;
    char *saveptr_word = NULL, *keyword = NULL, *keyword_replacement;
    char *str_duplicated=strdup(argCouplesKeywordConf);
    int cpt = 0;

    if(argConf != NULL && argConf[0] != '\0') {
        
        couple_keyword_conf = strtok_r(str_duplicated, ";", &saveptr_couples_keyword_conf);
        while(couple_keyword_conf != NULL) {
            
            if(couple_keyword_conf[0] != '\0') {
                couple_keyword_conf_duplicated = strdup(couple_keyword_conf);
                
                std::cout << "Couple found: " << couple_keyword_conf_duplicated << std::endl;
                
                keyword = strtok_r(couple_keyword_conf_duplicated,":", &saveptr_word);
                if(keyword != NULL && strncasecmp(argConf, keyword, argConfSize) == 0) {
                    
                    keyword_replacement = strtok_r(NULL,":", &saveptr_word);
                    if(keyword_replacement != NULL && keyword_replacement[0] != '\0') {
                        strncpy(argConf ,keyword_replacement, argConfSize);
                        free(couple_keyword_conf_duplicated);
                        break;
                    }
                }
                free(couple_keyword_conf_duplicated);
            }
            
            cpt++;
            couple_keyword_conf = strtok_r(NULL,";", &saveptr_couples_keyword_conf);
        }
        
        free(str_duplicated);
        
    } else {
        return -1;
    }
    
    return 0;
}

int main()
{
    char conf_1[CONF_LENGTH_MAX+1]="GPRS";
    char str[]="INTERNET:WAP;GPRS:WEB";

    std::cout << "Conf before: " << conf_1 << std::endl;

    if(replace_configuration_keyword(conf_1, str, CONF_LENGTH_MAX) != 0) {
        std::cout << "Replacement did not go well" << std::endl;
    }
    
    std::cout << "Conf after: " << conf_1 << std::endl;
    return 0;
}
