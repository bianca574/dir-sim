#ifndef OUVRIRFICHIER_H
#define OUVRIRFICHIER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"
#include "parser.h"


int ouvrirLeFichier();
void erreur();

struct gestionErreur {
    int numero_ligne;
    char instruction_commande[500];
};

extern struct gestionErreur gestionErreur;

#endif