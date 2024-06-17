#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// MaxiGrilleA.sud
#define N 4
#define TAILLE (N * N)
typedef int t_grille_valeur[TAILLE][TAILLE];

typedef struct
{
    int valeur;
    bool candidats[TAILLE];
    int nbCandidats;
} tCase2;
typedef tCase2 tGrille[TAILLE][TAILLE];

bool absentSurLigne(int valeur, tGrille grille, int ligne);
bool absentSurBloc(int valeur, tGrille grille, int ligne, int colonne);
bool absentSurColonne(int valeur, tGrille grille, int colonne);
bool possible(int valeur, tGrille grille, int ligne, int colonne);

void affiche_grille(tGrille grille);
void chargerGrille(tGrille g, char nomFichier[30]);

void ajouterCandidat(tCase2 *laCase, int val);
void retirerCandidat(tCase2 *laCase, int val);
bool estCandidat(tCase2 laCase, int val);
int nbCandidats(tCase2 laCase);
void afficheresult(char nom_fichier[10], float case_vide, float case_restante_vide, float candidat_depart, float candidat_fin);
void initialiserCandidats(tGrille grille);
int nombre_candidat_total(tGrille grille);
void retirer_tout_Candidat(tGrille grille, int val, int ligne, int colonne);
void ajouter_tout_Candidat(tGrille grille, int val, int ligne, int colonne);

bool backtracking(tGrille grille, int numeroCase, int nombre_candidat_rechercher);

// bool recu(tGrille grille, int numeroCase, int nombre_candidat_rechercher)
// {
//     int ligne, colonne, valeur, indice;
//     bool resultat;
//     if (numeroCase > 25)
//     {
//         recu(grille, 0, nombre_candidat_rechercher + 1);
//     }

//     if (nombre_candidat_rechercher > 5)
//     {
//         resultat = true;
//     }
//     else
//     {
//         recu(grille, numeroCase + 1, nombre_candidat_rechercher);
//     }
// }

bool backtracking2(tGrille grille, int numeroCase, int nombre_candidat_rechercher)
{

    int ligne, colonne, valeur, indice;
    bool resultat;

    resultat = false;
    if (numeroCase > TAILLE * TAILLE)
    {
        backtracking2(grille, 0, nombre_candidat_rechercher++);
    }
    else
    {
        if (nombre_candidat_rechercher > TAILLE)
    {

        resultat = true;
    }
    else
    {
        // On récupère les "coordonnées" de la case
        ligne = numeroCase / (TAILLE * 1);
        colonne = numeroCase % (TAILLE * 1);
        if (grille[ligne][colonne].valeur != 0)
        {
            // Si la case n’est pas vide, on passe à la suivante
            // (appel récursif)

            resultat = backtracking2(grille, numeroCase + 1, nombre_candidat_rechercher);
        }
        else
        {
            if ((grille[ligne][colonne].nbCandidats) == nombre_candidat_rechercher)
            {
                for (indice = 1; indice < TAILLE + 1; indice++)
                {
                    if (grille[ligne][colonne].candidats[indice])
                    {
                        valeur = indice;
                        if (possible(valeur, grille, ligne, colonne))
                        {
                            // Si la valeur est autorisée on  l'inscrit
                            // dans la case...
                            grille[ligne][colonne].valeur = valeur;
                            // retirer_tout_Candidat(grille, valeur, ligne, colonne);
                            // ... et on passe à la suivante : appel récursif
                            // pour voir si ce choix est bon par la suite
                            if (backtracking2(grille, numeroCase + 1, nombre_candidat_rechercher) == true)
                            {
                                resultat = true;
                            }

                            else
                            {
                                grille[ligne][colonne].valeur = 0;
                                // ajouter_tout_Candidat(grille, valeur, ligne, colonne);
                                // initialiserCandidats(grille);
                            }
                        }
                    }
                }
            }
            else
            {
                backtracking2(grille, numeroCase + 1, nombre_candidat_rechercher);
            }
        }
    }
    }
    

    

    return resultat;
}

int main()
{
    char nom_fichier[30];
    tGrille grille;
    // bool progression;

    printf("Nom du fichier ?\n");
    scanf("%s", nom_fichier);

    chargerGrille(grille, nom_fichier);
    printf("Grille de depart\n");
    affiche_grille(grille);

    clock_t begin = clock();

    initialiserCandidats(grille);
    backtracking2(grille, 0, 1);
    clock_t end = clock();

    double tmpsCPU = (end - begin) * 1.0 / CLOCKS_PER_SEC;

    printf("Grille finale\n");
    affiche_grille(grille);
    printf("Resolution de la grille en %.6f sec\n", tmpsCPU);

    return EXIT_SUCCESS;
}

// bool backtracking(tGrille grille, int numeroCase, int nombre_candidat_rechercher)
// {
//
//     int ligne, colonne, valeur, indice, nbCandidats;
//     bool resultat;
//     printf("%d", numeroCase);
//     resultat = false;
//
//     if (numeroCase == (TAILLE * TAILLE))
//     {
//         // on a traité toutes les cases, la grille est résolue
//         resultat = true;
//     }
//     else
//     {
//         // On récupère les "coordonnées" de la case
//         ligne = numeroCase / (TAILLE * 1);
//         colonne = numeroCase % (TAILLE * 1);
//         if (grille[ligne][colonne].valeur != 0)
//         {
//             // Si la case n’est pas vide, on passe à la suivante
//             // (appel récursif)
//
//             resultat = backtracking(grille, numeroCase + 1);
//         }
//         else
//         {
//             nbCandidats = grille[ligne][colonne].nbCandidats;
//             for (indice = 1; indice <= 9; indice++)
//             {
//
//                 // valeur = grille[ligne][colonne].candidats[indice];
//                 valeur = indice;
//                 if (possible(valeur, grille, ligne, colonne))
//                 {
//                     // Si la valeur est autorisée on  l'inscrit
//                     // dans la case...
//                     grille[ligne][colonne].valeur = valeur;
//                     // retirer_tout_Candidat(grille, valeur, ligne, colonne);
//                     grille[ligne][colonne].nbCandidats = 0;
//
//                     // ... et on passe à la suivante : appel récursif
//                     // pour voir si ce choix est bon par la suite
//                     if (backtracking(grille, numeroCase + 1) == true)
//                     {
//                         resultat = true;
//                     }
//
//                     else
//                     {
//                         grille[ligne][colonne].valeur = 0;
//                         // ajouter_tout_Candidat(grille, valeur, ligne, colonne);
//                         // initialiserCandidats(grille);
//                         grille[ligne][colonne].nbCandidats = nbCandidats;
//                     }
//                 }
//                 // indice++;
//             }
//         }
//     }
//
//     return resultat;
// }

bool possible(int valeur, tGrille grille, int ligne, int colonne)
{
    bool resultat = true;

    int case_x = ligne - (ligne % N);
    int case_y = colonne - (colonne % N);
    int numeroCase = 0;
    int lig = case_x, col = case_y;
    // printf("\n");
    while ((resultat == true) && numeroCase < TAILLE)
    {
        // printf("possible?  ");

        if (valeur == grille[ligne][numeroCase].valeur)
        {
            resultat = false;
        }

        if ((valeur == grille[numeroCase][colonne].valeur))
        {
            resultat = false;
        }
        if (valeur == grille[lig][col].valeur)
        {
            resultat = false;
        }
        col++;
        if (col % N == 0)
        {
            col = case_y;
            lig++;
        }
        numeroCase++;
    }

    return resultat;
}

bool absentSurLigne(int valeur, tGrille grille, int ligne)
{

    bool resultat = true;
    int col = 0;

    while ((resultat == true) && col < TAILLE)
    {
        if (valeur == grille[ligne][col].valeur)
        {
            resultat = false;
        }
        col++;
    }

    return resultat;
}

bool absentSurBloc(int valeur, tGrille grille, int ligne, int colonne)
{

    bool resultat = true;
    int case_x = ligne - (ligne % N);
    int case_y = colonne - (colonne % N);
    int numeroCase = 0;
    int lig = case_x, col = case_y;

    while ((resultat == true) && numeroCase < TAILLE)
    {

        if (valeur == grille[lig][col].valeur)
        {
            resultat = false;
        }
        col++;
        if (col % N == 0)
        {
            col = case_y;
            lig++;
        }
        numeroCase++;
    }

    return resultat;
}

bool absentSurColonne(int valeur, tGrille grille, int colonne)
{
    bool resultat = true;
    int lig = 0;

    while ((resultat == true) && lig < TAILLE)
    {
        if ((valeur == grille[lig][colonne].valeur))
        {
            resultat = false;
        }
        lig++;
    }

    return resultat;
}

void affiche_grille(tGrille t)
{
    printf("     1   2   3   4    5   6   7   8    9   10  11  12   13  14  15  16   \n");
    int ligne;   // indice de ligne
    int colonne; // indice de colonne
    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        if (ligne % N == 0)
        {
            printf("   +----------------+----------------+----------------+----------------+\n");
        }
        if (ligne < 9)
        {
            printf("%d  |", ligne + 1);
        }
        else
        {
            printf("%d |", ligne + 1);
        }

        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            // acces a chaque case t[ligne][colonne] du tableau
            if (colonne % N == 0 && colonne != 0)
            {
                printf("|"); // tout les N valeur affiche un | pour la formatation
            }
            if (t[ligne][colonne].valeur == 0)
            {
                printf(" .  "); // affiche un . quand la case est vide
            }

            else
            {
                if (t[ligne][colonne].valeur < 10)
                {
                    printf(" %d  ", t[ligne][colonne].valeur);
                }
                else
                {
                    printf(" %d ", t[ligne][colonne].valeur); // affiche la case du tableau correspondante
                }
            }
        }
        printf("|\n");
    }
    printf("   +----------------+----------------+----------------+----------------+\n");
}

void chargerGrille(tGrille g, char nomFichier[30])
{
    t_grille_valeur liste_valeur;
    FILE *f;
    int i, j;

    f = fopen(nomFichier, "rb");
    if (f == NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    }
    else
    {
        fread(liste_valeur, sizeof(int), TAILLE * TAILLE, f);
    }
    fclose(f);

    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            g[i][j].valeur = liste_valeur[i][j];
        }
    }
}

void ajouterCandidat(tCase2 *laCase, int val)
{
    if (laCase->candidats[val] == false)
    {
        laCase->candidats[val] = true;
        laCase->nbCandidats++;
    }
}

void retirerCandidat(tCase2 *laCase, int val)
{
    if (laCase->candidats[val] == true)
    {
        laCase->candidats[val] = false;
        laCase->nbCandidats--;
    }
}

bool estCandidat(tCase2 laCase, int val)
{

    return laCase.candidats[val];
}

void afficheresult(char nom_fichier[10], float case_vide, float case_restante_vide, float candidat_depart, float candidat_fin)
{

    float tx_remplissage, tx_elimination, candidat_en_moin, case_rempli;
    candidat_en_moin = candidat_depart - candidat_fin;
    case_rempli = (case_vide - case_restante_vide);
    tx_remplissage = case_rempli / case_vide * 100;
    tx_elimination = candidat_en_moin / candidat_depart * 100;
    // printf("candidat depart :%.3f ---> candidat(s) elimine(s) : %.3f ", candidat_depart, candidat_en_moin);
    // printf("tx_elimination : %.3f\n tx remplissage : %.3f\n", tx_elimination, tx_remplissage);

    printf("\n\n\n");

    printf("*****  RESULTATS POUR %s  *****\n", nom_fichier);

    printf("Nombre de cases remplies = %.0f sur %.0f           Taux de remplissage = %.3f %% \n", case_rempli, case_vide, tx_remplissage);
    printf("Nombre de candidats elimines = %.0f sur %.0f           Pourcent d'elimination = %.3f %% \n", candidat_en_moin, candidat_depart, tx_elimination);
    printf("\n\n\n");
}

void initialiserCandidats(tGrille grille)
{
    int ligne, colonne, candidat;

    for (ligne = 0; ligne < TAILLE; ligne++)
    {

        for (colonne = 0; colonne < TAILLE; colonne++)
        {

            grille[ligne][colonne].nbCandidats = 0;

            if ((grille[ligne][colonne].valeur) == 0)
            {

                for (candidat = 1; candidat < TAILLE + 1; candidat++)
                {

                    if (possible(candidat, grille, ligne, colonne))
                    {
                        ajouterCandidat(&grille[ligne][colonne], candidat);
                    }
                }
            }
        }
    }
}

int nombre_candidat_total(tGrille grille)
{
    int i, j, total = 0;
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            total += grille[i][j].nbCandidats;
        }
    }
    return total;
}

void retirer_tout_Candidat(tGrille grille, int val, int ligne, int colonne)
{
    int x, y;
    for (y = 0; y < TAILLE; y++)
    {
        retirerCandidat(&grille[ligne][y], val);
    }

    for (x = 0; x < TAILLE; x++)
    {
        retirerCandidat(&grille[x][colonne], val);
    }

    // parcours toutes les cases du block avec un case x/y
    int case_x = ligne - (ligne % N);
    int case_y = colonne - (colonne % N);

    for (x = case_x; x < case_x + N; x++)
    {

        for (y = case_y; y < case_y + N; y++)
        {

            retirerCandidat(&grille[x][y], val);
        }
    }
}

void ajouter_tout_Candidat(tGrille grille, int val, int ligne, int colonne)
{
    int i, j;
    int case_x = ligne - (ligne % N);
    int case_y = colonne - (colonne % N);
    // int numeroCase = 0;
    int lig = case_x, col = case_y;

    for (i = 0; i < TAILLE; i++)
    {
        if (possible(val, grille, ligne, i))
        {
            ajouterCandidat(&grille[ligne][i], val);
        }
        if (possible(val, grille, i, colonne))
        {
            ajouterCandidat(&grille[i][colonne], val);
        }
    }
    for (i = case_x; i < case_x + N; i++)
    {
        for (j = case_y; j < case_y + N; j++)
        {
            if (possible(val, grille, lig, col))
            {
                ajouterCandidat(&grille[lig][col], val);
            }
        }
    }

    // printf("\n");
    // while (numeroCase < TAILLE)
    // {
    //     // printf("possible?  ");

    //     if (possible(val, grille, ligne, numeroCase))
    //     {
    //         ajouterCandidat(&grille[ligne][numeroCase], val);
    //     }

    //     if (possible(val, grille, numeroCase, colonne))
    //     {
    //         ajouterCandidat(&grille[numeroCase][colonne], val);
    //     }
    //     if (possible(val, grille, lig, col))
    //     {
    //         ajouterCandidat(&grille[lig][col], val);
    //     }
    //     col++;
    //     if (col % N == 0)
    //     {
    //         col = case_y;
    //         lig++;
    //     }
    //     numeroCase++;
    // }
}
