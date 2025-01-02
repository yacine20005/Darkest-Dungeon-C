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