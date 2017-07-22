#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
	int coeff;
	int exp;
	struct node* next;
} Node;

typedef struct list {
	Node * head;
	int count;
} List;

//NODE FUNCTIONS
Node * createNode(void);
void setNode(Node * newNode);
void deleteNode(Node * p);
void updateNode(Node * newNode, const int coeff, const int exp);

//LIST FUNCTIONS
void createList(List * equation );
void deleteList(List * temp);
Node * getHead(List * equation);
void addNewNode( List * equation, const int coeff, const int exp);
Node * getNextNode(Node * node);
void displayList(List * a);

char * poly_to_string(const List *p);
void deleteString(char * string);
int insertCoEff(char * string, int num);


List * poly_add(const List *a, const List *b);
List * poly_sub(const List *eq1,const List *eq2);
const int compareExp(Node * p, Node * q);

bool poly_equal(const List *a, const List *b);
double poly_evaluate(const List *p, double x);

void poly_iterate(List *a, void (*transform)(Node *));
void triple(Node * term);
void negate(Node * term);  // Used to flip polynomial signs to assist in doing subtraction

List * poly_pow(const List * a, unsigned int e);
