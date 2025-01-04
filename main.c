#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h" //Permet d'importer les structs du fichier structures.h
#include <time.h>


int taille_liste(liste lst)
{
    int taille = 0;
    for(cellule *tmp = lst; tmp; tmp = tmp->suivant, taille++)
        ;//Boucle vide pour compter le nombre de cellules
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
            printf("Liste des classes:\n");
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
            printf("Liste des personnages:\n");
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
            printf("Liste des accessoires:\n");
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
            printf("Liste des ennemies:\n");
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


int fin_combat(liste lst_personnage_actif, liste lst_ennemie_actif){
    if(taille_liste(lst_personnage_actif) == 0)
    {
        return 1;
    }
    if(taille_liste(lst_ennemie_actif) == 0)
    {
        return 2;
    }
    return 0;
}


void attaque_personnage(personnage *perso, ennemie *ennemi)
{
    int att_total = perso->classe_perso.att;
    if(perso->accessoire)
    {
        att_total += ((accessoire *)perso->accessoire)->attbonus;
    }
    if(att_total - ennemi -> def > 0)
    {
        att_total = (att_total - ennemi->def) * ((rand() % 41 + 80) / 100.0);
    }
    else
    {
       att_total = 1;
    }
    ennemi->HP -= att_total;
    printf("L'ennemie %s a perdu %d HP, il est maintenant a %d HP\n", ennemi->nom, att_total, ennemi->HP);
}

void attaque_ennemie(personnage *perso, ennemie *ennemi, int type)
{
    if(perso->status == INUTILISABLE)
        type = 0;
    if(type == 1){
        int attstrenn = ennemi->attstr;
        int strred = 0;
        if(perso->accessoire)
        {
            strred = ((accessoire *)perso->accessoire)->strred;
        }
        attstrenn = (attstrenn - strred) * ((rand() % 41 + 80) / 100.0);
        perso -> stress += attstrenn;
        printf("%s a subi %d stress, il est maintenant a %d stress\n", perso->nom, attstrenn, perso->stress);
        if(perso->stress >= 100)
        {
            perso->status = INUTILISABLE;
            printf("Le personnage %s a atteins 100 ou plus de stress est inutilisable \n", perso->nom);
        }
    }
    else{
    int def_total = perso->classe_perso.def;
    if(perso->accessoire)
    {
        def_total += ((accessoire *)perso->accessoire)->defbonus;
    }
    if(perso -> status == DEFENDRE){
        def_total *= 1.10;
    }
    int att_total = (att_total - perso->classe_perso.def) * ((rand() % 41 + 80) / 100.0);
    perso->HP -= att_total;
    if(perso->HP <= 0)
    {
        perso->status = MORT;
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
    int hpgagner = perso -> classe_perso.rest;
    if(perso->accessoire)
    {
        hpgagner += ((accessoire *)perso->accessoire)->heal_bonus;
    }
    if(perso->HP + hpgagner >= perso->classe_perso.HPmax)
    {
        perso->HP = perso->classe_perso.HPmax;
    }
    else
    {
        perso->HP += hpgagner;
    }
}

void taverne(liste taverne){
    for(cellule *tmp = taverne; tmp; tmp = tmp->suivant){
        ((personnage *)tmp->valeur)->stress -= 25;
        if(((personnage *)tmp->valeur)->stress < 0){
            ((personnage *)tmp->valeur)->stress = 0;
            ((personnage *)tmp->valeur)->status = ATTAQUER;
        }
    }
}

void sanitarium(liste sanitarium){
    for(cellule *tmp = sanitarium; tmp; tmp = tmp->suivant){
        ((personnage *)tmp->valeur)->HP += 7;
        if(((personnage *)tmp->valeur)->HP > ((personnage *)tmp->valeur)->classe_perso.HPmax){
            ((personnage *)tmp->valeur)->HP = ((personnage *)tmp->valeur)->classe_perso.HPmax;
        }  
        }
    } 


int main(void)
{
    liste lst_classe = NULL;
    liste lst_personnage = NULL;
    liste lst_personnage_actif = NULL;
    liste roulotte = NULL; //liste accessoire, on change le nom pour correspondre au sujet
    liste accessoire_acquis = NULL;
    liste lst_ennemie = NULL;
    liste lst_ennemie_actif = NULL;
    liste sanitarium = NULL;
    liste taverne = NULL;
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



    ajouter_accessoire(&roulotte, "Bouclier", 10, 0, 5, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Epee", 15, 5, 0, 0, 0, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Potion de soin", 10, 0, 0, 0, 5, 0, TYPE_ACCESSOIRE);
    ajouter_accessoire(&roulotte, "Potion de stress", 10, 0, 0, 0, 0, 5, TYPE_ACCESSOIRE);
    

    ajouter_ennemie(&lst_ennemie, "Patient 13", 10, 20, 18, 75, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Mamadou", 9, 18, 16, 60, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Bernard", 8, 16, 14, 55, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Staline", 7, 14, 12, 40, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Adolph Hitler", 6, 12, 10, 35, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Oryx", 5, 10, 8, 30, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Athéon", 4, 8, 6, 25, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Priscillia", 3, 6, 4, 20, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Minotaure", 2, 4, 2, 15, 0, TYPE_ENNEMIE);
    ajouter_ennemie(&lst_ennemie, "Goblin", 1, 2, 0, 10, 10, TYPE_ENNEMIE);

    

    while(numero_combat < 10){
        printf("Combat numero %d\n", numero_combat);
        if(numero_combat % 2 == 0){
            perso_max++;
        }
        for(int num = 0; num < perso_max; num++){
            printf("Voici les personnages disponible:\n");
            afficher(lst_personnage);
            printf("Voici les personnages actifs:\n");
            afficher(lst_personnage_actif);
            char choix[10];
            printf("Choix du personnage numero %d/%d (ou 'N' pour ne pas choisir) : ", num + 1, perso_max);
            scanf("%s", choix);
            printf("\n");
            if (choix[0] == 'N' || choix[0] == 'n' && taille_liste(lst_personnage_actif) > 0) {
                continue;
            }
            else if (choix[0] == 'N' || choix[0] == 'n' && taille_liste(lst_personnage_actif) == 0) {
                printf("Vous devez choisir au moins un personnage\n");
                num--;
                continue;
            }
            int choix_num = atoi(choix);
            if (choix_num < 0 || choix_num >= taille_liste(lst_personnage)) {
                printf("Le choix est invalide\n");
                num--;
                continue;
            }
            ajouter_cellule(&lst_personnage_actif, supprimer_num(&lst_personnage,  choix_num));
        }
        printf("Voici les accessoires disponibles:\n");
        afficher(roulotte);
        printf("Vous avez %d or\n", or);
        char choix[1];
        printf("Quelle accessoire voulez vous achetez (Q pour quitter) : ");
        scanf("%s", choix);
        while(choix[0] != 'Q' && choix[0] != 'q'){
            int choix_num = atoi(choix);
            if (choix_num < 0 || choix_num >= taille_liste(roulotte))
            {
                printf("Le choix est invalide\n");
            }
            else
            {
                if(((accessoire *)roulotte->valeur)->prix > or){
                    printf("Vous n'avez pas assez d'or\n");
                    printf("Vous avez %d or\n", or);
                    printf("Quelle accessoire voulez vous achetez (Q pour quitter) : ");
                    scanf("%s", choix);
                    continue;
                }
                ajouter_cellule(&accessoire_acquis, supprimer_num(&roulotte, choix_num));
                or -= ((accessoire *)accessoire_acquis->valeur)->prix;
            }
            printf("Voici les accessoires disponibles:\n");
            afficher(roulotte);
            printf("Vous avez %d or\n", or);
            printf("Quelle accessoire voulez vous achetez (Q pour quitter : ");
            scanf("%s", choix);
        }
        printf("Voici les accessoires acquis:\n");
        afficher(accessoire_acquis);


        for(cellule *tmp = lst_personnage_actif; tmp && taille_liste(accessoire_acquis); tmp = tmp->suivant){
            printf("Quel accessoire voulez vous donner a %s ? : (N pour Aucun)", ((personnage *)tmp->valeur)->nom);
            char choix_joueur[1];
            scanf("%s", &choix_joueur);
            if(choix_joueur[0] == 'N' || choix_joueur[0] == 'n'){
                continue;
            }
            while(atoi(choix_joueur) < 0 || atoi(choix_joueur) >= taille_liste(accessoire_acquis)){
                printf("Le choix est invalide\n");
                printf("Quel accessoire voulez vous donner a %s ? : ", ((personnage *)tmp->valeur)->nom);
                scanf("%s ", &choix_joueur);
            }
            ((personnage *)tmp->valeur)->accessoire = (supprimer_num(&accessoire_acquis, atoi(choix_joueur))) -> valeur;
            }


        printf("le combat commence\n \n");
        ajouter_cellule(&lst_ennemie_actif, supprimer_num(&lst_ennemie, 0));
        while(!(fin_combat(lst_personnage_actif, lst_ennemie_actif))){
            printf("Voici vos personnages :\n");
            afficher(lst_personnage_actif);
            printf("Voici vos ennemies :\n");
            afficher(lst_ennemie_actif);
            int nb_personnage = 0;
            for(cellule *tmp = lst_personnage_actif; tmp; tmp = tmp->suivant, nb_personnage++){
                if(((personnage *)tmp->valeur)->status == INUTILISABLE)
                    continue;
                printf("Que voulez vous faire avec %s ?\n", ((personnage *)tmp->valeur)->nom);
                printf("1. Attaquer \n");
                printf("2. Defendre \n");
                printf("3. Restorer \n");
                int choix = 0;
                while(choix < 1 || choix > 3){
                    printf("Votre choix : ");
                    scanf("%d", &choix);
                }
                printf("%d\n", choix);
                if(choix >= 1 && choix <= 3){
                    switch (choix)
                    {
                    case 1:
                        printf("%s attaque\n", ((personnage *)tmp->valeur)->nom);
                        ((personnage *)tmp->valeur)->status = ATTAQUER;
                        attaque_personnage((personnage *)tmp->valeur, (ennemie *)lst_ennemie_actif->valeur);
                        break;
                    
                    case 2:
                        printf("%s se defend\n", ((personnage *)tmp->valeur)->nom);
                        ((personnage *)tmp->valeur)->status = DEFENDRE;
                        break;

                    default:
                        printf("%s se soigne\n", ((personnage *)tmp->valeur)->nom);
                        ((personnage *)tmp->valeur)->status = RESTORER;
                        restaurer((personnage *)tmp->valeur);
                        break;
                    }
                }
            }
            if(((ennemie *)lst_ennemie_actif->valeur)->HP <= 0){
                free(supprimer_num(&lst_ennemie_actif, 0));
                continue;
            }
            printf("Au tour des ennemies\n");
            int att_enemie = rand() % 2;
            int personnage_choisi = (rand() % taille_liste(lst_personnage_actif)) -1;
            liste tmp = lst_personnage_actif;
            for(int i = 0; i < personnage_choisi; i++){
                tmp = tmp->suivant;
            }
            attaque_ennemie(tmp -> valeur, lst_ennemie_actif -> valeur , att_enemie);
        }
        if(fin_combat(lst_personnage_actif, lst_ennemie_actif) == 1){
            printf("Vous avez perdu le combat\n");
            break;
        }
        printf("Vous avez gagne le combat\n");
        for(; lst_personnage_actif; ){
            ((personnage*) lst_personnage_actif -> valeur) -> NBcombat++;
            if(((personnage*) lst_personnage_actif -> valeur) -> accessoire){

                ajouter_accessoire(&accessoire_acquis, ((personnage *) lst_personnage_actif -> valeur) -> accessoire -> nom, 
                    (((personnage *) lst_personnage_actif -> valeur) -> accessoire) -> prix, 
                    (((personnage *) lst_personnage_actif -> valeur) -> accessoire) -> attbonus, 
                    (((personnage *) lst_personnage_actif -> valeur) -> accessoire) -> defbonus, 
                    (((personnage *) lst_personnage_actif -> valeur) -> accessoire) -> HPbonus, 
                    (((personnage *) lst_personnage_actif -> valeur) -> accessoire) -> heal_bonus, 
                    (((personnage *) lst_personnage_actif -> valeur) -> accessoire) -> strred, TYPE_ACCESSOIRE);
                free(((personnage *)lst_personnage_actif -> valeur) -> accessoire); 
                ((personnage*) lst_personnage_actif -> valeur) -> accessoire = NULL;
            }
            ajouter_cellule(&lst_personnage, supprimer_num(&lst_personnage_actif, 0));
        }
        printf("Vous avez gagne 10 or\n");
        printf("Vous avez gagne un accessoire\n");
        int accessoire_choisi = rand() % taille_liste(roulotte);
        ajouter_cellule(&accessoire_acquis, supprimer_num(&roulotte, accessoire_choisi));
        printf("Voici les accessoires disponibles:\n");
        afficher(accessoire_acquis);
        or += 10;
        numero_combat++;
        printf("Fin du combat\n");
        printf("%d \n", taille_liste(sanitarium));
        if(taille_liste(sanitarium) > 0){
            printf("Voici les personnages disponibles pour le sanitarium:\n");
            afficher(sanitarium);
            for(liste tmp = sanitarium; tmp; tmp = tmp->suivant){
                printf("Voulez vous faire sortir %s du sanitarium ? (Y/N) : ", ((personnage *)tmp->valeur)->nom);
                char choix[1];
                scanf("%s", choix);
                if(choix[0] == 'Y' || choix[0] == 'y'){
                    ajouter_cellule(&lst_personnage, supprimer_num(&sanitarium, 0));
                }
            }
        }
        printf("%d \n", taille_liste(sanitarium));
        if(taille_liste(sanitarium) < 2) {
            printf("Vous avez %d place dans le sanitarium, voulez vous faire entrer un personnage ? (Y/N) : ", (2 - taille_liste(sanitarium)));
            char choix[1];
            scanf("%s", choix);
            if(choix[0] == 'Y' || choix[0] == 'y'){
                printf("Voici les personnages disponibles pour le sanitarium:\n");
                afficher(lst_personnage);
                int nb_personnage = 0;
                do{
                printf("Combien de personnage voulez vous mettre dans la sanitarium ? : ");
                scanf("%d", &nb_personnage); } while(nb_personnage > 2 || nb_personnage < 0);
                for(int i = 0; i < nb_personnage; i++){
                    printf("Quel personnage voulez vous mettre dans le sanitarium ? : ");
                    int choix = 0;
                    scanf("%d", &choix);
                    if(choix < 0 || choix >= taille_liste(lst_personnage)){
                        printf("Le choix est invalide\n");
                        i--;
                        continue;
                    }
                    ajouter_cellule(&sanitarium, supprimer_num(&lst_personnage, choix));
                }      
            }
        
        }
        if(taille_liste(taverne) > 0){
            printf("Voici les personnages disponibles pour la taverne:\n");
            afficher(taverne);
            for(liste tmp = taverne; tmp; tmp = tmp->suivant){
                printf("Voulez vous faire sortir %s de la taverne ? (Y/N) : ", ((personnage *)tmp->valeur)->nom);
                char choix[1];
                scanf("%s", choix);
                if(choix[0] == 'Y' || choix[0] == 'y'){
                    ajouter_cellule(&lst_personnage, supprimer_num(&taverne, 0));
                }
             }
        }
        if(taille_liste(taverne) < 2) {
            printf("Vous avez %d place dans la taverne, voulez vous faire entrer un personnage ? (Y/N) : ", 2 - taille_liste(taverne));
            char choix[1];
            scanf("%s", choix);
            if(choix[0] == 'Y' || choix[0] == 'y'){
                printf("Voici les personnages disponibles pour la taverne:\n");
                afficher(lst_personnage);
                int nb_personnage = 0;
                do{
                printf("Combien de personnage voulez vous mettre dans la taverne ? : ");
                scanf("%d", &nb_personnage); } while(nb_personnage > 2 || nb_personnage < 0);
                for(int i = 0; i < nb_personnage; i++){
                    printf("Quel personnage voulez vous mettre dans la taverne ? : ");
                    int choix = 0;
                    scanf("%d", &choix);
                    if(choix < 0 || choix >= taille_liste(lst_personnage)){
                        printf("Le choix est invalide\n");
                        i--;
                        continue;
                    }
                    ajouter_cellule(&taverne, supprimer_num(&lst_personnage, choix));
                }
            }
        }
    }
    return 0;
}



