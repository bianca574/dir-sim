#ifndef COMMANDESFIND_H
#define COMMANDESFIND_H
#include <stdbool.h>

typedef struct
{
    bool dossiers_seulement; // option -d
    bool fichiers_seulement; // option -f
    bool sous_mot;           // option -s
    const char *sous_mot_val;
    const char *nom;
} OptionFind;

void find(int argc, char **argv);

#endif