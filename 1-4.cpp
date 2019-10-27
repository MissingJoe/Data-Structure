#include "Sqlist.h"
#define INSERT_NUM		10	//��ʼ������е�Ԫ������
#define MAX_NUM_PER_LINE 	10		//ÿ����������Ԫ�ظ���

/* ��ʼ�����Ա� */
Status initlist(SqList& l) {
	l.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!l.elem)
		return -2;//�����ڴ�ʧ�ܣ�����-2
	l.length = 0;
	l.listsize = LIST_INIT_SIZE;
	return 0;
}

/* ɾ�����Ա� */
Status DestroyList(SqList* L)
{
	if (L->elem)
		free(L->elem);
	L->length = 0;
	L->listsize = 0;

	return 0;
}

/* ������Ա��ѳ�ʼ�������ͷſռ䣬ֻ������ݣ� */
Status ClearList(SqList* L)
{
	L->length = 0;
	return 0;
}

/*ָ��λ�ò���Ԫ��*/
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

/*��������ʾ���Ա�����*/
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

/*������ǵݼ�������һ��Ԫ��*/
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

/*�������򣨷ǵݼ�����ϲ������µ������*/
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

/*ɾ��ָ��λ��Ԫ��*/
Status delete_loc(SqList& l, int i, ElemType& e) {
	if (i<1 || i>l.length)
		return -1;
	e = l.elem[i - 1];
	for (int j = i; j < l.length; j++)
		l.elem[j - 1] = l.elem[j];
	l.length--;
	return 0;
}

/*ɾ��ֵΪe�ĵ�һ��Ԫ��*/
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

/*ɾ��ֵΪe������Ԫ��*/
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

/*˳����Ԫ������*/
Status converse(SqList& l) {
	ElemType temp;
	for (int i = 0; i < l.length/2; i++) {
		temp = l.elem[i];
		l.elem[i] = l.elem[l.length - 1 - i];
		l.elem[l.length - 1 - i] = temp;
	}
	return 0;
}

/*ɾ��˳��������ж����Ԫ��*/
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

/*��ǰ��*/
Status ListLength(SqList l) {
	return l.length;
}

/*�ж��Ƿ�Ϊ�ձ�*/
Status ListEmpty(SqList l) {
	if (l.length == 0)
		return 1;
	else
		return 0;
}

/*ȡ����λ��i��Ԫ��*/
Status GetElem(SqList l, int i, ElemType& e) {
	if (i<1 || i>l.length)
		return -1;
	e = l.elem[i - 1];
	return 0;
}

/*���Ա�����*/
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

	/*printf("��ʼ�����Ա����\n");
	printf("1.����Ԫ��\n2.ɾ��Ԫ��\n3.")



*/
	initlist(L);

	printf("L �ձ�=%s\n", (ListEmpty(L) == 1) ? "TRUE" : "FALSE");
	printf("L ��=%d\n\n", ListLength(L));

	printf("L ����%d��Ԫ�أ�\n", INSERT_NUM);
	for (i = INSERT_NUM * 2; i > 0; i -= 2)
		insert(L, 1, i);
	traverse(L, MyVisit);//�˴�����MyVisit������

	printf("L �ձ�=%s\n", (ListEmpty(L) == 1) ? "TRUE" : "FALSE");
	printf("L ��=%d\n\n", ListLength(L));

	/* �ֱ�ȡ��1������Լ�С�ڵ�1����������4������µĵ�Ԫ��ֵ��ǰ��ֵ�����ֵ
	   ����ټ�һ����������ֵ */
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
			printf("������ҪȡԪ�ص�λ��[1..%d]��", ListLength(L));
			scanf("%d", &pos);
			break;
		}
		if (GetElem(L, pos, e1) == 0) 
			printf("��%d��Ԫ��=%d\n", pos, e1);
		else
			printf("�޷�ȡ�õ�%d��Ԫ��\n\n", pos);
	}

	printf("\n������Ҫ����Ԫ�ص�ֵ��\n");
	scanf("%d", &e1);
	printf("������Ҫ����Ԫ�ص�λ��\n");
	scanf("%d", &pos);
	if (insert(L, pos, e1) == 0) {
		printf("L ��λ��%dǰ����Ԫ��%d�ɹ�\n", pos, e1);
		printf("L �±�Ϊ��\n");
		traverse(L, MyVisit);
	}
	else
		printf("��%dǰ����Ԫ��%dʧ��\n", pos, e1);
	printf("��L����\n");
	if (converse(L) == 0)
		traverse(L, MyVisit);
	printf("L �����ı�ΪΪ��\n");
	if (sort_sq(L) == 0)
		traverse(L, MyVisit);

	SqList demo;
	initlist(demo);
	printf("demo �ձ�=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("demo ��=%d\n\n", ListLength(demo));

	printf("����%d��Ԫ�أ�\n", e1);
	for (i = 0; i < e1; i++)
		insert(demo, 1, i);
	traverse(demo, MyVisit);

	printf("demo �ձ�=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("demo ��=%d\n\n", ListLength(demo));
	printf("demo ������\n");
	sort_sq(demo);
	traverse(demo, MyVisit);
	printf("���������������ֵ:");
	scanf("%d", &e1);
	if (insert_seq(demo, e1) == 0)
		traverse(demo, MyVisit);
	printf("demo �ձ�=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("demo ��=%d\n\n", ListLength(demo));
	
	SqList demo2;
	initlist(demo2);
	printf("�������ϲ�\n");
	if (union_sqlist(L, demo, demo2) == 0)
		traverse(demo2, MyVisit);
	printf("demo2 �ձ�=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("demo2 ��=%d\n\n", ListLength(demo2));



	printf("demo2 ������ɾ����Ԫ��ֵ��(ɾ��һ��)\n");
	scanf("%d", &e1);
	if (delete_num(demo2, e1) == 0)
		traverse(demo2, MyVisit);
	else
		printf("�����޴�Ԫ��\n");
	printf("�ձ�=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("��=%d\n", ListLength(demo2));

	printf("demo2 ������ɾ����Ԫ��ֵ��(ɾ��ȫ��)\n");
	scanf("%d", &e1);
	if (del_num_all(demo2, e1) == 0)
		traverse(demo2, MyVisit);
	else
		printf("�����޴�Ԫ��\n");
	printf("�ձ�=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("��=%d\n", ListLength(demo2));

	printf("demo2 ɾ�������ظ�Ԫ��\n");
	del_mnum(demo2);
	traverse(demo2, MyVisit);
	printf("�ձ�=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("��=%d\n", ListLength(demo2));


	printf("\n��ձ�L��\n");
	ClearList(&L);
	printf("�ձ�=%s\n", (ListEmpty(L) == 1) ? "TRUE" : "FALSE");
	printf("��=%d\n", ListLength(L));

	printf("\n��ձ�demo��\n");
	ClearList(&demo);
	printf("�ձ�=%s\n", (ListEmpty(demo) == 1) ? "TRUE" : "FALSE");
	printf("��=%d\n", ListLength(demo));

	printf("\n��ձ�demo2��\n");
	ClearList(&demo2);
	printf("�ձ�=%s\n", (ListEmpty(demo2) == 1) ? "TRUE" : "FALSE");
	printf("��=%d\n", ListLength(demo2));

	DestroyList(&L);
	DestroyList(&demo);
	DestroyList(&demo2);
	return 0;
}