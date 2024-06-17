#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define N 3
#define TAILLE (N * N)

typedef struct
{
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;
typedef tCase1 tGrille[TAILLE][TAILLE];

// permet de retenir les information du fichier .sud
typedef int tGrille_valeur[TAILLE][TAILLE];

// permet de se souvenir du nombre d'apparition d'un candidat
typedef int tStock[TAILLE];

typedef struct
{
    int femme;
    int mari;
    int nombre_apparition;
} tCouple;

// typedef tCouple tMenage[TAILLE];
typedef struct
{
    tCouple stock[100];
    int nb_couple;

} tMenage;

void affiche_candidat(tCase1 la_case);
int chargerGrille2(tGrille g, char nomFichier[30]);
void ajouterCandidat(tCase1 *laCase, int val);
void retirerCandidat(tCase1 *laCase, int val);
bool estCandidat(tCase1 laCase, int val);

int compte_zero(tGrille grille);
int nbCandidats(tCase1 laCase);
void initialiserCandidats(tGrille grille);
int nombre_candidat_total(tGrille grille);
void retirer_tout_Candidat(tGrille grille, int val, int ligne, int colonne);

void afficheresult(char nom_fichier[10], float case_vide, float case_rempli, float candidat_depart, float candidat_fin);

void singleton_nu(tGrille grille, bool *progression);

void singleton_cache(tGrille grille, bool *progression);

void paire_nu(tGrille grille, bool *progression);
bool compare_couple(tCouple a, tCouple b);         // dit si deux couple sont les meme
bool couple_present(tCouple a, tMenage stock);     // dit si le couple est dans les candidats
void ajoute_couple(tCouple a, tMenage *stock);     // rajoute couple à stock*
void couple_apparition(tCouple a, tMenage *stock); // si un couple apparait on le compte
void initialiser_stock(tStock a_init);

void paire_cachees(tGrille grille, bool *progression);

int main()
{

    tGrille g;
    char nomFichier[30];
    bool progression;
    int nbCasesVides_depart = 0, nbCandidats_debut = 0, tours = 0, nbCasesVides = 0;
    printf("Nom du fichier ?\n");
    scanf("%s", nomFichier);
    nbCasesVides_depart = chargerGrille2(g, nomFichier);
    nbCasesVides = nbCasesVides_depart;
    initialiserCandidats(g);

    nbCandidats_debut = nombre_candidat_total(g);

    progression = true;
    while ((nbCasesVides != 0) && progression)
    {
        printf("\n tours : %d\n", tours);
        tours++;

        progression = false;
        singleton_nu(g, &progression);

        if (progression == false)
        {
            singleton_cache(g, &progression);
        }
        if (progression == false)
        {
            paire_nu(g, &progression);
        }
        if (progression == false)
        {
            paire_cachees(g, &progression);
        }
        nbCasesVides = compte_zero(g);
    }

    afficheresult(nomFichier, nbCasesVides_depart, compte_zero(g), nbCandidats_debut, nombre_candidat_total(g));
}

void affiche_candidat(tCase1 la_case)
{
    int i;

    for (i = 0; i < la_case.nbCandidats; i++)
    {
        printf("%d ", la_case.candidats[i]);
    }
    printf("\n");
}

int chargerGrille2(tGrille g, char nomFichier[30])
{
    tGrille_valeur liste_valeur;

    int i, j, nb_z = 0;
    FILE *f;

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
    nb_z = compte_zero(g);
    return nb_z;
}

int compte_zero(tGrille grille)
{
    int ligne, colonne, nb_z = 0;
    // printf("\n");
    // printf("\n+-------+-------+-------+\n");
    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        // printf("| ");
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            // printf("%d ", grille[ligne][colonne].valeur);
            if (grille[ligne][colonne].valeur == 0)
            {
                nb_z++;
            }
            if (colonne % N == 2)
            {
                // printf("| ");
            }
        }
        if (ligne % N == 2)
        {
            // printf("\n+-------+-------+-------+");
        }
        // printf("\n");
    }
    return (nb_z);
}

void ajouterCandidat(tCase1 *laCase, int val)
{
    int i = 0, j = 0;
    // printf(" candidat1 val :%d\n", val);
    if (laCase->nbCandidats == 0)
    {
        laCase->candidats[0] = val;
    }
    else
    {
        while (i < laCase->nbCandidats)
        {
            i++;
        }

        // printf(" candidat2\n");
        for (j = laCase->nbCandidats - 1; j >= i; j--)
        {
            laCase->candidats[j + 1] = laCase->candidats[j];
        }
        laCase->candidats[i] = val;
    }

    laCase->nbCandidats++;

    // printf(" candidat3 :");
    // affiche_candidat(*laCase);
}

void retirerCandidat(tCase1 *laCase, int val)
{
    int i, x, indice_candidat;
    if (estCandidat(*laCase, val))
    {
        for (x = 0; x < laCase->nbCandidats; x++)
        {
            if (laCase->candidats[x] == val)
            {
                indice_candidat = x;
            }
        }

        for (i = indice_candidat; i < laCase->nbCandidats; i++)
        {
            laCase->candidats[i] = laCase->candidats[i + 1];
        }
        laCase->candidats[laCase->nbCandidats + 1] = 0;
        laCase->nbCandidats--;
    }
}

bool estCandidat(tCase1 laCase, int val)
{
    bool verification;
    verification = false;
    int i;
    if (laCase.nbCandidats != 0)
    {
        for (i = 0; i < laCase.nbCandidats; i++)
        {
            if (laCase.candidats[i] == val)
            {
                verification = true;
            }
        }
    }
    return verification;
}

int nbCandidats(tCase1 laCase)
{
    int n, i;
    n = 0;
    i = 1;
    while (laCase.candidats[i] != 0)
    {
        n++;
        i++;
    }
    return n;
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
    int ligne, colonne, x, y, candidat;
    bool candidat_present;

    for (ligne = 0; ligne < TAILLE; ligne++)
    {

        for (colonne = 0; colonne < TAILLE; colonne++)
        {

            grille[ligne][colonne].nbCandidats = 0;

            if ((grille[ligne][colonne].valeur) == 0)
            {

                for (candidat = 1; candidat < TAILLE + 1; candidat++)
                {
                    candidat_present = false;
                    if (estCandidat(grille[ligne][colonne], candidat) == false)
                    {

                        for (y = 0; y < TAILLE; y++)
                        {
                            if (grille[ligne][y].valeur == candidat)
                            {
                                candidat_present = true;
                            }
                        }

                        for (x = 0; x < TAILLE; x++)
                        {
                            if (grille[x][colonne].valeur == candidat)
                            {
                                candidat_present = true;
                            }
                        }

                        // parcours toutes les cases du block avec un case x/y
                        int case_i = ligne - (ligne % 3);
                        int case_j = colonne - (colonne % 3);
                        for (x = case_i; x < case_i + 3; x++)
                        {
                            for (y = case_j; y < case_j + 3; y++)
                            {
                                if (grille[x][y].valeur == candidat)
                                {
                                    candidat_present = true;
                                }
                            }
                        }

                        if (candidat_present == false)
                        {
                            ajouterCandidat(&grille[ligne][colonne], candidat);
                        }
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
    int case_x = ligne - (ligne % 3);
    int case_y = colonne - (colonne % 3);

    for (x = case_x; x < case_x + 3; x++)
    {

        for (y = case_y; y < case_y + 3; y++)
        {

            retirerCandidat(&grille[x][y], val);
        }
    }
}

bool compare_couple(tCouple a, tCouple b)
{
    bool resultat = false;
    if ((a.femme == b.femme && a.mari == b.mari) || (a.femme == b.mari && a.mari == b.femme))
    {
        resultat = true;
    }
    return resultat;
}

bool couple_present(tCouple a, tMenage stock)
{ // si le couple est présent sont nombre d'apparition augmente
    bool resultat = false;
    int i;
    for (i = 0; i < stock.nb_couple; i++)
    {
        if (compare_couple(a, stock.stock[i]))
        {
            resultat = true;
        }
    }

    return resultat;
}

void ajoute_couple(tCouple a, tMenage *stock)
{
    stock->stock[stock->nb_couple] = a;
    stock->stock[stock->nb_couple].nombre_apparition = 1;
    stock->nb_couple++;
}

void couple_apparition(tCouple a, tMenage *menage)
{

    int i;
    for (i = 0; i < menage->nb_couple; i++)
    {
        if (compare_couple(a, menage->stock[i]))
        {
            menage->stock[i].nombre_apparition++;
        }
    }
}

void initialiser_stock(tStock a_init)
{

    int i;
    for (i = 0; i < TAILLE; i++)
    {
        a_init[i] = 0;
    }

    // for (i = 0; i < TAILLE; i++)
    // {
    //     printf(" %d", a_init[i]);
    // }
    // printf("\n");
}

// méthode de tri
void singleton_nu(tGrille grille, bool *progression)
{
    int ligne, colonne;

    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {

            if (((grille[ligne][colonne].valeur) == 0) && (grille[ligne][colonne].nbCandidats == 1))
            {
                grille[ligne][colonne].valeur = grille[ligne][colonne].candidats[0];
                grille[ligne][colonne].nbCandidats = 0;

                retirer_tout_Candidat(grille, grille[ligne][colonne].valeur, ligne, colonne);

                *progression = true;
            }
        }
    }
}

void singleton_cache(tGrille grille, bool *progression)
{
    tStock stock;
    int i, j, indice_stock, indice_dans_nbcandidats;

    int ligne, colonne;
    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            initialiser_stock(stock);

            if (grille[ligne][colonne].valeur == 0)
            {

                // parcours toutes les cases de la ligne "ligne"
                for (j = 0; j < TAILLE; j++)
                {
                    for (indice_dans_nbcandidats = 0; indice_dans_nbcandidats < grille[ligne][j].nbCandidats; indice_dans_nbcandidats++)
                    {
                        // on ajoute 1 au nombre de candidat de valeur grille[i][j].candidats[i] et donc d'indice grille[ligne][j].candidats[indice_dans_nbcandidats] - 1
                        // on compte le nombre d'apparition de chaque chiffre de 1 à 9
                        stock[grille[ligne][j].candidats[indice_dans_nbcandidats] - 1]++;
                    }
                }

                for (indice_stock = 0; indice_stock < TAILLE; indice_stock++)
                {
                    if (stock[indice_stock] == 1)
                    {
                        for (j = 0; j < TAILLE; j++)
                        {
                            if (estCandidat(grille[ligne][j], indice_stock + 1))
                            {
                                grille[ligne][j].valeur = indice_stock + 1;
                                grille[ligne][j].nbCandidats = 0;
                                retirer_tout_Candidat(grille, grille[ligne][j].valeur, ligne, j);
                                *progression = true;
                            }
                        }
                    }
                }
                initialiser_stock(stock);

                // parcours toutes les cases de la colonne "i"
                for (i = 0; i < TAILLE; i++)
                {

                    for (indice_dans_nbcandidats = 0; indice_dans_nbcandidats < grille[i][colonne].nbCandidats; indice_dans_nbcandidats++)
                    {

                        // on ajoute 1 au nombre de candidat de valeur grille[i][j].candidats[i]
                        stock[grille[i][colonne].candidats[indice_dans_nbcandidats] - 1]++;
                    }
                }

                for (indice_stock = 0; indice_stock < TAILLE; indice_stock++)
                {

                    if (stock[indice_stock] == 1)
                    {
                        for (i = 0; i < TAILLE; i++)
                        {
                            if (estCandidat(grille[i][colonne], indice_stock + 1))
                            {
                                grille[i][colonne].valeur = indice_stock + 1;
                                // affiche_candidat(grille[i][colonne]);
                                grille[i][colonne].nbCandidats = 0;
                                retirer_tout_Candidat(grille, grille[i][colonne].valeur, i, colonne);
                                *progression = true;
                            }
                        }
                    }
                }
                initialiser_stock(stock);
                // parcours toutes les cases du block avec un case x/y
                int case_x = ligne - (ligne % 3);
                int case_y = colonne - (colonne % 3);
                for (i = case_x; i < case_x + 3; i++)
                {
                    for (j = case_y; j < case_y + 3; j++)
                    {
                        for (indice_dans_nbcandidats = 0; indice_dans_nbcandidats < grille[i][j].nbCandidats; indice_dans_nbcandidats++)
                        {
                            // on ajoute 1 au nombre de candidat de valeur grille[i][j].candidats[i]
                            stock[grille[i][j].candidats[indice_dans_nbcandidats] - 1]++;
                        }
                    }
                }

                for (indice_stock = 0; indice_stock < TAILLE; indice_stock++)
                {
                    if (stock[indice_stock] == 1)
                    {
                        for (i = case_x; i < case_x + 3; i++)
                        {
                            for (j = case_y; j < case_y + 3; j++)
                            {
                                if (estCandidat(grille[i][j], indice_stock + 1))
                                {
                                    grille[i][j].valeur = indice_stock + 1;
                                    // affiche_candidat(grille[i][j]);
                                    grille[i][j].nbCandidats = 0;
                                    retirer_tout_Candidat(grille, grille[i][j].valeur, i, j);
                                    *progression = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void paire_nu(tGrille grille, bool *progression)
{
    int i, j, ligne, colonne, x, y;
    tMenage menage;
    menage.nb_couple = 0;
    tCouple couple;
    // parcours

    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {

            for (j = 0; j < TAILLE; j++)
            {
                menage.nb_couple = 0;

                if (grille[ligne][j].nbCandidats == 2)
                {

                    couple.femme = grille[ligne][j].candidats[0];
                    couple.mari = grille[ligne][j].candidats[1];
                    if (couple_present(couple, menage) == 0)
                    {

                        ajoute_couple(couple, &menage);
                    }
                    else
                    {

                        for (y = 0; y < TAILLE; y++)
                        {
                            // if (((estCandidat(grille[ligne][y], couple.femme) == false) && (estCandidat(grille[ligne][y], couple.mari) == false)) || grille[ligne][y].nbCandidats != 2)
                            if (((estCandidat(grille[ligne][y], couple.femme) || estCandidat(grille[ligne][y], couple.mari)) && estCandidat(grille[ligne][y], couple.femme) != estCandidat(grille[ligne][y], couple.mari)) || ((estCandidat(grille[ligne][y], couple.femme) && estCandidat(grille[ligne][y], couple.mari)) && grille[ligne][y].nbCandidats != 2))
                            {
                                retirerCandidat(&grille[ligne][y], couple.femme);
                                retirerCandidat(&grille[ligne][y], couple.mari);
                                *progression = true;
                            }
                        }
                    }
                }
            }

            menage.nb_couple = 0;
            // parcours toutes les cases de la colonne "i"
            for (i = 0; i < TAILLE; i++)
            {
                if (grille[i][colonne].nbCandidats == 2)
                {

                    couple.femme = grille[i][colonne].candidats[0];
                    couple.mari = grille[i][colonne].candidats[1];
                    if (couple_present(couple, menage) == 0)
                    {
                        ajoute_couple(couple, &menage);
                    }
                    else
                    {

                        for (x = 0; x < TAILLE; x++)
                        {
                            // if (((estCandidat(grille[x][colonne], couple.femme) == false) && (estCandidat(grille[x][colonne], couple.mari) == false)) || grille[x][colonne].nbCandidats != 2)
                            if (((estCandidat(grille[x][colonne], couple.femme) || estCandidat(grille[x][colonne], couple.mari)) && estCandidat(grille[x][colonne], couple.femme) != estCandidat(grille[x][colonne], couple.mari)) || ((estCandidat(grille[x][colonne], couple.femme) && estCandidat(grille[x][colonne], couple.mari)) && grille[x][colonne].nbCandidats != 2))
                            {
                                retirerCandidat(&grille[x][colonne], couple.femme);
                                retirerCandidat(&grille[x][colonne], couple.mari);
                                *progression = true;
                            }
                        }
                    }
                }
            }

            menage.nb_couple = 0;
            // parcours toutes les cases du block avec un case x/y
            int case_x = ligne - (ligne % 3);
            int case_y = colonne - (colonne % 3);
            for (i = case_x; i < case_x + 3; i++)
            {
                for (j = case_y; j < case_y + 3; j++)
                {
                    if (grille[i][j].nbCandidats == 2)
                    {

                        couple.femme = grille[i][j].candidats[0];
                        couple.mari = grille[i][j].candidats[1];
                        if (couple_present(couple, menage) == 0)
                        {
                            ajoute_couple(couple, &menage);
                        }
                        else
                        {

                            for (x = case_x; x < case_x + 3; x++)
                            {
                                for (y = case_y; y < case_y + 3; y++)
                                {
                                    if (((estCandidat(grille[x][y], couple.femme) || estCandidat(grille[x][y], couple.mari)) && estCandidat(grille[x][y], couple.femme) != estCandidat(grille[x][y], couple.mari)) || ((estCandidat(grille[x][y], couple.femme) && estCandidat(grille[x][y], couple.mari)) && grille[x][y].nbCandidats != 2))
                                    {
                                        retirerCandidat(&grille[x][y], couple.femme);
                                        retirerCandidat(&grille[x][y], couple.mari);
                                        *progression = true;
                                    }
                                } // if ( (femme || mari) && present(mari) != present(femme) )  ||  (femme && mari && nbcandidat != 2 )
                            }
                        }
                    }
                }
            }
            menage.nb_couple = 0;
        }
    }
}

void paire_cachees(tGrille grille, bool *progression)
{
    int i, j, indice_couple, x, y, ligne, colonne, indice_dans_nbcandidats;
    tMenage menage;
    tStock stock;
    menage.nb_couple = 0;
    tCouple couple;
    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            menage.nb_couple = 0;
            initialiser_stock(stock);

            // parcours
            // parcours toutes les cases de la ligne "ligne"
            for (j = 0; j < TAILLE; j++)
            {
                for (indice_dans_nbcandidats = 0; indice_dans_nbcandidats < grille[ligne][j].nbCandidats; indice_dans_nbcandidats++)
                {
                    // on ajoute 1 au nombre de candidat de valeur grille[i][j].candidats[i]
                    stock[grille[ligne][j].candidats[indice_dans_nbcandidats] - 1]++;
                }

                for (x = 0; x < grille[ligne][j].nbCandidats; x++)
                {
                    for (y = 0; y < grille[ligne][j].nbCandidats; y++)

                    {
                        if (x < y)
                        {
                            couple.femme = grille[ligne][j].candidats[x];
                            couple.mari = grille[ligne][j].candidats[y];

                            if (couple_present(couple, menage) == 0)
                            {

                                ajoute_couple(couple, &menage);
                            }
                            else
                            {
                                if ((j != colonne))
                                {
                                    couple_apparition(couple, &menage);
                                }
                            }
                        }
                    }
                }
            }
            for (indice_couple = 0; indice_couple < menage.nb_couple; indice_couple++)
            {
                if ((menage.stock[indice_couple].nombre_apparition == 2) && stock[menage.stock[indice_couple].femme - 1] == 2 && stock[menage.stock[indice_couple].mari - 1] == 2)
                {
                    // parcours toutes les cases de la ligne "ligne"
                    for (j = 0; j < TAILLE; j++)
                    {
                        if (estCandidat(grille[ligne][j], menage.stock[indice_couple].femme) && estCandidat(grille[ligne][j], menage.stock[indice_couple].mari))

                        {
                            for (indice_dans_nbcandidats = 0; indice_dans_nbcandidats < grille[ligne][j].nbCandidats; indice_dans_nbcandidats++)
                            {

                                if ((grille[ligne][j].candidats[indice_dans_nbcandidats] != menage.stock[indice_couple].femme) && (grille[ligne][j].candidats[indice_dans_nbcandidats] != menage.stock[indice_couple].mari))
                                {
                                    retirerCandidat(&grille[ligne][j], grille[ligne][j].candidats[indice_dans_nbcandidats]);
                                    *progression = true;
                                }
                            }
                        }
                    }
                }

                menage.nb_couple = 0;
                initialiser_stock(stock);

                // parcours
                // parcours toutes les cases de la colonne "colonne"
                for (i = 0; i < TAILLE; i++)
                {
                    for (indice_dans_nbcandidats = 0; indice_dans_nbcandidats < grille[i][colonne].nbCandidats; indice_dans_nbcandidats++)
                    {
                        // on ajoute 1 au nombre de candidat de valeur grille[i][j].candidats[i]
                        stock[grille[i][colonne].candidats[indice_dans_nbcandidats] - 1]++;
                    }

                    for (x = 0; x < grille[i][colonne].nbCandidats; x++)
                    {
                        for (y = 0; y < grille[i][colonne].nbCandidats; y++)

                        {
                            if (x < y)
                            {
                                couple.femme = grille[i][colonne].candidats[x];
                                couple.mari = grille[i][colonne].candidats[y];

                                if (couple_present(couple, menage) == 0)
                                {

                                    ajoute_couple(couple, &menage);
                                }
                                else
                                {
                                    if (i != ligne)
                                    {
                                        couple_apparition(couple, &menage);
                                    }
                                }
                            }
                        }
                    }
                }

                for (indice_couple = 0; indice_couple < menage.nb_couple; indice_couple++)
                {
                    if ((menage.stock[i].nombre_apparition == 2) && stock[menage.stock[indice_couple].femme - 1] == 2 && stock[menage.stock[indice_couple].mari - 1] == 2)
                    {
                        // parcours
                        for (i = 0; i < TAILLE; i++)
                        {
                            if (estCandidat(grille[i][colonne], menage.stock[indice_couple].femme) && estCandidat(grille[i][colonne], menage.stock[indice_couple].mari))

                            {
                                for (indice_dans_nbcandidats = 0; indice_dans_nbcandidats < grille[i][colonne].nbCandidats; indice_dans_nbcandidats++)
                                {

                                    if ((grille[i][colonne].candidats[indice_dans_nbcandidats] != menage.stock[indice_couple].femme) && (grille[i][colonne].candidats[indice_dans_nbcandidats] != menage.stock[indice_couple].mari))
                                    {
                                        retirerCandidat(&grille[i][colonne], grille[i][colonne].candidats[indice_dans_nbcandidats]);
                                        *progression = true;
                                    }
                                }
                            }
                        }
                    }
                }
                menage.nb_couple = 0;
                initialiser_stock(stock);
                // parcours
                // parcours toutes les cases du block avec un case x/y
                int case_x = ligne - (ligne % 3);
                int case_y = colonne - (colonne % 3);
                for (i = case_x; i < case_x + 3; i++)
                {
                    for (j = case_y; j < case_y + 3; j++)
                    {
                        for (indice_dans_nbcandidats = 0; indice_dans_nbcandidats < grille[i][j].nbCandidats; indice_dans_nbcandidats++)
                        {
                            // on ajoute 1 au nombre de candidat de valeur grille[i][j].candidats[i]
                            stock[grille[i][j].candidats[indice_dans_nbcandidats] - 1]++;
                        }

                        for (x = 0; x < grille[i][j].nbCandidats; x++)
                        {
                            for (y = 0; y < grille[i][j].nbCandidats; y++)

                            {
                                if (x < y)
                                {
                                    couple.femme = grille[i][j].candidats[x];
                                    couple.mari = grille[i][j].candidats[y];

                                    if (couple_present(couple, menage) == 0)
                                    {

                                        ajoute_couple(couple, &menage);
                                    }
                                    else
                                    {
                                        if ((i != ligne) && (j != colonne))
                                        {
                                            couple_apparition(couple, &menage);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                for (indice_couple = 0; indice_couple < menage.nb_couple; indice_couple++)
                {
                    // je reconnai la case
                    if ((menage.stock[indice_couple].nombre_apparition == 2) && (stock[menage.stock[indice_couple].femme - 1] == 2 && stock[menage.stock[indice_couple].mari - 1] == 2))
                    {
                        // parcours toutes les cases du block avec un case x/y

                        for (i = case_x; i < case_x + 3; i++)
                        {
                            for (j = case_y; j < case_y + 3; j++)
                            {

                                // je supprime le reste des candidats

                                if (estCandidat(grille[i][j], menage.stock[indice_couple].femme) && estCandidat(grille[i][j], menage.stock[indice_couple].mari))

                                {
                                    for (indice_dans_nbcandidats = 0; indice_dans_nbcandidats < grille[i][j].nbCandidats; indice_dans_nbcandidats++)
                                    {
                                        if ((grille[i][j].candidats[indice_dans_nbcandidats] != menage.stock[indice_couple].femme) && (grille[i][j].candidats[indice_dans_nbcandidats] != menage.stock[indice_couple].mari))
                                        {
                                            retirerCandidat(&grille[i][j], grille[i][j].candidats[indice_dans_nbcandidats]);
                                            *progression = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
