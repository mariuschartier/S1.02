#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define N 3
#define TAILLE (N*N)
typedef struct{
    int valeur;
    bool candidats[TAILLE];
    int nbCandidats;
}tCase2;
typedef tCase2 tGrille[TAILLE][TAILLE];


void chargerGrille(tGrille *g){
    char nomFichier[30];
    FILE * f;
    
    printf("Nom du fichier ?\n");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(*g, sizeof(int), 9*9, f);
    }
    fclose(f);
}

void ajouterCandidat(tCase2 laCase, int val){
    laCase.candidats[val]=true;
}

void retirerCandidat(tCase2 laCase, int val){
    laCase.candidats[val]=false;
}

bool estCandidat(tCase2 laCase, int val){
    bool verification;
    if(laCase.candidats[val]=true){
        verification=true;
    }else{
        verification=false;
    }
    return verification;
}

int nbCandidats(tCase2 laCase){
    int n,i;
    n=0;
    for(i=0;i<TAILLE;i++){
        if(laCase.candidats[i]=true){
            n++;
        }
    }
    return n;
}

int main(){
    chargerGrille(&grille1);
    return EXIT_SUCCESS;
}