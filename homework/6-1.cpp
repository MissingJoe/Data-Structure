#include "iostream"
#include "string.h"
using namespace std;

typedef int QElemType;
typedef int Status;

typedef struct Qnode{
	QElemType data;
	Qnode* next;
}Qnode, * QueuPtr;

typedef struct {
	QueuPtr front;
	QueuPtr rear;
}LinkQueue;

Status InitQueue(LinkQueue* q) {
	q->front = q->rear = new Qnode;
	if (q->front == NULL)
		return -2;
	q->front->next = NULL;
	return 0;
}

Status DestroyQueue(LinkQueue* q) {
	while (q->front) {
		q->rear = q->front->next;
		delete q->front;
		q->front = q->rear;
	}
	q->front = q->rear = NULL;
	return 0;
}

Status QueueEmpty(LinkQueue q) {
	if (q.front == q.rear)
		return 1;
	else
		return 0;
}

int QueueLength(LinkQueue q) {
	int length = 0;
	QueuPtr p = q.front->next;
	while (p) {
		length++;
		p = p->next;
	}
	return length;
}

Status GetHead(LinkQueue q,QElemType *e) {
	if (q.front == q.rear)
		return -1;
	*e = q.front->next->data;
	return 0;
}

Status QueueTraverse(LinkQueue q, int len) {
	QueuPtr p = q.front->next;
	int length = 0;
	while (p && length < len) {
		cout << p->data << " ";
		p = p->next;
		length++;
	}
	cout << endl;
	return 0;
}

Status EnQueue(LinkQueue* q, QElemType e,int len) {
	int length = QueueLength(*q);
	if (length >= len)
		return -1;
	QueuPtr p = new Qnode;
	if (p == NULL)
		return -2;
	p->data = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
	//QueueTraverse(*q, 4);
	return 0;
}

Status DeQueue(LinkQueue* q, QElemType* e) {
	if (q->front == q->rear)
		return -1;
	QueuPtr p = q->front->next;
	q->front->next = p->next;
	if (q->front->next == NULL)
		q->rear = q->front;
	*e = p->data;
	//QueueTraverse(*q, 4);
	delete p;
	return 0;
}


int main() {
	int i;
	cin >> i;
	char s[20];
	int OutQueue, InQueue;
	LinkQueue q;
	InitQueue(&q);
	while (1) {
		cin >> s;
		if (strcmp(s, "quit") == 0)
			break;
		if (strcmp(s, "dequeue") == 0) {
			if (DeQueue(&q, &OutQueue) == -1)
				cout << "Queue is Empty" << endl;
			else
				cout << OutQueue << endl;
		}
		if (strcmp(s, "enqueue") == 0) {
			cin >> InQueue;
			if (EnQueue(&q, InQueue, i) == -1)
				cout << "Queue is Full" << endl;
		}
	}
	QueueTraverse(q, i);
	DestroyQueue(&q);
	return 0;
}