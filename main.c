#include <stdio.h>
#include "revision.h"

int main() {
    printf("hello");
    t_tree tree;
    int nb_nodes;
    int strict, degenere, perfect;
    int hauteur = 0;
    tree = CreateEmptyTree();
    AddNode(&tree, 10);
    AddNode(&tree, 6);
    AddNode(&tree, 1);
    AddNode(&tree, 3);
    AddNode(&tree, 15);
    AddNode(&tree, 24);
    AddNode(&tree, 13);


    displayTree(tree.root);
    hauteur = Height(tree.root);
    printf("hauteur: %d\n", hauteur);
    nb_nodes = CountNodes(tree.root);
    printf("Nombre de noeuds: %d\n", nb_nodes);
    Parcours_prof(tree.root);

    strict = IsStrictTree(tree.root);
    if (strict) {
        printf("\nArbre strict\n");
    }
    else printf("\nArbre non strict\n");

    degenere = IsDegenerated(tree.root);
    if (degenere) {
        printf("\nArbre degenere (liste)\n");
    }
    else printf("\nArbre non degenere\n");

    perfect = IsPerfectTree(tree.root);
    if (perfect) {
        printf("\nArbre parfait \n");
    }
    else printf("\nArbre imparfait\n");
    return 0;
}
