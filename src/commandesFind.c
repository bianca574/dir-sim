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
    if (opt->regex_active && regexec(&opt->regex_compile, no->nom, 0, NULL, 0) != 0)
    {
        return false;
    }
    return true;
}

static int find_aux(noeud *no, const OptionFind *opt)
{
    if (no == NULL)
    {
        return 0;
    }
    int compteur = 0;

    if (no != no->racine && correspond(no, opt))
    {
        pwd_noeud(no);
        printf("\n");
        compteur++;
    }
    liste_noeud *liste = no->fils;

    while (liste != NULL)
    {
        compteur += find_aux(liste->no, opt);
        liste = liste->succ;
    }
    return compteur;
}

void find(int argc, char **argv)
{
    if (argc == 0)
    {
        printf("Usage : find [-d|-f] [-r regex] [-s sous_mot] [nom]\n");
        return;
    }
    OptionFind opt;
    memset(&opt, 0, sizeof(opt));

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
                erreur();
                printf("-s attend un sous-mot.\n");
                exit(1);
            }
            opt.sous_mot = true;
            opt.sous_mot_val = argv[i];
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            i++;
            if (i >= argc)
            {
                erreur();
                printf("-r attend une expression régulière.\n");
                exit(1);
            }
            int ret = regcomp(&opt.regex_compile, argv[i], REG_EXTENDED);
            if (ret != 0)
            {
                char errbuf[100];
                regerror(ret, &opt.regex_compile, errbuf, sizeof(errbuf));
                erreur();
                printf("Expression régulière invalide : %s\n", errbuf);
                exit(1);
            }
            opt.regex_active = true;
        }
        else
        {
            opt.nom = argv[i];
        }
        if (opt.dossiers_seulement && opt.fichiers_seulement)
        {
            erreur();
            printf("-d et -f sont incompatibles.\n");
            if (opt.regex_active)
            {
                regfree(&opt.regex_compile);
            }
            exit(1);
        }
    }
    int compteur = find_aux(noeudCourant->racine, &opt);
    if (compteur == 0)
    {
        printf("Aucune expression trouvée.\n");
    }
    if (opt.regex_active)
    {
        regfree(&opt.regex_compile);
    }
}