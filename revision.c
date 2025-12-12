#include "revision.h"
#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------------------------------
// Fonction interne récursive pour afficher l'arbre horizontalement
void printTree(t_node* node, int depth) {
    if (node == NULL) {
        for (int i = 0; i < depth; i++) printf("    ");
        printf("NULL\n");
        return;
    }

    // Affichage du sous-arbre droit en premier (donc en haut)
    printTree(node->right, depth + 1);

    // Indentation selon la profondeur
    for (int i = 0; i < depth; i++) printf("    ");

    // Affichage du noeud
    printf("%d\n", node->value);

    // Affichage du sous-arbre gauche
    printTree(node->left, depth + 1);
}

// Fonction publique pour l'utilisateur
void displayTree(t_node* root) {
    printf("\n===== ARBRE BINAIRES =====\n\n");
    printTree(root, 0);
    printf("\n===========================\n");
}


//----------------------------------------------------------------------------------------------------------


p_node CreateNode(T val) {
    p_node node = malloc(sizeof(t_node));
    if (!node) {
        printf("Erreur d'allocation.\n");
        exit(EXIT_FAILURE);
    }
    node->value = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

t_tree CreateEmptyTree() {
    t_tree tree;
    tree.root = NULL;
    return tree;
}

void AddNodeRec(p_node *root, T val) {

    if (*root == NULL) {
        *root = CreateNode(val);
        return;
    }
    p_node curr = *root;
    if (val == curr->value) {
        return;
    }
    if (val < curr->value) {
        AddNodeRec(&curr->left, val);
    }
    else {
        AddNodeRec(&curr->right, val);
    }
}

void AddNodeR(t_tree* tree, T val) {
    AddNodeRec(&tree->root, val);
}

void AddNode(t_tree* tree, T val) {
    p_node new_node = CreateNode(val);
    if (!tree->root) {
        tree->root = new_node;
        return;
    }
    p_node curr = tree->root;
    p_node father = NULL;
    while (curr) {
        father = curr;
        if (val == curr->value) {
            return;
        }
        else if (val < curr->value) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    if (val < father->value) {
        father->left = new_node;
        return;
    }
    else {
        father->right = new_node;
        return;
    }
}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int Height(p_node root) {
    if (root == NULL) {
        return -1;
    }

    int left = Height(root->left);
    int right = Height(root->right);

    return 1 + max(left, right);
}

int CountNodes(p_node root) {
    if (root == NULL) {
        return 0;
    }
    p_node left = root->left;
    p_node right = root->right;
    return 1 + CountNodes(left) + CountNodes(right);
}

void Parcours_prof(p_node root) {
    if (root == NULL) {
        return;
    }
    p_node left = root->left;
    p_node right = root->right;

    Parcours_prof(left);
    printf(" %d ", root->value);
    Parcours_prof(right);
}

int IsStrictTree(p_node root) {
    if (root == NULL) {
        return 1;
    }
    p_node left = root->left;
    p_node right = root->right;

    if (left && right || !left && !right) {
        return IsStrictTree(left) && IsStrictTree(right);
    }
    else {
        return 0;
    }
}

/*int ArbreComplet(p_node root) {
    if (root == NULL) {
        return 1;
    }



}*/

int IsDegenerated(p_node root) {
    if (root == NULL) {
        return 1;
    }
    p_node left = root->left;
    p_node right = root->right;
    if (left && right) {
        return 0;
    }
    if (!left && right || left && !right) {
        return IsDegenerated(left) && IsDegenerated(right);
    }
    else return 1;
}

int IsPerfectTree(p_node root) {
    if (root == NULL) {
        return 1;
    }
    p_node left = root->left;
    p_node right = root->right;
    if (Height(left) == Height(right)) {
        return IsPerfectTree(left) && IsPerfectTree(right);
    }
    return 0;
}

