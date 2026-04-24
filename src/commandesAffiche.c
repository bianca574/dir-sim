#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dataNode.h"
#include "commandesAffiche.h"
#include "ouvrirFichier.h"

void ls()
{
    liste_noeud *copie = noeudCourant->fils;
    while (copie != NULL)
    {

        printf("%s \n", copie->no->nom);
        copie = copie->succ;
    }
}

void pwd_noeud(noeud *no)
{
    if (no != no->racine)
    {
        pwd_noeud(no->pere);
        printf("/%s", no->nom);
    }
}

void pwd()
{
    noeud *copieNo = noeudCourant;
    pwd_noeud(copieNo);
    printf("\n");
}

void print_noeud(noeud *noeud)
{

    // nom noeud
    if (strcmp(noeud->nom, "\0") != 0)
    {
        printf("Noeud %s ", noeud->nom);
    }
    else
    {
        printf("Noeud / ");
    }
    if (noeud->est_dossier)
    {
        printf("(D), ");
    }
    else
    {
        printf("(F), ");
    }

    // pere
    if (noeud != noeud->racine)
    {
        if (strcmp(noeud->pere->nom, "\0") == 0)
        {
            printf("pere : /, ");
        }
        else
        {
            printf("pere : %s ", noeud->pere->nom);
        }
    }

    // fils
    printf("fils : ");
    liste_noeud *copie = noeud->fils;
    while (copie != NULL)
    {
        printf("%s", copie->no->nom);
        if (copie->no->est_dossier)
        {
            printf("(D)");
        }
        else
        {
            printf("(F)");
        }
        if (copie->succ != NULL)
        {
            printf(", ");
        }
        copie = copie->succ;
    }
}

void print_aux(noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }
    print_noeud(noeud);
    printf("\n");
    liste_noeud *copie = noeud->fils;
    while (copie != NULL)
    {
        print_aux(copie->no);

        copie = copie->succ;
    }
}

// affichage qui va en profndeur le plus possible : préfixe ?
void print()
{
    print_aux(noeudCourant->racine);
}
