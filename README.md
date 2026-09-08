# C DirSim - Groupe 29 (Mars - Mai 2026)

Simulateur de système de fichiers UNIX implémenté en C.

Projet réalisé en collaboration avec Agnès KOCIK dans le cadre de ma deuxième année de licence.

## Compiler et afficher le projet

```bash
make program && ./program
```

Pour réinitialiser :

```bash
make clean && make program && ./program
```

## Mode interactif

Sans paramètre, le projet ouvrira le terminal interactif.

## Avec paramètre

On peut choisir :

```bash
make program && ./program tests/fichierPDF.txt
```

```bash
make program && ./program --terminal
```

## Noms des fichiers tests :

- fichierPDF.txt (copie de celui donné dans l'énoncé du projet)
- fichier1.txt
- fichier2.txt
- fichier3.txt (provoque une erreur pour voir la réaction face à une erreur dans un fichier)
- fichier4.txt (réagit à une erreur)
- fichier5.txt (provoque une erreur et réagit à une erreur)

## Valgrind

```bash
valgrind --leak-check=full ./program
```

## Documentation

- CONTRIBUTING : reglès et procédure pour contribuer au projet
- AUTHORS : auteurs du projet
- LICENSE : licence du projet
