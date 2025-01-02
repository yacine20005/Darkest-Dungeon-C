#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h" //Permet d'importer les structs du fichier structures.h

void afficher(liste lst)
{
    if (lst) // Si la liste n'est pas vide
    {
        switch (lst->type) // On regarde le type de la liste
        {
        case TYPE_CLASSE: // Si c'est une liste de classe
        {
            printf("---\n");
            for (cellule *tmp = lst; tmp; tmp = tmp->suivant) // On parcourt la liste
            {
                printf("Classe: %s, Attaque: %d, Defense: %d, HP max: %d, Restauration: %d\n",
                       ((classe *)tmp->valeur)->nom, ((classe *)tmp->valeur)->att, ((classe *)tmp->valeur)->def, ((classe *)tmp->valeur)->HPmax, ((classe *)tmp->valeur)->rest); // On affiche les infos en spécifiant le type de la valeur avant d'accéder aux champs avec ((type *)tmp->valeur)->champ
                printf("---\n");
            }
            break;
        }

        case TYPE_PERSONNAGE:
        {
            printf("---\n");
            for (cellule *tmp = lst; tmp; tmp = tmp->suivant)
            {
                printf("Personnage: %s, Classe : %s, Attaque: %d, Defense: %d, HP/HPmax: %d, Restauration : %d, Stress: %d, Nombre de combats: %d\n",
                       ((personnage *)tmp->valeur)->nom, ((personnage *)tmp->valeur)->classe_perso.nom, ((personnage *)tmp->valeur)->classe_perso.att, ((personnage *)tmp->valeur)->classe_perso.def, ((personnage *)tmp->valeur)->HP, ((personnage *)tmp->valeur)->classe_perso.rest, ((personnage *)tmp->valeur)->stress, ((personnage *)tmp->valeur)->NBcombat);
                printf("---\n");
            }
            break;
        }

        case TYPE_ACCESSOIRE:
        {
            printf("---\n");
            for (cellule *tmp = lst; tmp; tmp = tmp->suivant)
            {
                printf("Accessoire: %s, Prix: %d, Attaque bonus: %d, Defense bonus: %d, HP bonus: %d, Heal bonus: %d, Stress reduit: %d\n",
                       ((accessoire *)tmp->valeur)->nom, ((accessoire *)tmp->valeur)->prix, ((accessoire *)tmp->valeur)->attbonus, ((accessoire *)tmp->valeur)->defbonus, ((accessoire *)tmp->valeur)->HPbonus, ((accessoire *)tmp->valeur)->heal_bonus, ((accessoire *)tmp->valeur)->strred);
                printf("---\n");
            }
            break;
        }

        case TYPE_ENNEMIE:
        {
            printf("---\n");
            for (cellule *tmp = lst; tmp; tmp = tmp->suivant)
            {
                printf("Ennemie: %s, Niveau: %d, Attaque: %d, Defense: %d, HP: %d, Attaque stress: %d\n",
                       ((ennemie *)tmp->valeur)->nom, ((ennemie *)tmp->valeur)->niveau, ((ennemie *)tmp->valeur)->att, ((ennemie *)tmp->valeur)->def, ((ennemie *)tmp->valeur)->HP, ((ennemie *)tmp->valeur)->attstr);
                printf("---\n");
            }
            break;
        }
        default:
            printf("Le type n'est pas reconnu\n");
            break;
        }
    }
}

void ajouter_classe(liste *lst_classe, const char *nom, int att, int def, int hpmax, int rest, type type)
{
    classe *c = (classe *)malloc(sizeof(classe));              // Allocation de la mémoire pour la classe en elle meme
    cellule *new_cellule = (cellule *)malloc(sizeof(cellule)); // Allocation de la mémoire pour la nouvelle cellule de la liste
    if (c == NULL || new_cellule == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        return;
    }
    strncpy(c->nom, nom, sizeof(c->nom) - 1); // On met les infos dans la classe
    c->nom[sizeof(c->nom) - 1] = '\0';
    c->att = att;
    c->def = def;
    c->HPmax = hpmax;
    c->rest = rest;
    new_cellule->valeur = c;            // On met la classe dans la cellule
    new_cellule->type = type;           // On met le type dans la cellule
    new_cellule->suivant = *lst_classe; // On met la cellule en tete de liste
    *lst_classe = new_cellule;          // On met la nouvelle liste en tete de liste
}

void ajouter_personnage(liste *lst_personnage, liste *lst_classe, const char *nom_perso, const char *nom_classe, type type)
{
    personnage *p = (personnage *)malloc(sizeof(personnage));  // Allocation de la mémoire pour la classe en elle meme
    cellule *new_cellule = (cellule *)malloc(sizeof(cellule)); // Allocation de la mémoire pour la nouvelle cellule de la liste
    int classe_trouve = 0;
    if (p == NULL || new_cellule == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        return;
    }
    for (cellule *tmp = *lst_classe; tmp; tmp = tmp->suivant) // On parcourt la liste des classes
    {
        if (strcmp(((classe *)tmp->valeur)->nom, nom_classe) == 0) // Si on trouve la classe spécifiée en argument
        {
            p->classe_perso = *(classe *)tmp->valeur; // On met la classe dans le personnage
            classe_trouve = 1;                        // On indique qu'on a trouvé la classe
            break;                                    // On sort de la boucle
        }
    }
    if (classe_trouve) // Si on a trouvé la classe
    {
        strncpy(p->nom, nom_perso, sizeof(p->nom) - 1);
        p->nom[sizeof(p->nom) - 1] = '\0';
        p->HP = p->classe_perso.HPmax;
        p->stress = 0;
        p->NBcombat = 0;
        p->accessoire = NULL;
        new_cellule->valeur = p;                // On met la classe dans la cellule
        new_cellule->type = type;               // On met le type dans la cellule
        new_cellule->suivant = *lst_personnage; // On met la cellule en tete de liste
        *lst_personnage = new_cellule;          // On met la nouvelle liste en tete de liste
    }
    else
    {
        printf("La classe n'a pas été trouvée\n");
    }
}

void ajouter_accessoire(liste *lst_accessoire, const char *nom, int prix, int attbonus, int defbonus, int hpbonus, int heal_bonus, int strred, type type)
{
    accessoire *a = (accessoire *)malloc(sizeof(accessoire));  // Allocation de la mémoire pour la classe en elle meme
    cellule *new_cellule = (cellule *)malloc(sizeof(cellule)); // Allocation de la mémoire pour la nouvelle cellule de la liste
    if (a == NULL || new_cellule == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        return;
    }
    strncpy(a->nom, nom, sizeof(a->nom) - 1); // On met les infos dans la classe
    a->nom[sizeof(a->nom) - 1] = '\0';
    a->prix = prix;
    a->attbonus = attbonus;
    a->defbonus = defbonus;
    a->HPbonus = hpbonus;
    a->heal_bonus = heal_bonus;
    a->strred = strred;
    new_cellule->valeur = a;                // On met la classe dans la cellule
    new_cellule->type = type;               // On met le type dans la cellule
    new_cellule->suivant = *lst_accessoire; // On met la cellule en tete de liste
    *lst_accessoire = new_cellule;          // On met la nouvelle liste en tete de liste
}

void ajouter_ennemie(liste *lst_ennemie, const char *nom, int niveau, int att, int def, int hp, int attstr, type type)
{
    ennemie *e = (ennemie *)malloc(sizeof(ennemie));           // Allocation de la mémoire pour la classe en elle meme
    cellule *new_cellule = (cellule *)malloc(sizeof(cellule)); // Allocation de la mémoire pour la nouvelle cellule de la liste
    if (e == NULL || new_cellule == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire\n");
        return;
    }
    strncpy(e->nom, nom, sizeof(e->nom) - 1); // On met les infos dans la classe
    e->nom[sizeof(e->nom) - 1] = '\0';
    e->niveau = niveau;
    e->att = att;
    e->def = def;
    e->HP = hp;
    e->attstr = attstr;
    new_cellule->valeur = e;             // On met la classe dans la cellule
    new_cellule->type = type;            // On met le type dans la cellule
    new_cellule->suivant = *lst_ennemie; // On met la cellule en tete de liste
    *lst_ennemie = new_cellule;          // On met la nouvelle liste en tete de liste
}

void ajouter_cellule(liste *liste, cellule *c)
{
    if (!(*liste))
    {
        *liste = c;
        return;
    }
    cellule *tmp = *liste;
    for (; tmp->suivant; tmp = tmp->suivant)
        ;//Boucle vide pour se placer sur la dernière cellule
    tmp->suivant = c;
}

cellule* supprimer_num(liste *liste, int num)
{
    if (!(*liste))
    {
        return 0;
    }
    int taille = 0;
    for(cellule *tmp = *liste; tmp; tmp = tmp->suivant, taille++)
        ;//Boucle vide pour compter le nombre de cellules
    if (num < 0 || num >= taille)
    {
        printf("Le numero est invalide\n");
        return 0;
    }
    if (num == 0) //Si on veut supprimer la première cellule
    {
        cellule *c = *liste;
        *liste = c->suivant;
        c ->suivant = NULL;
        return c;
    }
    cellule *tmp = *liste;
    for(int i = 0; i < num - 1; i++, tmp = tmp->suivant)
        ;//Boucle vide pour se placer sur la cellule précédant celle à supprimer
        
    cellule *c = tmp -> suivant; //On récupère la cellule à supprimer
    if(!(c -> suivant)) //Si c'est la dernière cellule
    {
        tmp -> suivant = NULL;
        return c;
    }
    tmp -> suivant = c -> suivant;
    c -> suivant = NULL;
    return c;
}

int main(void)
{

    liste lst_classe = NULL;
    liste lst_personnage = NULL;
    liste lst_personnage_actif = NULL;
    liste roulotte = NULL; //liste accessoire, on change le nom pour correspondre au sujet.
    liste lst_ennemie = NULL;
    liste sanitarium = NULL;
    liste taverne = NULL;*

    ajouter_classe(&lst_classe, "Furie", 13, 0, 20, 0, TYPE_CLASSE);
    ajouter_classe(&lst_classe, "Vestale", 3, 0, 20, 10, TYPE_CLASSE);
    ajouter_classe(&lst_classe, "Chasseur de primes", 7, 3, 25, 3, TYPE_CLASSE);
    ajouter_classe(&lst_classe, "Maitre chien", 10, 6, 17, 5, TYPE_CLASSE);


    ajouter_personnage(&lst_personnage, &lst_classe, "Kaaris", "Furie", TYPE_PERSONNAGE);
    ajouter_personnage(&lst_personnage, &lst_classe, "Damso", "Vestale", TYPE_PERSONNAGE);
    ajouter_personnage(&lst_personnage, &lst_classe, "Nekfeu", "Chasseur de primes", TYPE_PERSONNAGE);
    ajouter_personnage(&lst_personnage, &lst_classe, "Gims", "Maitre chien", TYPE_PERSONNAGE);
    ajouter_personnage(&lst_personnage, &lst_classe, "Sammy", "Maitre chien", TYPE_PERSONNAGE);
    ajouter_personnage(&lst_personnage, &lst_classe, "Scooby-doo", "Vestale", TYPE_PERSONNAGE);
    ajouter_personnage(&lst_personnage, &lst_classe, "Maissa Ben Hamouda", "Furie", TYPE_PERSONNAGE);
    ajouter_personnage(&lst_personnage, &lst_classe, "Maitre Yoda", "Chasseur de primes", TYPE_PERSONNAGE);



    ajouter_accessoire(&roulotte, "Bouclier", 10, 0, 5, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Epee", 15, 5, 0, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Potion de soin", 10, 0, 0, 0, 5, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Potion de stress", 10, 0, 0, 0, 0, 5, TYPE_ACCESSOIRE);
    

    ajouter_ennemie(&lst_ennemie, "Goblin", 1, 2, 0, 10, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Minotaure", 2, 4, 2, 15, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Serviteur", 3, 6, 4, 20, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Athéon", 4, 8, 6, 25, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Oryx", 5, 10, 8, 30, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Adolph Hitler", 6, 12, 10, 35, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Staline", 7, 14, 12, 40, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Bernard", 2, 4, 2, 15, 0, TYPE_ENNEMIE);

    afficher(lst_personnage);
    ajouter_cellule(&lst_personnage_actif, supprimer_num(&lst_personnage, 2)); //On supprime le 3ème personnage et on l'ajoute à la liste des personnages actifs
    afficher(lst_personnage_actif);
    afficher(lst_personnage);

    return 0;
}
