#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define N 3
#define TAILLE (N*N)
typedef struct{
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
}tCase1;
typedef tCase1 tGrille[TAILLE][TAILLE];
tGrille grille1;

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

void ajouterCandidat(tCase1 laCase, int val){
    int i,j;
    for(i=TAILLE-1;i>=0;i--){
        if(laCase.candidats[i]>val){
            for(j=TAILLE-1;j>=i;j--){
                laCase.candidats[j+1]=laCase.candidats[j];
            }
        }
        laCase.candidats[i]=val;
    }
}

void retirerCandidat(tCase1 laCase, int val){
    int i;
    for(i=val;i<TAILLE-1;i++){
        laCase.candidats[i]=laCase.candidats[i+1];
    }
    laCase.candidats[TAILLE]=0;
}

bool estCandidat(tCase1 laCase, int val){
    bool verification;
    verification=false;
    int i;
    for(i=0;i<TAILLE;i++){
        if(laCase.candidats[i]==val){
            verification=true;
        }
    }
    return verification;
}

int nbCandidats(tCase1 laCase){
    int n,i;
    n=0;
    i=1;
    while(laCase.candidats[i]!=0){
        n++;
        i++;
    }
    return n;
}

int main(){
    chargerGrille(&grille1);
    return EXIT_SUCCESS;
}