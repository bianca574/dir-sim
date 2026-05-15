#ifndef COMMANDES_AJOUT_SUPPRESSION_H
#define COMMANDES_AJOUT_SUPPRESSION_H

#include "dataNode.h"

int mkdir(const char *nom);
int touch(const char *nom);
int rm(const char *chem);
int mv(const char *chem1, const char *chem2);
int cp(const char *chem1, const char *chem2);


#endif