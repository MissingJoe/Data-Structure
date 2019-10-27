#include <stdio.h>
#include <stdlib.h> 

#define LIST_INIT_SIZE	100	//��ʼ��С����Ϊ100���ɰ����޸ģ�
#define LISTINCREMENT	10	//���ռ䲻����ÿ������10���ɰ����޸ģ�

typedef int Status;
typedef int ElemType;
typedef struct {
	ElemType* elem; // ָ������Ԫ�صĻ���ַ
	int length; // ���Ա�ĵ�ǰ���� 
	int listsize; //���Ա��������� 
}SqList;


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
	l.elem[i - 1] = e;
	l.length++;
	return 0;
}

/*������*/
Status traverse(SqList l, Status(*visit)(ElemType e)) {
	int i = 1;
	while (i <= l.length && (*visit)(l.elem[i - 1]) == 0)
		i++;
	if (i <= l.length)
		return -1;
	return 0;
}

/*�����Ա���*/
Status sq_len(SqList l) {
	return l.length;
}

/*ɾ��ָ��λ��Ԫ��*/
Status delete_sq(SqList& l, int i, ElemType& e) {
	if (i<1 || i>l.length)
		return -1;
	e = l.elem[i - 1];
	for (int j = i; j < l.length ; j++)
		l.elem[j - 1] = l.elem[j];
	l.length--;
	return 0;
}

/*ɾ����ָ��Ԫ����ͬ��Ԫ��*/
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