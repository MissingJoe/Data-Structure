#include <stdio.h>
#include <stdlib.h> 

typedef int ElemType;
typedef int Status;
typedef  struct  Node {
	ElemType  data_pi;//µ×Êý
	ElemType data_ei;//Ö¸Êý
	Node* next;
}Node, * LinkList;

Status initial(LinkList* l) {
	*l = (Node*)malloc(sizeof(Node));
	if (*l == NULL)
		return -2;
	(*l)->next = NULL;
	return 0;
}

Status traverse(LinkList l, Status(*visit)(ElemType e, ElemType f)) {
	LinkList p = l->next;
	while (p && (*visit)(p->data_pi, p->data_ei) == 0)
		p = p->next;
	printf("\n");
	if (p != NULL)
		return -1;
	return 0;
}
Status MyVisit(ElemType e,ElemType f)
{
	printf("%d %d\n", e, f);
	return 0;
}

Status insert(LinkList* l, ElemType ei, ElemType pi, int i) {
	int j = 0;
	Node* p = *l;
	while (p && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (p == NULL || j > i - 1)
		return -1;
	Node* s = (Node*)malloc(sizeof(Node));
	if (s == NULL)
		return -2;
	s->data_pi = pi;
	s->data_ei = ei;
	s->next = p->next;
	p->next = s;
	return 0;
}

Status destory(LinkList* l) {
	LinkList p = *l, q;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	return 0;
}

int listlength(LinkList l) {
	Node* p = l->next;
	int len = 0;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

void add(LinkList& a, LinkList b, LinkList c) {
	LinkList q, p, r;
	int loc=1;
	p = b->next; q = c->next;
	while (p&&q) {
		if (p->data_ei == q->data_ei)
		{
			if ((p->data_pi + q->data_pi) != 0)
				insert(&a, p->data_ei, (p->data_pi + q->data_pi), loc++);
			p = p->next; q = q->next;	
		}
		else
		{
			if (p->data_ei < q->data_ei)
			{
				insert(&a, p->data_ei, p->data_pi, loc++);
				p = p->next;
			}
			else
			{
				insert(&a, q->data_ei, q->data_pi, loc++);
				q = q->next;
			}
		}
	}
	while (p) {
		insert(&a, p->data_ei, p->data_pi, loc++);
		p = p->next;
	}
	while (q) {
		insert(&a, q->data_ei, q->data_pi, loc++);
		q = q->next;
	}
}


int main() {
	int length1, length2;
	scanf("%d", &length1);
	LinkList test1, test2;
	initial(&test1);
	initial(&test2);
	ElemType e, f;
	for (int i = 0; i < length1; i++) {
		scanf("%d %d", &e, &f);
		insert(&test1, f, e, listlength(test1) + 1);
	}

	scanf("%d", &length2);
	for (int i = 0; i < length2; i++) {
		scanf("%d %d", &e, &f);
		insert(&test2, f, e, listlength(test2) + 1);
	}
	
	LinkList test3;
	initial(&test3);
	add(test3, test1, test2);
	traverse(test3, MyVisit);
	destory(&test1);
	destory(&test2);
	destory(&test3);
	return 0;
}