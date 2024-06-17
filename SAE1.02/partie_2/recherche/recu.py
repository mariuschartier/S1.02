grille = """\
.1......6
.......2.
..6......
.9.2.....
.........
1....9...
...3.....
.4..8....
7......1."""


def prepare_grille(grille):
    return [list(ligne) for ligne in grille.split()]


def affiche_grille(grille):
    for l in range(9):
        for c in range(9):
            print(grille[l][c], end=" ")
            if c == 2 or c == 5:
                print(" ", end=" ")
        if l == 2 or l == 5:
            print("")
        print("")


def sudoku3(grille):
    lsets = [{"1", "2", "3", "4", "5", "6", "7", "8", "9"} for _ in range(9)]
    csets = [{"1", "2", "3", "4", "5", "6", "7", "8", "9"} for _ in range(9)]
    bsets = [{"1", "2", "3", "4", "5", "6", "7", "8", "9"} for _ in range(9)]
    cases = []

    def selectionne_case(pos):
        # on regarde la case actuelle
        l, c, b = cases[pos]
        courant = pos
        cardinal_courant = len(lsets[l] & csets[c] & bsets[b])
        print(cardinal_courant)
        for i in range(pos + 1, len(cases)):
            l, c, b = cases[i]
            cardinal_i = len(lsets[l] & csets[c] & bsets[b])
            if cardinal_i < cardinal_courant:
                courant = i
                cardinal_courant = cardinal_i
        if courant != pos:
            # on échange les cases
            cases[courant], cases[pos] = cases[pos], cases[courant]

    def essaye_case(pos):
        if pos == len(cases):
            return True
        selectionne_case(pos)
        l, c, b = cases[pos]
        lset = lsets[l]
        cset = csets[c]
        bset = bsets[b]
        for v in lset & cset & bset:
            lset.remove(v)
            cset.remove(v)
            bset.remove(v)
            if essaye_case(pos + 1):
                grille[l][c] = v
                return True
            lset.add(v)
            cset.add(v)
            bset.add(v)
        return False
    # préparation
    for l in range(9):
        for c in range(9):
            b = (c // 3) + 3 * (l // 3)
            # print(grille)
            # print("c : ", c, " l ", l)
            if grille[l][c] == ".":
                cases.append((l, c, b))
            else:
                lsets[l].remove(grille[l][c])
                csets[c].remove(grille[l][c])
                bsets[b].remove(grille[l][c])
    # résolution
    return essaye_case(0)


# def essaye(solveur, grille):
#     return timeit.timeit("{0}(prepare_grille({1}))".format(solveur, grille),
#                          "from __main__ import {0}, {1}, prepare_grille".format(
#                              solveur, grille),
#                          number=1000)

grille = prepare_grille(grille)

sudoku3(grille)
print(grille)
