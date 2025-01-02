/* Page 2 du PDF : 
"On imp ose les 4 classes suivantes. Vous p ourrez changer les valeurs des attributs p our tester
et adapter le niveau de difficultée du jeu aux ennemis que vous aurez créés."
*/


ajouter_classe(&lst_classe, "Chien", 5, 2, 10, 0, TYPE_CLASSE);
ajouter_classe(&lst_classe, "Terroriste", 15, 0, 20, 0, TYPE_CLASSE);
ajouter_classe(&lst_classe, "ADC", 20, 0, 20, 0, TYPE_CLASSE);
ajouter_classe(&lst_classe, "Support", 5, 12, 20, 10, TYPE_CLASSE);


ajouter_personnage(&lst_personnage, &lst_classe, "Maxime", "ADC", TYPE_PERSONNAGE);
ajouter_personnage(&lst_personnage, &lst_classe, "Esteban", "Support", TYPE_PERSONNAGE);



    while(numero_combat < 10){
        printf("Combat numero %d\n", numero_combat);
        for(int num = 0; num < perso_max; num++){
            printf("Voici les personnages disponible:\n");
            afficher(lst_personnage);
            printf("Voici les personnages actifs:\n");
            afficher(lst_personnage_actif);
            char choix[10];
            printf("Choix du personnage numéro %d (ou 'N' pour ne pas choisir) : ", num);
            scanf("%s", choix);
            printf("\n");
            if (choix[0] == 'N' || choix[0] == 'n') {
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
        scanf("%s", choix);



        printf("le combat commence\n \n");
        afficher(lst_ennemie_actif);
        while(!(fin_combat(lst_personnage_actif, lst_ennemie_actif))){
            printf("Voici vos personnages :\n");
            afficher(lst_personnage_actif);
            printf("Voici vos ennemies :\n");
            afficher(lst_ennemie_actif);
            printf("Que voulez vous faire ?\n");
            printf("1. Attaquer \n");
            printf("2. Defendre \n");
            printf("3. Restorer \n");
        }
        
        or += 10;
        numero_combat++;
    }


    return 0;