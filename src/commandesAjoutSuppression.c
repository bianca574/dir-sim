#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

#include "commandesAjoutSuppression.h"
#include "ouvrirFichier.h"

// utile seulement pour touch et mkdir

int cheminAbsoluPreparartionCreation(const char *nom, char **chemin, char **dernierNomDossier, noeud **pereDuDossier)
{

    // découpe le chemin pour trouver le pere après
    if (separer_chemin(nom, chemin, dernierNomDossier) != OK){
        return ERREUR_EXECUTION;
    }

    if (chercher_fils(noeudCourant, *dernierNomDossier) != NULL)
    {
        erreur();
        printf("%s existe déjà.\n", *dernierNomDossier);
        free(*chemin);
        free(*dernierNomDossier);
        return ERREUR_EXECUTION;
    }

    *pereDuDossier = trouver_noeud(*chemin); 
    if (*pereDuDossier == NULL)
    {
        erreur();
        printf("Erreur : le dossier %s n'existe pas\n", *chemin);
        free(*chemin);
        free(*dernierNomDossier);
        return ERREUR_EXECUTION;
    }
    return OK;
}
// fonctionne pour chemin absolu et relatif
int mkdir(const char *nom)
{
    char *chemin;
    char *dernierNomDossier;
    noeud *pereDuDossier;
    if (cheminAbsoluPreparartionCreation(nom, &chemin, &dernierNomDossier, &pereDuDossier) != OK){
        return ERREUR_EXECUTION;
    }

    noeud *nouveauDossier;
    nouveauDossier = malloc(sizeof(noeud));
    if (nouveauDossier == NULL)
    {
        printf("Échec d'allocation\n");
        free(chemin);
        free(dernierNomDossier);
        return ERREUR_EXECUTION;
    }
    nouveauDossier->est_dossier = true;
    strncpy(nouveauDossier->nom, dernierNomDossier, 99);
    nouveauDossier->nom[99] = '\0';
    nouveauDossier->pere = pereDuDossier;
    nouveauDossier->racine = noeudCourant->racine;
    nouveauDossier->fils = NULL;

    ajouterFilsANoeudCourant(nouveauDossier, pereDuDossier);

    free(chemin);
    free(dernierNomDossier);
    return OK;
}

int nomIncorrect(const char *nom)
{
    if (nom[0] == '\0')
    {
        erreur();
        printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier est vide. Changez le !!\n");
        return ERREUR_EXECUTION;
    }
    if (strlen(nom) > 99)
    {
        erreur();
        printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier est trop long. Changez le !!\n");
        return ERREUR_EXECUTION;;
    }
    int i = 0;
    while (nom[i] != '\0')
    {
        if (!(nom[i] >= 'a' && nom[i] <= 'z') && !(nom[i] >= 'A' && nom[i] <= 'Z') && !(nom[i] >= '0' && nom[i] <= '9'))
        {
            erreur();
            printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier ne contient pas que des caractères alpha-numériques. Changez le !!\n");
            return ERREUR_EXECUTION;;
        }
        i++;
    }
    // doublons ?
    liste_noeud *noeudFilsCopie = noeudCourant->fils;

    while (noeudFilsCopie != NULL)
    {
        if (strcmp(nom, noeudFilsCopie->no->nom) == 0)
        {
            erreur();
            printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier existe déja dans ce répertoire. Changez le !!\n");
            return ERREUR_EXECUTION;;
        }
        noeudFilsCopie = noeudFilsCopie->succ;
    }
    return OK;
}

// fonctionne pour chemin absolu et relatif
int touch(const char *nom)
{
    char *chemin;
    char *dernierNomFichier;
    noeud *pereDuDossier;
    if (cheminAbsoluPreparartionCreation(nom, &chemin, &dernierNomFichier, &pereDuDossier)!= OK){
        return ERREUR_EXECUTION;
    }

    if (nomIncorrect(dernierNomFichier) != OK){
        return ERREUR_EXECUTION;
    }

    noeud *nouveaufichier;
    nouveaufichier = malloc(sizeof(noeud));
    if (nouveaufichier == NULL)
    {
        erreur();
        printf("Echec d'allocation du fichier");
        free(chemin);
        free(dernierNomFichier);
        return ERREUR_EXECUTION;
    }
    nouveaufichier->est_dossier = false;
    strncpy(nouveaufichier->nom, dernierNomFichier, 99);
    nouveaufichier->nom[99] = '\0';
    nouveaufichier->pere = pereDuDossier;
    nouveaufichier->racine = noeudCourant->racine;
    nouveaufichier->fils = NULL;

    ajouterFilsANoeudCourant(nouveaufichier, pereDuDossier);

    free(dernierNomFichier);
    free(chemin);
    return OK;
}

int rm(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0 || strcmp(chem, "/") == 0) // interdit la suppression de la racine
    {
        erreur();
        printf("Impossible de supprimer %s.\n", chem);
        return ERREUR_EXECUTION;;
    }

    noeud *cible = trouver_noeud(chem);

    if (cible == NULL)
    {
        erreur();
        printf("le chemin %s n'existe pas.\n", chem);
        return ERREUR_EXECUTION;
    }

    if (est_ancetre(cible, noeudCourant)) // interdit la suppression d'un ancêtre du noeud courant
    {
        erreur();
        printf("Impossible de supprimer %s. \n", chem);
        return ERREUR_EXECUTION;
    }
    retirer_fils(cible->pere, cible);
    free_noeud(cible);

    return OK;
}

// déplace le noeud chem1 vers chem2
int mv(const char *chem1, const char *chem2)
{
    noeud *cible = trouver_noeud(chem1);
    if (cible == NULL)
    {
        erreur();
        printf("Le chemin %s n'existe pas.\n", chem1);
        return ERREUR_EXECUTION;
    }
    char *parent_dest_chem = NULL;
    char *nouveau_nom = NULL;

    noeud *chem2_noeud = trouver_noeud(chem2);

    if (chem2_noeud != NULL && chem2_noeud->est_dossier) // si chem2 est un dossier existant, on déplace dedans
    {
        nouveau_nom = malloc(strlen(cible->nom) + 1);
        if (nouveau_nom == NULL)
        {
            printf("Erreur malloc.\n");
            return ERREUR_EXECUTION;
        }
        strcpy(nouveau_nom, cible->nom);
    }
    else // si la destination est un chemin vers un nouveau noeud
    {
        if (separer_chemin(chem2, &parent_dest_chem, &nouveau_nom)!= OK){
            return ERREUR_EXECUTION;
        } // on découpe pour trouver son nom (après le dernier /) et son père
        chem2_noeud = trouver_noeud(parent_dest_chem);
    }

    noeud *dest_parent = chem2_noeud; // dossier de destination

    if (dest_parent == NULL || !dest_parent->est_dossier)
    {
        erreur();
        printf("La destination %s n'est pas un dossier valide.\n", chem2);
        free(parent_dest_chem);
        free(nouveau_nom);
        return ERREUR_EXECUTION;
    }
    if (est_ancetre(cible, dest_parent))
    {
        erreur();
        printf("Impossible de déplacer un dossier dans lui-même ou un de ses fils.\n");
        free(parent_dest_chem);
        free(nouveau_nom);
        return ERREUR_EXECUTION;;
    }
    if (chercher_fils(dest_parent, nouveau_nom))
    {
        erreur();
        printf("%s existe déja dans ce dossier.\n", nouveau_nom);
        free(parent_dest_chem);
        free(nouveau_nom);
        return ERREUR_EXECUTION;;
    }
    retirer_fils(cible->pere, cible); // détache la cible de son ancien père

    strcpy(cible->nom, nouveau_nom);

    ajouterFilsANoeudCourant(cible, dest_parent); // attache la cible au nouveau père

    cible->pere = dest_parent; // met à jour le lien père

    free(parent_dest_chem);
    free(nouveau_nom);
    return OK;
}

// fonction auxiliaire pour copier le no_a_cp au pere
int cp_noeud(noeud *no_a_cp, noeud *pere, noeud **resultat)
{
    noeud *copie_de_no;
    copie_de_no = malloc(sizeof(noeud));
    if (copie_de_no == NULL){
        printf("Erreur de malloc");
        return ERREUR_EXECUTION;
    }
    copie_de_no->est_dossier= no_a_cp->est_dossier;
    copie_de_no->racine = no_a_cp-> racine;
    strcpy(copie_de_no->nom, no_a_cp->nom);
    ajouterFilsANoeudCourant(copie_de_no, pere);
    
    copie_de_no->fils = NULL;
    liste_noeud *copie_de_fils = no_a_cp->fils;

    while(copie_de_fils != NULL){

        cp_noeud(copie_de_fils->no, copie_de_no, NULL);
        copie_de_fils = copie_de_fils->succ;
    }
    if (resultat != NULL){
        *resultat = copie_de_no; 
    }
    return OK;
}

int verifier_doublon(noeud *dest, const char *nom)
{
    liste_noeud *f = dest->fils;

    while (f != NULL)
    {
        if (strcmp(f->no->nom, nom) == 0)
        {
            erreur();
            printf("Attention %s existe déjà dans le dossier.\n", nom);
            return ERREUR_EXECUTION;;
        }
        f = f->succ;
    }
    return OK; 
}

noeud *verifier_destination(const char *chemin)
{
    noeud *dest = trouver_noeud(chemin);

    if (dest == NULL || !dest->est_dossier)
    {
        erreur();
        printf("Attention le dernier nom du chemin %s n'est pas correct (pas un dossier ou n'existe pas)\n", chemin);
        return NULL;
    }

    return dest;
}
int verifier_sous_arbre(noeud *depart, noeud *dest)
{
    noeud *tmp = dest;

    while (tmp != tmp->pere)
    {
        if (tmp == depart)
        {
            erreur();
            printf("Le chemin se trouve dans le sous-arbre.\n");
            return ERREUR_EXECUTION;
        }
        tmp = tmp->pere;
    }
    return OK;
}

int cp(const char *chem1, const char *chem2)
{
    noeud *chemin1 = trouver_noeud(chem1);
    if (chemin1 == NULL)
    {
        erreur();
        printf("Le chemin %s n'est pas correct.", chem1);
        return ERREUR_EXECUTION;;
    }

    char *chemin;
    char *nom;

    // dans nom = nom du dossier/fichier
    // chemin = s'arrête au père
    if (separer_chemin(chem2, &chemin, &nom)){
        return ERREUR_EXECUTION;
    }

    noeud *dest = verifier_destination(chemin);
    if (dest == NULL) {
        free(chemin);
        free(nom);
        return ERREUR_EXECUTION;
    }
    if( verifier_doublon(dest, nom) != OK){
        free(chemin);
        free(nom);
        return ERREUR_EXECUTION;
    }

    if( verifier_sous_arbre(chemin1, dest)){
        free(chemin);
        free(nom);
        return ERREUR_EXECUTION;
    }
    noeud *copie ;
    int err = cp_noeud(chemin1, dest, &copie);
    strcpy(copie->nom, nom);

    free(chemin);
    free(nom);
    return err;
}
