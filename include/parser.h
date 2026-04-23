#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"


void parserLs(char *ligneSansCommande);
void parserPwd(char *ligneSansCommande);
void parserPrint(char *ligneSansCommande);
void parserMkdir(char *ligneSansCommande);
void parserTouch(char *ligneSansCommande);