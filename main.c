/************************************ZAOUI WALID - CHAIBI ALAADINE - 1CPI G06 *******************************************/
//                                                                                                                      //
/*                                                                                       //
//                                                                                                      //
//                                                                                               //
//                                                                                                    //
//                                                                                                       //
//                                                                                       //
//                                                                                                                      */
//                                                                                                                      //
//                                                                                                                      //
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  1-IMPLEMENTATION  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>



/*---------------------------------------------la déclaration des structres---------------------------------------------*/

typedef struct porte_de_skiplist {   //Chaque skiplist contient une structure au début [avant la tête] ,on la considére comme l'outil de l'accés à notre skiplist.Elle contient les élèments suivants:
    int niveau;             // 1-Le plus grand niveau actuel
    struct maillon_de_sikiplist *tete;  //2-un ponteur vers la tete de notre skiplist [la tête de la skiplist est aussi un maillon mais qui n'a ni symbole ni valeur, elle a juste un tableau de pointeurs vers les maillon suivants]
} porte;


typedef struct maillon_de_sikiplist {//Chaque maillon de notre skiplist contient les élèments suivants :
    int symbole;                                        //    1-la valeur.
    int valeur;                                         //    2-Un symbole qui le spécifie [on a utilisé le symbole pour faciliter l'accés aux élèments de la skiplist]
    struct maillon_de_sikiplist **tableau;              //    3-Un tableau qui contient des pointeurs vers les maillons de la skiplist.
} maillon;

/*------------------------------------les fonctions et les procédures de l'implementation-------------------------------*/

const int niveau_maximal=10;    //le niveau maximale de la skiplist est une constante

/* UNE FONCTION QUI ALLOUE UN NOUVEAU MAILLON ET RETOURNE SON POINTEUR */
maillon *allouer_maillon(void){
return ((maillon*)malloc(sizeof(maillon)));};


/* UNE PROCEDURE DE LIBERATION D'UN MAILLON DANS UNE SKIPLIST */
 void liberer_maillon(maillon*s) {

        free(s->tableau);
        free(s);

}

/* UNE FONCTION QUI COMMENCE UNE NOUVELLE SKIPLIST ET RETOURNE LE POINTEUR VERS SON PORTE*/
porte *nouvelle_liste(porte *L) {
    int i;
    maillon *p;

    p = allouer_maillon();
    (*L).tete = p;
    (*p).tableau = (maillon **) malloc(sizeof(maillon*) * (niveau_maximal + 1));//l'allocation dynamique d'un tableau
    for (i = 0; i <= niveau_maximal; i++) {
        (*p).tableau[i] = p;
    }
    (*L).niveau = 1;
    return L;
}

/* UNE FONCTION QUI GENERE ALEATOIREMENT UN NIVEAU , ELLE REPRESENTE L'OPERATION PILE OU FACE */
int pile_face() {
    int niveau = 1;

    while (rand() % 2 == 0 && niveau < niveau_maximal){
        niveau++;}
    return niveau;
}


/*UNE PROCEDURE QUI AFFICHE LES ELEMENTS D'UN NIVEAU PRESCIS*/
 void afficher_niveau(porte *L,int nb) {
    maillon *s;

    s=(*L).tete;
    while (s && (*s).tableau[nb+1] != (*L).tete) {
        printf("S:%d|V:[%d]-->", (*(*s).tableau[nb+1]).symbole, (*(*s).tableau[nb+1]).valeur); // S designe le symbole et V designe la valeur
        s = (*s).tableau[nb+1];
    }
    printf("NULL\n");
}


/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 2-INSERTION ET SUPRESSION &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/* LA PROCEDURE D'INSERTION D'UN ELEMENT DANS UNE SKIPLIST  */
int insertion(porte *L, int symbole, int valeur) {
    maillon*temp[niveau_maximal + 1]; // temp est un tableau temporaire , on met dans ce tableau
    maillon*s;
    int niveau;
    int i;
    int cpt=0;
    s = (*L).tete;
    for (i = (*L).niveau; i >= 1; i--) {
        while ((*(*s).tableau[i]).symbole < symbole)
            s = (*s).tableau[i];
            temp[i] = s;
            cpt++;
    }
    s = (*s).tableau[1];

    if (symbole == (*s).symbole) {
       (*s).valeur = valeur;} else {
        niveau = pile_face();
        if (niveau > (*L).niveau) {
            for (i = (*L).niveau + 1; i <= niveau; i++) {
                temp[i] = (*L).tete;
            }
        (*L).niveau = niveau;
        }

        s = allouer_maillon();
        (*s).tableau = (maillon*) malloc(sizeof(maillon) * (niveau +  1));
        (*s).symbole = symbole; (*s).valeur = valeur;


        for (i = 1; i <= niveau; i++) {
            (*s).tableau[i] = (*temp[i]).tableau[i];
            (*temp[i]).tableau[i] = s;
        }
    }
    return cpt;
}

/* LA PROCEDURE DE SUPRESSION D'UN ELEMENT DANS UNE SKIPLIST */
int supression(porte *L, int symbole) {
    int i;
    int cpt=0;
    maillon* temp[niveau_maximal + 1];
    maillon* s;


    s = (*L).tete;
    for (i = (*L).niveau; i >= 1; i--) {
        while ((*(*s).tableau[i]).symbole < symbole)
            s = (*s).tableau[i];
            temp[i] = s;
            cpt++;
    }

    s = (*s).tableau[1];
    if ((*s).symbole == symbole) {
        for (i = 1; i <= (*L).niveau; i++) {
            if ((*temp[i]).tableau[i] != s)
             break;
            (*temp[i]).tableau[1] = (*s).tableau[i];
        }
       liberer_maillon(s);

        while ((*L).niveau > 1 && (*(*L).tete).tableau[(*L).niveau]== (*L).tete)
           (*L).niveau=(*L).niveau - 1 ;
    }
   return cpt;
}

/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&3-PROGRAMME PRINCIPALE&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
int main() {

    porte L;

    nouvelle_liste(&L);/*on insere dans cette liste les valeurs suivants par ordre : 4,7,11,16,19,21,25,33,42,68,101,234*/
    insertion(&L,1,4);/* et on donne les symbole suivants : 1,2,3,4,5,6,7,8,9,10,11,12*/
    insertion(&L,2,7);
    insertion(&L,3,11);
    insertion(&L,4,16);
    insertion(&L,5,19);
    insertion(&L,6,21);
    insertion(&L,7,25);
    insertion(&L,8,33);
    insertion(&L,10,42);
    insertion(&L,11,68);
    insertion(&L,12,101);
    insertion(&L,13,234);

    printf("**********************VOICI LA SKIPLIST*******************************\n\n");

    insertion(&L,9,40);// pour l'insertion de la valeur 40 qui porte le symbole 9

    printf("NIVEAU 0\n");
    afficher_niveau(&L,0);
    printf("NIVEAU 1\n");
    afficher_niveau(&L,1);
    printf("NIVEAU 2\n");
    afficher_niveau(&L,2);
    printf("NIVEAU 3\n");
    afficher_niveau(&L,3);
    printf("NIVEAU 4\n");
    afficher_niveau(&L,4);
    printf("NIVEAU 5\n");
    afficher_niveau(&L,5);
    printf("NIVEAU 6\n");
    afficher_niveau(&L,6);

    printf("\n\n");
    printf("/ / /POUR L'INSERTION DE LA VALEUR 40 ON EST PASSE PAR %d ELEMENTS/ / / /", insertion(&L,9,40));


    supression(&L,11);//pour la supression de la valeur 68 qui porte le symbole 11
    printf("\n");
    printf("************VOICI LA SKIPLIST APRES LA SUPRESSION DE LA VALEUR 68*************");
    printf("\n\n");
    printf("NIVEAU 0\n");
    afficher_niveau(&L,0);
    printf("NIVEAU 1\n");
    afficher_niveau(&L,1);
    printf("NIVEAU 2\n");
    afficher_niveau(&L,2);
    printf("NIVEAU 3\n");
    afficher_niveau(&L,3);
    printf("NIVEAU 4\n");
    afficher_niveau(&L,4);
    printf("NIVEAU 5\n");
    afficher_niveau(&L,5);
    printf("NIVEAU 6\n");
    afficher_niveau(&L,6);
    printf("\n\n");

printf("/ / /POUR LA SUPRESSION DE LA VALEUR 102 ON EST PASSE PAR %d  ELEMENTS / / /", supression(&L,11));

}

/**********************************ZAOUI WALID - CHAIBI ALAADINE - 1CPI G06 ********************************************/
