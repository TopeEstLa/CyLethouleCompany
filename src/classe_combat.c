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
    j->vie = 150;
    // Exp
    j->exp = 0;
    // Return result
    return j;
}


Joueur* creerBoss(){
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
    j->vie = 150;
    // Exp
    j->exp = 0;
    // Return result
    return j;
}


//Inventaire


typedef enum material {
    COUPE[1],
    EPEE[2],
    CRANE[3],
} Material;


typedef struct {
    char* name;
    int capacite;
    int quantite
    Material material;
} Inventaire;



// Fonction pour initialiser l'inventaire (capacité de 3 item)

Inventaire* initialiserInv(){
    Inventaire* p = NULL;
    p = malloc(sizeof(Inventaire));
    if( p == NULL){
        exit(2);
    }
    p->capacite = 3;
    p->material = malloc(sizeof(Inventaire) * p->capacite);
    if( p->material == NULL){
        exit(3);
    }


}

// FOnction pour ajouter item

void ajoutItem(Inventaire* p){
    if (p == NULL || p->item == NULL){
        exit(1);
    }
    if (p->quantite <= p->capacite){
        p->quantite++;
        p->material[p->quantite] = p->material[1];
    }
    else{
        printf("Inventaire chargé !");
    }
}


//Fonction pour verifier son inventaire

void afficheInv(Inventaire* p){
    if (p == NULL || p->item == NULL){
        exit(1);
    }
    printf("Voici votre inventaire :\n");
    for(int i = 0; i < p->quantite; i++){
        printf("%s", p->item[i].nom);
    }
}


// Creation Abilité


void resetData(Joueur* j){
    if (j == NULL || j->nom == NULL){
        exit(1);
    }
    switch(j->current_class){
        case ARCHER:
            j->attaque = rand()%5 + 8;
            j->defense = rand()%3 + 3;
            j->esquive = rand()%12 + 5;
            break;
        case SORCIER:
            j->attaque = rand()%7 + 4;
            j->defense = rand()%5 + 8;
            j->esquive = rand()%9 + 8;
            break;
        case GUERRIER:
            j->attaque = rand()%4 + 12;
            j->defense = rand()%4 + 5;
            j->esquive = rand()%14 + 3;

    }
}

// Reset archer

void resetArcher(Joueur* a, Joueur* b) {
    a->current_class = ARCHER;
    resetData(a);

    b->current_class = GUERRIER;
    resetData(b);
}

// Reset wizard
void resetSorcier(Joueur* a, Joueur* b) {
    a->current_class = SORCIER;
    resetData(a);

    b->current_class = GUERRIER;
    resetData(b);
}

// Reset Warrior
void resetGuerrier(Joueur* a, Joueur* b) {
    a->current_class = GUERRIER;
    resetData(a);

    b->current_class = ARCHER;
    resetData(b);
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
    printf("1 : Archer :\n Attaque : 8 à 12\n Defense : 3 à 5\n Esquive: 5 à 16\n");
    printf("2 : Sorcier :\n Attaque : 4 à 10\n Defense : 8 à 12\n Esquive: 8 à 16\n");
    printf("3 : Guerrier :\n Attaque : 12 à 15\n Defense : 5 à 8\n Esquive: 3 à 16\n");


    int res = 0;
    do {
        res = 0;
        printf("Quelle classe voulait vous choisir ? : ");
        res = scanf("%d", &N);
    } while (res != 1 || N < 1 || N > 3);

    switch (N) {
        case 1:
            resetArcher(a, b);
            break;
        case 2:
            resetSorcier(a, b);
            break;
        case 3:
            resetGuerrier(a, b);
            break;
        default:
            printf("Choix inexistant\n");
            return;
    }


    printf("Debut du combat ! :\n");



    while (a->vie > 0 && b->vie > 0) {

        usleep(500000);
        resetData(a);
        resetData(b);

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

void combatBoss1(Joueur* a, Joueur* b, int N){
    if (a == NULL || b == NULL){
        exit(1);
    }
    if (a->nom == NULL || b->nom == NULL){
        exit(1);
    }
    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 8 à 12\n Defense : 3 à 5\n Esquive: 5 à 16\n");
    printf("2 : Sorcier :\n Attaque : 4 à 10\n Defense : 8 à 12\n Esquive: 8 à 16\n");
    printf("3 : Guerrier :\n Attaque : 12 à 15\n Defense : 5 à 8\n Esquive: 3 à 16\n");


    int res = 0;
    do {
        res = 0;
        printf("Quelle classe voulait vous choisir ? : ");
        res = scanf("%d", &N);
    } while (res != 1 || N < 1 || N > 3);

    switch (N) {
        case 1:
            resetArcher(a, b);
            break;
        case 2:
            resetSorcier(a, b);
            break;
        case 3:
            resetGuerrier(a, b);
            break;
        default:
            printf("Choix inexistant\n");
            return;
    }
    if (a->current_class == 2){
        b->vie = 290;
    } else {
        b->vie = 230;
    }

    printf("Debut du combat ! :\n");


    while (a->vie > 0 && b->vie > 0) {

        usleep(800000);
        resetData(a);

        b->esquive=0;
        b->attaque= rand()%10 + 10;
        b->defense=0;


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
            //Item_Stack item;
            //item.name = "Coupe du Roi";
            //item.material = COUPE;

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
    int degats = 0;
    int N = 0;

    i1 = initialiserInv();
    ajouteItem(i1);
    afficheInv(i1);

    j1  = creerJoueur();
    //j2  = creerJoueur();
    j3 = creerBoss();

    //combat(j1, j2, N);
    combatBoss1(j1, j3, N);
    /



    printf("Exp : %d", j1->exp);

    free(j1);
    free(j2);
    free(j3);

    return 0;
}