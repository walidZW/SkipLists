#include <stdio.h>
#include <stdlib.h>
#include "mylibLLC.h"

int main()
{
    int nombres[12]={4,7,11,16,19,21,25,33,42,68,101,234};
maillon *p;
lect_llc(&p,12,nombres);
ins_pos(&p,9,40);
printf("********VOICI LA LISTE QUI CONTIENT LES MEME VALEURS QUE NOTRE SKIPLIST********");
printf("\n");
show_LLC(p);

printf("\n\n");
printf("/ / / /POUR L'INSERTION DE LA MEME VALEUR DANS UNE SIMPLE LISTE ON EST PASSE PAR %d MAILLONS / / / ", ins_pos(&p,9,40));


printf("\n\n");
printf("/ / / POUR LA SUPRESSION DE LA MEME VALEUR 68 ON EST PASSE PAR %d MAILLONS/ / /", suppr_pos(&p,11));
 }

