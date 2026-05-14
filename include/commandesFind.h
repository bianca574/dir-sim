#ifndef COMMANDESFIND_H
#define COMMANDESFIND_H
#include <stdbool.h>
#include <regex.h>

// aide : https://nicolasj.developpez.com/articles/regex/

typedef struct
{
    bool dossiers_seulement; // option -d
    bool fichiers_seulement; // option -f
    bool sous_mot;           // option -s
    const char *sous_mot_val;
    const char *nom;
    bool regex_active; // option -r
    regex_t regex_compile;
} OptionFind;

void find(int argc, char **argv);

#endif