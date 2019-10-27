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
	printf("%d ", e);
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

//Status getelem(LinkList l, ElemType& e,int i) {
//	LinkList p = l->next;
//	int loc = 1;
//	while (p && loc < i) {
//		p = p->next;
//		loc++;
//	}
//	if (p == NULL || loc > i)
//		return -1;
//	e = p->data;
//	return 0;
//}

//Status set_num(LinkList& l, int i, ElemType e) {
//	LinkList p = l->next;
//	int loc = 1;
//	while (p && loc < i) {
//		p = p->next;
//		loc++;
//	}
//	if (p == NULL || loc > i)
//		return -1;
//	p->data = e;
//	return 0;
//}


Status union_linklist(LinkList& a, LinkList b, LinkList c) {
	LinkList p = b->next, q = c->next;
	int len = 1;
	while (p && q) {
		if (p->data >= q->data)
		{
			insert(&a, q->data, len++);
			q = q->next;
		}
		else {
			insert(&a, p->data, len++);
			p = p->next;
		}
	}
	while (p) {
		insert(&a, p->data, len++);
		p = p->next;
	}
	while (q) {
		insert(&a, q->data, len++);
		q = q->next;
	}
	return 0;
}

//void swap(LinkList& l, int i, int j) {
//	ElemType e, f;
//	getelem(l, e, i);
//	getelem(l, f, j);
//	set_num(l, i, f);
//	set_num(l, j, e);
//}
//
//void qsort(LinkList list, int left, int right) {
//
//	if (left < right) {
//		int i = left; 
//		int j = i + 1; 
//		ElemType x,e;
//		getelem(list, x, i);
//		while (j <= right) { 
//
//			while (j <= right) {
//				getelem(list, e, j);
//				if (e >= x)
//					j++;
//				else
//					break;
//			}
//			if (j <= right) {
//				i++; 
//				swap(list, i, j); 
//				j++; 
//			}
//
//		}
//		swap(list, left, i);
//		qsort(list, left, i - 1);  
//		qsort(list, i + 1, right);
//	}
//}

/*Á´±íÓÐÐò²åÈë*/
Status minloc(LinkList l, ElemType e) {
	LinkList p = l->next;
	int loc = 1;
	while (p) {
		if (p->data >= e)
			break;	
		loc++; p = p->next;
	}
	insert(&l, e, loc);
	return 0;
}

int main() {
	ElemType e;
	LinkList test1,test2,test3;
	int insert_loc;
	initial(&test1);
	initial(&test2);
	initial(&test3);
	while (1) {
		scanf("%d", &e);
		if (e == 0)
			break;
		else
			minloc(test1, e);
			
	}
	while (1) {
		scanf("%d", &e);
		if (e == 0)
			break;
		else
			minloc(test2, e);
	}
	//qsort(test1, 1, listlength(test1));
	//qsort(test2, 1, listlength(test2));
	union_linklist(test3, test1, test2);
	traverse(test3, MyVisit);
	destory(&test1);
	destory(&test2);
	destory(&test3);
	return 0;
}