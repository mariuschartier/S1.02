
#define N 3
#define TAILLE (N * N)

typedef struct
{
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];

void parcour(x, y)
{
    tGrille grille;
    int i, j;

    // parcours toutes les cases
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            printf("%d", grille[i][j].valeur);
        }
    }
    // parcours toutes les cases de la colonne "x"
    for (j = 0; j < TAILLE; j++)
    {
        printf("%d", grille[x][j].valeur);
    }
    // parcours toutes les cases de la ligne "y"
    for (i = 0; i < TAILLE; i++)
    {
        printf("%d", grille[j][y].valeur);
    }
    // parcours toutes les cases du block avec un case x/y
    int case_x = i - (i % 3);
    int case_y = i - (j % 3);
    for (i = case_x; i < case_x + 2; i++)
    {
        for (j = case_y; j < case_y + 2; j++)
        {
            printf("%d", grille[i][j].valeur);
        }
    }
}
