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

/*void RemoveNode(t_tree *tree, T val) {
    if (tree->root == NULL) {
        return;
    }
    if (val == tree->root->value) {
        p_node left = tree->root->left;
        p_node right = tree->root->right;
        left->right = right;
        free(tree->root);
        tree->root = left;
    }
    p_node curr = tree->root;
    p_node father = NULL;
    while (curr) {
        father = curr;
        if (val < curr->value) {
            curr = curr->left;
        }
        else if (val > curr->value) {
            curr = curr->right;
        }
        if (val == curr->value) {
            if (father->value < curr->value) {
                father->left = curr->left;
                curr->left->right = curr->right;
            }
            else {
                father->right = curr->left;
                curr->left->right = curr->right;
            }
        }
    }
}*/



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

int IsEmptyQueue(t_queue list) {
    if (!list.head) {
        return 1;
    }
    return 0;
}

c_queue* CreateCqueue() {
    c_queue *cell = malloc(sizeof(c_queue));
    cell->node = NULL;
    cell->next = NULL;
    return cell;
}

t_queue EmptyQueue() {
    t_queue list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

void Enqueue(t_queue *list, p_node node){
    c_queue *new_cell = CreateCqueue();
    new_cell->node = node;
    if (list->head == NULL) {
        list->head = new_cell;
        list->tail = list->head;
    }
    else {
        list->tail->next = new_cell;
        list->tail = new_cell;
    }
}

p_node Dequeue(t_queue *list) {
    if (list->head == NULL) {
        return NULL;
    }
    p_node node = list->head->node;
    c_queue *curr = list->head;
    list->head = curr->next;
    free(curr);
    if (list->head == NULL){
        list->tail = NULL;
    }
    return node;
}

void Parcours_Larg(t_tree tree) {
    if (tree.root == NULL) {
        return;
    }
    p_node node = tree.root;
    t_queue list = EmptyQueue();
    Enqueue(&list, node);
    while (!IsEmptyQueue(list)) {
        node = Dequeue(&list);
        printf(" %d ", node->value);
        if (node->left){
            Enqueue(&list, node->left);
        }
        if (node->right) {
            Enqueue(&list, node->right);
        }
    }
}

p_node SearchValue(t_tree tree, T val) {
    if (tree.root == NULL) {
        return NULL;
    }
    p_node curr = tree.root;
    while (curr) {
        if (val == curr->value) {
            return curr;
        }
        if (val < curr->value) {
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    return NULL;
}

p_node RightRotation(p_node root) {
    if (root == NULL) {
        return NULL;
    }
    p_node pivot = root->left;
    root->left = pivot->right;
    pivot->right = root;
    return pivot;
}

p_node LeftRotation(p_node root) {
    if (root == NULL) {
        return NULL;
    }
    p_node pivot = root->right;
    root->right = pivot->left;
    pivot->left = root;
    return pivot;
}

