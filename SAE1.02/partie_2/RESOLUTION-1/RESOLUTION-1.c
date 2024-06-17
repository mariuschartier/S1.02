#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// MaxiGrilleA.sud
#define N 4
#define TAILLE (N * N)
typedef int tGrille[TAILLE][TAILLE];


bool absentSurLigne(int valeur, tGrille grille, int ligne);
bool absentSurBloc(int valeur, tGrille grille, int ligne, int colonne);
bool absentSurColonne(int valeur, tGrille grille, int colonne);
bool possible(int valeur, tGrille grille, int ligne, int colonne);

void affiche_grille(tGrille grille);
void chargerGrille(tGrille g, char nomFichier[30]);

bool backtracking(tGrille grille, int numeroCase)
{

  int ligne, colonne, valeur;
  bool resultat;

  resultat = false;

  if (numeroCase == (TAILLE * TAILLE))
  {
    // on a traité toutes les cases, la grille est résolue
    resultat = true;
  }
  else
  {
    // On récupère les "coordonnées" de la case
    ligne = numeroCase / (TAILLE * 1);
    colonne = numeroCase % (TAILLE * 1);
    if (grille[ligne][colonne] != 0)
    {
      // Si la case n’est pas vide, on passe à la suivante
      // (appel récursif)

      resultat = backtracking(grille, numeroCase + 1);
    }
    else
    {
      for (valeur = 1; valeur < TAILLE + 1; valeur++)
      {
        if (possible(valeur, grille, ligne, colonne))
        {
          // Si la valeur est autorisée on  l'inscrit
          // dans la case...
          grille[ligne][colonne] = valeur;
          // ... et on passe à la suivante : appel récursif
          // pour voir si ce choix est bon par la suite
          if (backtracking(grille, numeroCase + 1) == true)
          {
            resultat = true;
          }

          else
          {
            grille[ligne][colonne] = 0;
          }
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

  printf("Nom du fichier ?\n");
  scanf("%s", nom_fichier);

  chargerGrille(grille, nom_fichier);
  printf("Grille de depart\n");
  affiche_grille(grille);

  clock_t begin = clock();
  backtracking(grille, 0);
  clock_t end = clock();
  double tmpsCPU = (end - begin) * 1.0 / CLOCKS_PER_SEC;

  printf("Grille finale\n");
  affiche_grille(grille);
  printf("Resolution de la grille en %.6f sec\n", tmpsCPU);

  return EXIT_SUCCESS;
}

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
    
    if (valeur == grille[ligne][numeroCase])
    {
      resultat = false;
    }

    if ((valeur == grille[numeroCase][colonne]))
    {
      resultat = false;
    }
    if (valeur == grille[lig][col])
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
    if (valeur == grille[ligne][col])
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

    if (valeur == grille[lig][col])
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
    if ((valeur == grille[lig][colonne]))
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
      if (t[ligne][colonne] == 0)
      {
        printf(" .  "); // affiche un . quand la case est vide
      }

      else
      {
        if (t[ligne][colonne] < 10)
        {
          printf(" %d  ", t[ligne][colonne]);
        }
        else
        {
          printf(" %d ", t[ligne][colonne]); // affiche la case du tableau correspondante
        }
      }
    }
    printf("|\n");
  }
  printf("   +----------------+----------------+----------------+----------------+\n");
}

void chargerGrille(tGrille g, char nomFichier[30])
{

  FILE *f;

  f = fopen(nomFichier, "rb");
  if (f == NULL)
  {
    printf("\n ERREUR sur le fichier %s\n", nomFichier);
  }
  else
  {
    fread(g, sizeof(int), TAILLE * TAILLE, f);
  }
  fclose(f);
}

