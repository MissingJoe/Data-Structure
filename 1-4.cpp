#include "Sqlist.h"
#define INSERT_NUM		10	//初始插入表中的元素数量
#define MAX_NUM_PER_LINE 	10		//每行最多输出的元素个数

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

/* 清除线性表（已初始化，不释放空间，只清除内容） */
Status ClearList(SqList* L)
{
	L->length = 0;
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
	*p = e;

	l.length++;
	return 0;
}

/*遍历并显示线性表内容*/
Status traverse(SqList l, Status(*visit)(ElemType e)) {
	int i = 1;
	while (i <= l.length && (*visit)(l.elem[i - 1]) == 0)
		i++;
	if (i <= l.length)
		return -1;
	printf("\n");
	return 0;
}
Status MyVisit(ElemType e)
{
	printf("%d ", e);
	return 0;
}

/*有序表（非递减）插入一个元素*/
Status insert_seq(SqList& l, ElemType e) {
	bool a = false;
	for (int i = 0; i < l.length; i++)
		if (l.elem[i] >= e)
		{
			insert(l, i+1, e);
			a = true;
			break;
		}
	if (a == false)
		insert(l, l.length+1, e);
	return 0;
}

/*两个有序（非递减）表合并生成新的有序表*/
Status union_sqlist(SqList a, SqList b,SqList &c) {
	int i = 0, j = 0, k = 1;
	while (i < a.length && j < b.length) {
		if (a.elem[i] >= b.elem[j]) {
			insert(c, k++, b.elem[j]);
			j++;
		}
		else{
			insert(c, k++, a.elem[i]);
			i++;
		}
	}
	while (i < a.length)
		insert(c, k++, a.elem[i++]);
	while (j < b.length)
		insert(c, k++, b.elem[j++]);
	return 0;
}

/*删除指定位置元素*/
Status delete_loc(SqList& l, int i, ElemType& e) {
	if (i<1 || i>l.length)
		return -1;
	e = l.elem[i - 1];
	for (int j = i; j < l.length; j++)
		l.elem[j - 1] = l.elem[j];
	l.length--;
	return 0;
}

/*删除值为e的第一个元素*/
Status delete_num(SqList& l, ElemType e) {
	ElemType a;
	int j;
	for (j = 0; j < l.length; j++)
		if (l.elem[j] == e)
		{
			delete_loc(l, j + 1, a);
			break;
		}
	if (j == l.length)
		return -1;
	return 0;
}

/*删除值为e的所有元素*/
Status del_num_all(SqList& l, ElemType e) {
	ElemType a;
	bool b = false;
	for (int i = 0; i < l.length; i++)
		if (l.elem[i] == e)
		{
			delete_loc(l, i + 1, a);
			i--;
			b = true;
		}
	if (b == false)
		return -1;
	return 0;
}

/*顺序表的元素逆置*/
Status converse(SqList& l) {
	ElemType temp;
	for (int i = 0; i < l.length/2; i++) {
		temp = l.elem[i];
		l.elem[i] = l.elem[l.length - 1 - i];
		l.elem[l.length - 1 - i] = temp;
	}
	return 0;
}

/*删除顺序表中所有多余的元素*/
Status del_mnum(SqList& l) {
	ElemType e;
	for (int i = 0; i < l.length; i++)
		for (int j = i + 1; j < l.length; j++)
			if (l.elem[j] == l.elem[i])
			{
				delete_loc(l, j + 1, e);
				j--;
			}
	return 0;
}

/*求当前表长*/
Status ListLength(SqList l) {
	return l.length;
}

/*判断是否为空表*/
Status ListEmpty(SqList l) {
	if (l.length == 0)
		return 1;
	else
		return 0;
}

/*取表中位置i的元素*/
Status GetElem(SqList l, int i, ElemType& e) {
	if (i<1 || i>l.length)
		return -1;
	e = l.elem[i - 1];
	return 0;
}

/*线性表排序*/
Status sort_sq(SqList& l) {
	ElemType temp;
	for(int i=0;i<l.length;i++)
		for(int j=i;j<l.length;j++)
			if (l.elem[i] > l.elem[j]) {
				temp = l.elem[i];
				l.elem[i] = l.elem[j];
				l.elem[j] = temp;
			}
	return 0;
}

int main() {
	SqList   L;
	ElemType e1;
	int      i, pos;

	/*printf("初始化线性表完成\n");
	printf("1.插入元素\n2.删除元素\n3.")



*/
	initlist(L);

	printf("L 空表=%s\n", (ListEmpty(L) == 1) ? "TRUE" : "FALSE");
	printf("L 表长=%d\n\n", ListLength(L));

	printf("L 插入%d个元素：\n", INSERT_NUM);
	for (i = INSERT_NUM * 2; i > 0; i -= 2)
		insert(L, 1, i);
	traverse(L, MyVisit);//此处传入MyVisit函数名

	printf("L 空表=%s\n", (ListEmpty(L) == 1) ? "TRUE" : "FALSE");
	printf("L 表长=%d\n\n", ListLength(L));

	/* 分别取第1、最后、以及小于第1、大于最后的4种情况下的的元素值、前驱值、后继值
	   最后再加一个任意输入值 */
	for (i = 0; i < 5; i++) {
		int pos;
		switch (i) {
		case 0:
			pos = 1;
			break;
		case 1:
			pos = ListLength(L);
			break;
		case 2:
			pos = -1;
			break;
		case 3:
			pos = ListLength(L) + 1;
			break;
		case 4:
			printf("请输入要取元素的位序[1..%d]：", ListLength(L));
			scanf("%d", &pos);
			break;
		}
		if (GetElem(L, pos, e1) == 0) 
			printf("第%d个元素=%d\n", pos, e1);
		else
			printf("无法取得第%d个元素\n\n", pos);
	}

	printf("\n请输入要插入元素的值：\n");
	scanf("%d", &e1);
	printf("请输入要插入元素的位序：\n");
	scanf("%d", &pos);
	if (insert(L, pos, e1) == 0) {
		printf("L 在位置%d前插入元素%d成功\n", pos, e1);
		printf("L 新表为：\n");
		traverse(L, MyVisit);
	}
	else
		printf("在%d前插入元素%d失败\n", pos, e1);
	printf("表L逆置\n");
	if (converse(L) == 0)
		traverse(L, MyVisit);
	printf("L 排序后的表为为：\n");
	if (sort_sq(L) == 0)
		traverse(L, MyVisit);

	SqList demo;
	initlist(demo);
	printf("demo 空表=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("demo 表长=%d\n\n", ListLength(demo));

	printf("插入%d个元素：\n", e1);
	for (i = 0; i < e1; i++)
		insert(demo, 1, i);
	traverse(demo, MyVisit);

	printf("demo 空表=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("demo 表长=%d\n\n", ListLength(demo));
	printf("demo 表排序\n");
	sort_sq(demo);
	traverse(demo, MyVisit);
	printf("请输入有序插入数值:");
	scanf("%d", &e1);
	if (insert_seq(demo, e1) == 0)
		traverse(demo, MyVisit);
	printf("demo 空表=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("demo 表长=%d\n\n", ListLength(demo));
	
	SqList demo2;
	initlist(demo2);
	printf("两有序表合并\n");
	if (union_sqlist(L, demo, demo2) == 0)
		traverse(demo2, MyVisit);
	printf("demo2 空表=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("demo2 表长=%d\n\n", ListLength(demo2));



	printf("demo2 请输入删除的元素值：(删除一个)\n");
	scanf("%d", &e1);
	if (delete_num(demo2, e1) == 0)
		traverse(demo2, MyVisit);
	else
		printf("表中无此元素\n");
	printf("空表=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("表长=%d\n", ListLength(demo2));

	printf("demo2 请输入删除的元素值：(删除全部)\n");
	scanf("%d", &e1);
	if (del_num_all(demo2, e1) == 0)
		traverse(demo2, MyVisit);
	else
		printf("表中无此元素\n");
	printf("空表=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("表长=%d\n", ListLength(demo2));

	printf("demo2 删除所有重复元素\n");
	del_mnum(demo2);
	traverse(demo2, MyVisit);
	printf("空表=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("表长=%d\n", ListLength(demo2));


	printf("\n清空表L：\n");
	ClearList(&L);
	printf("空表=%s\n", (ListEmpty(L) == 1) ? "TRUE" : "FALSE");
	printf("表长=%d\n", ListLength(L));

	printf("\n清空表demo：\n");
	ClearList(&demo);
	printf("空表=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("表长=%d\n", ListLength(demo));

	printf("\n清空表demo2：\n");
	ClearList(&demo2);
	printf("空表=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("表长=%d\n", ListLength(demo2));

	DestroyList(&L);
	DestroyList(&demo);
	DestroyList(&demo2);
	return 0;
}