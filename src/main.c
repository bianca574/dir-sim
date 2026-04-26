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

int main(int argc, char **argv){
    
    init();
    //mkdir("Cours");
    //cd ("Cours");
    //touch("copie");
    //mkdir("ok");
    //cd ("..");

    if (argc == 1){
        ouvrirLeFichier("monfichier.txt"); 
    }
    else if (argc != 2){
        printf("Erreur: le programme prend un seul argument");
        exit(1);
    } else {
        ouvrirLeFichier(argv[1]);
    }
    
    free_noeud(noeudCourant->racine);
    return 0;
    
}
int main2()
{
    init();
    printf("Début :\n");
    ls();

    printf("\nAjout d'un dossier:\n");
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
    
    cd ("../../");
    ls();

    pwd();

    print();

    //test rm
    printf("\nTest RM\n");
    cd("/");
    rm("edt");
    print();

    printf("\nTest MV\n");
    mv("/Cours/ProjetC/ok", "/OkAtRoot");
    print();

    // printf("\n Test RM soi-même\n");
    // cd("/");
    // cd("/Cours/ProjetC");
    // rm("/Cours/ProjetC");

    // printf("\n Test RM ancêtre \n");
    // cd("/");
    // cd("/Cours/ProjetC");
    // rm("/Cours");

    printf("\nTest RM dossier\n");
    cd("/");
    rm("Td");
    print();

    //tesp pwd
    //pwd();
    
    // test cp
    //cp("ProjetC", "Anglais/nouveau");
    //printf("ajout cp: \n");
    //print();

    free_noeud(noeudCourant->racine);

    return 0;
}