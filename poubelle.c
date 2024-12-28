classe* allouer_classe(classe *c, int nb){
    c = (classe *)malloc(nb * sizeof(classe));
    return c;
}

personnage* allouer_personnage(personnage *p, int nb){
    p = (personnage *)malloc(nb * sizeof(personnage));
    return p;
}

ennemie* allouer_ennemie(ennemie *e, int nb){
    e = (ennemie *)malloc(nb * sizeof(ennemie));
    return e;
}

accessoire* allouer_accessoire(accessoire *a, int nb){
    a = (accessoire *)malloc(nb * sizeof(accessoire));
    return a;
}



void afficher_classe(classe *c){
    printf("Nom : %s\n", c->nom);
    printf("Attaque : %d\n", c->att);
    printf("Defense : %d\n", c->def);
    printf("HPmax : %d\n", c->HPmax);
    printf("Restauration : %d\n", c->rest);
}