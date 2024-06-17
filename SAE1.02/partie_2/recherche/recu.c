/**
 * \file
 * \author Marius Chartier--Le Goff
 * \date 17/01/24
 * \brief Résolution de sudoku avec Backtracking avancée
 *
 * Résolution d'une grille de sudoku avec la technique Backtraking
 *   - Parcours la grille case par case
 *   - Sélectionne les candidats des cases
 *   - Commence par les cases qui ont le moins de candidats
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// MaxiGrilleA.sud
/**
 * \def N Longueur d'une case de Sudoku
 */
#define N 4
/**
 * \def TAILLE Dimension d'une ligne/colonne/bloc de la grille
 */
#define TAILLE (N * N)

/**
 *
 */
typedef int tGrille[TAILLE][TAILLE];

/**
 * \struct t_candidat
 * \brief
 */
typedef struct
{
    int nb_candidat;
    int candidat[TAILLE][TAILLE];
} t_candidat;

/**
 * \struct tValeur
 * \brief
 */
typedef struct
{
    int nb_valeur;      /* Nombre de valeur */
    int valeur[TAILLE]; /* Tanleau de valeur */
} tValeur;

/**
 * \struct t_tuple
 * \brief
 */
typedef struct
{
    int l;
    int c;
    int b;
} t_tuple;

/**
 * \struct t_cases_vides
 * \brief Stocks les cases vides
 * - Compte le nombre de case vide
 * - note leurs cordonnées
 */
typedef struct
{
    t_tuple cases[TAILLE * TAILLE + 1]; /* Coordonnées des cases vides */
    int nb_tuple;                       /* Nombre de case vide*/
} t_cases_vides;

/**
 * \fn void affiche_grille(tGrille grille)
 * \brief affiche la grille de sudoku
 * \param grille E/S tableau d'entier qui représente la grille de sudoku
 */
void affiche_grille(tGrille grille);

/**
 * \fn void chargerGrille(tGrille g, char nomFichier[30])
 * \brief initialise une grille se sudoku à partir d'un fichier
 * \param grille E/S tableau d'entier qui représente la grille de sudoku
 * \param nomFichier E nom du fichier source
 */
void chargerGrille(tGrille g, char nomFichier[30]);

/**
 * \fn void sudoku(tGrille grille)
 * \brief initialise les candidats et appel le backtracking
 * \param grille E/S tableau d'entier qui représente la grille de sudoku
 */
void sudoku(tGrille grille);

/**
 * \fn void selectionne_case(int pos, t_cases_vides *cases, t_candidat lsets, t_candidat csets, t_candidat bsets)
 * \brief
 * \param pos E
 * \param cases E/S
 * \param lsets E
 * \param csets E
 * \param bsets E
 */
void selectionne_case(int pos, t_cases_vides *cases, t_candidat lsets, t_candidat csets, t_candidat bsets);

/**
 * \fn bool essaye_case(tGrille grille, int pos, t_cases_vides *cases, t_candidat *lsets, t_candidat *csets, t_candidat *bsets)
 * \brief
 * \param grille E/S tableau d'entier qui représente la grille de sudoku
 * \param pos E
 * \param cases E/S
 * \param lsets E/S
 * \param csets E/S
 * \param bsets E/S
 */
bool essaye_case(tGrille grille, int pos, t_cases_vides *cases, t_candidat *lsets, t_candidat *csets, t_candidat *bsets);

/**
 * \fn void init_candidat(t_candidat *candidat)
 * \brief initialise la liste de candidats
 * \param candidat E/S liste de candidats
 */
void init_candidat(t_candidat *candidat);

/**
 * \fn void init_t_cases_vides(t_cases_vides *cases_vides)
 * \brief initialise les cases vides avec les cordonnées et le nombre de cases vides
 * \param cases_vides E/S liste de candidats vides
 */
void init_t_cases_vides(t_cases_vides *cases_vides);

/**
 * \fn void add(t_candidat *candidat, int ligne, int val)
 * \brief ajoute le candidat d'une case
 * \param candidat E/S liste des candidats
 * \param ligne E position de la case d'une ligne
 * \param val E valeur de la case à ajouter
 */
void add(t_candidat *candidat, int ligne, int val);

/**
 * \fn void remove1(t_candidat *candidat, int ligne, int val)
 * \brief retire le candidat d'une case
 * \param candidat E/S liste des candidats
 * \param ligne E ligne de la case
 * \param val E valeur du candidat à retirer
 */
void remove1(t_candidat *candidat, int ligne, int val);

/**
 * \fn void ajout_case_vide(t_cases_vides *case_vide, t_tuple pos)
 * \brief
 * \param case_vide E/S
 * \param pos E
 */
void ajout_case_vide(t_cases_vides *case_vide, t_tuple pos);

/**
 * \fn int intersection(t_candidat lsets, t_candidat csets, t_candidat bsets, int l, int c, int b)
 * \brief
 * \param lsets E
 * \param csets E
 * \param bsets E
 * \param l E
 * \param c E
 * \param b E
 */
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

void sudoku(tGrille grille)
{

    int l, c, b;
    t_candidat lsets, csets, bsets;
    t_cases_vides cases;
    t_tuple pour_ajout;
    init_candidat(&lsets);
    init_candidat(&csets);
    init_candidat(&bsets);
    init_t_cases_vides(&cases);

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
                // printf(" %d",cases.nb_tuple);
                ajout_case_vide(&cases, pour_ajout);
            }
            else
            {
                remove1(&lsets, l, grille[l][c] - 1);
                remove1(&csets, c, grille[l][c] - 1);
                remove1(&bsets, b, grille[l][c] - 1);
            }
        }
    }

    // résolution
    essaye_case(grille, 0, &cases, &lsets, &csets, &bsets);
}
void selectionne_case(int pos, t_cases_vides *cases, t_candidat lsets, t_candidat csets, t_candidat bsets)
{
    // on regarde la case actuelle
    t_tuple temporaire;
    int l, c, b, i, courant, cardinal_courant, cardinal_i;

    l = cases->cases[pos].l;
    c = cases->cases[pos].c;
    b = cases->cases[pos].b;
    courant = pos;
    cardinal_courant = intersection(lsets, csets, bsets, l, c, b);

    for (i = pos + 1; i < cases->nb_tuple; i++)
    {

        l = cases->cases[i].l;
        c = cases->cases[i].c;
        b = cases->cases[i].b;
        cardinal_i = intersection(lsets, csets, bsets, l, c, b);

        if (cardinal_i < cardinal_courant)
        {
            courant = i;
            cardinal_courant = cardinal_i;
        }
    }

    if (courant != pos)
    {
        temporaire = cases->cases[courant];
        cases->cases[courant] = cases->cases[pos];
        cases->cases[pos] = temporaire;
    }
}

bool essaye_case(tGrille grille, int pos, t_cases_vides *cases, t_candidat *lsets, t_candidat *csets, t_candidat *bsets)
{
    int l, c, b, v;

    if (pos == cases->nb_tuple)
    {
        return true;
    }
    selectionne_case(pos, cases, *lsets, *csets, *bsets);
    l = cases->cases[pos].l;
    c = cases->cases[pos].c;
    b = cases->cases[pos].b;

    //  intersection(lsets, csets, bsets, l, c, b)
    for (v = 0; v < TAILLE; v++)
    {

        if (lsets->candidat[l][v] == 1 && csets->candidat[c][v] == 1 && bsets->candidat[b][v] == 1)
        {

            remove1(lsets, l, v);
            remove1(csets, c, v);
            remove1(bsets, b, v);
            if (essaye_case(grille, pos + 1, cases, lsets, csets, bsets))
            {
                grille[l][c] = v + 1;
                return true;
            }
            add(lsets, l, v);
            add(csets, c, v);
            add(bsets, b, v);
        }
    }
    return false;
}

void init_candidat(t_candidat *candidat)
{
    int ligne, colonne;
    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            candidat->candidat[ligne][colonne] = 1;
        }
    }
    candidat->nb_candidat = 9;
}

void init_t_cases_vides(t_cases_vides *cases_vides)
{
    int i;
    for (i = 0; i < TAILLE * TAILLE; i++)
    {
        cases_vides->cases[i].l = 0;
        cases_vides->cases[i].c = 0;
        cases_vides->cases[i].b = 0;
    }
    cases_vides->nb_tuple = 0;
}

void add(t_candidat *candidat, int ligne, int val)
{

    if (candidat->candidat[ligne][val] != 1)
    {
        candidat->candidat[ligne][val] = 1;
        candidat->nb_candidat++;
    }
}

void remove1(t_candidat *candidat, int ligne, int val)
{

    if (candidat->candidat[ligne][val] != 0)
    {
        candidat->candidat[ligne][val] = 0;
        candidat->nb_candidat--;
    }
}

void ajout_case_vide(t_cases_vides *case_vide, t_tuple pos)
{
    // printf(" %d",case_vide->nb_tuple);
    case_vide->cases[case_vide->nb_tuple] = pos;

    case_vide->nb_tuple++;
}

int intersection(t_candidat lsets, t_candidat csets, t_candidat bsets, int l, int c, int b)
{
    tValeur temporaire;
    for (int i = 0; i < TAILLE; i++)
    {

        if ((lsets.candidat[l][i] == csets.candidat[c][i]) && (lsets.candidat[l][i] == bsets.candidat[b][i]) && (lsets.candidat[l][i] == 1))
        {
            temporaire.valeur[i] = 1;
            temporaire.nb_valeur++;
        }
    }

    return temporaire.nb_valeur;
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
