#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define INSERT_NUM 10

typedef int ElemType;
typedef int Status;
typedef  struct  Node {
	ElemType  data;    
	Node* next;             
}Node, * LinkList;

Status initial(LinkList *l) {
	*l = (Node*)malloc(sizeof(Node));
	if (*l == NULL)
		return -2;
	(*l)->next = NULL;
	return 0;
}

int listlength(LinkList l) {
	Node* p = l->next;
	int len = 0;
	while(p){
		if (p->data == -1)
		{
			p = p->next;
			continue;
		}
		len++;
		p = p->next;
	}
	return len;
}

Status insert(LinkList* l, ElemType e, int i) {
	int j = 0;
	Node *p = *l;
	while (p && j < i-1)
	{
		p = p->next;
		j++;
	}
	if (p == NULL || j > i-1)
		return -1;
	Node* s = (Node*)malloc(sizeof(Node));
	if (s == NULL)
		return -2;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 0;
}

Status del(LinkList* l, int i) {
	int j = 0;
	LinkList p = *l;
	while (p && j < i-1 )
	{
		p = p->next;
		j++;
	}
	if (p->next == NULL || j > i-1||p==NULL)
		return -1;
	Node* q = p->next;
	p->next = q->next;
	free(q);
	return 0;
}

Status search(LinkList l, ElemType e,int &i) {
	Node* p = l->next;
	int loc = 1;
	while (p) {
		if (p->data == e)
			break;
		loc++;
		p = p->next;
	}
	if (p == NULL)
		return -1;
	i = loc;
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

Status destory(LinkList* l) {
	LinkList p = *l, q;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	return 0;
}

Status set_num(LinkList& l, int i, ElemType e) {
	LinkList p = l->next;
	int loc = 1;
	while (p && loc < i) {
		p = p->next;
		loc++;
	}
	if (p == NULL || loc > i)
		return -1;
	p->data = e;
	return 0;
}

Status getelem(LinkList l, ElemType& e, int i) {
	LinkList p = l->next;
	int loc = 1;
	while (p && loc < i) {
		p = p->next;
		loc++;
	}
	if (p == NULL || loc > i)
		return -1;
	e = p->data;
	return 0;
}

void swap(LinkList& l, int i, int j) {
	ElemType e, f;
	getelem(l, e, i);
	getelem(l, f, j);
	set_num(l, i, f);
	set_num(l, j, e);
}

void qsort(LinkList *list, int left, int right) {

	if (left < right) {
		int i = left; 
		int j = i + 1; 
		ElemType x,e;
		getelem(*list, x, i);
		while (j <= right) { 

			while (j <= right) {
				getelem(*list, e, j);
				if (e >= x)
					j++;
				else
					break;
			}
			if (j <= right) {
				i++; 
				swap(*list, i, j); 
				j++; 
			}

		}
		swap(*list, left, i);
		qsort(list, left, i - 1);  
		qsort(list, i + 1, right);
	}
}

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

Status ListEmpty(LinkList l)
{
	LinkList p = l->next;
	if (!p)
		return 1;
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

/*删除重复元素*/
Status del_mnum(LinkList* l) {
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


int main() {
	/*int num;
	ElemType e;
	LinkList test;
	initial(&test);
	scanf("%d", &num);
	for (int i = 0; i < num; i++)
	{
		scanf("%d", &e);
		insert(&test, e, 1);
	}
	int insert_loc, insert_num, del_loc, search_num;
	scanf("%d %d", &insert_loc, &insert_num);
	scanf("%d", &del_loc);
	scanf("%d", &search_num);
	traverse(test, MyVisit);

	if (insert(&test, insert_num, insert_loc) == -1)
		printf("-1\n");
	else
		traverse(test, MyVisit);

	if(del(&test,del_loc)==-1)
		printf("-1\n");
	else
		traverse(test, MyVisit);

	int search_result;
	if (search(test, search_num, search_result) == -1)
		printf("-1\n");
	else
		printf("%d\n", search_result);
	printf("%d\n", listlength(test));
	destory(&test);
	return 0;*/

	LinkList L;
	ElemType e1;
	int i, pos;
	initial(&L);
	printf("L 空表=%s\n", (ListEmpty(L) == 1) ? "TRUE" : "FALSE");
	printf("L 表长=%d\n\n", listlength(L));
	printf("L 插入%d个元素：\n", INSERT_NUM);
	for (i = INSERT_NUM * 2; i > 0; i -= 2)
		insert(&L, i, 1);
	traverse(L, MyVisit);//此处传入MyVisit函数名
	printf("L 空表=%s\n", (ListEmpty(L) == 1) ? "TRUE" : "FALSE");
	printf("L 表长=%d\n\n", listlength(L));
	/* 分别取第1、最后、以及小于第1、大于最后的4种情况下的的元素值、前驱值、后继值
	最后再加一个任意输入值 */
	for (i = 0; i < 5; i++) {
		int pos;
		switch (i) {
		case 0:
			pos = 1;
			break;
		case 1:
			pos = listlength(L);
			break;
		case 2:
			pos = -1;
			break;
		case 3:
			pos = listlength(L) + 1;
			break;
		case 4:
			printf("请输入要取元素的位序[1..%d]：", listlength(L));
			scanf("%d", &pos);
			break;
		}
		if (getelem(L,e1, pos) == 0)
			printf("第%d个元素=%d\n", pos, e1);
		else
			printf("无法取得第%d个元素\n\n", pos);
	}
	printf("\n请输入要插入元素的值：\n");
	scanf("%d", &e1);
	printf("请输入要插入元素的位序：\n");
	scanf("%d", &pos);
	if (insert(&L, e1, pos) == 0) {
		printf("L 在%d前插入元素%d成功\n", pos, e1);
		printf("L 新表为：\n");
		traverse(L, MyVisit);
	}
	else
		printf("在%d前插入元素%d失败\n", pos, e1);
	printf("表L逆置\n");
	if (treave(&L) == 0)
		traverse(L, MyVisit);
	qsort(&L, 1, listlength(L));
	printf("表排序:\n");
	traverse(L, MyVisit);
	printf("L 空表=%s\n", (ListEmpty(L) == 1) ? "TRUE" : "FALSE");
	printf("L 表长=%d\n\n", listlength(L));

	LinkList demo;
	initial(&demo);
	printf("demo 空表=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("demo 表长=%d\n\n", listlength(demo));
	printf("插入%d个元素：\n", e1);
	for (i = 0; i < e1; i++)
		insert(&demo, i, 1);
	traverse(demo, MyVisit);
	printf("demo 空表=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("demo 表长=%d\n\n", listlength(demo));
	qsort(&demo, 1, listlength(demo));
	printf("表排序:\n");
	traverse(demo, MyVisit);
	printf("demo 空表=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("demo 表长=%d\n\n", listlength(demo));

	LinkList demo2;
	initial(&demo2);
	printf("两有序表合并\n");
	if (union_linklist(demo2, L, demo) == 0)
		traverse(demo2, MyVisit);
	printf("demo2 空表=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("demo2 表长=%d\n\n", listlength(demo2));
	printf("demo2 请输入删除的元素位置：(删除一个)\n");
	scanf("%d", &e1);
	if (del(&demo2, e1) == 0)
		traverse(demo2, MyVisit);
	else
		printf("位置不合法\n");
	printf("空表=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("表长=%d\n", listlength(demo2));
	printf("demo2 删除所有重复元素\n");
	del_mnum(&demo2);
	traverse(demo2, MyVisit);
	printf("空表=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("表长=%d\n", listlength(demo2));
	destory(&L);
	destory(&demo);
	destory(&demo2);
	return 0;
}