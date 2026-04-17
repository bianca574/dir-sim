#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

// ajout à la fin de fils
void ajouterFilsANoeudCourant(noeud *parent, noeud *nouveauFils)
{
    if (parent->fils == NULL)
    {
        parent->fils = malloc(sizeof(liste_noeud));
        parent->fils->no = nouveauFils;
        parent->fils->succ = NULL;
    }
    else
    {
        liste_noeud *copie = parent->fils;
        while (copie->succ != NULL)
        {
            copie = copie->succ;
        }
        copie->succ = malloc(sizeof(liste_noeud));
        copie->succ->no = nouveauFils;
        copie->succ->succ = NULL;
    }
}

void free_noeud(noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }
    liste_noeud *copie = noeud->fils;
    while (copie != NULL)
    {
        liste_noeud *suivant = copie->succ;
        free_noeud(copie->no);
        free(copie);
        copie = suivant;
    }
    free(noeud);
}

noeud *trouver_noeud(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0)
    {
        return NULL;
    }

    char *copie_chem = malloc((strlen(chem) + 1) * sizeof(char));

    if (copie_chem == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(1);
    }

    strcpy(copie_chem, chem);

    char *chemin = strtok(copie_chem, "/");

    noeud *actuel = chem[0] == '/' ? noeudCourant->racine : noeudCourant;

    noeud *trouve = actuel;

    while (chemin != NULL)
    {
        if (strcmp(chemin, "..") == 0)
        {
            trouve = actuel->pere;
        }
        else if (strcmp(chemin, ".") == 0)
        {
            trouve = actuel;
        }
        else
        {
            trouve = chercher_fils(actuel, chemin);
        }
        if (trouve == NULL)
        {
            free(copie_chem);
            return NULL;
        }
        chemin = strtok(NULL, "/");

        if (chemin != NULL)
        {
            if (!trouve->est_dossier)
            {
                free(copie_chem);
                return NULL;
            }
            actuel = trouve;
        }
    }
    free(copie_chem);
    return trouve;
}

void separer_chemin(const char *chem, char *nouveau_chem, char *nom_fic)
{
    if (chem == NULL || strlen(chem) == 0)
    {
        return;
    }

    char *copie_chem = malloc((strlen(chem) + 1) * sizeof(char));

    if (copie_chem == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(1);
    }
    strcpy(copie_chem, chem);

    char *dernier_slash = strrchr(copie_chem, '/');

    if (dernier_slash == NULL)
    {
        strcpy(nouveau_chem, ".");
        strcpy(nom_fic, chem);
    }
    else
    {
        strcpy(nom_fic, dernier_slash + 1);

        if (dernier_slash == copie_chem)
        {
            strcpy(nouveau_chem, "/");
        }
        else
        {
            *dernier_slash = '\0';
            strcpy(nouveau_chem, copie_chem);
        }
    }
    free(copie_chem);
}

bool est_ancetre(noeud *potentiel_ancetre, noeud *depart)
{
    noeud *temp = depart;

    while (temp != temp->racine)
    {
        if (temp == potentiel_ancetre)
        {
            return true;
        }
        temp = temp->pere;
    }
    return temp == potentiel_ancetre;
}

noeud *chercher_fils(noeud *parent, const char *nom)
{
    if (parent == NULL)
    {
        return NULL;
    }

    liste_noeud *liste = parent->fils;

    while (liste != NULL)
    {
        if (strcmp(liste->no->nom, nom) == 0)
        {
            return liste->no;
        }
        liste = liste->succ;
    }
    return NULL;
}

void retirer_fils(noeud *parent, noeud *cible)
{
    if (parent == NULL || parent->fils == NULL || cible == NULL)
    {
        return;
    }

    liste_noeud *courant = parent->fils;
    liste_noeud *precedent = NULL;

    while (courant != NULL && courant->no != cible)
    {
        precedent = courant;
        courant = courant->succ;
    }
    if (courant != NULL)
    {
        if (precedent == NULL) // si c'est le premier fils de la liste
        {
            parent->fils = courant->succ;
        }
        else
        {
            precedent->succ = courant->succ;
        }
        free(courant);
    }
}
