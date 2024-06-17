#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define N 3
#define TAILLE (N * N)

typedef struct
{
    int valeur;
    bool candidats[TAILLE];
    int nbCandidats;
} tCase2;
typedef tCase2 tGrille[TAILLE][TAILLE];



bool technique_hiddenPair(tGrille grid, int row, int column)
{
    bool progress = false;
    int const BLOCK_ROW = blockIndex(row);
    int const BLOCK_COL = blockIndex(column);

#define PAIR_SIZE 2

    // déclaration des variables
    int candidate1;
    int candidate2;
    int appearanceCount = 0;

    tTile *tilesContainingPair[PAIR_SIZE];

    // identifie les candidats
    for (int id1 = 1; appearanceCount < PAIR_SIZE && id1 < grid[row][column].candidateCount + 1; id1++) {
        candidate1 = tile_candidateAt(&grid[row][column], id1);
        for (int id2 = 1; appearanceCount < PAIR_SIZE && id2 < grid[row][column].candidateCount + 1; id2++) {
            candidate2 = tile_candidateAt(&grid[row][column], id2);

            appearanceCount = 0;
            if (candidate1 != candidate2) {
                // recherche des paires cachés
                for (int r = BLOCK_ROW; appearanceCount < PAIR_SIZE && r < BLOCK_ROW + N; r++) {
                    for (int c = BLOCK_COL; appearanceCount < PAIR_SIZE && c < BLOCK_COL + N; c++) {
                        if (tile_hasCandidate(&grid[r][c], candidate1) && tile_hasCandidate(&grid[r][c], candidate2)) {
                            tilesContainingPair[appearanceCount++] = &grid[r][c];
                        }
                    }
                }
                // rechercher les candidats tout seuls qui invalideraient la paire
                for (int r = BLOCK_ROW; appearanceCount > 0 && r < BLOCK_ROW + N; r++) {
                    for (int c = BLOCK_COL; appearanceCount > 0 && c < BLOCK_COL + N; c++) {
                        if ((tile_hasCandidate(&grid[r][c], candidate1) ^ tile_hasCandidate(&grid[r][c], candidate2)) || grid[r][c].candidateCount != PAIR_SIZE) {
                            appearanceCount = 0;
                        }
                    }
                }
            }
        }
    }

    // supprime les candidats si le nombre d'apparition est de 2
    if (appearanceCount == PAIR_SIZE) {
        for (int i = 0; i < PAIR_SIZE; i++) {
            for (int candidate = 1; candidate <= SIZE; candidate++) {
                if (candidate != candidate1 && candidate != candidate2) {
                    progress |= tile_removeCandidate(tilesContainingPair[i], candidate);
                }
            }
        }
    }

    return progress;

#undef PAIR_SIZE
}