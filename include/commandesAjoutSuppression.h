#ifndef COMMANDES_AJOUT_SUPPRESSION_H
#define COMMANDES_AJOUT_SUPPRESSION_H

#include "dataNode.h"

void mkdir(const char *nom);
void touch(const char *nom);
void rm(const char *chem);
void mv(const char *chem1, const char *chem2);

#endif