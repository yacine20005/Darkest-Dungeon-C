#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h" //Permet d'importer les structs du fichier structures.h

void afficher_elem(void *structure, type_struct t)
{
    /*
    En gros on donne à la fonction un type qui permettra d'aller dans le bon case
    et avec cela la strucutre qui correspond
    Ensuite on affiche les informations de la structure
    On utilisera souvent la synthaxe suivante : ((type *)structure)->attribut
    */
    switch (t)
    {
    case type_classe:
        for(classe *c = (classe *)structure; c -> suivant; c = c ->suivant)
        {
            printf("Nom : %s\n", c->nom);
            printf("Attaque : %d\n", c->att);
            printf("Defense : %d\n", c->def);
            printf("HP max : %d\n", c->HPmax);
            printf("Rest : %d\n", c->rest);
        }
        break;

    case type_personnage:
        for(personnage *p = (personnage *)structure; p -> suivant; p = p->suivant)
        {
            printf("Nom : %s\n", p->nom);
            printf("Classe : %s\n", p->type.nom);
            printf("HP : %d\n", p->HP);
            printf("Stress : %d\n", p->stress);
            printf("Nombre de combat : %d\n", p->NBcombat);
        }
        break;

    case type_accessoire:
        for(accessoire *a = (accessoire *)structure; a -> suivant; a = a->suivant)
        {
            printf("Nom : %s\n", a->nom);
            printf("Prix : %d\n", a->prix);
            printf("Attaque bonus : %d\n", a->attbonus);
            printf("Defense bonus : %d\n", a->defbonus);
            printf("HP bonus : %d\n", a->HPbonus);
            printf("Heal bonus : %d\n", a->heal_bonus);
            printf("Stress reduit : %d\n", a->strred);
        }
        break;

    case type_ennemie:
        for(ennemie *e = (ennemie *)structure; e -> suivant; e = e->suivant)
        {
            printf("Nom : %s\n", e->nom);
            printf("Niveau : %d\n", e->niveauenn);
            printf("Attaque : %d\n", e->attenn);
            printf("Defense : %d\n", e->defenn);
            printf("HP : %d\n", e->HPenn);
            printf("Attaque stress : %d\n", e->attstrenn);
        }
        break;

    default:
        printf("Le type n'est pas reconnu, pitié fait relis la fonction stp\n");
        break;
    }
}

void init_classe(classe *c, char nom[20], int att, int def, int HPmax, int rest)
{
    strncpy(c->nom, nom, sizeof(c->nom) - 1);
    c->nom[sizeof(c->nom) - 1] = '\0';
    c->att = att;
    c->def = def;
    c->HPmax = HPmax;
    c->rest = rest;
    c->suivant = NULL;
}

void init_personnage(personnage *p, char nom[20], classe *type)
{
    strncpy(p->nom, nom, sizeof(p->nom) - 1);
    p->nom[sizeof(p->nom) - 1] = '\0';
    p->type = *type;
    p->HP = type->HPmax;
    p->stress = 0;
    p->NBcombat = 0;
    p->suivant = NULL;
}

void init_accessoire(accessoire *a, char nom[20], int prix, int att, int def, int HP, int rest, int strred)
{
    strncpy(a->nom, nom, sizeof(a->nom) - 1);
    a->nom[sizeof(a->nom) - 1] = '\0';
    a->prix = prix;
    a->attbonus = att;
    a->defbonus = def;
    a->HPbonus = HP;
    a->heal_bonus = rest;
    a->strred = strred;
    a->suivant = NULL;
}

void init_ennemie(ennemie *e, char nomenem[20], int niveau, int att, int def, int HP, int attstr)
{
    strncpy(e->nom, nomenem, sizeof(e->nom) - 1);
    e->nom[sizeof(e->nom) - 1] = '\0';
    e->niveauenn = niveau;
    e->attenn = att;
    e->defenn = def;
    e->HPenn = HP;
    e->attstrenn = attstr;
    e->suivant = NULL;
}

void ajouter_classe(liste_classe *liste, char nom[20], int att, int def, int hpmax, int rest)
{
    classe *c = (classe *)malloc(sizeof(classe));
    if (c == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        exit(1);
    }
    init_classe(c, nom, att, def, hpmax, rest);
    c->suivant = liste->suivant;
    liste = c;
}

void ajouter_personnage(liste_personnage *liste, char nom[20], classe *type)
{
    personnage *p = (personnage *)malloc(sizeof(personnage));
    if (p == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        exit(1);
    }
    init_personnage(p, nom, type);
    p->suivant = liste->suivant;
    liste = p;
}

void ajouter_accessoire(liste_accessoire *liste, char nom[20], int prixa, int attb, int defb, int HPb, int restb, int strredb)
{
    accessoire *a = (accessoire *)malloc(sizeof(accessoire));
    if (a == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        exit(1);
    }
    init_accessoire(a, nom, prixa, attb, defb, HPb, restb, strredb);
    a->suivant = liste->suivant;
    liste = a;
}

void ajouter_ennemie(liste_ennemie *liste, char nomenem[20], int niveau, int att, int def, int HP, int attstr)
{
    ennemie *e = (ennemie *)malloc(sizeof(ennemie));
    if (e == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        exit(1);
    }
    init_ennemie(e, nomenem, niveau, att, def, HP, attstr);
    e->suivant = liste->suivant;
    liste = e;
}

int supprimer(void *liste, type_struct t)
{
    if (liste == NULL)
    {
        return 0;
    }
    if (liste->suivant == NULL)
    {
        free(liste);
        liste = NULL;
        return 0;
    }
    switch (t)
    {
    case type_classe:
        classe *c = (classe *)liste;
        liste = c->suivant;
        free(c);
        break;
    case type_personnage:
        personnage *p = (personnage *)liste;
        liste = p->suivant;
        free(p);
        break;
    case type_accessoire:
        accessoire *a = (accessoire *)liste;
        liste = a->suivant;
        free(a);
        break;
    case type_ennemie:
        ennemie *e = (ennemie *)liste;
        liste = e->suivant;
        free(e);
        break;
    default:
        printf("Le type n'est pas reconnu, pitié fait relis la fonction stp\n");
        break;
    }
}

int main(void)
{
    liste_classe *liste_c = NULL;
    liste_accessoire *liste_a = NULL;
    liste_personnage *liste_p = NULL;
    liste_ennemie *liste_e = NULL;
    ajouter_classe(liste_c, "Furie", 13, 0, 20, 0);
    ajouter_classe(liste_c, "Vestale", 3, 0, 20, 10);
    ajouter_classe(liste_c, "Chasseur de primes", 7, 3, 25, 3);
    ajouter_classe(liste_c, "Maitre chien", 10, 6, 17, 5);

    afficher_elem(liste_c, type_classe);

    ajouter_personnage(liste_p, "Gims", liste_c);
    ajouter_personnage(liste_p, "Kaaris", liste_c);
    ajouter_personnage(liste_p, "Ninho", liste_c);
    ajouter_personnage(liste_p, "Nekfeu", liste_c);
    ajouter_personnage(liste_p, "Damso", liste_c);
    ajouter_personnage(liste_p, "Orelsan", liste_c);
    ajouter_personnage(liste_p, "Vald", liste_c);
    printf("Hello, World!\n");
    return 0;
}
