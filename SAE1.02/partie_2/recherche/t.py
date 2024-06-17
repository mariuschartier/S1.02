grille = """\
.1......6
....9..2.
.56.18.7.
89.2....7
.........
1....9.32
.8.34.76.
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


def sudoku2(grille):
    lsets = [{"1", "2", "3", "4", "5", "6", "7", "8", "9"} for _ in range(9)]
    csets = [{"1", "2", "3", "4", "5", "6", "7", "8", "9"} for _ in range(9)]
    bsets = [{"1", "2", "3", "4", "5", "6", "7", "8", "9"} for _ in range(9)]
    cases = []

    def essaye_case(pos):
        if pos == len(cases):
            return True
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
            if grille[l][c] == ".":
                cases.append((l, c, b))
            else:
                lsets[l].remove(grille[l][c])
                csets[c].remove(grille[l][c])
                bsets[b].remove(grille[l][c])
    # résolution
    return essaye_case(0)


grille = prepare_grille(grille)
print(grille)
sudoku2(grille)
print(grille)
