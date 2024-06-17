def selectionne_case(pos):
    # on regarde la case actuelle
    l, c, b = cases[pos]
    courant = pos
    cardinal_courant = len(lsets[l] & csets[c] & bsets[b])
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


def sudoku3(grille):
    lsets = [{"1", "2", "3", "4", "5", "6", "7", "8", "9"} for _ in range(9)]
    csets = [{"1", "2", "3", "4", "5", "6", "7", "8", "9"} for _ in range(9)]
    bsets = [{"1", "2", "3", "4", "5", "6", "7", "8", "9"} for _ in range(9)]
    cases = []

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
