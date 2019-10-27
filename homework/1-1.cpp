#include <stdio.h>
#include <stdlib.h> 
#include "string.h"
#define LIST_INIT_SIZE	100	//��ʼ��С����Ϊ100���ɰ����޸ģ�
#define LISTINCREMENT	10	//���ռ䲻����ÿ������10���ɰ����޸ģ�

typedef struct {
	char no[8]; //8 λѧ��
	char name[20]; // ����
	double score; // �ɼ�
}Student;
typedef Student ElemType;
typedef int Status;
typedef struct {
	ElemType* elem; // ָ������Ԫ�صĻ���ַ
	int length; // ���Ա�ĵ�ǰ���� 
	int listsize; //���Ա��������� 
}SqList;

/*��ʼ�����Ա�*/
Status initlist(SqList& l) {
	l.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!l.elem)
		return -2;
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

/*��ָ��λ�ò���Ԫ��*/
Status insert(SqList& l, int i, ElemType e) {
	if (i<1 || i>l.length+1)
		return -1;
	if (l.length >= l.listsize) {
		ElemType* newbase;
		newbase = (ElemType*)realloc(l.elem, (l.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
			return -2;
		l.elem = newbase;
		l.listsize += LISTINCREMENT;
	}
	for (int j = l.length - 1; j >= i - 1; j--)
		//l.elem[j + 1] = l.elem[j];
		memcpy(&(l.elem[j + 1]), &(l.elem[j]), sizeof(ElemType));
	//e = l.elem[i - 1];
	memcpy(&(l.elem[i - 1]), &e, sizeof(ElemType));
	l.length++;
	return 0;
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

/*����ָ��Ԫ��*/
Status search(SqList l, char* s, double& score, char* no) {
	bool find = false;
	for (int i = 0; i < l.length; i++)
	{
		if (strcmp(s, l.elem[i].name) == 0)
		{
			score = l.elem[i].score;
			strcpy(no, l.elem[i].no);
			find = true;
		}
	}
	if (find == false)
		return -1;
	return 0;
}

Status MyVisit(ElemType e)
{
	printf("%s %s %.2f\n", e.name, e.no, e.score);
	return 0;
}

/*������*/
Status traverse(SqList l, Status(*visit)(ElemType e)) {
	int i = 1;
	while(i <= l.length && (*visit)(l.elem[i - 1]) == 0)
		i++;
	if (i <= l.length)
		return -1;
	return 0;
}
int sq_len(SqList l) {
	return l.length;
}

int main() {
	int num;
	scanf("%d", &num);
	ElemType s;
	SqList test;
	initlist(test);
	for (int i = 0; i < num; i++)
	{
		scanf("%s %s %lf", s.no, s.name, &s.score);
		insert(test, test.length+1, s);
	}
	int del_num, insert_num;
	scanf("%d %s %s %lf", &insert_num, s.no, s.name, &s.score);
	int test_insert = insert(test, insert_num, s);
	scanf("%d", &del_num);
	int test_del = delete_sq(test, del_num, s);
	char search_name[20], search_no[8];
	double search_sc;
	scanf("%s", search_name);
	int test_search=search(test, search_name, search_sc, search_no);
	int test_len = sq_len(test);
	printf("%d\n%d\n", test_insert, test_del);
	if (test_search == -1)
		printf("-1\n");
	else
		printf("%s %.2f\n", search_no, search_sc);
	printf("%d\n", test_len);
	DestroyList(&test);
	return 0;
}