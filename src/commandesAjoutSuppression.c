#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

#include "commandesAjoutSuppression.h"

void mkdir(const char *nom)
{   
    if (chercher_fils(noeudCourant, nom) != NULL)
    {
        printf("Attention : un dossier avec ce nom existe déjà.\n");
        exit(1);
    }
    noeud *nouveauDossier;
    nouveauDossier = malloc(sizeof(noeud));
    if (nouveauDossier == NULL)
    {
        printf("Échec d'allocation\n");
        exit(1);
    }
    nouveauDossier->est_dossier = true;
    strncpy(nouveauDossier->nom, nom, 99);
    nouveauDossier->nom[99] = '\0';
    nouveauDossier->pere = noeudCourant;
    nouveauDossier->racine = noeudCourant->racine;
    nouveauDossier->fils = NULL;

    ajouterFilsANoeudCourant(nouveauDossier, noeudCourant);
}

void nomInvalide(const char *nom){
    if (nom[0] == '\0')
    {
        printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier est vide. Changez le !!\n");
        exit(1);
    }
    if (strlen(nom) > 99)
    {      
        printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier est trop long. Changez le !!\n");
        exit(1);
    }
    int i = 0;
    while (nom[i] != '\0')
    {
        if (!(nom[i] >= 'a' && nom[i] <= 'z') && !(nom[i] >= 'A' && nom[i] <= 'Z') && !(nom[i] >= '0' && nom[i] <= '9'))
        {
            printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier ne contient pas que des caractères alpha-numériques. Changez le !!\n");
            exit(1);
        }
        i++;
    }
      // doublons ?
    liste_noeud *nfils_copie = noeudCourant->fils;

    while (nfils_copie != NULL)
    {
        if (strcmp(nom, nfils_copie->no->nom) == 0)
        {
            printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier existe déja dans ce répertoire. Changez le !!\n");
            exit(1);
        }
        nfils_copie = nfils_copie->succ;
    }

}

void touch(const char *nom)
{    nomInvalide(nom);
    
    // création fichier
    if (chercher_fils(noeudCourant, nom) != NULL)
    {
        printf("Erreur : Un fichier avec ce nom existe déjà.\n");
        exit(1);
    }

    noeud *nouveaufichier;
    nouveaufichier = malloc(sizeof(noeud));
    if (nouveaufichier == NULL)
    {
        printf("Echec d'allocation du fichier");
        exit(1);
    }
    nouveaufichier->est_dossier = false;
    strncpy(nouveaufichier->nom, nom, 99);
    nouveaufichier->nom[99] = '\0';
    nouveaufichier->pere = noeudCourant;
    nouveaufichier->racine = noeudCourant->racine;
    nouveaufichier->fils = NULL;

    ajouterFilsANoeudCourant(nouveaufichier, noeudCourant);
}

void rm(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0 || strcmp(chem, "/") == 0)
    {
        printf("Erreur : impossible de supprimer les dossiers/fichiers indiqués.\n");
        exit(1);
    }

    noeud *cible = trouver_noeud(chem);

    if (cible == NULL)
    {
        printf("Erreur : le chemin n'existe pas.\n");
        exit(1);
    }
    
    if (est_ancetre(cible, noeudCourant))
    {
        printf("Erreur : Impossible de supprimer les dossiers/fichiers indiqués.\n");
        exit(1);
    }
    retirer_fils(cible->pere, cible);
    free_noeud(cible);
}

void mv(const char *chem1, const char *chem2)
{
    noeud *cible = trouver_noeud(chem1);
    if (cible == NULL)
    {
        printf("Erreur : Le chemin n'existe pas.\n");
        exit(1);
    }
    char *parent_dest_chem;
    char *nouveau_nom;

    separer_chemin(chem2, &parent_dest_chem, &nouveau_nom);

    noeud *dest_parent = trouver_noeud(parent_dest_chem);
    if (dest_parent == NULL || !dest_parent->est_dossier)
    {
        printf("Erreur : La destination n'est pas un dossier valide.\n");
        exit(1);
    }
    if (est_ancetre(cible, dest_parent))
    {
        printf("Erreur : Impossible de déplacer un dossier dans lui-même ou un de ses fils.\n");
        exit(1);
    }
        if (chercher_fils(dest_parent, nouveau_nom))
    {
        printf("Erreur : Le dossier/fichier que vous voulez déplacer existe déja dans ce dossier.\n");
        exit(1);
    }
    retirer_fils(cible->pere, cible);

    strcpy(cible->nom, nouveau_nom);

    ajouterFilsANoeudCourant(cible, dest_parent);

    cible->pere = dest_parent;

    free(parent_dest_chem);
    free(nouveau_nom);
}


noeud* cp_noeud(noeud *no_a_cp, noeud *pere){
    noeud *copie_de_no;
    copie_de_no= malloc(sizeof(noeud));
    if (copie_de_no==NULL){
        printf("Erreur de malloc");
        exit(1);
    }
    copie_de_no->est_dossier = no_a_cp->est_dossier;
    copie_de_no->racine = no_a_cp->racine;
    strcpy(copie_de_no->nom, no_a_cp->nom);
    ajouterFilsANoeudCourant(copie_de_no,pere);
    

    copie_de_no->fils= NULL;
    liste_noeud *copie_des_fils = no_a_cp->fils;

    while (copie_des_fils!= NULL){
        cp_noeud(copie_des_fils->no, copie_de_no);        
        copie_des_fils= copie_des_fils->succ;
    }
    return copie_de_no;


}


void verifier_doublon(noeud *dest, const char *nom)
{
    liste_noeud *f = dest->fils;

    while (f != NULL)
    {
        if (strcmp(f->no->nom, nom) == 0)
        {
            printf("Attention le nom existe déjà dans le dossier\n");
            exit(1);
        }
        f = f->succ;
    }
}

noeud* verifier_destination(const char *chemin)
{
    noeud *dest = trouver_noeud(chemin);

    if (dest == NULL || !dest->est_dossier)
    {
        printf("Attention le dernier nom du chemin chem2 n'est pas correct (pas un dossier ou n'existe pas)\n");
        exit(1);
    }

    return dest;
}
void verifier_sous_arbre(noeud *source, noeud *dest)
{
    noeud *tmp = dest;

    while (tmp != tmp->pere)
    {
        if (tmp == source)
        {
            printf("Attention le chemin se trouve dans le sous-arbre\n");
            exit(1);
        }
        tmp = tmp->pere;
    }
}

void cp(const char *chem1, const char *chem2){
    noeud *bon_chemin1 = trouver_noeud(chem1);
    if (! bon_chemin1){
        printf("Le premier chemin n'est pas correct");
        exit(1);
    }

    char *chemin;
    char *nom;

    separer_chemin(chem2, &chemin, &nom);

    noeud *dest = verifier_destination(chemin);
    verifier_doublon(dest, nom);
    verifier_sous_arbre(bon_chemin1, dest);

    noeud *copie = cp_noeud(bon_chemin1, dest);
    strcpy(copie->nom, nom);

    free(chemin);
    free(nom);

}
