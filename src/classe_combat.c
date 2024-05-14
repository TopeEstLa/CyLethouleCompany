#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define SIZE 50

typedef enum class {
    ARCHER,
    SORCIER,
    GUERRIER,
} Class;

typedef struct{
    char* nom;
    Class current_class;
    int attaque;
    int defense;
    int esquive;
    int vie;
    int exp;
} Joueur;
void flush(){
    int  a;
    char c;
    do{
        a = scanf("%c", &c);
    } while(a==1 && c != '\n' );
}
Joueur* creerJoueur(){
    Joueur* j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if( j == NULL){
        exit(1);
    }
    // Create first name
    char tab[256];
    int res = 0;
    do{
        res = 0;
        printf("Saissisez le nom du joueur\n");
        res = scanf("%[^\n]", tab);
        flush();
    } while (res != 1);
    if (tab == NULL){
        exit(404);
    }
    if (strlen(tab) <= 0){
        exit(404);
    }
    (*j).nom = malloc((strlen(tab) + 1) * sizeof(char));
    if ((*j).nom == NULL){
        exit(404);
    }
    strcpy((*j).nom, tab);
    // Vie
    j->vie = 1500;
    // Exp
    j->exp = 0;
    // Return result
    return j;
}


Joueur* creerBoss1(){
    Joueur* j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if( j == NULL){
        exit(1);
    }
    // Create first name
    char tab[256];
    int res = 0;
    char* tmp = "Lazarus";
    if (strlen(tmp) > 0){
        j->nom = malloc(((strlen(tmp)+1) * sizeof(char)));
    }
    if (j->nom == NULL){
        exit(404);
    }
    strcpy(j->nom, tmp);

    // Vie
    j->vie = 20;
    // Return result
    return j;
}


Joueur* creerBoss2(){
    Joueur* j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if( j == NULL){
        exit(1);
    }
    // Create first name
    char tab[256];
    int res = 0;
    char* tmp = "Xaroth";
    if (strlen(tmp) > 0){
        j->nom = malloc(((strlen(tmp)+1) * sizeof(char)));
    }
    if (j->nom == NULL){
        exit(404);
    }
    strcpy(j->nom, tmp);

    // Vie
    j->vie = 50;
    // Return result
    return j;
}


Joueur* creerBoss3(){
    Joueur* j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if( j == NULL){
        exit(1);
    }
    // Create first name
    char tab[256];
    int res = 0;
    char* tmp = "Morlok";
    if (strlen(tmp) > 0){
        j->nom = malloc(((strlen(tmp)+1) * sizeof(char)));
    }
    if (j->nom == NULL){
        exit(404);
    }
    strcpy(j->nom, tmp);

    // Vie
    j->vie = 30;
    // Return result
    return j;
}


//Inventaire


typedef enum material {
    COUPE,
    EPEE,
    CRANE,
} Material;


typedef struct {
    char* name;
    int capacite;
    int quantite;
    Material* material;
} Inventaire;



// Fonction pour initialiser l'inventaire (capacité de 3 item)

Inventaire* initialiserInv(){
    Inventaire* p = NULL;
    p = malloc(sizeof(Inventaire));
    if( p == NULL){
        exit(2);
    }
    p->capacite = 3;
    p->quantite = 0;
    p->material = malloc(sizeof(Material) * p->capacite);
    if( p->material == NULL){
        exit(3);
    }
    return p;

}

// FOnction pour ajouter item

void ajoutItem(Inventaire* p, Material material){
    if (p == NULL || p->material == NULL){
        exit(1);
    }
    if (p->quantite <= p->capacite){
        p->material[p->quantite] = material;
        p->quantite++;
    }
    else{
        printf("Inventaire chargé !");
    }
}


//Fonction pour verifier son inventaire

void afficheInv(Inventaire* p){
    if (p == NULL || p->material == NULL){
        exit(1);
    }
    printf("Voici votre inventaire :\n");
       for(int i = 0; i < p->quantite; i++){
        switch(p->material[i]){
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


void resetData(Joueur* j){
    if (j == NULL || j->nom == NULL){
        exit(1);
    }
    switch(j->current_class){
        case ARCHER:
            j->attaque = rand()%3 + 9;
            j->defense = rand()%3 + 4;
            j->esquive = rand()%8 + 7;
            break;
        case SORCIER:
            j->attaque = rand()%5 + 5;
            j->defense = rand()%5 + 7;
            j->esquive = rand()%7 + 9;
            break;
        case GUERRIER:
            j->attaque = rand()%4 + 11;
            j->defense = rand()%4 + 6;
            j->esquive = rand()%10 + 4;

    }
}

// Reset archer

void resetArcher(Joueur* a) {
    a->current_class = ARCHER;
    resetData(a);
}

// Reset wizard
void resetSorcier(Joueur* a) {
    a->current_class = SORCIER;
    resetData(a);
}

// Reset Warrior
void resetGuerrier(Joueur* a){
    a->current_class = GUERRIER;
    resetData(a);
}


// reset boss 1


void resetBoss1(Joueur* b){
        b->attaque = rand()%4 + 12;
        b->defense = rand()%4 + 8;
        b->esquive = rand()%10 + 6;
}

//reset boss 2

void resetBoss2(Joueur* b){
        b->esquive=rand()%5 + 3;
        b->attaque= rand()%3 + 6;
        b->defense= rand()%3 + 5;

}

// reset boss 3

void resetBoss3(Joueur* b){
        b->esquive=rand()%8 + 7;
        b->attaque= rand()%4 + 10;
        b->defense= rand()%4 + 7;

}


// Creation Combat


void combat(Joueur* a, Joueur* b, int N){
    if (a == NULL || b == NULL){
        exit(1);
    }
    if (a->nom == NULL || b->nom == NULL){
        exit(1);
    }
    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 9 à 11\n Defense : 4 à 6\n Esquive: 7 à 14\n");
    printf("2 : Sorcier :\n Attaque : 5 à 9\n Defense : 7 à 11\n Esquive: 9 à 16\n");
    printf("3 : Guerrier :\n Attaque : 11 à 14\n Defense : 6 à 9\n Esquive: 4 à 13\n");


    int res = 0;
    do {
        res = 0;
        printf("Quelle classe voulait vous choisir ? : ");
        res = scanf("%d", &N);
    } while (res != 1 || N < 1 || N > 3);

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
        default:
            printf("Choix inexistant\n");
            return;
    }



    printf("Debut du combat ! :\n");



    while (a->vie > 0 && b->vie > 0) {

        usleep(500000);
        resetData(a);
        resetGuerrier(b);

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
            a->exp += 1;
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
            b->exp +=1;
            break;
        }
    }
}


// Fonction boss1

void combatBoss1(Joueur* a, Joueur* b, int N, Inventaire* i1){
    if (a == NULL || b == NULL){
        exit(1);
    }
    if (a->nom == NULL || b->nom == NULL){
        exit(1);
    }
    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 9 à 11\n Defense : 4 à 6\n Esquive: 7 à 14\n");
    printf("2 : Sorcier :\n Attaque : 5 à 9\n Defense : 7 à 11\n Esquive: 9 à 16\n");
    printf("3 : Guerrier :\n Attaque : 11 à 14\n Defense : 6 à 9\n Esquive: 4 à 13\n");


    int res = 0;
    do {
        res = 0;
        printf("Quelle classe voulait vous choisir ? : ");
        res = scanf("%d", &N);
    } while (res != 1 || N < 1 || N > 3);
    
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
        default:
            printf("Choix inexistant\n");
            return;
    }


    printf("Debut du combat ! :\n");


    while (a->vie > 0 && b->vie > 0) {

        usleep(800000);
        resetData(a);
        resetBoss1(b);

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
            printf("Exp : %d\n", a->exp);
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


void combatBoss2(Joueur* a, Joueur* b, int N, Inventaire* i1){
    if (a == NULL || b == NULL){
        exit(1);
    }
    if (a->nom == NULL || b->nom == NULL){
        exit(1);
    }
    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 9 à 11\n Defense : 4 à 6\n Esquive: 7 à 14\n");
    printf("2 : Sorcier :\n Attaque : 5 à 9\n Defense : 7 à 11\n Esquive: 9 à 16\n");
    printf("3 : Guerrier :\n Attaque : 11 à 14\n Defense : 6 à 9\n Esquive: 4 à 13\n");

    int res = 0;
    do {
        res = 0;
        printf("Quelle classe voulait vous choisir ? : ");
        res = scanf("%d", &N);
    } while (res != 1 || N < 1 || N > 3);

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
        default:
            printf("Choix inexistant\n");
            return;
    }


    printf("Debut du combat ! :\n");


    while (a->vie > 0 && b->vie > 0) {

        usleep(800000);
        resetData(a);
        resetBoss2(b);

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
            printf("Exp : %d\n", a->exp);
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

void combatBoss3(Joueur* a, Joueur* b, int N, Inventaire* i1){
    if (a == NULL || b == NULL){
        exit(1);
    }
    if (a->nom == NULL || b->nom == NULL){
        exit(1);
    }
    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 9 à 11\n Defense : 4 à 6\n Esquive: 7 à 14\n");
    printf("2 : Sorcier :\n Attaque : 5 à 9\n Defense : 7 à 11\n Esquive: 9 à 16\n");
    printf("3 : Guerrier :\n Attaque : 11 à 14\n Defense : 6 à 9\n Esquive: 4 à 13\n");


    int res = 0;
    do {
        res = 0;
        printf("Quelle classe voulait vous choisir ? : ");
        res = scanf("%d", &N);
    } while (res != 1 || N < 1 || N > 3);

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
        default:
            printf("Choix inexistant\n");
            return;
    }


    printf("Debut du combat ! :\n");


    while (a->vie > 0 && b->vie > 0) {

        usleep(800000);
        resetData(a);
        resetBoss3(b);



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
            printf("Exp : %d\n", a->exp);
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

    Inventaire* i1 = NULL;
    Joueur*  j1    = NULL;
    Joueur*  j2    = NULL;
    Joueur*  j3    = NULL;
    Joueur*  j4    = NULL;
    Joueur* j5 = NULL;
    int degats = 0;
    int N = 0;

    i1 = initialiserInv();

    j1  = creerJoueur();
    //j2  = creerJoueur();
    j3 = creerBoss1();
    j4 = creerBoss2();
    j5 = creerBoss3();

    //combat(j1, j2, N);
    combatBoss1(j1, j3, N, i1);
    combatBoss2(j1, j4, N, i1);
    combatBoss3(j1, j5, N, i1);


// FOnction shop avec point d'exp à faire (heal, degats bonus, etc...)

    free(j1);
    free(j2);
    free(j3);
    free(j4);
    free(j5);

    return 0;

}



