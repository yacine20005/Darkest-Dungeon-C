#ifndef STRUCTURES_H

#define STRUCTURES_H

typedef enum { // Permettra de vérifier le type de chaque cellule et de s'adapter en fonction de leur données
    TYPE_CLASSE,
    TYPE_PERSONNAGE,
    TYPE_ACCESSOIRE,
    TYPE_ENNEMIE
} type;

typedef enum
{
    ATTAQUER,
    DEFENDRE,
    RESTORER,
    MORT, // plus de PV DONC MORT
    INUTILISABLE // PLUS DE 100 de stress donc inutilisable

}status;

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
    int att;
    int def;
    int HPmax;
    int rest;
} classe;

typedef struct
{
    char nom[20];
    classe classe_perso;
    int HP;
    int stress;
    int NBcombat;
    accessoire *accessoire;
    status status;

} personnage;



typedef struct
{
    char nom[20];
    int niveau;
    int att;
    int def;
    int HP;
    int attstr;
} ennemie;

typedef struct cellule
{
    void *valeur; // Permet de stocker n'importe quel type de valeur comme un ennemi, un personnage, une classe ou un accessoire
    type type; // Permet de savoir quel type de valeur est stocké dans la cellule pour pouvoir anticiper et manipuler les données correctement
    struct cellule *suivant; // Permet de pointer vers la cellule suivante
} cellule, *liste; // liste est un pointeur vers une cellule

#endif // STRUCTURES_H
