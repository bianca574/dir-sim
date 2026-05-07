#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"
#include "utile.h"
#include "ouvrirFichier.h"
#include "parser.h"

noeud *noeudCourant = NULL;

void init()
{
    noeudCourant = malloc(sizeof(noeud));
    if (noeudCourant == NULL)
    {
        printf("Échec d'allocation\n");
        exit(1);
    }
    noeudCourant->est_dossier = true;
    noeudCourant->nom[0] = '\0';
    noeudCourant->pere = noeudCourant;
    noeudCourant->racine = noeudCourant;
    noeudCourant->fils = NULL;
}

int main(int argc, char **argv)
{

    init();

    if (argc == 1)
    {
        lancerTerminal(); // pas d'arguments : mode terminal interactif
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "--terminal") == 0)
        {
            lancerTerminal();
        }
        else
        {
            ouvrirLeFichier(argv[1]);
        }
    }
    else
    {
        printf("Erreur : Trop d'arguments! Usage : %s [fichier.txt | --terminal]\n", argv[0]);
        exit(1);
    }

    free_noeud(noeudCourant->racine);
    return 0;
}
int mainTest()
{
    init();

    mkdir("Cours");
    mkdir("Td");
    touch("edt");

    cd("Cours");
    mkdir("ProjetC");
    mkdir("Anglais");

    cd("..");
    cd("Td");
    touch("td1");
    touch("td2");

    cd("../Cours/ProjetC");
    mkdir("ok");
    cd("ok");

    cd("../../..");

    print();

    printf("Ls :\n");
    ls("");

    printf("Rm : suppression de Td\n");
    rm("Td/");
    print();

    cd("Cours");
    printf("pwd : ( normalement dans Cours)\n");
    pwd();

    printf("CP :\n");
    cp("ProjetC", "Anglais/nouveau");
    print();

    free_noeud(noeudCourant->racine);

    return 0;
}