typedef struct {
    char nom[10];
    int att;
    int def;
    int HPmax;
    int rest; // Points de restauration, notés rest, qui permettent de soigner un camarade.
} classe;

typedef struct {
    char nom[20];
    classe type;
    int HP; // Points de vie actuelle != points de vie max de la classe 
    int str; // Points de stress conformement au sujet !
    int nbcomb; // Nombre de combat auquel il a participé
} personnage; 

typedef struct {
    char nomaccess[20];
    int prix;
    int attbonus;
    int defbonus;
    int HPbonus;
    int restbonus;
    int strred; // des points qui diminueront les attaques de stress de l'ennemi.
} accessoire;

typedef struct {
    char nomenem[20];
    int niveauenn;
    int attenn;
    int defenn;
    int HPenn;
    int attstrenn;
} ennemie;

typedef struct {
    personnage *perso;
    int *cellule;
} cellule;

typedef struct {
    accessoire *item;
    int *roulotte;
} roulotte;


void initclasse(classe *c,  char nom[20], int att, int def, int hpmax, int rest){
    c -> att = att; 
    c -> def = def;
    c -> HPmax = hpmax;
    c -> rest = rest;
};

void initpersonnage(personnage *p,  char nom[20], classe *type){
    p -> type = *type; 
    p -> HP = type -> HPmax;
    p -> str = 0;
    p -> nbcomb = 0;
};

void initaccessoire(accessoire *a, char nom[20], int prixa, int attb, int defb, int HPb, int restb, int strredb) {
    //a -> nomaccess = nom;
    a -> prix = prixa;
    a -> attbonus = attb;
    a -> defbonus = defb;
    a -> HPbonus = HPb;
    a -> restbonus = restb;
    a -> strred = strredb;
}

void initennemie(ennemie *e, char nomenem[20], int niveau, int att, int def, int HP, int attstr){
   
    /* strncpy(e->nomenem, nomenem, sizeof(e->nomenem) - 1);
    e->nomenem[sizeof(e->nomenem) - 1] = '\0'; */

    e->niveauenn = niveau;
    e->attenn = att;
    e->defenn = def;
    e->HPenn = HP;
    e->attstrenn = attstr;
}