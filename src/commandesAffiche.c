#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dataNode.h"
#include "commandesAffiche.h"

#include "ouvrirFichier.h"

// on peut mettre chemin absolu ou relatif ou pas d'argument (noeud courant)
int ls(const char *nom)
{
    liste_noeud *copie;

    if (strcmp(nom, "") == 0)
    {
        copie = noeudCourant->fils;
    }
    else
    {
        noeud *noeudALs = trouver_noeud(nom);
        if (noeudALs == NULL)
        {
            erreur();
            printf("Le chemin %s n'existe pas\n", nom);
            return ERREUR_EXECUTION;
        }
        copie = noeudALs->fils;
    }

    while (copie != NULL)
    {
        printf("%s \n", copie->no->nom);
        copie = copie->succ;
    }
    return OK;
}

// fonction auxiliaire pour remonter le noeud no jusqu'au père
void pwd_noeud(noeud *no)
{
    if (no != no->racine)
    {
        pwd_noeud(no->pere);
        printf("/%s", no->nom); // affichage après pour que ce soit dans le bon ordre
    }
}

void pwd()
{
    noeud *copieNo = noeudCourant;
    if (copieNo == noeudCourant->racine){
        printf("/");
    }
    else {
        pwd_noeud(copieNo);
    }
    printf("\n");
}

// afficher la ligne de "noeud"
void print_noeud(noeud *noeud)
{

    // nom noeud
    if (strcmp(noeud->nom, "\0") != 0)
    {
        printf("Noeud %s ", noeud->nom);
    }
    else
    {
        printf("Noeud / "); // cas racine
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
            printf("pere : %s, ", noeud->pere->nom);
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

// fonction auxiliaire récursive pour print
// affiche le noeud courant puis descend dans chaque fils
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

// affichage qui va en profondeur le plus possible : préfixe
void print()
{
    print_aux(noeudCourant->racine);
}
