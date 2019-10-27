#include <stdio.h>
#include <stdlib.h> 

#define LIST_INIT_SIZE	100	//初始大小定义为100（可按需修改）
#define LISTINCREMENT	10	//若空间不够，每次增长10（可按需修改）

typedef int Status;
typedef int ElemType;
typedef struct {
	ElemType* elem; // 指向数据元素的基地址
	int length; // 线性表的当前长度 
	int listsize; //线性表的最大容量 
}SqList;

/*初始化线性表*/
Status initlist(SqList& l) {
	l.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!l.elem)
		return -2;
	l.length = 0;
	l.listsize = LIST_INIT_SIZE;
	return 0;
}

/* 删除线性表 */
Status DestroyList(SqList* L)
{
	/* 若未执行 InitList，直接执行本函数，则可能出错，因为指针初始值未定 */
	if (L->elem)
		free(L->elem);
	L->length = 0;
	L->listsize = 0;

	return 0;
}

/*指定位置插入元素*/
Status insert(SqList& l, int i, ElemType e) {
	if (i<1 || i>l.length + 1)
		return -1;
	if (l.length >= l.listsize) {
		ElemType* newbase;
		newbase = (ElemType*)realloc(l.elem, (l.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
			return -2;
		l.elem = newbase;
		l.listsize += LISTINCREMENT;
	}
	ElemType* p, * q;
	p = &l.elem[i - 1];
	for (q = &l.elem[l.length - 1]; q >= p; q--)
		* (q + 1) = *q;
	l.elem[i - 1] = e;
	l.length++;
	return 0;
}

/*删除重复元素*/
Status del_mnum(SqList& l) {
	ElemType e;
	int a[10000] = {0};
	for (int i = 0; i < l.length; i++) {
		if (a[l.elem[i] - 1] == 0)
		{
			printf("%d ", l.elem[i]);
			a[l.elem[i] - 1] = 1;
		}
		else
			continue;
	}
	printf("\n");
	return 0;
}

int main() {
	int num;
	scanf("%d", &num);
	ElemType s;
	SqList test;
	initlist(test);
	for (int i = 0; i < num; i++)
	{
		scanf("%d", &s);
		insert(test, test.length + 1, s);
	}
	del_mnum(test);
	DestroyList(&test);
	return 0;
}