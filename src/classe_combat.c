#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
//#include <ncurses.h>

#define SIZE 50

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

      // A voir (permet de verifier si tout est un espace)
    /* 
    
    void is_all_spaces(char str) {
    while (str) {
        if (!isspace((char)*str)) {
            return 0;
        }
        str++;
    }
}
*/

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
    j->vie = 125;
    // Exp
    j->exp = 30;
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
    ITEM4,
    ITEM5,
} Material;


typedef struct {
    char *name;
    int capacite;
    int quantite;
    Material *material;
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
    p->material = malloc(sizeof(Material) * p->capacite);
    if (p->material == NULL) {
        exit(3);
    }
    return p;

}

// FOnction pour ajouter item

void ajoutItem(Inventaire *p, Material material) {
    if (p == NULL || p->material == NULL) {
        exit(1);
    }
    if (p->quantite <= p->capacite) {
        p->material[p->quantite] = material;
        p->quantite++;
    } else {
        printf("Inventaire rempli !");
    }
}


//Fonction pour verifier son inventaire

void afficheInv(Inventaire *p) {
    if (p == NULL || p->material == NULL) {
        exit(1);
    }
    printf("Voici votre inventaire :\n");
    for (int i = 0; i < p->quantite; i++) {
        switch (p->material[i]) {
            case COUPE:
                printf("COUPE\n");
                break;
            case EPEE:
                printf("EPEE\n");
                break;
            case CRANE:
                printf("CRANE\n");
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

// choix classe

void choixClasse(){
    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 5 à 7\n Defense : 2 à 5\n Esquive: 2 à 7\n");
    printf("2 : Sorcier :\n Attaque : 3 à 5\n Defense : 4 à 7\n Esquive: 4 à 12\n");
    printf("3 : Guerrier :\n Attaque : 7 à 11\n Defense : 0\n Esquive: 0\n");


    int res = 0;
    int N = 0;
    do {
        res = 0;
        printf("Quelle classe voulez-vous choisir ? : ");
        res = scanf("%d", &N);
            if (res != 1 || N < 1 || N > 3 || sizeof(N) != 4) {
                printf("Veuillez choisir un nombre entre 1 et 3\n");
            flush();
            } 
    } while (res != 1 || N < 1 || N > 3 || sizeof(N) != 4);
    
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
  do {
        printf("Choisissez le numero correspondant au service voulu :\n");
        res = scanf("%d", &C);
         if(res != 1 || sizeof(C) != 4 || C < 1 || C > 4){
                printf("Veuillez entrer un chiffre entre 1 et 4\n");
                flush();
                count1++;

                if (count1 == 5) {
                        printf("Garedon n'aime pas perdre son temps. La boutique est fermé\n");
                        printf("Ame(s) de Morlok restant: %d\n", a->exp);
                        break;
                    }   
    
            }
           if((C == 1 && a->exp < 10) || (C == 2 && a->exp < 15) || (C == 3 && a->exp < 150)) {
                printf("Ame(s) de Morlok insuffisante(s)\n");
                count1++;

                if (count1 == 5) {
                        printf("Garedon n'aime pas perdre son temps. La boutique est fermé\n");
                        printf("Ame(s) de Morlok restant: %d\n", a->exp);
                        break;
                    }   
            }   
    } while (res != 1 || C < 1 || C > 4 || sizeof(C) != 4 || (C == 1 && a->exp < 10) || (C == 2 && a->exp < 15) || (C == 3 && a->exp < 150));


    switch (C) {
        case 1:
            if (count1 == 5) {
                break;
            }
            printf("Point de vie : %d\n", a->vie);
            sleep(1);
            printf("Fiole consommé\n");
            a->vie += 100;
            a->exp -= 10;
            printf("Ame(s) de Morlok restant(s) : %d\n", a->exp);
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
            break;
        case 4:
            if (count1 == 5) {
                break;
            }
            printf("Un vrai guerrier se doit de gagner des ames de Morlok...\n");
    }

}





// Creation Combat


void combat(Joueur *a, Joueur *b, int N) {
    if (a == NULL || b == NULL) {
        exit(1);
    }
    choixClasse();

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
    choixClasse();

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
            ajoutItem(i1, COUPE);
            printf("Ame(s) de Morlok : %d\n", a->exp);
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
            ajoutItem(i1, COUPE);
            a->exp += 10;
            printf("Ame(s) de Morlok : %d\n", a->exp);
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
    choixClasse();

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
            ajoutItem(i1, EPEE);
            a->exp += 30;
            printf("Ame(s) de Morlok : %d\n", a->exp);
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
            ajoutItem(i1, EPEE);
            a->exp += 30;
            printf("Ame(s) de Morlok : %d\n", a->exp);
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
 
    choixClasse();

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


    while (a->vie > 0 && b->vie > 0) {

        usleep(800000);
        resetData(a);
        resetBoss3(b);

        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            ajoutItem(i1, CRANE);
            a->exp += 60;
            printf("Ame(s) de Morlok : %d\n", a->exp);
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
            ajoutItem(i1, CRANE);
            a->exp += 60;
            printf("Ame(s) de Morlok : %d\n", a->exp);
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
    int degats = 0;
    int N = 0;

    i1 = initialiserInv();

    j1 = creerJoueur();
    j2 = creerCradorien();
    j3 = creerBoss1();
    j4 = creerBoss2();
    j5 = creerBoss3();

    //combat(j1, j2, N);
    combatBoss1(j1, j3, N, i1);
    //combatBoss2(j1, j4, N, i1);
    //combatBoss3(j1, j5, N, i1);


    // test d'aller plus loin avec 4 item (ici ca a l'air de marcher avec 4 item donc bloqué ou sinon accepté un inventaire infini)
    // de notre faute si dans un scanf où il faut rentrer un chiffre, on rentre une lettre et ca full bug (ex choix de classe avec lettre)
    // faire une page données sur le main menu pour retirer les stats des printf ici  et les mettre la bas
    // si on écrit autre chiffre que 1 à 4 dans boutique, prends pas en compte le count1 ++


    // pour (E) probleme regler donc suffit de faire pareil avec autre scanf
    // bug avec exp (si on a que 30 exp mais qu'on prend 150(abilité3) alors ca marche et donne exp negatif)
    // gerer soucis si 2gzgzgzgz marche car première lettre 2 (pas de notre faute au final)
    // voir si c'est un soucis de mettre des espaces 
    // (E) = rendre robuste tous les scanf (exemple avec classe qui accepte 3iegigei3 car chiffre trois seul dispo)
    
    // tester n'importe comment tous les scanf
    // rendre robuste TOUS LES SCANF.....



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

    return 0;

}
  
