#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
//#include <ncurse.h>

//Simple balancing test for the combat system, not taken into account in the project

typedef enum class {
    ARCHER,
    SORCIER,
    GUERRIER,
} Class;

typedef struct {
    char *nom;
    Class current_class;
    int attaque;
    int defense;
    int esquive;
    int vie;
    int exp;
} Joueur;


// check scan

void flush() {
    int a;
    char c;
    do {
        a = scanf("%c", &c);
    } while (a == 1 && c != '\n');
}


// create player model

Joueur *creerJoueur() {
    Joueur *j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if (j == NULL) {
        exit(1);
    }
    // Create first name

    char tab[51];
    int reset = 0;

    do {
        reset = 0;
        printf("Saissisez le nom du joueur :\n");
        reset = scanf("%50[^\n]", tab);
        flush();
        if (strlen(tab) <= 0 || strlen(tab) >= 50) {
            printf("Prenom incorrect\n");
        }
    } while ((reset != 1)|| (strlen(tab) <= 0) || (strlen(tab) >= 50));


    (*j).nom = malloc((strlen(tab) + 1) * sizeof(char));
    if ((*j).nom == NULL) {
        exit(404);
    }
    strcpy((*j).nom, tab);
    // Vie
    j->vie = 1250;
    // Exp
    j->exp = 2000;
    // Return result
    return j;
}


Joueur *creerCradorien() {
    Joueur *j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if (j == NULL) {
        exit(1);
    }
    // Create first name
    char tab[256];
    int res = 0;
    char *tmp = "Guerrier Cradorien";
    if (strlen(tmp) > 0) {
        j->nom = malloc(((strlen(tmp) + 1) * sizeof(char)));
    }
    if (j->nom == NULL) {
        exit(404);
    }
    strcpy(j->nom, tmp);
    // Vie
    j->vie = 20;
    // Return result
    return j;
}

//Create boss 1

Joueur *creerBoss1() {
    Joueur *j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if (j == NULL) {
        exit(1);
    }
    // Create first name
    char tab[256];
    int res = 0;
    char *laz = "Lazarus";
    if (strlen(laz) > 0) {
        j->nom = malloc(((strlen(laz) + 1) * sizeof(char)));
    }
    if (j->nom == NULL) {
        exit(404);
    }
    strcpy(j->nom, laz);

    // Vie
    j->vie = 125;
    // Return result
    return j;
}

// create boss 2

Joueur *creerBoss2() {
    Joueur *j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if (j == NULL) {
        exit(1);
    }
    // Create first name
    char tab[256];
    int res = 0;
    char *tmp = "Xaroth";
    if (strlen(tmp) > 0) {
        j->nom = malloc(((strlen(tmp) + 1) * sizeof(char)));
    }
    if (j->nom == NULL) {
        exit(404);
    }
    strcpy(j->nom, tmp);

    // Vie
    j->vie = 150;
    // Return result
    return j;
}

// create boss 3

Joueur *creerBoss3() {
    Joueur *j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if (j == NULL) {
        exit(1);
    }
    // Create first name
    char tab[256];
    int res = 0;
    char *tmp = "Morlok";
    if (strlen(tmp) > 0) {
        j->nom = malloc(((strlen(tmp) + 1) * sizeof(char)));
    }
    if (j->nom == NULL) {
        exit(404);
    }
    strcpy(j->nom, tmp);

    // Vie
    j->vie = 175;
    // Return result
    return j;
}


//Inventaire


typedef enum material {
    COUPE,
    EPEE,
    CRANE,
    TETE_DE_CRADORIEN,
    ITEM5,
} Material;

typedef struct {
    Material materials;
    int quantite;
} Item;


typedef struct {
    int capacite;
    int quantite;
    Item *item;
} Inventaire;



// Fonction pour initialiser l'inventaire (capacité de 3 item)

Inventaire *initialiserInv() {
    Inventaire *p = NULL;
    p = malloc(sizeof(Inventaire));
    if (p == NULL) {
        exit(2);
    }
    p->capacite = 3;
    p->quantite = 0;
    p->item = malloc(sizeof(Item) * p->capacite);
    if (p->item == NULL) {
        exit(3);
    }
    return p;

}

// FOnction pour ajouter item

void ajoutItem(Inventaire *p, Material material) {
    if (p == NULL || p->item == NULL) {
        exit(1);
    }
    for (int i = 0; i < p->quantite; i++){
        if (p->item[i].materials == material) {
                p->item[i].quantite ++;
                return;
            }
        }
 
    if (p->quantite < p->capacite) {
        p->item[p->quantite].materials = material;
        p->item[p->quantite].quantite = 1;
        p->quantite++;
    } else {
        printf("Inventaire rempli !\n");
    }
}


//Fonction pour verifier son inventaire

void afficheInv(Inventaire *p) {
    if (p == NULL || p->item == NULL) {
        exit(1);
    }
    printf("Voici votre inventaire :\n");
    for (int i = 0; i < p->quantite; i++) {
        switch (p->item[i].materials) {
            case COUPE:
                printf("COUPE\n");
                break;
            case EPEE:
                printf("EPEE\n");
                break;
            case CRANE:
                printf("CRANE\n");
                break;
            case TETE_DE_CRADORIEN:
                printf("TETE DE CRADORIEN x%d\n", p->item[i].quantite);
                break;
            case ITEM5 :
                printf("ITEM5\n");
                break;
            default:
                printf("Item inconnu\n");
                break;
        }
    }
}


// Creation Abilité


void resetData(Joueur *j) {
    if (j == NULL || j->nom == NULL) {
        exit(1);
    }
    switch (j->current_class) {
        case ARCHER:
            j->attaque = rand() % 3 + 5;
            j->defense = rand() % 4 + 2;
            j->esquive = rand() % 6 + 2;
            break;
        case SORCIER:
            j->attaque = rand() % 3 + 3;
            j->defense = rand() % 4 + 4;
            j->esquive = rand() % 9 + 4;
            break;
        case GUERRIER:
            j->attaque = rand() % 5 + 7;
            j->defense = 0;
            j->esquive = 0;

    }
}

// Reset archer

void resetArcher(Joueur *a) {
    if (a == NULL || a->nom == NULL) {
        exit(404);
    }
    a->current_class = ARCHER;
    resetData(a);
}

// Reset wizard
void resetSorcier(Joueur *a) {
    if (a == NULL || a->nom == NULL) {
        exit(404);
    }
    a->current_class = SORCIER;
    resetData(a);
}

// Reset Warrior
void resetGuerrier(Joueur *a) {
    if (a == NULL || a->nom == NULL) {
        exit(404);
    }
    a->current_class = GUERRIER;
    resetData(a);
}



//reset Cradorien

void resetCradorien(Joueur *b) {
    if (b == NULL || b->nom == NULL) {
        exit(404);
    }
    b->attaque = rand() % 4 + 2;
    b->defense = 0;
    b->esquive = 0;
}

// reset boss 1


void resetBoss1(Joueur *b) {
    if (b == NULL || b->nom == NULL) {
        exit(404);
    }
    b->attaque = rand() % 5 + 5;
    b->defense = 0;
    b->esquive = 0;
}

//reset boss 2

void resetBoss2(Joueur *b) {
    if (b == NULL || b->nom == NULL) {
        exit(404);
    }
    b->attaque = rand() % 5 + 5;
    b->defense = 0;
    b->esquive = 0;


}

// reset boss 3

void resetBoss3(Joueur *b) {
    if (b == NULL || b->nom == NULL) {
        exit(404);
    }
    b->attaque = rand() % 4 + 9; // 8 à 13
    b->defense = rand() % 3 + 2;
    b->esquive = rand() % 3 + 1;

}

// fonction shop 



void shopExp(Joueur *a, Joueur *b) {
    if (b == NULL || b->nom == NULL || a == NULL || a->nom == NULL) {
        exit(404);
    }


    printf("Bienvenu dans la taverne de Garedon !\n");
    printf("Vous possédez actuellement %d ame(s) de Morlok !\n", a->exp);
    printf("Voici les services proposés par Garedon :\n");
    printf("1 - Fiole de vie : La vie n'a pas de prix ! (+100 points de vie)\n");
    printf("Prix : 10 ames de Morlok\n");
    printf("2 - Pari risqué : Qui ne tente rien n'a rien ! (1 chances sur 2 de doubler sa mise)\n");
    printf("Prix : 15 ames de Morlok\n");
    printf("3 - Mort instantané : L'ennemi est mort ! (Tue instantannément l'ennemi)\n");
    printf("Prix : 150 ames de Morlok\n");
    printf("4 - Ne rien acheter\n");
    int res = 0;
    int C = 0;
    int ran = 0;
    int count1 = 0;
    char E;

    do {


        printf("Choisissez le numero correspondant au service voulu :\n");
        res = scanf("%1d%c", &C, &E);
            if(res != 2 || C < 1 || C > 4 || E != '\n'){
                if(count1 != 5 && count1 != 4){
                printf("Veuillez entrer un chiffre entre 1 et 4\n");
                }
                count1++;
                
                flush();
            }
            else if((C == 1 && a->exp < 10) || (C == 2 && a->exp < 15) || (C == 3 && a->exp < 150)) {
                    printf("Ame(s) de Morlok insuffisante(s)\n");
                    flush();
                    count1++;
            }
            
            

            if (count1 == 5) {
                    printf("Garedon n'aime pas perdre son temps. La boutique est fermé\n");
                    printf("Ame(s) de Morlok restant: %d\n", a->exp);
                    break;
                    flush();
            }   

             
    } while (res != 2 ||  E != '\n' || C < 1 || C > 4 || (C == 1 && a->exp < 10) || (C == 2 && a->exp < 15) || (C == 3 && a->exp < 150));


    switch (C) {
        case 1:
            if (count1 == 5) {
                break;
            }
            a->exp -= 10;
            printf("Ame(s) de Morlok restant(s) : %d\n", a->exp);
            printf("Point de vie : %d\n", a->vie);
            sleep(1);
            for (int i = 0; i <= 5; i++){
                printf("Consommation de la fiole : %d%% \n", 20*i);
                sleep(1);
            }
            a->vie += 100;
            printf("Fiole consommé !\n");
            break;
        case 2:
            if (count1 == 5) {
                break;
            }
            ran = rand() % 2 + 1;
            if (ran == 1) {
                printf("Vous avez perdu votre mise\n");
                a->exp -= 15;
                printf("Ame(s) de Morlok restant(s) : %d\n", a->exp);
            }
            if (ran == 2) {
                printf("Vous avez gagne !\n");
                a->exp += 15;
                printf("Ame(s) de Morlok restant(s) : %d\n", a->exp);
            }
            break;
        case 3:
            if (count1 == 5) {
                break;
            }
            b->vie = 0;
            a->exp -= 150;
            printf("Ame(s) de Morlok restant(s) : %d\n", a->exp);
            for (int i = 0; i <= 5; i++){
                printf("Invocation en cours : %d%% \n", 20*i);
                sleep(1);
            }
            printf("Invocation prête !\n");
            break;
        case 4:
            if (count1 == 5) {
                break;
            }
            if(a->exp <10){
                printf("Un vrai guerrier se doit de gagner des ames de Morlok...\n");
            }
            else{
                printf("Un vrai guerrier se doit d'utiliser ses ames de Morlok...\n");
            }
    }

}



// Creation Combat


void combat(Joueur *a, Joueur *b, int N, Inventaire *i1) {
    if (a == NULL || b == NULL) {
        exit(1);
    }

    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 5 à 7\n Defense : 2 à 5\n Esquive: 2 à 7\n");
    printf("2 : Sorcier :\n Attaque : 3 à 5\n Defense : 4 à 7\n Esquive: 4 à 12\n");
    printf("3 : Guerrier :\n Attaque : 7 à 11\n Defense : 0\n Esquive: 0\n");


    int res = 0;
    N = 0;
    char EX;
    do {
        printf("Quelle classe voulez-vous choisir ? : ");
        res = scanf("%1d%c", &N, &EX);
            if (res != 2 || N < 1 || N > 3 || EX != '\n') {
                printf("Veuillez choisir un nombre entre 1 et 3\n");
                flush();
            } 
    } while (res != 2 ||EX != '\n' || N < 1 || N > 3);



    switch (N) {
        case 1:
            resetArcher(a);
            resetCradorien(b);
            break;
        case 2:
            resetSorcier(a);
            resetCradorien(b);
            break;
        case 3:
            resetGuerrier(a);
            resetCradorien(b);
            break;
    }

    shopExp(a, b);
    sleep(1);
    printf("Point de vie : %d\n", a->vie);
    sleep(1);

    printf("Debut du combat ! :\n");


    while (a->vie > 0 && b->vie >= 0) {


        usleep(500000);
        resetData(a);
        resetCradorien(b);


        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            a->exp += 2;
            printf("Ame(s) de Morlok : %d\n", a->exp);
            ajoutItem(i1, TETE_DE_CRADORIEN);
            afficheInv(i1);
            break;
        }


        if (a->attaque < b->esquive) {
            printf("%s esquive l'attaque de %s!\n", b->nom, a->nom);
        } else {
            int degats = a->attaque - b->defense;
            if (degats < 0) degats = 0;
            b->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", a->nom, b->nom, degats);
        }

        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            a->exp += 2;
            printf("Ame(s) de Morlok : %d\n", a->exp);
            ajoutItem(i1, TETE_DE_CRADORIEN);
            afficheInv(i1);
            break;
        }


        if (b->attaque < a->esquive) {
            printf("%s esquive l'attaque de %s!\n", a->nom, b->nom);
        } else {
            int degats = b->attaque - a->defense;
            if (degats < 0) degats = 0;
            a->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", b->nom, a->nom, degats);
        }

        if (a->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", a->nom, b->nom);
            break;
        }
    }
}


// Fonction boss1

void combatBoss1(Joueur *a, Joueur *b, int N, Inventaire *i1) {
    if (a == NULL || b == NULL || i1 == NULL) {
        exit(404);
    }

    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 5 à 7\n Defense : 2 à 5\n Esquive: 2 à 7\n");
    printf("2 : Sorcier :\n Attaque : 3 à 5\n Defense : 4 à 7\n Esquive: 4 à 12\n");
    printf("3 : Guerrier :\n Attaque : 7 à 11\n Defense : 0\n Esquive: 0\n");


    int res = 0;
    N = 0;
    char A;
    do {
        printf("Quelle classe voulez-vous choisir ? : ");
        res = scanf("%1d%c", &N, &A);
            if (res != 2 || N < 1 || N > 3 || A != '\n') {
                printf("Veuillez choisir un nombre entre 1 et 3\n");
                flush();
            } 
    } while (res != 2 || A != '\n' || N < 1 || N > 3);

    switch (N) {
        case 1:
            resetArcher(a);
            resetBoss1(b);
            break;
        case 2:
            resetSorcier(a);
            resetBoss1(b);
            break;
        case 3:
            resetGuerrier(a);
            resetBoss1(b);
            break;

    }

    shopExp(a, b);
    sleep(1);
    printf("Point de vie : %d\n", a->vie);
    sleep(1);

    printf("Debut du combat ! :\n");


    while (a->vie > 0 && b->vie >= 0) {

        usleep(800000);
        resetData(a);
        resetBoss1(b);

        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            printf("Ame(s) de Morlok : %d\n", a->exp);
            ajoutItem(i1, COUPE);
            afficheInv(i1);
            break;
        }

        if (a->attaque < b->esquive) {
            printf("%s esquive l'attaque de %s!\n", b->nom, a->nom);
        } else {
            int degats = a->attaque - b->defense;
            if (degats < 0) degats = 0;
            b->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", a->nom, b->nom, degats);
        }

        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            a->exp += 10;
            printf("Ame(s) de Morlok : %d\n", a->exp);
            ajoutItem(i1, COUPE);
            afficheInv(i1);
            break;
        }


        if (b->attaque < a->esquive) {
            printf("%s esquive l'attaque de %s!\n", a->nom, b->nom);
        } else {
            int degats = b->attaque - a->defense;
            if (degats < 0) degats = 0;
            a->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", b->nom, a->nom, degats);
        }

        if (a->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", a->nom, b->nom);
            break;
        }
    }
}



// Fonction Boss 2


void combatBoss2(Joueur *a, Joueur *b, int N, Inventaire *i1) {
    if (a == NULL || b == NULL || i1 == NULL) {
        exit(1);
    }
    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 5 à 7\n Defense : 2 à 5\n Esquive: 2 à 7\n");
    printf("2 : Sorcier :\n Attaque : 3 à 5\n Defense : 4 à 7\n Esquive: 4 à 12\n");
    printf("3 : Guerrier :\n Attaque : 7 à 11\n Defense : 0\n Esquive: 0\n");


    int res = 0;
    N = 0;
    char G;
    do {
        res = 0;
        printf("Quelle classe voulez-vous choisir ? : ");
        res = scanf("%1d%c", &N, &G);
            if (res != 2 || N < 1 || N > 3 || G != '\n') {
                printf("Veuillez choisir un nombre entre 1 et 3\n");
                flush();
            } 
    } while (res != 2 || G != '\n' || N < 1 || N > 3);

    switch (N) {
        case 1:
            resetArcher(a);
            resetBoss2(b);
            break;
        case 2:
            resetSorcier(a);
            resetBoss2(b);
            break;
        case 3:
            resetGuerrier(a);
            resetBoss2(b);
            break;
    }

    shopExp(a, b);
    sleep(1);
    printf("Point de vie : %d\n", a->vie);
    sleep(1);

    printf("Debut du combat ! :\n");


    while (a->vie > 0 && b->vie >= 0) {

        usleep(800000);
        resetData(a);
        resetBoss2(b);

        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            a->exp += 30;
            printf("Ame(s) de Morlok : %d\n", a->exp);
            ajoutItem(i1, EPEE);
            afficheInv(i1);
            break;
        }


        if (a->attaque < b->esquive) {
            printf("%s esquive l'attaque de %s!\n", b->nom, a->nom);
        } else {
            int degats = a->attaque - b->defense;
            if (degats < 0) degats = 0;
            b->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", a->nom, b->nom, degats);
        }

        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            a->exp += 30;
            printf("Ame(s) de Morlok : %d\n", a->exp);
            ajoutItem(i1, EPEE);
            afficheInv(i1);
            break;
        }


        if (b->attaque < a->esquive) {
            printf("%s esquive l'attaque de %s!\n", a->nom, b->nom);
        } else {
            int degats = b->attaque - a->defense;
            if (degats < 0) degats = 0;
            a->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", b->nom, a->nom, degats);
        }

        if (a->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", a->nom, b->nom);
            break;
        }
    }
}

void combatBoss3(Joueur *a, Joueur *b, int N, Inventaire *i1) {
    if (a == NULL || b == NULL || i1 == NULL) {
        exit(1);
    }
 
    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 5 à 7\n Defense : 2 à 5\n Esquive: 2 à 7\n");
    printf("2 : Sorcier :\n Attaque : 3 à 5\n Defense : 4 à 7\n Esquive: 4 à 12\n");
    printf("3 : Guerrier :\n Attaque : 7 à 11\n Defense : 0\n Esquive: 0\n");


    int res = 0;
    N = 0;
    char U;
    do {
        res = 0;
        printf("Quelle classe voulez-vous choisir ? : ");
        res = scanf("%1d%c", &N, &U);
            if (res != 2 || N < 1 || N > 3 || U != '\n') {
                printf("Veuillez choisir un nombre entre 1 et 3\n");
                flush();
            } 
    } while (res != 2 || U != '\n' || N < 1 || N > 3);

    switch (N) {
        case 1:
            resetArcher(a);
            break;
        case 2:
            resetSorcier(a);
            break;
        case 3:
            resetGuerrier(a);
            break;
    }

    shopExp(a, b);
    sleep(1);
    printf("Point de vie : %d\n", a->vie);
    sleep(1);


    printf("Debut du combat ! :\n");


    while (a->vie > 0 && b->vie >= 0) {

        usleep(800000);
        resetData(a);
        resetBoss3(b);

        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            a->exp += 60;
            printf("Ame(s) de Morlok : %d\n", a->exp);
            ajoutItem(i1, CRANE);
            afficheInv(i1);
            break;
        }


        if (a->attaque < b->esquive) {
            printf("%s esquive l'attaque de %s!\n", b->nom, a->nom);
        } else {
            int degats = a->attaque - b->defense;
            if (degats < 0) degats = 0;
            b->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", a->nom, b->nom, degats);
        }

        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            a->exp += 60;
            printf("Ame(s) de Morlok : %d\n", a->exp);
            ajoutItem(i1, CRANE);
            afficheInv(i1);
            break;
        }


        if (b->attaque < a->esquive) {
            printf("%s esquive l'attaque de %s!\n", a->nom, b->nom);
        } else {
            int degats = b->attaque - a->defense;
            if (degats < 0) degats = 0;
            a->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", b->nom, a->nom, degats);
        }

        if (a->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", a->nom, b->nom);
            break;
        }
    }
}


int main() {

    srand(time(NULL));

    Inventaire *i1 = NULL;
    Joueur *j1 = NULL;
    Joueur *j2 = NULL;
    Joueur *j3 = NULL;
    Joueur *j4 = NULL;
    Joueur *j5 = NULL;
    Joueur *j8 = NULL;
    int degats = 0;
    int N = 0;

    i1 = initialiserInv();

    j1 = creerJoueur();
    j2 = creerCradorien();
    j3 = creerBoss1();
    j4 = creerBoss2();
    j5 = creerBoss3();

    combat(j1, j2, N, i1);
    combatBoss1(j1, j3, N, i1);
    combatBoss2(j1, j4, N, i1);
    combatBoss3(j1, j5, N, i1);


    // faire une page données sur le main menu pour retirer les stats des printf ici  et les mettre la bas
   
    free(j1->nom);
    free(j2->nom);
    free(j3->nom);
    free(j4->nom);
    free(j5->nom);
    free(j1);
    free(j2);
    free(j3);
    free(j4);
    free(j5);
    free(i1->item);
    free(i1);

    return 0;

}

/*
Données :

La Company : Missionée par Garedon, la Company a pour objectif d'empêcher Morlok à récuperer l'anneau de ces ancestres à des fins dévastatrices.


Les fondations : Type de bâtiment multiples cachés dans les tréfonds de la Terre, une fondation est un bâtiment détenu par Morlok pour créer des ames.


Morlok : Dernier monstre des enfers, Morlok ne veut pas que la Company faillit à son projet final : Récuperer l'anneau des Morlok.


Garedon: Garde de l'anneau des Morlok, Garedon n'hésitera pas à apparaitre avant chaque combat pour vous aider à faillir au plan de Morlok.


Archer : Classe polyvalente, l'archer est l'archétype du soldat fidèle : Attaque : 5 à 7, Defense : 2 à 5, Esquive : 2 à 7 

	
Sorcier : Adepte de la magie noir, le sorcier n'hésitera pas à user de sa magie pour esquiver : Attaque : 3 à 5, Defense : 4 à 7, Esquive : 4 à 12


Guerrier : Imposant, le guerrier n'usera que de l'attaque pour exterminer son adversaire : Attaque : 7 à 11


Monstres : Ces obstacles, envoyés par Morlok, n'hésiteront pas à vous affaiblir pour empêcher la réussite de la mission Company : Attaque : 1 à 5, Défense : 1 à 3


Trader : Individu vivant dans les fondations, le trader acceptera d'acheter vos items pour son projet secret !

*/
  
  
