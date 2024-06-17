
#define N 3
#define TAILLE (N * N)

typedef struct
{
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];

typedef int tStock[TAILLE];

typedef struct
{
    int femme;
    int mari;
} tCouple;

// typedef tCouple tMenage[TAILLE];
typedef struct
{
    tCouple stock[1100];
    int nb_couple;

} tMenage;

void est_candidat(int x);
void compare_couple(tCouple a, tCouple b); // dit si deux couple sont les meme

int couple_present(tCouple a, tMenage stock); // dit si le couple est dans les candidats

void ajoute_couple(tCouple a, tMenage stock); // rajoute couple à stock

void singleton_nu(tGrille grille, int x, int y)
{
    // pour une case
    int candidat, i;
    if (grille[x][y].nbCandidats == 1)
    {
        // methode 1
        // candidat =  grille[x][y].candidats[0]
        // methode 2
        /*for ( i = 0; i < TAILLE; i++)
        {
            if(grille[x][y].candidats[i]){candidat = i+1;}
        }*/

        grille[x][y].valeur = candidat;
        // vider la liste des candidats
    }
}

void singleton_caché(tGrille grille)
{
    tStock stock;
    int i, j, n;
    // parcours
    // compte les candidats dans stock

    for (n = 0; n < TAILLE; n++)
    {
        if (stock[n] == 1)
        {
            // parcours
            if (est_candidat(stock[n] + 1))
            {
                grille[i][j].valeur = stock[n] + 1;
                // vider la liste des candidats
            }
        }
    }
}

void paire_nu(tGrille grille)
{
    int i, j, nb_couple;
    tMenage stock;
    stock.nb_couple = 0;
    tCouple couple;
    // parcours
    // met les different couple dans stock.
    if (grille[i][j].nbCandidats == 2)
    {
        // methode 1
        couple.femme = grille[i][j].candidats[0];
        couple.mari = grille[i][j].candidats[1];
        if (couple_present(couple, stock) = 0)
        {
            ajoute_couple(couple, stock);
        }
        else
        {
            // parcours
            // supprimme les couple autre
            if (grille[i][j].nbCandidats != 2)
            {
                retirerCandidat(grille[i][j], couple.femme);
                retirerCandidat(grille[i][j], couple.mari);
            }
        }
    }
}

void paire_cachées(tGrille grille)
{

    int i, j, nb_couple, x, y;
    tMenage stock;
    stock.nb_couple = 0;
    tCouple couple;
    // parcours
    if (grille[i][j].nbCandidats > 1)
    {
        // selection du couple : metode 1
        for (x = 0; x < grille[i][j].nbCandidats; x++)
        {
            for (y = 0; y < grille[i][j].nbCandidats; y++)
            {
            }
        }

        couple.femme = grille[i][j].candidats[0];
        couple.mari = grille[i][j].candidats[1];

        // comparaison au autre case
        // si 2 apparition suppression des autres nombres
    }
}

void singleton_cache(tGrille grille, bool progression);
void paire_nu(tGrille grille, bool progression);
void paire_cachees(tGrille grille, bool progression);

singleton_cache(g, progression);
paire_nu(g, progression);
paire_cachees(g, progression);

printf(" test\n");
S1.02/GrilleA.sud
S1.02/GrilleB.sud
S1.02/GrilleC.sud
S1.02/GrilleD.sud