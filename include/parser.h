#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"
#include "commandesFind.h"

void parserLs(char *ligneSansCommande);
void parserPwd(char *ligneSansCommande);
void parserPrint(char *ligneSansCommande);
void parserMkdir(char *ligneSansCommande);
void parserTouch(char *ligneSansCommande);
void parserCp(char *ligneSansCommande);
void parserCd(char *ligneSansCommande);
void parserRm(char *ligneSansCommande);
void parserMv(char *ligneSansCommande);
void parserFind(char *ligneSansCommande);

#endif