#include <iostream>
using namespace std;

typedef int Status;
typedef int ElemType;

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
	l->next = l->prior = l;
	l->data = 9999;
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
	delete head;//释放头结点
	l = NULL;
	return 0;
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

int DulLength(DuLinkList l) {
	DuLNode* p = l->next;
	int length = 0;
	while (p != l) {
		length++;
		p = p->next;
	}
	return length;
}

Status ListInsert_Dul(DuLinkList& l, int i, ElemType e) {
	DuLNode* p = GetElemP_Dul(l, i);
	if (p == NULL)
		return -1;
	DuLNode* s = new DuLNode;
	if (s == NULL)
		return -2;
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return 0;
}

Status ListDeleteValue_Dul(DuLinkList& l, ElemType e) {
	DuLNode* p = l->next;
	while (p != l && p->data != e)
		p = p->next;
	if (p == l)
		return -1;
	p->next->prior = p->prior;
	p->prior->next = p->next;
	return 0;
}

Status traverse(DuLinkList l) {
	DuLNode* p = l->prior;
	while (p != l) {
		cout << p->data << " ";
		p = p->prior;
	}
	cout << endl;
	return 0;
}

DuLNode* GetElemP_Dul_UP(DuLinkList l, int i) {
	DuLNode* p = l->prior;
	int length = 1;
	while (p != l && i > length) {
		length++;
		p = p->prior;
	}
	if (p == l && i > length)
		return NULL;
	else
		return p;
}

void Joseph(DuLinkList& l, int m, int k) {
	DuLNode* p = GetElemP_Dul_UP(l, k);
	int count = 1;
	while (DulLength(l) != 1) {
		if (p->data == 9999) {
			p = p->prior;
			continue;
		}	
		if (count == m) {
			ListDeleteValue_Dul(l, p->data);
			cout << p->data << "死亡" << endl;
			traverse(l);
			count = 1;
		}
		else
		    count++;
		p = p->prior;
	}
}

int main() {
	DuLinkList l;
	InitialDuLinkList(l);
	int m, n, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		ListInsert_Dul(l, DulLength(l)+1, i);
	traverse(l);
	Joseph(l, m, k);
	Destroy_Dul(l);
	return 0;
}