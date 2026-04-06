# CONTRIBUTING


## Commencer à travailler sur une nouvelle branche localement

- checkout develop
- git pull
- checkout -b MaBranche

Remarque : utiliser la notation feature/ajout-contenu ou documentation/ajout-documentation

- Travailler dessus
- git add, git commit -m "messsage"
- git push -u origin MaBranche


## Récupérer une branche distante

- git fetch
- git branch -v -a (pour afficher toutes les noms des branches)
- git checkout -b nomBranche origin/nomBranche


## Récupérer le travail des autres

- git checkout develop
- git pull
- git checkout maBranche
- git merge develop

=> conflits possibles (résoudre)

Remarque : head (chez moi)

+ git add, git commit
+ git merge --continue
Pour annuler le merge : git merge --abort