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

/*链表逆置*/
Status treave(LinkList* l) {
	LinkList m = (*l)->next, r, q = NULL;
	while (m) {
		r = m->next;
		m->next = q;
		q = m; m = r;
	}
	(*l)->next = q;
	return 0;
}

Status traverse(LinkList l, Status(*visit)(ElemType e)) {
	LinkList p = l->next;
	while (p && (*visit)(p->data) == 0)
		p = p->next;
	printf("\n");
	if (p!=NULL)
		return -1;
	return 0;
}
Status MyVisit(ElemType e)
{
	printf("%d ", e);
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

int listlength(LinkList l) {
	Node* p = l->next;
	int len = 0;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
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

/*显示所有的倍数的结点数值*/
void three(LinkList l) {
	LinkList p = l->next;
	while (p) {
		if (p->data % 3 == 0)
			printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
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
		insert(&test, e, listlength(test)+1);
	}
	treave(&test);
	traverse(test, MyVisit);
	treave(&test);
	three(test);
	destory(&test);
	return 0;
}