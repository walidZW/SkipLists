#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED


/***********""""""""""""""""""""ZAOUI WALID 1CPIG6 """"""""""""""""""""""""*****************/
typedef struct Maillon {int number; struct Maillon *next }maillon;
int prime(int N){int i,j=1;for (i=2;i<N/2+1;i++){if (N%i==0) {j=0; break;}}return j;} // Fonction Premier
void permut (int* A , int* B) { int tmp; tmp = *A; *A = *B; *B = tmp; } //Fonction Permut

/** Implémentation de la machine abstraite des Listes Linéaires Chainées **/
maillon* Allouer ( ) { return ((maillon*) malloc( sizeof(maillon))); }
void Liberer (maillon* P) { free(P); }
void Aff_Val(maillon *P, int v)  { P->number =v; }
void Aff_Adr(maillon *P, maillon *Q) { P->next = Q; }
maillon *Suivant( maillon *P) { return( P->next ); }
int Valeur(maillon *P) { return(P->number) ; }

/** Création d'une LLC à partir de N données lues **/
void lect_llc ( maillon** head,int nb , int *tableau[] )
{
      int i;   int v;
    maillon* P=NULL;
    maillon* Q=NULL;

    *head=NULL;
    for (i=0;i<nb;i++)
    {

        P=Allouer();
        Aff_Val(P,tableau[i]);
        Aff_Adr(P,NULL);
        if (*head==NULL) { *head=P; } else { Aff_Adr(Q,P); }
        Q=P;
    }
}

/** Intialisation de la LLC avec la valeur v **/
void init_LLC (maillon** head , int v)
{
    *head=Allouer();
    Aff_Val( *head , v);
    Aff_Adr( *head , NULL);
}

/** Afficher une LLC **/
void show_LLC (maillon* head)
{
    maillon* current;
    current=head;
    while (current!=NULL)
    {
        printf("%d\t" , current->number);
        current=current->next;
    }
    printf ("NULL \n");
}

/** Longueur d'une LLC **/
int length_LLC (maillon* head)
{
    int c=0;
    maillon* current;
    current=head;
    while (current!=NULL) {c++; current=current->next;}
    return c;
}

/** Nombre d'occurences de la valeur v dans une LLC **/
int nb_occurences ( maillon* head , int v)
{
    int c=0;
    maillon* current = head;
    while (current!=NULL)
    {
        if (Valeur(current)==v) {c++;}
        current=Suivant(current);
    }
    return c;
}

/** Donner la valeur avec le plus grand nombre d'occurences ainsi que sa fréquence **/
void max_nb_occurences (maillon* head , int* v , int* f)
{
    maillon* P;
    int elem;
    P=head;
    elem=Valeur(P);
    *f=nb_occurences(head , Valeur(P));
    while (P!=NULL)
    {
        if (Valeur(P)!=elem)
        {
            if (nb_occurences(head,Valeur(P)) > *f)
            {
                *f = nb_occurences(head, Valeur(P));
                elem=Valeur(P);
            }
        }
        P=Suivant(P);
    }
    *v = elem;
}

/** Accès par position **/
maillon* acces_pos (maillon *tete , int pos )
{
    int i=1;  maillon *p;  p=tete;
    while((p!=NULL)&&(i!=pos))
    {
        i++;
        p=Suivant(p);
    }
    return p;
}

/** Accès par valeur dans une LLC **/
maillon* acces_val(maillon *tete,int val)
{
    maillon *p;
    p=tete;
    while((Valeur(p)!=val)&&(p!=NULL))
    {
        p=Suivant(p);
    }
    return(p!=NULL)?p:NULL;
}

/** Fonction qui donne la position de l'élément w par rapport à la tete de la LLC **/
int m_pos(maillon *tete,int val)
{
    maillon *w;
    int cpt=1;
    w=tete;
    while(Valeur(w)!=val)
    {
        cpt++;
        w=Suivant(w);
    }
    return cpt;
}

/** Suppresion par position **/
int suppr_pos (maillon** head , int pos)
{
    int cpt;
    maillon* P;
    maillon* prec;
    P=*head;
    if (pos==1)
    {
        if (*head!=NULL)
        {
            *head = Suivant(*head);
            free(P);
        }
    }
    else
    {
        int cpt=1;
        while (cpt<pos && P!=NULL)
        {
            prec=P;
            P=Suivant(P);
            cpt++;
        }
        if (P!=NULL)
        {
            Aff_Adr(prec , Suivant(P));
            free(P);
        }
    }
    cpt=pos-1;
    return cpt;
}

/** Suppression par valeur dans une LLC **/
void suppr_val(maillon **tete,int val)
{
    while(nb_occurences(*tete,val))
    {
        maillon *p,*q;
        p=acces_val(*tete,val);
        q=acces_pos(*tete,m_pos(*tete,val)-1);
        if(p==*tete)
        {
            *tete=Suivant(p);
            free(p);
        }
        else
        {
            Aff_Adr(q,Suivant(p));
            free(p);
        }
    }
}

/** Insérer la valeur v au début de la LLC **/
void insert_start (maillon** head , int v)
{
    maillon* neu;
    neu=Allouer();
    Aff_Val(neu,v);
    Aff_Adr(neu,*head);
    *head=neu;
}

/** Insérer la valeur v à la fin de la LLC **/
void insert_end (maillon** head , int v)
{
    if ( *head==0 || *head==50 )  {  *head=Allouer();   Aff_Val(*head,v);  Aff_Adr(*head,NULL);  }
    else
    {
    maillon* curr;
    maillon* neu;
    curr = *head;
    while ( Suivant(curr) !=NULL) { curr = Suivant( curr ); }
    neu=Allouer();
    Aff_Val(neu,v);
    Aff_Adr(neu,NULL);
    Aff_Adr( curr,neu);
    }
}

/** Insértion par position dans une LLC **/
int ins_pos(maillon **tete,int pos,int val)
{
    int cpt;
    maillon *p,*q;
    p=Allouer();
    Aff_Val(p,val);
    if(pos==1)
    {
        Aff_Adr(p,*tete);
        *tete=p;

    }
    else
    {
        q=acces_pos(*tete,pos-1);
        Aff_Adr(p,Suivant(q));
        Aff_Adr(q,p);
    }
    cpt=pos-1;
    return cpt;
}

/** Permuter deux éléments d'une LLC **/
void permut_elem ( maillon** A , maillon** B )
{
    maillon* tmp;
    tmp=*A;
    *A=*B;
    *B=tmp;
}

/** Tri par bulles **/
void tri_bulles ( maillon* head )
{
    int cpt; int tmp; maillon* P; maillon* Q;
    do
    {
        cpt=0;P=head;Q=Suivant(P);
        while ( Q!=NULL )
        {
            if ( Valeur(P) > Valeur(Q) )
            {
                tmp = Valeur(P);
                Aff_Val( P , Valeur(Q) );
                Aff_Val( Q , tmp );
                cpt++;
            }
            P=Q;
            Q=Suivant(Q);
        }
    } while ( cpt!=0 );
}

/** Interclassement de deux LLC **/
maillon* interclass ( maillon* T1 , maillon* T2 )
{
    maillon* P;   maillon* Result;   maillon* P1;   maillon* P2;
    if (Valeur(T1)<Valeur(T2))
    {
        Result=T1;
    }
    else
    {
        Result=T2;
    }
    P1=T1;
    P2=T2;
    P=Result;
    while ( Suivant(P1)!=NULL && Suivant(P2)!=NULL )
    {
        if (Valeur(P1)<Valeur(P2))
        {
            while (Suivant(P1)!=NULL && Valeur(P1)<Valeur(P2))
            {
                P =P1;
                P1=Suivant(P1);
            }
            Aff_Adr(P,P2);
        }
        if ( Suivant(P1)!=NULL )
        {
            while (P2!=NULL && Valeur(P2)<Valeur(P1))
            {
                P =P2;
                P2=Suivant(P2);
            }
            Aff_Adr(P,P1);
        }
    }
    return Result;
}





#endif // MYLIB_H_INCLUDED
