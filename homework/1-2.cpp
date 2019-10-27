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


/* 初始化线性表 */
Status initlist(SqList& l) {
	l.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!l.elem)
		return -2;//申请内存失败，返回-2
	l.length = 0;
	l.listsize = LIST_INIT_SIZE;
	return 0;
}

/* 删除线性表 */
Status DestroyList(SqList* L)
{
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

/*遍历表*/
Status traverse(SqList l, Status(*visit)(ElemType e)) {
	int i = 1;
	while (i <= l.length && (*visit)(l.elem[i - 1]) == 0)
		i++;
	if (i <= l.length)
		return -1;
	return 0;
}

/*求线性表长度*/
Status sq_len(SqList l) {
	return l.length;
}

/*删除指定位置元素*/
Status delete_sq(SqList& l, int i, ElemType& e) {
	if (i<1 || i>l.length)
		return -1;
	e = l.elem[i - 1];
	for (int j = i; j < l.length ; j++)
		l.elem[j - 1] = l.elem[j];
	l.length--;
	return 0;
}

/*删除与指定元素相同的元素*/
Status del_num(SqList& l, ElemType e) {
	ElemType a;
	bool b = false;
	for (int i = 0; i < l.length; i++)
		if (l.elem[i] == e)
		{
			b = true;
			break;
		}
	if (b == false)
	{
		printf("-1\n");
		return 0;
	}
	for (int i = 0; i < l.length; i++)
	{
		if (l.elem[i] == e)
		{
			//delete_sq(l, i+1, a);
			//i--;
			b = true;
			continue;
		}
		else
			printf("%d ",l.elem[i]);
	}
	printf("\n");
	return 0;
}

Status MyVisit(ElemType e)
{
	printf("%d ", e);
	return 0;
}

int main()
{
	int num, del_number;
	scanf("%d", &num);
	ElemType s;
	SqList test;
	initlist(test);
	for (int i = 0; i < num; i++)
	{
		scanf("%d", &s);
		insert(test, test.length+1, s);
	}
	scanf("%d", &del_number);
	del_num(test, del_number);
	DestroyList(&test);
	return 0;
}