
#include "polynomial.h"


// BASIC NODE FUNTIONs

Node * createNode(void)
{
	Node * newNode = malloc(sizeof(Node));
	
	if (!newNode)
	{
		fprintf(stderr, "Memory Error");
		return NULL;
	}
	
	setNode(newNode);
	
	return newNode;
}

void setNode(Node * newNode)
{
	newNode->coeff = 0;
	newNode->exp = 0;
	newNode->next = NULL;
	
}

void deleteNode(Node * p)
{
	free(p);
}

void updateNode(Node * newNode, const int coeff, const int exp)
{
	newNode->coeff = coeff;
	newNode->exp = exp;
}

//BASIC LINKED LIST FUNCTIONS //
void createList(List * equation )
{
	equation->head = NULL;
	equation->count = 0;
}

void deleteList(List * temp)
{
	Node * n = temp->head, * last;
	while (n != NULL)
	{
		last = n;
		n=n->next;
		deleteNode(last);
	}
}

Node * getHead(List * equation)
{
	return equation->head;
}

void displayList(List * newList)
{	//DISPLAY THE NODES IN A LIST
	Node * eq3 = newList->head;
	for ( int i = 0; i < newList->count; i++)
	{
		printf("Node[%d]: %dx^%d\n", i, eq3->coeff, eq3->exp);
		eq3 = eq3->next;
	}
}


void addNewNode( List * equation, const int coeff, const int exp)
{
	Node * nextTerm = equation->head, *term = createNode();
	//initializeNode(term);
	updateNode(term, coeff, exp);
	
	if ( equation->head == NULL)
	{
		equation->head = term;
		term->next = NULL;
		(equation->count)++;
	}
	else
	{
		while(nextTerm->next != NULL)
		{
			nextTerm = nextTerm->next;
		}
		nextTerm->next = term;
		(equation->count)++;
	}
}

// PROJECT LINKED LIST FUNCTIONS //
char * poly_to_string(const List *n)
{
	Node * p = n->head;
	char * string;
	int multiplier = 5;
	string = (char *)malloc(n->count * multiplier);
	
	if (!string)
	{
		fprintf(stderr, "Memory Error");
		return string;
	}
	int i = 0;
	
	int x = n->count;
		while(p != NULL)
		{ 
			//Check to see if string buffer is full -> realloc and start over
			if ( i == (n->count * multiplier) )
			{
				multiplier *= 2;
				string = realloc(&string, n->count * multiplier);
				fprintf(stderr, "reallocating memory\n");
				p = n->head;
			}
			
			if (p->coeff == 0)
			{
				//SKIP Terms with coefficient = 0;
			} 
			else
			{	
				//Put the operator prior to coefficient
				string[i++] = ( p->coeff < 0) ? '-':'+';
				//Remove '+' at the beginning of string if coeff is positive
				if ( (i == 1) && ( p->coeff > 0) )
					string[--i] = '\0';
					
				//Check if coefficient = 1 OR -1.
				if ( (p->coeff != 1) && (p->coeff != -1) )
				{
					//Use the absolute value of a digit to convert into a character.
					i = i + insertCoEff(string, (p->coeff < 0 ? p->coeff * -1: p->coeff));
				}
				//Plug is variable, unless exp == 0, than no x. 
				string[i++] = (p->exp > 0)?'x':'\0';
				if ( p->exp > 1)
				{
					string[i++] = '^';
					string[i++] = p->exp + '0';
				}
			}
			p=p->next;
		}
	
	return string;
}

int insertCoEff(char * string, int num)
{
	char number[10];
	sprintf(number, "%d", num);
	strcat(string, number);
	
	return strlen(number);
}

void deleteString(char * string)
{
	free(string);
}

void triple(Node * term)
{
	while (term != NULL)
	{
		term->coeff = (term->coeff) * 3;
		term = term->next;
	}
}

void negate(Node * term)
{
	while (term != NULL)
	{
		term->coeff = (term->coeff) * -1;
		term = term->next;
	}
}

void poly_iterate(List *a, void (*transform)(Node *))
{
	Node * current = a->head;
	transform(current);
}

const int compareExp(Node * p, Node * q)
{
	//If no term for p or q.
	if (p == NULL)
	{
		return -1;
	}	
	else if (q == NULL)
	{
		return 1;
	}	
		
	int x = p->exp - q->exp;

	if (x == 0)
	{
		return 0;
	}
	else if (x > 0)
	{
		return 1;
	}
	return -1;
}

List * poly_add(const List *a, const List *b)
{
	int x;
	
	List * newList = malloc(sizeof(List));
	createList(newList);
	Node * eq1 = a->head, * eq2 = b->head, *eq3 = newList->head;
	
	while ( (eq2 != NULL) || (eq1 != NULL) )
	{
		x = compareExp(eq1, eq2);
		if (x == 0)
		{
			//If exponents are equal.
			addNewNode(newList, eq1->coeff + eq2->coeff, eq2->exp);
			eq1 = eq1->next;
			eq2 = eq2->next;
		}
		else if ( x > 0)
		{
			//eq1 exp is greater than eq2
			addNewNode(newList, eq1->coeff, eq1->exp);
			eq1 = eq1->next;
			
		}
		else
		{
			addNewNode(newList, eq2->coeff, eq2->exp);
			eq2 = eq2->next;
		}
		
		eq3 = newList->head->next;
		
	}
	return newList;
	
}

List * poly_sub(const List *eq1, const List *eq2)
{
	List * newList;
	createList(newList);
	
	//Add eq1 to create newList
	newList = poly_add(eq2, newList);
	//Negate the signs in newList and add to eq2 == subtraction
	poly_iterate(newList, negate);
	
	newList = poly_add(eq1, newList);
	
	
	return newList;
}


bool poly_equal(const List *a, const List *b)
{
	Node * eq1 = a->head, *eq2 = b->head;
	
	
	if ((eq1 == NULL) || (eq2 == NULL) )
		return false;
	
	while ( (eq1 != NULL) || (eq2 != NULL) )
	{
		if (eq1->coeff != eq2->coeff)
			return false;
			
		if (eq1->exp != eq2->exp)
			return false;
	}
	
	return true;
}

double poly_evaluate(const List *p, double x)
{
	Node * term = p->head;
	double result, total = 0;
	while (term != NULL)
	{
		result = 1;
		for (int i = 0; i < term->exp; i++)
		{
			result = result*x;
		}
		
		total += (term->coeff) * result;
		term = term->next;
	}
	
	
	
	return total;
}


List * poly_pow(const List * a, unsigned int e)
{
	List * newList = (List *)malloc(sizeof(List));
	newList = poly_add(newList, a);
	Node * term = newList->head;
	while(term != NULL)
	{
		int x = term->coeff;
		for (int i = 0; i < e - 1 ; i++)
		{
			term->coeff *= x;
		}
		term->exp += e;
		
		term = term->next;
	}
	
	return newList;
}




