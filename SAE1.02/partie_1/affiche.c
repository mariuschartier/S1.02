#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

/**
 * \file programme1.c
 * \brief programme qui resoud un sudoku avec la methode 1 
 * \author Chartie--Le Goff Marius
 * \version 1
 * \date 6/12/2023
*/




#define N 3
#define TAILLE (N*N)


typedef struct {
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];




void afficheresult(char nom_fichier[10], float case_vide, float case_rempli, float candidat_depart, float candidat_fin){

float tx_remplissage, tx_elimination;
tx_remplissage = case_rempli / case_vide * 100;
tx_elimination = candidat_fin / candidat_depart * 100;
printf("%f\n%f\n",tx_elimination,tx_remplissage);

printf("*****  RESULTATS POUR %s  *****\n",nom_fichier);

printf("Nombre de cases remplies = %.0f sur %.0f           Taux de remplissage = %.3f %% \n",case_rempli,case_vide,tx_remplissage);
printf("Nombre de candidats eliminés = %.0f              Pourcent d'elimination = %.3f %% \n,",candidat_fin,tx_elimination);
}



int main()
{
    char mot[10];
    strcpy(mot,"bonjour");
    afficheresult(mot,99,55,999,257);
    return 0;
}



















