# Projet_langage_C_groupe_29



##  Compiler et afficher le projet

```bash
make program && ./program
```
Pour réinitialiser :
```bash
make clean && make program && ./program
```

Remarque :
Sans paramètre, le projet utilisera le fichier fichierPDF.txt
Si on veut choisir :
```bash
make program && ./program fichierPDF.txt
```
Noms des fichiers tests:
- fichierPDF.txt (copie de celui donné dans l'énoncé du projet)
- fichier1.txt
- fichier2.txt
- fichier3.txt (provoque une erreur pour voir réaction face à une erreur dans un fichier)


## Valgrind

```bash
valgrind --leak-check=full ./program
```