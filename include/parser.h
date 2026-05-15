#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"
#include "commandesFind.h"

int parserLs(char *ligneSansCommande);
int parserPwd(char *ligneSansCommande);
int parserPrint(char *ligneSansCommande);
int parserMkdir(char *ligneSansCommande);
int parserTouch(char *ligneSansCommande);
int parserCp(char *ligneSansCommande);
int parserCd(char *ligneSansCommande);
int parserRm(char *ligneSansCommande);
int parserMv(char *ligneSansCommande);
int parserFind(char *ligneSansCommande);

#endif