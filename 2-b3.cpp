#include <iostream>
using namespace std;

typedef int Status;

typedef struct student {
	int   num;
	char  name[10];
	float score;
} *ElemType;

typedef struct DuLNode {
	ElemType data;
	DuLNode* prior;
	DuLNode* next;
}DulNode, * DuLinkList;

Status InitialDuLinkList(DuLinkList& l) {
	//l = (DuLinkList)malloc(sizeof(DuLNode));
	l = new DuLNode;
	if (!l)
		return -2;
	l->data = NULL;
	l->next = l->prior = l;
	return 0;
}

/*摧毁双向循环链表*/
Status Destroy_Dul(DuLinkList& l) {
	DuLNode* p = l->next, * q;
	DuLNode* head = l;
	while (p != head) {
		q = p->next;
		delete p;
		p = q;
	}
	delete head->data;
	delete head;//释放头结点
	l = NULL;
	return 0;
}

int DulLength(DuLinkList l) {
	DuLNode* p = l->next;
	int length = 0;
	while (p != l) {
		length++;
		p = p->next;
	}
	return length;
}

DuLNode* GetElemP_Dul(DuLinkList l, int i) {
	DuLNode* p = l->next;
	int length = 1;
	while (p != l && i > length) {
		length++;
		p = p->next;
	}
	if (p == l && i > length)
		return NULL;
	else
		return p;
}

Status ListInsert_Dul(DuLinkList& l, int i, ElemType e) {
	DuLNode* p = GetElemP_Dul(l, i);
	if (p == NULL)
		return -1;
	DuLNode* s = new DuLNode;
	if (s == NULL)
		return -2;
	s->data = e;
	//cout << "学号:" << s->data->num << " 姓名:" << s->data->name << " 成绩:" << s->data->score << endl;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return 0;
}

Status ListDelete_Dul(DuLinkList& l, int i, ElemType e) {
	DuLNode* p = GetElemP_Dul(l, i);
	if (p == NULL)
		return -1;
	e = p->data;
	p->next->prior = p->prior;
	p->prior->next = p->next;
	delete p;
	return 0;
}

Status traverse(DuLinkList l) {
	DuLNode* p = l->next;
	cout << "打印开始" << endl;
	while (p != l) {
		cout << "学号:" << p->data->num << " 姓名:" << p->data->name << " 成绩:" << p->data->score << endl;
		p = p->next;
	}
	cout << "打印结束" << endl;
	return 0;
}

int main() {
	DuLinkList l;
	InitialDuLinkList(l);
	student       e[] = { {1001, "张三", 76.5},
		 {1002, "李四", 87},
		 {1003, "王五", 80},
		 {1004, "赵六", 54},
		 {1005, "牛七", 85},
		 {1006, "马八", 60} };
	for (int i = 0; i < 6; i++) 
		ListInsert_Dul(l, DulLength(l) + 1, e+i);
	traverse(l);
	ListInsert_Dul(l, 1, e);
	traverse(l);
	ListInsert_Dul(l, DulLength(l) + 1, e);
	traverse(l);
	ListInsert_Dul(l, 2, e);
	traverse(l);
	cout << "删除开始" << endl;
	ListDelete_Dul(l, DulLength(l), e);
	traverse(l);
	ListDelete_Dul(l, 1, e);
	traverse(l);
	ListDelete_Dul(l, 2, e);
	traverse(l);
	Destroy_Dul(l);
	return 0;
}