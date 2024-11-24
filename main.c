#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void initclasse(classe *c,  char nom[20], int att, int def, int hpmax, int rest){
    c -> att = att; 
    c -> def = def;
    c -> HPmax = hpmax;
    c -> rest = rest;
};

void initpersonnage(personnage *p,  char nom[20], classe *type){
    p -> type = *type; 
    p -> HP = type -> HPmax;
    p -> stress = 0;
    p -> nb_combat = 0;
};

void initaccessoire(accessoire *a, char nom[20], int prixa, int attb, int defb, int HPb, int restb, int strredb) {
    //a -> nomAccessoire = nom;
    a -> prix = prixa;
    a -> attbonus = attb;
    a -> defbonus = defb;
    a -> HPbonus = HPb;
    a -> heal_bonus = restb;
    a -> strred = strredb;
}

void initennemie(ennemie *e, char nomenem[20], int niveau, int att, int def, int HP, int attstr){
   
    /* strncpy(e->nomenem, nomenem, sizeof(e->nomenem) - 1);
    e->nomenem[sizeof(e->nomenem) - 1] = '\0'; */

    e->niveauenn = niveau;
    e->attenn = att;
    e->defenn = def;
    e->HPenn = HP;
    e->attstrenn = attstr;
}

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
