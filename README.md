# Projet_langage_C_groupe_29



##  Compiler et afficher le projet

```bash
make program && ./program
```
Pour réinitialiser :
```bash
make clean && make program && ./program
```

## Remarque :

Sans paramètre, le projet ouvrira le terminal interactif.

Si on veut choisir :
```bash
make program && ./program fichierPDF.txt
```
```bash
make program && ./program --terminal
```
Noms des fichiers tests :
- fichierPDF.txt (copie de celui donné dans l'énoncé du projet)
- fichier1.txt
- fichier2.txt
- fichier3.txt (provoque une erreur pour voir réaction face à une erreur dans un fichier)
- fichier4.txt
- fichier5.txt


## Valgrind

```bash
valgrind --leak-check=full ./program
```