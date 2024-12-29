#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h" //Permet d'importer les structs du fichier structures.h

void afficher_classe(classe *c)
{
    printf("Nom : %s\n", c->nom);
    printf("Attaque : %d\n", c->att);
    printf("Defense : %d\n", c->def);
    printf("HPmax : %d\n", c->HPmax);
    printf("Restauration : %d\n", c->rest);
}

void afficher_personnage(personnage *p)
{
    printf("Nom : %s\n", p->nom);
    printf("Classe : %s\n", p->type.nom);
    printf("HP : %d\n", p->HP);
    printf("Stress : %d\n", p->stress);
    printf("Nombre de combats : %d\n", p->NBcombat);
}

void afficher_accessoire(accessoire *a)
{
    printf("Nom : %s\n", a->nom);
    printf("Prix : %d\n", a->prix);
    printf("Bonus attaque : %d\n", a->attbonus);
    printf("Bonus defense : %d\n", a->defbonus);
    printf("Bonus HP : %d\n", a->HPbonus);
    printf("Bonus restauration : %d\n", a->heal_bonus);
    printf("Reduction de stress : %d\n", a->strred);
}

void afficher_ennemie(ennemie *e)
{
    printf("Nom : %s\n", e->nom);
    printf("Niveau : %d\n", e->niveauenn);
    printf("Attaque : %d\n", e->attenn);
    printf("Defense : %d\n", e->defenn);
    printf("HP : %d\n", e->HPenn);
    printf("Attaque de stress : %d\n", e->attstrenn);
}

void ajouter_classe(liste_classe *liste, const char *nom, int att, int def, int hpmax, int rest)
{
    classe *c = (classe *)malloc(sizeof(classe));
    if (c == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        exit(1);
    }
    strncpy(c->nom, nom, sizeof(c->nom) - 1);
    c->nom[sizeof(c->nom) - 1] = '\0';
    c->att = att;
    c->def = def;
    c->HPmax = hpmax;
    c->rest = rest;
    c->suivant = liste;
    liste = c;
}

void ajouter_personnage(liste_personnage *liste, const char *nom, classe *type)
{
    personnage *p = (personnage *)malloc(sizeof(personnage));
    if (p == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        exit(1);
    }
    strncpy(p->nom, nom, sizeof(p->nom) - 1);
    p->nom[sizeof(p->nom) - 1] = '\0';
    p->type = *type;
    p->HP = type->HPmax;
    p->stress = 0;
    p->NBcombat = 0;
    p->suivant = liste;
    liste = p;
}

void ajouter_accessoire(liste_accessoire *liste, const char *nom, int prixa, int attb, int defb, int HPb, int restb, int strredb)
{
    accessoire *a = (accessoire *)malloc(sizeof(accessoire));
    if (a == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        exit(1);
    }
    strncpy(a->nom, nom, sizeof(a->nom) - 1);
    a->nom[sizeof(a->nom) - 1] = '\0';
    a->prix = prixa;
    a->attbonus = attb;
    a->defbonus = defb;
    a->HPbonus = HPb;
    a->heal_bonus = restb;
    a->strred = strredb;
    a->suivant = liste;
    liste = a;
}

void ajouter_ennemie(liste_ennemie *liste, const char *nomenem, int niveau, int att, int def, int HP, int attstr)
{
    ennemie *e = (ennemie *)malloc(sizeof(ennemie));
    if (e == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        exit(1);
    }
    strncpy(e->nom, nomenem, sizeof(e->nom) - 1);
    e->nom[sizeof(e->nom) - 1] = '\0';
    e->niveauenn = niveau;
    e->attenn = att;
    e->defenn = def;
    e->HPenn = HP;
    e->attstrenn = attstr;
    e->suivant = liste;
    liste = e;
}

int supprimer(void *liste, type_struct t)
{
    if (liste == NULL)
    {
        return 0;
    }
    switch (t)
    {
    case type_classe:
    {
        classe *c = (classe *)liste;
        if (c->suivant == NULL)
        {
            free(c);
            return 1;
        }
        liste = c->suivant;
        free(c);
        return 1;
    }
    case type_personnage:
    {
        personnage *p = (personnage *)liste;
        if (p->suivant == NULL)
        {
            free(p);
            return 1;
        }
        liste = p->suivant;
        free(p);
        return 1;
    }
    case type_accessoire:
    {
        accessoire *a = (accessoire *)liste;
        if (a->suivant == NULL)
        {
            free(a);
            return 1;
        }
        liste = a->suivant;
        free(a);
        return 1;
    }
    case type_ennemi:
    {
        ennemie *e = (ennemie *)liste;
        if (e->suivant == NULL)
        {
            free(e);
            return 1;
        }
        liste = e->suivant;
        free(e);
        return 1;
    }
    default:
        printf("Le type n'est pas reconnu\n");
        return 0;
    }
}

int main(void)
{
    liste_classe *liste_c = NULL;
    liste_accessoire *liste_a = NULL;
    liste_personnage *liste_p = NULL;
    liste_ennemie *liste_e = NULL;

    ajouter_classe(liste_c, "Furie", 13, 0, 20, 0);
    //ajouter_classe(&liste_c, "Vestale", 3, 0, 20, 10);
    //ajouter_classe(&liste_c, "Chasseur de primes", 7, 3, 25, 3);
    //ajouter_classe(&liste_c, "Maitre chien", 10, 6, 17, 5);

    afficher_classe(liste_c);

    printf("Hello World!\n");
    return 0;
}
