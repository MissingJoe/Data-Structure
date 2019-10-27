#include "iostream"
#include "string.h"
using namespace std;

typedef int Status;

Status str2num(char* s,char a[100]) {
	while (*s != '\0') {
		for (int i = 0; i < 100; i++)
			if (*s == a[i])
				* s = i + 1;
		s++;
	}
	return 0;
}

int isrepeat(char* s, int len) {
	for (int i = 0; i < len; i++)
		for (int j = i + 1; j < len; j++)
			if (s[j] == s[i])
				return 1;
	return 0;
}

int isok(char* s) {
	int n = strlen(s), max, count = 0;
	if (isrepeat(s, n) == 1)
		return -1;
	for (int i = 0; i < n; i++) {
		count = 0; max = 0;
		for (int j = i + 1; j < n; j++) {
			if (s[j] < s[i] && count == 0) {
				max = s[j];
				count++;
			}
			if (s[j] > max && count == 1 && s[j] < s[i])
				return -1;
		}
	}
	return 1;
}

int main() {
	char s[100], temp[100];
	int i;
	cin >> s;
	while (cin >> temp) {
		str2num(temp, s);
		i = isok(temp);
		if (i == 1)
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
	return 0;
}