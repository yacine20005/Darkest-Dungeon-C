#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h" //Permet d'importer les structs du fichier structures.h
#include <time.h>

int taille_liste(liste lst)
{
    int taille = 0;
    for (cellule *tmp = lst; tmp; tmp = tmp->suivant, taille++)
        ; // Boucle vide pour compter le nombre de cellules avec la variable taille
    return taille;
}

void afficher(liste lst)
{
    if (lst) // Si la liste n'est pas vide
    {
        switch (lst->type) // On regarde le type de la liste
        {
        case TYPE_CLASSE: // Si c'est une liste de classe
        {
            printf("--------------------------------------------------\n");
            printf("| Numero | Nom | att | def | HPmax | rest |\n");
            printf("--------------------------------------------------\n");
            int num = 0;
            for (cellule *tmp = lst; tmp; tmp = tmp->suivant, num++) // On parcourt la liste
            {
                printf("| %d | %s | %d | %d | %d | %d |\n",
                       num, ((classe *)tmp->valeur)->nom, ((classe *)tmp->valeur)->att, ((classe *)tmp->valeur)->def, ((classe *)tmp->valeur)->HPmax, ((classe *)tmp->valeur)->rest); // On affiche les infos en spécifiant le type de la valeur avant d'accéder aux champs avec ((type *)tmp->valeur)->champ
                printf("--------------------------------------------------\n");
            }
            printf("\n");
            break;
        }

        case TYPE_PERSONNAGE:
        {
            printf("-----------------------------------------------------------------------------------------------------------------------------\n");
            printf("| Numero | Nom | Classe | Attaque | Defense | HP/HPmax | Restauration | Stress | Nombre de combats | Accessoire |\n");
            printf("-----------------------------------------------------------------------------------------------------------------------------\n");
            int num = 0;
            for (cellule *tmp = lst; tmp; tmp = tmp->suivant, num++)
            {
                personnage *perso = (personnage *)tmp->valeur;
                printf("| %d | %s | %s | %d | %d | %d/%d | %d | %d | %d | %s |\n",
                       num, perso->nom, perso->classe_perso.nom, perso->classe_perso.att, perso->classe_perso.def, perso->HP, perso->classe_perso.HPmax, perso->classe_perso.rest, perso->stress, perso->NBcombat, perso->accessoire ? ((accessoire *)perso->accessoire)->nom : "Aucun");
                printf("-----------------------------------------------------------------------------------------------------------------------------\n");
            }
            printf("\n");
            break;
        }

        case TYPE_ACCESSOIRE:
        {
            printf("---------------------------------------------------------------------------------------------\n");
            printf("| Numero | Nom | Prix | Attaque bonus | Defense bonus | HP bonus | Heal bonus | Stress reduit |\n");
            printf("---------------------------------------------------------------------------------------------\n");
            int num = 0;
            for (cellule *tmp = lst; tmp; tmp = tmp->suivant, num++)
            {
                printf("| %d | %s | %d | %d | %d | %d | %d | %d |\n",
                       num, ((accessoire *)tmp->valeur)->nom, ((accessoire *)tmp->valeur)->prix, ((accessoire *)tmp->valeur)->attbonus, ((accessoire *)tmp->valeur)->defbonus, ((accessoire *)tmp->valeur)->HPbonus, ((accessoire *)tmp->valeur)->heal_bonus, ((accessoire *)tmp->valeur)->strred);
                printf("---------------------------------------------------------------------------------------------\n");
            }
            printf("\n");
            break;
        }

        case TYPE_ENNEMIE:
        {
            printf("---------------------------------------------------------------------------------------------\n");
            printf("| Numero | Nom | Niveau | Attaque | Defense | HP | Attaque stress |\n");
            printf("---------------------------------------------------------------------------------------------\n");
            int num = 0;
            for (cellule *tmp = lst; tmp; tmp = tmp->suivant, num++)
            {
                printf("| %d | %s | %d | %d | %d | %d | %d |\n",
                       num, ((ennemie *)tmp->valeur)->nom, ((ennemie *)tmp->valeur)->niveau, ((ennemie *)tmp->valeur)->att, ((ennemie *)tmp->valeur)->def, ((ennemie *)tmp->valeur)->HP, ((ennemie *)tmp->valeur)->attstr);
                printf("---------------------------------------------------------------------------------------------\n");
            }
            printf("\n");
            break;
        }
        default:
            printf("Le type n'est pas reconnu\n");
            printf("\n");
            break;
        }
    }
    else
    {
        printf("La liste est vide\n");
        printf("\n");
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
        p->status = ATTAQUER;
        new_cellule->valeur = p;                // On met la classe dans la cellule
        new_cellule->type = type;               // On met le type dans la cellule
        new_cellule->suivant = *lst_personnage; // On met la cellule en tete de liste
        *lst_personnage = new_cellule;          // On met la nouvelle liste en tete de liste
    }
    else // Si on a pas trouvé la classe
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
    if (!(*liste)) // Si la liste est vide
    {
        *liste = c; // La liste est seulement composée de la cellule
        return;
    }
    cellule *tmp = *liste;
    for (; tmp->suivant; tmp = tmp->suivant)
        ;             // Boucle vide pour se placer sur la dernière cellule
    tmp->suivant = c; // On met la cellule à la fin de la liste
}

cellule *supprimer_num(liste *liste, int num)
{
    if (!(*liste))
    {
        return 0; // Bah on a rien a supprimer
    }
    int taille = 0;
    for (cellule *tmp = *liste; tmp; tmp = tmp->suivant, taille++)
        ;                         // Boucle vide pour compter le nombre de cellules avec la variable taille
    if (num < 0 || num >= taille) // Si le numéro est invalide car il n'existe pas dans la liste
    {
        printf("Le numero est invalide\n");
        return 0;
    }
    if (num == 0) // Si on veut supprimer la première cellule
    {
        cellule *c = *liste; // On récupère la cellule à supprimer
        *liste = c->suivant; // La liste commence maintenant à la cellule suivante
        c->suivant = NULL;   // On enlève le lien de la cellule avec la liste
        return c;
    }
    cellule *tmp = *liste;
    for (int i = 0; i < num - 1; i++, tmp = tmp->suivant)
        ; // Boucle vide pour se placer sur la cellule précédant celle à supprimer

    cellule *c = tmp->suivant; // On récupère la cellule à supprimer
    if (!(c->suivant))         // Si c'est la dernière cellule
    {
        tmp->suivant = NULL; // On enlève le lien de la cellule précédente avec la cellule à supprimer
        return c;
    }
    tmp->suivant = c->suivant; // On relie la cellule précédente à la suivante de celle à supprimer
    c->suivant = NULL;         // On enlève le lien de la cellule avec la liste
    return c;
}

int fin_combat(liste lst_personnage_actif, liste lst_ennemie_actif)
{
    if (taille_liste(lst_personnage_actif) == 0) // Si il n'y a plus de personnage actif
    {
        return 1; // Donc on a perdu
    }
    if (taille_liste(lst_ennemie_actif) == 0) // Si il n'y a plus d'ennemie actif
    {
        return 2; // Donc on a gagné
    }
    return 0; // Sinon le combat continue
}

void attaque_personnage(personnage *perso, ennemie *ennemi)
{
    int att_total = perso->classe_perso.att; // On récupère l'attaque de base du personnage
    if (perso->accessoire)
    {
        att_total += ((accessoire *)perso->accessoire)->attbonus; // On ajoute l'attaque bonus de l'accessoire équipé
    }
    if (att_total - ennemi->def > 0) // Si l'attaque est supérieure à la défense de l'ennemie
    {
        att_total = (att_total - ennemi->def) * ((rand() % 41 + 80) / 100.0); // On calcule les dégâts à infligés
    }
    else
    {
        att_total = 1; // Sinon on inflige 1 de dégât fallait être plus fort
    }
    ennemi->HP -= att_total; // On retire les dégâts à l'ennemie
    printf("L'ennemie %s a perdu %d HP, il est maintenant a %d HP\n", ennemi->nom, att_total, ennemi->HP);
}

void attaque_ennemie(personnage *perso, ennemie *ennemi, int type)
{
    if (perso->status == INUTILISABLE)
        type = 0;
    if (type == 1) // Si l'ennemie stresse le personnage
    {
        int attstrenn = ennemi->attstr; // On récupère l'attaque stress de l'ennemie
        int strred = 0;
        if (perso->accessoire)
        {
            strred = ((accessoire *)perso->accessoire)->strred; // On récupère la réduction de stress apporté par l'accessoire
        }
        attstrenn = (attstrenn - strred) * ((rand() % 40 / 100.0) + (80 / 100.0)); // On calcule le stress à infligé
        perso->stress += attstrenn;                                                // On ajoute le stress au personnage
        printf("%s a subi %d stress, il est maintenant a %d stress\n", perso->nom, attstrenn, perso->stress);
        if (perso->stress >= 100) // Si le personnage a 100 ou plus de stress
        {
            perso->status = INUTILISABLE; // Le perso devient inutilisable
            printf("Le personnage %s a atteins 100 ou plus de stress est inutilisable \n", perso->nom);
        }
    }
    else // Si l'ennemie attaque le personnage
    {
        int def_total = perso->classe_perso.def; // On récupère la défense de base du personnage
        int att_total = 1;                       // On initialise les dégâts à 1 au cas où la défense est supérieure à l'attaque de l'ennemie
        if (perso->accessoire)                   // Si le personnage a un accessoire
        {
            def_total += ((accessoire *)perso->accessoire)->defbonus; // On ajoute la défense bonus de l'accessoire équipé
        }
        if (perso->status == DEFENDRE) // Si le personnage se défend lors du tour
        {
            def_total *= 1.10; // On augmente la défense de 10%
        }
        if (ennemi->att - def_total > 0) // Si l'attaque de l'ennemie est supérieure à la défense du personnage
        {
            att_total = (ennemi->att - perso->classe_perso.def) * ((rand() % 40 / 100.0) + (80 / 100.0)); // On calcule les dégâts à infligés
        }
        perso->HP -= att_total; // On retire les dégâts au personnage
        if (perso->HP <= 0)     // Si le personnage n'a plus de HP
        {
            perso->status = MORT; // Le perso est mort
            printf("Le personnage %s est mort\n", perso->nom);
        }
        else
        {
            printf("Le personnage %s a perdu %d HP, il est maintenant a %d HP\n", perso->nom, att_total, perso->HP);
        }
    }
}

void restaurer(personnage *perso)
{
    int hpgagner = perso->classe_perso.rest; // On récupère le montant de restauration de base du personnage
    if (perso->accessoire)                   // Si le personnage a un accessoire
    {
        hpgagner += ((accessoire *)perso->accessoire)->heal_bonus; // On ajoute le bonus de restauration de l'accessoire équipé
    }
    if (perso->HP + hpgagner >= perso->classe_perso.HPmax) // Si le personnage aura plus de HP que son maximum après la restauration
    {
        perso->HP = perso->classe_perso.HPmax; // On met ses HP au maximum
    }
    else
    {
        perso->HP += hpgagner; // Sinon on ajoute les HP gagnés
    }
    printf("%s a gagne %d HP, il est maintenant a %d HP\n", perso->nom, hpgagner, perso->HP);
}

void taverne(liste taverne)
{
    for (cellule *tmp = taverne; tmp; tmp = tmp->suivant)
    {
        ((personnage *)tmp->valeur)->stress -= 25;   // On retire 25 de stress pour chaque personnage de la taverne
        if (((personnage *)tmp->valeur)->stress < 0) // Si le stress est négatif
        {
            ((personnage *)tmp->valeur)->stress = 0;        // On met le stress à 0
            ((personnage *)tmp->valeur)->status = ATTAQUER; // On remet le personnage en état d'attaque
        }
    }
}

void sanitarium(liste sanitarium)
{
    for (cellule *tmp = sanitarium; tmp; tmp = tmp->suivant)
    {
        ((personnage *)tmp->valeur)->HP += 7;                                                  // On ajoute 7 HP pour chaque personnage du sanitarium
        if (((personnage *)tmp->valeur)->HP > ((personnage *)tmp->valeur)->classe_perso.HPmax) // Si le personnage a plus de HP que son maximum
        {
            ((personnage *)tmp->valeur)->HP = ((personnage *)tmp->valeur)->classe_perso.HPmax; // On met ses HP au maximum
        }
    }
}

int main(void)
{
    liste lst_classe = NULL;
    liste lst_personnage = NULL;
    liste lst_personnage_actif = NULL;
    liste roulotte = NULL; // liste accessoire, on change le nom pour correspondre au sujet
    liste accessoire_acquis = NULL;
    liste lst_ennemie = NULL;
    liste lst_ennemie_actif = NULL;
    liste lst_sanitarium = NULL;
    liste lst_taverne = NULL;

    int numero_combat = 0;
    int perso_max = 1;
    int or = 0;

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

    ajouter_accessoire(&roulotte, "Bouclier en bois", 5, 0, 3, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Bouclier", 10, 0, 5, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Bouclier en diamant", 15, 0, 10, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Epee en bois", 10, 3, 0, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Epee", 15, 5, 0, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Epee en diamant", 20, 10, 0, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Potion de soin", 10, 0, 0, 0, 5, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Monster Energy", 15, 0, 0, 0, 10, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Potion de stress", 10, 0, 0, 0, 0, 5, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Red Bull", 15, 0, 0, 0, 0, 10, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Akimbo Saug", 15, 5, 0, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "XM4", 20, 10, 0, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Pointeur C (->)", 50, 25, 10, 0, 0, 100, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "LIB MLV", 50, 0, 100, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Segmentation fault", 50, 0, 0, 100, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Pingouin de Linux (Tux)", 100, 100, 100, 100, 100, 100, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Honda NSX", 1000, 0, 100, 0, 0, 0, TYPE_ACCESSOIRE);

    ajouter_ennemie(&lst_ennemie, "Patient 13", 10, 20, 18, 75, 50, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Mamadou", 9, 18, 16, 60, 45, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Bernard", 8, 16, 14, 55, 40, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Staline", 7, 14, 12, 40, 35, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Adolph Hitler", 6, 12, 10, 35, 30, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Oryx", 5, 10, 8, 30, 25, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Athéon", 4, 8, 6, 25, 20, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Priscillia", 3, 6, 4, 20, 15, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Minotaure", 2, 4, 2, 15, 10, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Goblin", 1, 2, 0, 10, 5, TYPE_ENNEMIE);

    srand(time(NULL)); // Initialisation de la seed pour la génération de nombre aléatoire

    while (numero_combat < 10) // Tant qu'on a pas passé le niveau 10
    {
        printf("Combat numero %d\n", numero_combat);
        if (numero_combat % 2 == 0) // Si le numéro de combat est pair
        {
            perso_max++; // On augmente le nombre de personnage max
        }
        for (int num = 0; num < perso_max; num++) // On choisit les personnages actifs
        {
            printf("Voici les personnages disponible:\n");
            afficher(lst_personnage);
            printf("Voici les personnages actifs:\n");
            afficher(lst_personnage_actif);
            char choix[10];
            printf("Choix du personnage numero %d/%d (ou 'N' pour ne pas choisir) : ", num + 1, perso_max);
            scanf("%s", choix);
            printf("\n");
            if (choix[0] == 'N' || choix[0] == 'n' && taille_liste(lst_personnage_actif) > 0) // Si le joueur ne veut pas choisir de personnage
            {
                continue; // On passe à la sélécion du prochain personnage
            }
            else if (choix[0] == 'N' || choix[0] == 'n' && taille_liste(lst_personnage_actif) == 0) // Si le joueur ne veut pas choisir de personnage mais qu'il n'y a pas de personnage actif
            {
                printf("Vous devez choisir au moins un personnage\n");
                num--; // On refait le dernier choix
                continue;
            }
            int choix_num = atoi(choix);                                    // atoi permet de convertir une chaine de caractère en entier
            if (choix_num < 0 || choix_num >= taille_liste(lst_personnage)) // Si le numéro de personnage est invalide
            {
                printf("Le choix est invalide\n");
                num--; // On refait le dernier choix
                continue;
            }
            ajouter_cellule(&lst_personnage_actif, supprimer_num(&lst_personnage, choix_num)); // Si tout se passe bien on ajoute le personnage à la liste des personnages actifs
        }
        if (numero_combat >= 1) // Permet d'éviter d'afficher la roulotte et de choisir des accessoires au premier combat alors qu'on a pas encore d'or ou gagné de combat
        {
            printf("Voici les accessoires possédés:\n");
            afficher(accessoire_acquis);
            printf("Voici les accessoires disponibles:\n");
            afficher(roulotte);
            printf("Vous avez %d or\n", or);
            char choix[1];
            printf("Quelle accessoire voulez vous achetez (Q pour quitter) : ");
            scanf("%s", choix);
            while (choix[0] != 'Q' && choix[0] != 'q')
            {
                int choix_num = atoi(choix); // atoi permet de convertir une chaine de caractère en entier
                if (choix_num < 0 || choix_num >= taille_liste(roulotte))
                {
                    printf("Le choix est invalide\n");
                }
                else
                {
                    cellule *tmp = roulotte;
                    int parcours_liste = 0;
                    for (; choix_num != parcours_liste; tmp = tmp->suivant, parcours_liste++)
                        ;                                       // Boucle vide pour aller sur la cellule rechercher
                    if (((accessoire *)tmp->valeur)->prix > or) // Si le joueur n'a pas assez d'or
                    {
                        printf("Vous n'avez pas assez d'or\n");
                        printf("Vous avez %d or\n", or);
                    }
                    else
                    {
                        ajouter_cellule(&accessoire_acquis, supprimer_num(&roulotte, choix_num)); // On ajoute l'accessoire acquis à la liste des accessoires acquis
                        or -= ((accessoire *)accessoire_acquis->valeur)->prix;                    // On retire le prix de l'accessoire acheté à l'or du joueur
                    }
                }
                printf("Voici les accessoires possédés:\n");
                afficher(accessoire_acquis);
                printf("Voici les accessoires disponibles:\n");
                afficher(roulotte);
                printf("Vous avez %d or\n", or);
                printf("Quelle accessoire voulez vous achetez (Q pour quitter) : ");
                scanf("%s", choix);
            }
            for (cellule *tmp = lst_personnage_actif; tmp && taille_liste(accessoire_acquis); tmp = tmp->suivant) // On parcourt la liste des personnages actifs
            {
                printf("Voici les accessoires acquis:\n");
                afficher(accessoire_acquis);
                printf("Quel accessoire voulez vous donner a %s ? : (N pour Aucun) : ", ((personnage *)tmp->valeur)->nom);
                char choix_joueur[1];
                scanf("%s", &choix_joueur);
                if (choix_joueur[0] == 'N' || choix_joueur[0] == 'n')
                {
                    continue;
                }
                while (atoi(choix_joueur) < 0 || atoi(choix_joueur) >= taille_liste(accessoire_acquis)) // Si le numéro de l'accessoire est invalide
                {
                    printf("Le choix est invalide\n");
                    printf("Quel accessoire voulez vous donner a %s ? : ", ((personnage *)tmp->valeur)->nom);
                    scanf("%s ", &choix_joueur); // On redemande un choix
                }
                ((personnage *)tmp->valeur)->accessoire = (supprimer_num(&accessoire_acquis, atoi(choix_joueur)))->valeur; // On donne l'accessoire au personnage
            }
        }
        printf("le combat commence\n \n");
        ajouter_cellule(&lst_ennemie_actif, supprimer_num(&lst_ennemie, 0)); // On ajoute le premier ennemie à la liste des ennemies actifs
        while (!(fin_combat(lst_personnage_actif, lst_ennemie_actif)))       // Tant que le combat n'est pas fini
        {
            printf("Voici vos personnages :\n");
            afficher(lst_personnage_actif);
            printf("Voici vos ennemies :\n");
            afficher(lst_ennemie_actif);
            int nb_personnage = 0;
            for (cellule *tmp = lst_personnage_actif; tmp; tmp = tmp->suivant, nb_personnage++)
            {
                if (((personnage *)tmp->valeur)->status == INUTILISABLE)
                    continue; // Sert à skip le tour du personnage si il est inutilisable
                printf("Que voulez vous faire avec %s ?\n", ((personnage *)tmp->valeur)->nom);
                printf("1. Attaquer \n");
                printf("2. Defendre \n");
                printf("3. Restorer \n");
                int choix = 0;
                while (choix < 1 || choix > 3) // Tant que le choix n'est pas valide
                {
                    printf("Votre choix : ");
                    scanf("%d", &choix); // On demande un choix
                }
                printf("%d\n", choix);
                if (choix >= 1 && choix <= 3)
                {
                    switch (choix) // On effectue l'action en fonction du choix
                    {
                    case 1: // Attaquer
                        printf("%s attaque\n", ((personnage *)tmp->valeur)->nom);
                        ((personnage *)tmp->valeur)->status = ATTAQUER;                                      // On met le personnage en état d'attaque
                        attaque_personnage((personnage *)tmp->valeur, (ennemie *)lst_ennemie_actif->valeur); // On attaque l'ennemie
                        break;

                    case 2: // Se défendre
                        printf("%s se defend\n", ((personnage *)tmp->valeur)->nom);
                        ((personnage *)tmp->valeur)->status = DEFENDRE; // On met le personnage en état de défense pas besoin d'appeller une fonction ici car on gère la défense dans la fonction attaque_ennemie
                        break;

                    default: // Se soigner
                        printf("%s se soigne\n", ((personnage *)tmp->valeur)->nom);
                        ((personnage *)tmp->valeur)->status = RESTORER; // On met le personnage en état de restauration
                        restaurer((personnage *)tmp->valeur);           // On restaure le personnage
                        break;
                    }
                }
            }
            if (((ennemie *)lst_ennemie_actif->valeur)->HP <= 0) // Si l'ennemie est mort
            {
                free(supprimer_num(&lst_ennemie_actif, 0)); // On le supprime de la liste des ennemies actifs
                continue;                                   // Sert à skip le tour des ennemies si l'ennemie est mort
            }
            printf("Au tour des ennemies\n");
            int att_enemie = rand() % 2;                                           // Permet de choisir aléatoirement si l'ennemie attaque ou stresse le personnage
            int personnage_choisi = (rand() % taille_liste(lst_personnage_actif)); // Permet de choisir aléatoirement le personnage qui va subir l'attaque ou le stress
            liste tmp = lst_personnage_actif;
            for (int i = 0; i < personnage_choisi; i++)
            {
                tmp = tmp->suivant; // Permet de se placer sur le personnage choisi aléatoirement par l'ennemie
            }
            attaque_ennemie(tmp->valeur, lst_ennemie_actif->valeur, att_enemie); // On attaque le personnage choisi
            if (((personnage *)tmp->valeur)->status == MORT)                     // Si le personnage est mort
            {
                free(supprimer_num(&lst_personnage_actif, personnage_choisi)); // On le supprime de la liste des personnages actifs
            }
        } // Fin du tour
        if (fin_combat(lst_personnage_actif, lst_ennemie_actif) == 1) // Si on a perdu le combat
        {
            printf("Vous avez perdu le combat\n");
            break;
        }
        printf("Vous avez gagne le combat\n");
        for (; lst_personnage_actif;) // On parcourt la liste des personnages actifs
        {
            ((personnage *)lst_personnage_actif->valeur)->NBcombat++;     // On incrémente le nombre de combat du personnage
            if (((personnage *)lst_personnage_actif->valeur)->accessoire) // Si le personnage a un accessoire
            {

                ajouter_accessoire(&accessoire_acquis, ((personnage *)lst_personnage_actif->valeur)->accessoire->nom,
                                   (((personnage *)lst_personnage_actif->valeur)->accessoire)->prix,
                                   (((personnage *)lst_personnage_actif->valeur)->accessoire)->attbonus,
                                   (((personnage *)lst_personnage_actif->valeur)->accessoire)->defbonus,
                                   (((personnage *)lst_personnage_actif->valeur)->accessoire)->HPbonus,
                                   (((personnage *)lst_personnage_actif->valeur)->accessoire)->heal_bonus,
                                   (((personnage *)lst_personnage_actif->valeur)->accessoire)->strred, TYPE_ACCESSOIRE); // Permet de copier l'accessoire dans la liste des accessoires initialement équipé par le personnage dans la liste des accessoires acquis la folie le code de malade
                free(((personnage *)lst_personnage_actif->valeur)->accessoire);                                          // On libère la mémoire de l'accessoire équipé par le personnage
                ((personnage *)lst_personnage_actif->valeur)->accessoire = NULL;                                         // Le personnage n'a plus d'accessoire
            }
            ajouter_cellule(&lst_personnage, supprimer_num(&lst_personnage_actif, 0)); // On remet le personnage dans la liste des personnages non actifs
        }
        printf("Vous avez gagne 10 or\n");
        or += 10; // On gagne 10 or à la fin du combat
        printf("Vous avez gagne un accessoire\n");
        int accessoire_choisi = rand() % taille_liste(roulotte);                          // Permet de choisir aléatoirement un accessoire pour avoir gagngé le combat
        ajouter_cellule(&accessoire_acquis, supprimer_num(&roulotte, accessoire_choisi)); // On ajoute l'accessoire à la liste des accessoires acquis
        printf("Voici les accessoires disponibles:\n");
        afficher(accessoire_acquis);
        numero_combat++; // On incrémente le niveau de combat
        printf("Fin du combat\n");
        sanitarium(lst_sanitarium);           // On soigne les personnages du sanitarium
        taverne(lst_taverne);                 // On diminue le stress des personnages de la taverne
        if (taille_liste(lst_sanitarium) > 0) // Si il y a des personnages dans le sanitarium
        {
            printf("Voici les personnages disponibles pour le sanitarium:\n");
            afficher(lst_sanitarium);
            for (liste tmp = lst_sanitarium; tmp; tmp = tmp->suivant)
            {
                printf("Voulez vous faire sortir %s du sanitarium ? (Y/N) : ", ((personnage *)tmp->valeur)->nom);
                char choix[1];
                scanf("%s", choix); // On demande si le joueur veut faire sortir le personnage du sanitarium
                if (choix[0] == 'Y' || choix[0] == 'y')
                {
                    ajouter_cellule(&lst_personnage, supprimer_num(&lst_sanitarium, 0)); // On remet le personnage dans la liste des personnages non actifs
                }
            }
        }
        if (taille_liste(lst_sanitarium) < 2) // Si il y a moins de 2 perso dans le sanitarium
        {
            printf("Vous avez %d place dans le sanitarium, voulez vous faire entrer un personnage ? (Y/N) : ", (2 - taille_liste(lst_sanitarium)));
            char choix[1];
            scanf("%s", choix); // On demande si le joueur veut faire entrer un personnage dans le sanitarium
            if (choix[0] == 'Y' || choix[0] == 'y')
            {
                printf("Voici les personnages disponibles pour le sanitarium:\n");
                afficher(lst_personnage);
                int nb_personnage = 0;
                do
                {
                    printf("Combien de personnage voulez vous mettre dans la sanitarium ? : ");
                    scanf("%d", &nb_personnage); // On demande combien de personnage le joueur veut mettre dans le sanitarium
                } while (nb_personnage > 2 || nb_personnage < 0); // Tant que le nombre de personnage est invalide
                for (int i = 0; i < nb_personnage; i++)
                {
                    printf("Voici les personnages disponibles pour le sanitarium:\n");
                    afficher(lst_personnage);
                    printf("Quel personnage voulez vous mettre dans le sanitarium ? : ");
                    int choix = 0;
                    scanf("%d", &choix);                                    // On demande quel personnage le joueur veut mettre dans le sanitarium
                    if (choix < 0 || choix >= taille_liste(lst_personnage)) // Si le numéro de personnage est invalide
                    {
                        printf("Le choix est invalide\n");
                        i--; // On refait le dernier choix
                        continue;
                    }
                    ajouter_cellule(&lst_sanitarium, supprimer_num(&lst_personnage, choix)); // On met le personnage dans le sanitarium
                }
            }
        }
        if (taille_liste(lst_taverne) > 0) // Si il y a des personnages dans la taverne
        {
            printf("Voici les personnages disponibles pour la taverne:\n");
            afficher(lst_taverne);
            for (liste tmp = lst_taverne; tmp; tmp = tmp->suivant) // On parcourt la liste des personnages de la taverne
            {
                printf("Voulez vous faire sortir %s de la taverne ? (Y/N) : ", ((personnage *)tmp->valeur)->nom);
                char choix[1];
                scanf("%s", choix); // On demande si le joueur veut faire sortir le personnage de la taverne
                if (choix[0] == 'Y' || choix[0] == 'y')
                {
                    ajouter_cellule(&lst_personnage, supprimer_num(&lst_taverne, 0)); // On remet le personnage dans la liste des personnages non actifs
                }
            }
        }
        if (taille_liste(lst_taverne) < 2) // Si il y a moins de 2 perso dans la taverne
        {
            printf("Vous avez %d place dans la taverne, voulez vous faire entrer un personnage ? (Y/N) : ", 2 - taille_liste(lst_taverne));
            char choix[1];
            scanf("%s", choix); // On demande si le joueur veut faire entrer un personnage dans la taverne
            if (choix[0] == 'Y' || choix[0] == 'y')
            {
                printf("Voici les personnages disponibles pour la taverne:\n");
                afficher(lst_personnage);
                int nb_personnage = 0;
                do
                {
                    printf("Combien de personnage voulez vous mettre dans la taverne ? : ");
                    scanf("%d", &nb_personnage); // On demande combien de personnage le joueur veut mettre dans la taverne
                } while (nb_personnage > 2 || nb_personnage < 0); // Tant que le nombre de personnage est invalide
                for (int i = 0; i < nb_personnage; i++)
                {
                    printf("Voici les personnages disponibles pour la taverne:\n");
                    afficher(lst_personnage);
                    printf("Quel personnage voulez vous mettre dans la taverne ? : ");
                    int choix = 0;
                    scanf("%d", &choix);                                    // On demande quel personnage le joueur veut mettre dans la taverne
                    if (choix < 0 || choix >= taille_liste(lst_personnage)) // Si le numéro de personnage est invalide
                    {
                        printf("Le choix est invalide\n");
                        i--; // On refait le dernier choix
                        continue;
                    }
                    ajouter_cellule(&lst_taverne, supprimer_num(&lst_personnage, choix)); // On met le personnage dans la taverne
                }
            }
        }
    }
    return 0;
}