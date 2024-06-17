#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// MaxiGrilleA.sud
#define N 4
#define TAILLE (N * N)
typedef int tGrille[TAILLE][TAILLE];

typedef struct
{
    int nb_candidat;
    int candidat[TAILLE][TAILLE];
} t_candidat;

typedef struct
{
    int nb_valeur;
    int valeur[TAILLE];
} tValeur;

typedef struct
{
    int l;
    int c;
    int b;
} t_tuple;

typedef struct
{
    t_tuple cases[TAILLE * TAILLE + 1];
    int nb_tuple;
} t_cases_vides;

bool possible(int valeur, tGrille grille, int ligne, int colonne);

void affiche_grille(tGrille grille);
void chargerGrille(tGrille g, char nomFichier[30]);

bool sudoku(tGrille grille);
void selectionne_case(int pos, t_cases_vides cases, t_candidat lsets, t_candidat csets, t_candidat bsets);
bool essaye_case(tGrille grille, int pos, t_cases_vides cases, t_candidat lsets, t_candidat csets, t_candidat bsets);

void init_candidat(t_candidat candidat);
void init_t_cases_vides(t_cases_vides cases_vides);
void add(t_candidat candidat, int ligne, int val);
void remove1(t_candidat candidat, int ligne, int val);
void ajout_case_vide(t_cases_vides case_vide, t_tuple pos);
int intersection(t_candidat lsets, t_candidat csets, t_candidat bsets, int l, int c, int b);

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

    sudoku(grille);
    clock_t end = clock();
    double tmpsCPU = (end - begin) * 1.0 / CLOCKS_PER_SEC;

    printf("Grille finale\n");
    affiche_grille(grille);
    printf("Resolution de la grille en %.6f sec\n", tmpsCPU);

    return EXIT_SUCCESS;
}

bool sudoku(tGrille grille)
{

    int l, c, b;
    t_candidat lsets, csets, bsets;
    t_cases_vides cases;
    t_tuple pour_ajout;
    init_candidat(lsets);
    init_candidat(csets);
    init_candidat(bsets);
    init_t_cases_vides(cases);

    // préparation
    for (l = 0; l < TAILLE; l++)
    {
        for (c = 0; c < TAILLE; c++)
        {
            b = (c / N) + N * (l / N);
            // print(grille)
            // print("c : ", c, " l ", l)

            if (grille[l][c] == 0)
            {
                pour_ajout.l = l;
                pour_ajout.c = c;
                pour_ajout.b = b;

                ajout_case_vide(cases, pour_ajout);
            }
            else
            {
                remove1(lsets, l, grille[l][c]);
                remove1(csets, c, grille[l][c]);
                remove1(bsets, b, grille[l][c]);
            }
        }
    } // résolution
    return essaye_case(grille, 0, cases, lsets, csets, bsets);
}
void selectionne_case(int pos, t_cases_vides cases, t_candidat lsets, t_candidat csets, t_candidat bsets)
{
    // on regarde la case actuelle
    t_tuple temporaire;
    int l, c, b, i, courant, cardinal_courant, cardinal_i;
    l = cases.cases[pos].l;
    c = cases.cases[pos].c;
    b = cases.cases[pos].b;
    courant = pos;
    cardinal_courant = intersection(lsets, csets, bsets, l, c, b);
    // printf("CC%d",cardinal_courant);
    for (i = 0; i < cases.nb_tuple; i++)
    {
        // i in range(pos + 1, len(cases)) :

        l = cases.cases[i].l;
        c = cases.cases[i].c;
        b = cases.cases[i].b;
        cardinal_i = intersection(lsets, csets, bsets, l, c, b);

        if (cardinal_i < cardinal_courant)
        {
            courant = i;
            cardinal_courant = cardinal_i;
        }
    }

    if (courant != pos)
    { // on échange les cases
        temporaire = cases.cases[courant];
        cases.cases[courant] = cases.cases[pos];
        cases.cases[pos] = temporaire;
    }
}

bool essaye_case(tGrille grille, int pos, t_cases_vides cases, t_candidat lsets, t_candidat csets, t_candidat bsets)
{
    printf("test");
    int l, c, b, v;

    if (pos == cases.nb_tuple)
    {
        return true;
    }
    selectionne_case(pos, cases, lsets, csets, bsets);
    l = cases.cases[pos].l;
    c = cases.cases[pos].c;
    b = cases.cases[pos].b;

    for (v = 0; v < intersection(lsets, csets, bsets, l, c, b); v++)
    {
        remove1(lsets, l, v);
        remove1(csets, c, v);
        remove1(bsets, b, v);
        if (essaye_case(grille, pos + 1, cases, lsets, csets, bsets))
        {
            grille[l][c] = v;
            return true;
        }
        add(lsets, l, v);
        add(csets, c, v);
        add(bsets, b, v);
    }
    return false;
}

void init_candidat(t_candidat candidat)
{
    int ligne, colonne;
    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            candidat.candidat[ligne][colonne] = 1;
        }
    }
    candidat.nb_candidat = 9;
}
void init_t_cases_vides(t_cases_vides cases_vides)
{
    int i;
    for (i = 0; i < TAILLE * TAILLE; i++)
    {
        cases_vides.cases[i].l = 0;
        cases_vides.cases[i].c = 0;
        cases_vides.cases[i].b = 0;
    }
    cases_vides.nb_tuple = 0;
}
void add(t_candidat candidat, int ligne, int val)
{
    int indice;

    for (indice = 0; indice < TAILLE; indice++)
    {
        if (candidat.candidat[ligne][indice] == val)
        {
            if (candidat.candidat[ligne][indice] != 1)
            {
                candidat.candidat[ligne][indice] = 1;
                candidat.nb_candidat++;
            }
        }
    }
}

void remove1(t_candidat candidat, int ligne, int val)
{
    int indice;

    for (indice = 0; indice < TAILLE; indice++)
    {
        if (candidat.candidat[ligne][indice] == val)
        {
            if (candidat.candidat[ligne][indice] != 0)
            {
                candidat.candidat[ligne][indice] = 0;
                candidat.nb_candidat--;
            }
        }
    }
}

void ajout_case_vide(t_cases_vides case_vide, t_tuple pos)
{
    case_vide.cases[case_vide.nb_tuple] = pos;
    case_vide.nb_tuple++;
}

int intersection(t_candidat lsets, t_candidat csets, t_candidat bsets, int l, int c, int b)
{
    tValeur temporaire;
    int i, nombre_de_candidat = 0;
    for (i = 0; i < TAILLE; i++)
    {

        if ((lsets.candidat[l][i] == csets.candidat[c][i]) && (lsets.candidat[l][i] == bsets.candidat[b][i]) && (lsets.candidat[l][i] == 1))
        {
            temporaire.valeur[i] = 1;
            temporaire.nb_valeur++;
        }
    }
    for (i = 0; i < TAILLE; i++)
    {

        if (temporaire.valeur[i] == 1)
        {
            nombre_de_candidat++;
        }
    }

    return nombre_de_candidat;
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
