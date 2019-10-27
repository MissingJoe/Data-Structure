#include "stack"
#include "iostream"
using namespace std;

typedef struct {
	int n;//阶乘函数的参数
}Data;

stack<Data> myStack;

int temo = 0;

int f(long long int n) {
	temo++;
	if(temo> 4500)
		cout << "第" << temo << "次调用递归" << endl;
	if (n == 0 || n == 1)
		return 1;
	else
		return f(n - 1);
}

int main() {
	long long int count;
	cout << "请输入数字：" << endl;
	cin >> count;
	Data a, temp;
	long long int result = 1;
	long long int count2 = 0;
	for (long long int i = count; i >= 1; i--) {
		if (i != 1) {
			a.n = i;
			myStack.push(a);
			
			count2++;
			if (count2 > 4990)
				cout << "第" << count2 << "次进栈" << endl;
			if (count2 > 120888750)
				cout << "第" << count2<< "次进栈" << endl;
		}
		else
			result *= i;
	}
	for (int i = 1; i < count; i++) {
		temp = myStack.top();
		result *= temp.n;
		myStack.pop();
	}
	long long int result;
	result = f(count);
	cout << result << endl;
	return 0;
}