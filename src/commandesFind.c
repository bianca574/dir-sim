#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dataNode.h"

#include "commandesAffiche.h"
#include "commandesFind.h"
#include "ouvrirFichier.h"

static bool correspond(noeud *no, const OptionFind *opt) // static pour qu'elle soit visible que dans ce fichier,
                                                         // tout le monde n'a pas besoin de la voir?
{
    if (opt->dossiers_seulement && !no->est_dossier)
    {
        return false;
    }
    if (opt->fichiers_seulement && no->est_dossier)
    {
        return false;
    }
    if (opt->sous_mot && strstr(no->nom, opt->sous_mot_val) == NULL)
    {
        return false;
    }
    if (opt->nom != NULL && strcmp(no->nom, opt->nom) != 0)
    {
        return false;
    }
    return true;
}

static void find_aux(noeud *no, const OptionFind *opt)
{
    if (no == NULL)
    {
        return;
    }
    if (correspond(no, opt))
    {
        pwd(no);
        printf("\n");
    }
    liste_noeud *liste = no->fils;
    while (liste != NULL)
    {
        find_aux(liste->no, opt);
        liste = liste->succ;
    }
}

void find(int argc, char **argv)
{
    if (argc == 0)
    {
        printf("Usage : find [-d|-f] [-s sous_mot] [nom]\n");
        return;
    }
    OptionFind opt = {false, false, false, NULL, NULL};

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            opt.dossiers_seulement = true;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            opt.fichiers_seulement = true;
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            i++; // le prochain arg est le sous-mot
            if (i >= argc)
            {
                printf("Erreur : -s attend un sous-mot.\n");
                exit(1);
            }
            opt.sous_mot = true;
            opt.sous_mot_val = argv[i];
        }
        else
        {
            opt.nom = argv[i];
        }
        if (opt.dossiers_seulement && opt.fichiers_seulement)
        {
            printf("Erreur : -d et -f sont incompatibles.\n");
            exit(1);
        }
    }
    find_aux(noeudCourant->racine, &opt);
}