#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
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
Status MyVisit(ElemType e, ElemType f)
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

double cal(LinkList a, double num) {
	double result = 0;
	LinkList p = a->next;
	while (p) {
		result = result + pow(num, p->data_ei) * p->data_pi;
		p = p->next;
	}
	return result;
}

int main() {
	int length1;
	double num;
	scanf("%d", &length1);
	LinkList test1;
	initial(&test1);
	ElemType e, f;
	for (int i = 0; i < length1; i++) {
		scanf("%d %d", &e, &f);
		insert(&test1, f, e, listlength(test1) + 1);
	}
	scanf("%lf", &num);
	double h = cal(test1, num);
	printf("%.1f\n", h);
	destory(&test1);
	return 0;
}