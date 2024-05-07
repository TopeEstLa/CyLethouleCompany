#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50


typedef struct{
    char* nom[SIZE];
    int attaque;
    int defense;
    int esquive;
    int vie;
    int exp;
} Joueur;


Joueur* creerJoueur(){
    Joueur* j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if( j == NULL){
        exit(1);
    }
    // Create first name
    printf("Saissisez le nom du joueur\n");
    scanf("%s", j->nom);
    // Attack (10 to 20)
    j->attaque = rand()%11 + 10;
    // Defense (2 to 4)  
    j->defense = rand()%6 + 5;
    // Esquive (5 to 14)
    j->esquive = rand()%12 + 5;
    // Vie      
    j->vie = 150;
    // Exp
    j->exp = 0;
    // Return result 
    return j;
}

//Inventaire

typedef struct{
    char* nom[SIZE];
    int nombre;
} Info;

typedef struct{
    Info* item;
    int capacite;
    int quantite;
} Inventaire;

// Fonction pour initialiser l'inventaire (capacité de 3 item)

Inventaire* initialiserInv(){
    Inventaire* p = NULL;
    p = malloc(sizeof(Inventaire));
    if( p == NULL){
        exit(2);
    }
    p->capacite = 3;
    p->item = malloc(sizeof(Inventaire) * p->capacite);
    if( p->item == NULL){
        exit(3);
    }


}

// FOnction pour ajouter item

void ajoutItem(Inventaire* p, char* nom){
    if (p->quantite <= p->capacite){
        p->item[p->quantite] = // item à prévoir 
        p->quantite++;
    }
    else{
        printf("Inventaire chargé !");
    }
}


//FOnction pour verifier son inventaire

void afficheInv(Inventaire* p){
    printf("Voici votre inventaire :\n");
        for(int i = 0; i < p->quantite; i++){
            printf("%s", p->item[i].nom);
        }
}


// Creation Abilité


void resetData(Joueur* a, Joueur* b){
    a->attaque = rand()%11 + 10;
    a->defense = rand()%6 + 5;
    a->esquive = rand()%12 + 5;
}
int resetArcher(Joueur* a, Joueur* b){
    a->attaque = rand()%5 + 8;
    a->defense = rand()%3 + 3;
    a->esquive = rand()%12 + 5;

    b->attaque = rand()%4 + 12;
    b->defense = rand()%4 + 5;
    b->esquive = rand()%14 + 3;
}
int resetSorcier(Joueur* a, Joueur* b){
    a->attaque = rand()%7 + 4;
    a->defense = rand()%5 + 8;
    a->esquive = rand()%9 + 8;

    b->attaque = rand()%4 + 12;
    b->defense = rand()%4 + 5;
    b->esquive = rand()%14 + 3;
}
int resetGuerrier(Joueur* a, Joueur* b){
    a->attaque = rand()%4 + 12;
    a->defense = rand()%4 + 5;
    a->esquive = rand()%14 + 3;

    b->attaque = rand()%4 + 12;
    b->defense = rand()%4 + 5;
    b->esquive = rand()%14 + 3;

}

// Creation Combat


void combat(Joueur* a, Joueur* b, int N){

    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 8 à 12\n Defense : 3 à 5\n Esquive: 5 à 16\n");
    printf("2 : Sorcier :\n Attaque : 4 à 10\n Defense : 8 à 12\n Esquive: 8 à 16\n");
    printf("3 : Guerrier :\n Attaque : 12 à 15\n Defense : 5 à 8\n Esquive: 3 à 16\n");
    printf("Quelle classe voulait vous choisir ? : ");
    scanf("%d", &N);

    int reset;

    if(N == 1){
        reset = resetArcher(a,b);
    }
    if(N == 2){
        reset = resetSorcier(a,b);
    }
    if(N == 3){
       reset = resetGuerrier(a,b);
    }

    printf ("Debut du combat ! :\n");



     while (a->vie > 0 && b->vie > 0) {

    //soucis avec le reset 

      resetData(a, b) = reset;

        
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




int main() {

srand(time(NULL));

    Joueur*  j1    = NULL;
    Joueur*  j2     = NULL;
    int degats = 0;
    int N = 0;

    j1  = creerJoueur();
    j2  = creerJoueur();

    combat(j1, j2, N);

    printf("Exp : %d", j1->exp);

    free(j1);
    free(j2);

return 0;

}


