#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum
{
    type_classe,
    type_personnage,
    type_accessoire,
    type_ennemi
} type_struct;

typedef struct classe
{
    char nom[20];
    int att;
    int def;
    int HPmax;
    int rest;
    struct classe *suivant;
} classe, liste_classe;

typedef struct personnage
{
    char nom[20];
    classe type;
    int HP;
    int stress;
    int NBcombat;
    struct personnage *suivant;
} personnage, liste_personnage;

typedef struct accessoire
{
    char nom[20];
    int prix;
    int attbonus;
    int defbonus;
    int HPbonus;
    int heal_bonus;
    int strred;
    struct accessoire *suivant;
} accessoire, liste_accessoire;

typedef struct ennemie
{
    char nom[20];
    int niveauenn;
    int attenn;
    int defenn;
    int HPenn;
    int attstrenn;
    struct ennemie *suivant;
} ennemie, liste_ennemie;

#endif // STRUCTURES_H
