#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef int Status;

#define STACKINCREMENT 10

typedef int SElemType;

typedef struct {
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

/*��ʼ��ջ*/
Status initialstack(SqStack* s, int initialstacksize) {
	s->base = (SElemType*)malloc(sizeof(SElemType) * initialstacksize);
	if (!s->base)
		return -2;
	s->top = s->base;
	s->stacksize = initialstacksize;
	return 0;
}

/*ɾ��ջ���ͷ�����ռ�*/
Status destroystack(SqStack* s) {
	if (s->base)
		free(s->base);
	s->top = NULL;
	s->stacksize = 0;
	return 0;
}

/*���ջ�����ͷſռ�*/
Status clearstack(SqStack* s, int initialstacksize) {
	if (s->stacksize > initialstacksize) {
		SElemType* a;
		a = (SElemType*)realloc(s->base, initialstacksize * sizeof(SElemType));
		if (!a)
			return -2;
		else
			s->base = a;
		s->stacksize = initialstacksize;
	}
	s->top = s->base;
	return 0;
}

/*�ж��Ƿ�Ϊ��ջ*/
Status isempty(SqStack s) {
	if (s.top == s.base)
		return 1;
	else
		return 0;
}

/*��ջ����*/
Status stacklength(SqStack s) {
	return s.top - s.base;
}

/*ȡջ��Ԫ��*/
Status gettop(SqStack s, SElemType *e) {
	if (s.top == s.base)
		return -1;
	*e = *(s.top - 1);
	return 0;
}

/*Ԫ����ջ*/
Status push(SqStack* s, SElemType e) {
	if ((s->top - s->base) >= s->stacksize) {
		/*SElemType* a;
		a = (SElemType*)realloc(s->base, sizeof(SElemType) * (s->stacksize + STACKINCREMENT));
		if (!a)
			return -2;
		else
			s->base = a;
		s->top = s->base + stacklength(*s);
		s->stacksize += STACKINCREMENT;*/
		return -1;
	}
	*(s->top++) = e;
	return 0;
}

/*Ԫ�س�ջ*/
Status pop(SqStack* s, SElemType* e, int initialstack) {
	if (s->top == s->base)
		return -1;
	*e = *(--s->top);
	if (s->stacksize > initialstack && s->stacksize - stacklength(*s) > STACKINCREMENT) {
		SElemType* a;
		a = (SElemType*)realloc(s->base, sizeof(SElemType) * (s->stacksize - STACKINCREMENT));
		if (!a)
			return -2;
		else
			s->base = a;
		s->top = s->base + stacklength(*s);
		s->stacksize -= STACKINCREMENT;
	}
	return 0;
}

/*����ջ*/
Status traverse(SqStack s) {
	SElemType* a = --s.top;
	while (a >= s.base) {
		printf("%d ", *a);
		a--;
	}
	if (a < s.base)
		return -1;
	printf("\n");
	return 0;
}

int main() {
	int initialstacksize;
	int scanfresult;
	scanfresult = scanf("%d", &initialstacksize);
	SqStack s;
	SElemType e;
	initialstack(&s, initialstacksize);
	int popresult, pushresult;
	char opt[10];
	int optresult[100] = {0};
	int i = 0;
	while (1) {
		strcpy(opt, "");
		scanfresult = scanf("%s", opt);
		if (strcmp(opt, "quit") == 0)
			break;
		else
		{
			if (strcmp(opt, "pop") == 0)
				optresult[i] = 10001;
			if (strcmp(opt, "push") == 0)
			{
				scanfresult = scanf("%d", &e);
				optresult[i] = e;
			}	
		}
		i++;
	}
	for (int j = 0; j < i; j++) {
		if (optresult[j] == 10001) {
			popresult = pop(&s, &e, initialstacksize);
			if (popresult == 0)
				printf("%d\n", e);
			else
				printf("Stack is Empty\n");
		}
		if (optresult[j] <= 10000) {
			pushresult = push(&s, optresult[j]);
			if (pushresult == -1)
				printf("Stack is Full\n");
		}
	}
	traverse(s);
	destroystack(&s);
	return 0;
}