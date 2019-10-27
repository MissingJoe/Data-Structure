#include<iostream>
using namespace std;

typedef int ElemType;//定义数据类型
typedef int Status;
#define MAXSIZE 20
typedef struct{
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE];

int Malloc_SL(SLinkList& list) {
	int i = list[0].cur;
	if (list[0].cur) {
		list[0].cur = list[i].cur;
	}
	return i;
}

//回收空闲分量
void Free_SL(SLinkList& list, int i) {
	list[i].cur = list[0].cur;
	list[0].cur = i;
}

Status IniSpace_SL(SLinkList& l) {
	for (int i = 0; i < MAXSIZE - 1; i++)
		l[i].cur = i + 1;
	l[MAXSIZE - 1].cur = 0;
	return 0;
}

int LocateElem_SL(SLinkList l, ElemType e) {
	int i = l[1].cur;
	while (i && l[i].data != e)
		i = l[i].cur;
	return i;
}

Status difference(SLinkList& a, SLinkList b) {
	int i = b[1].cur, p, k;
	while (i!=0) {
		p = 1; k = a[p].cur;
		while (k != 0 && a[k].data != b[i].data) {
			p = k; k = a[k].cur;
		}
		if (k == 0) {
			int j = Malloc_SL(a);
			a[j].data = b[i].data;
			a[j].cur = 0;
			a[p].cur = i;
		}
		else {
			a[p].cur = a[k].cur;
			Free_SL(a, k);		
		}
		i = b[i].cur;
	}
	return 0;
}

Status Setup_SL(SLinkList& l) {
	ElemType e;
	int i = Malloc_SL(l), j;//链表头结点为地址为1
	while (1) {
		scanf("%d", &e);
		if (e == -1)
			break;
		if (LocateElem_SL(l, e) != 0)
			continue;
		j = Malloc_SL(l);
		if (j == 0)
			return -1;
		l[j].data = e;
		l[i].cur = j;
		i = j;
	}
	l[i].cur = 0;
	return 0;
}

Status traverse(SLinkList l) {
	int i = l[1].cur, linenum;
	printf("\n");
	while (l[i].cur != 0) {
		linenum = 0;
		if (linenum == 10)
			printf("\n");
		printf("%d ", l[i].data);
		linenum++;
		i = l[i].cur;
	}
	if (linenum == 10)
		printf("\n");
	printf("%d ", l[i].data);
	return 0;
}

int main() {
	SLinkList a, b;
	IniSpace_SL(a);
	IniSpace_SL(b);
	Setup_SL(a);
	Setup_SL(b);
	traverse(a);
	traverse(b);
	difference(a, b);
	traverse(a);
	return 0;
}
