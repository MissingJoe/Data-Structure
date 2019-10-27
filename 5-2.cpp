#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "iostream"
using namespace std;

typedef int Status;

#define STACKINCREMENT 100
#define STACK_INI_SIZE 1000
typedef int SElemType;

typedef struct {
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

/*初始化栈*/
Status initialstack(SqStack* s) {
	s->base = (SElemType*)malloc(sizeof(SElemType) * STACK_INI_SIZE);
	if (!s->base)
		return -2;
	s->top = s->base;
	s->stacksize = STACK_INI_SIZE;
	return 0;
}

/*删除栈，释放申请空间*/
Status destroystack(SqStack* s) {
	if (s->base)
		free(s->base);
	s->top = NULL;
	s->stacksize = 0;
	return 0;
}

/*求栈长度*/
Status stacklength(SqStack s) {
	return s.top - s.base;
}

/*取栈顶元素*/
Status gettop(SqStack s, SElemType* e) {
	if (s.top == s.base)
		return -1;
	*e = *(s.top - 1);
	return 0;
}

/*元素入栈*/
Status push(SqStack* s, SElemType e) {
	if ((s->top - s->base) >= s->stacksize) {
		SElemType* a;
		a = (SElemType*)realloc(s->base, sizeof(SElemType) * (s->stacksize + STACKINCREMENT));
		if (!a)
			return -2;
		else
			s->base = a;
		s->top = s->base + stacklength(*s);
		s->stacksize += STACKINCREMENT;
	}
	*s->top = e;
	s->top++;
	return 0;
}

/*元素出栈*/
Status pop(SqStack* s, SElemType* e) {
	if (s->top == s->base)
		return -1;
	s->top--;
	*e = *s->top;
	if (s->stacksize > STACK_INI_SIZE && s->stacksize - stacklength(*s) > STACKINCREMENT) {
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

/*遍历栈*/
Status traverse(SqStack s) {
	SElemType* a = --s.top;
	while (a >= s.base) {
		printf("%d ", *a);
		a--;
	}
	printf("\n");
	if (a >= s.base)
		return -1;
	return 0;
}

int calculate2(int a, int b, char s) {
	if (s == '+')
		return a + b;
	else if (s == '-')
		return a - b;
	else if (s == '*')
		return a * b;
	else
		return a / b;
}

int pow(int i) {
	int mult = 1;
	for (int j = 1; j <= i; j++)
		mult *= 10;
	return mult;
}

int str2num(char* str, int len) {
	int i = 0;
	int sum = 0;
	while (i < len) {
		sum = sum + pow(len - i - 1) * (str[i] - '0');
		i++;
	}
	return sum;
}

int levelopt(char s) {
	if (s == '+' || s == '-')
		return 1;
	else if (s == '*' || s == '/')
		return 2;
	else
		return 0;
}

int optmatch(char s1, char s2) {
	int level1 = levelopt(s1);
	int level2 = levelopt(s2);
	if (level1 < level2)
		return -1;
	else if (level1 == level2)
		return 0;
	else
		return 1;
}

Status isdiv0(int a, char s) {
	if (a == 0 && s == '/')
		return 1;
	else
		return 0;
}

Status stackcalculate(SqStack* snum, SqStack* sopt) {
	int temp, numright, numleft, nouse, sum;
	if (stacklength(*snum) < 2)
		return -99999;
	gettop(*sopt, &temp);
	gettop(*snum, &numright);
	pop(snum, &nouse);
	gettop(*snum, &numleft);
	pop(snum, &nouse);
	if (isdiv0(numright, (char)temp))
		return -99999;
	sum = calculate2(numleft, numright, (char)temp);
	pop(sopt, &temp);
	push(snum, sum);
	return 0;
}

int operatestring(SqStack* snum, SqStack* sopt, char a[100]) {
	int i = 0, j, nouse;
	int calculatestatus = 0;
	//char* strnum;
	while (a[i] != '=') {
		if (a[i] >= '0' && a[i] <= '9') {
			j = i;
			while (a[j] >= '0' && a[j] <= '9')
				j++;
			nouse = str2num(&a[i], j - i);
			push(snum, nouse);
			i = j;
		}
		else if ((a[i] > 39 && a[i] < 44) || a[i] == 45 || a[i] == 47) {
			if (sopt->base != sopt->top) {
				gettop(*sopt, &nouse);
				if (optmatch(a[i], (char)nouse) > 0 || a[i] == '(')
					push(sopt, a[i]);
				else
				{
					if (a[i] == ')') {
						while (gettop(*sopt, &nouse) == 0 && (char)nouse != '(') {
							calculatestatus = stackcalculate(snum, sopt);
							if (calculatestatus == -99999)
								return -99999;
						}
						if ((char)nouse == '(')
							pop(sopt, &nouse);
						else
							return -99999;
					}
					else {
						while (gettop(*sopt, &nouse) == 0 && optmatch(a[i], (char)nouse) <= 0) {
							calculatestatus = stackcalculate(snum, sopt);
							if (calculatestatus == -99999)
								return -99999;
						}
						push(sopt, a[i]);
					}
				}
			}
			else
				push(sopt, a[i]);
			i++;
		}
		else
			return -99999;
		/*cout << "snum:";
		traverse(*snum);
		cout << "sopt:";
		traverse(*sopt);*/
	}
	/*cout << "snum:";
	traverse(*snum);
	cout << "sopt:";
	traverse(*sopt);*/
	if (stacklength(*snum) != stacklength(*sopt) + 1)
		return -99999;
	while (sopt->base != sopt->top) {
		calculatestatus = stackcalculate(snum, sopt);
		if (calculatestatus == -99999)
			return -99999;
	}
	gettop(*snum, &nouse);
	return nouse;
}

int main() {
	char a[100];
	/*int scanfresult = scanf("%s", a);*/
	cin >> a;
	SqStack s1, s2;
	initialstack(&s1);
	initialstack(&s2);
	int result = operatestring(&s1, &s2, a);
	if (result == -99999)
		printf("ERROR\n");
	else
		printf("%d\n", result);
	destroystack(&s1);
	destroystack(&s2);
	//system("pause");
	return 0;
}