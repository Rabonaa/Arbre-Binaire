#ifndef REV_TREE_REVISION_H
#define REV_TREE_REVISION_H
#define T int

typedef struct node {
    T value;
    struct node *left;
    struct node *right;
}t_node, *p_node;

typedef struct tree {
    p_node root;
}t_tree;

typedef struct c_queue {
    p_node node;
    struct c_queue *next;
}c_queue;

typedef struct l_queue {
    c_queue *head;
    c_queue *tail;
}t_queue;



p_node CreateNode(T);
t_tree CreateEmptyTree();
void AddNode(t_tree *, T);
void AddNodeRec(p_node *, T );
void AddNodeR(t_tree *, T );

void printTree(t_node *, int );
void displayTree(t_node *);
int Height(p_node);
int CountNodes(p_node);
void Parcours_prof(p_node);
int IsStrictTree(p_node);
//int ArbreComplet(p_node);
int IsDegenerated(p_node);
int IsPerfectTree(p_node);

int IsEmptyQueue(t_queue);
c_queue* CreateCqueue();
t_queue EmptyQueue();
void Enqueue(t_queue *, p_node);
p_node Dequeue(t_queue *);
void Parcours_Larg(t_tree );

#endif