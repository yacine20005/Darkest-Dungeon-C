#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct
{
    char nom[20];
    int att;
    int def;
    int HPmax;
    int rest;
} classe;

typedef struct
{
    char nom[20];
    classe type;
    int HP;
    int stress;
    int nb_combat;
} personnage;

typedef struct
{

    char nom[20];

    int prix;

    int attbonus;

    int defbonus;

    int HPbonus;

    int heal_bonus;

    int strred;

} accessoire;

typedef struct
{

    char nom[20];

    int niveauenn;

    int attenn;

    int defenn;

    int HPenn;

    int attstrenn;

} ennemie;