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