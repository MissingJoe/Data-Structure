#include <stdio.h>
#include <stdlib.h> 

typedef int ElemType;
typedef int Status;
typedef  struct  Node {
	ElemType  data;
	Node* next;
}Node, * LinkList;

Status initial(LinkList* l) {
	*l = (Node*)malloc(sizeof(Node));
	if (*l == NULL)
		return -2;
	(*l)->next = NULL;
	return 0;
}

Status traverse(LinkList l, Status(*visit)(ElemType e)) {
	LinkList p = l->next;
	while (p && (*visit)(p->data) == 0)
		p = p->next;
	printf("\n");
	if (p != NULL)
		return -1;
	return 0;
}
Status MyVisit(ElemType e)
{
	if (e != -1)
		printf("%d ", e);
	return 0;
}

/*É¾³ýÖØ¸´ÔªËØ*/
Status del_mnum(LinkList* l) {
	/*LinkList p = (*l)->next, q;
	int* a = (int*)malloc(sizeof(int)*1000000000);
	if (!a)
		return -2;
	for (int i = 0; i < 1000000000; i++)
		a[i] = 0;
	while(p) {
		if (p->next == NULL)
			break;
		q = p->next;
		if (a[q->data-1] == -1)
		{
			a[q->data-1] = 1;
			p = p->next;
		}
		else
		{
			p->next = q->next;
			free(q);
		}
	}
	free(a);*/
	LinkList p = (*l)->next, q;
	while (p) {
		q = p->next;
		while (q) {
			if (q->data == p->data)
				q->data = -1;
			q = q->next;
		}
		p = p->next;
	}
	return 0;
}

Status insert(LinkList* l, ElemType e, int i) {
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
	s->data = e;
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


int main() {
	int num;
	ElemType e;
	LinkList test;
	initial(&test);
	scanf("%d", &num);
	for (int i = 0; i < num; i++)
	{
		scanf("%d", &e);
		insert(&test, e, listlength(test) + 1);
	}
	del_mnum(&test);
	traverse(test,MyVisit);
	destory(&test);
	return 0;
}