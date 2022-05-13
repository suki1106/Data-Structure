#include <iostream>
#include <string>
using namespace std;

string evaluate(string s) {
	string res = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= '0' && s[i] <= '9') { // n[s] operation  find right square bracket
			int num = s[i] - 48, k = i + 1, k2;
			while ((s[k] >= '0' && s[k] <= '9')) {
				num = num * 10 + s[k] - 48;
				++k;
			}
			++k;
			k2 = k;
			for (int op = 1; op != 0; k++) {
				if (s[k] == '[') ++op;
				else if (s[k] == ']') --op;
			}
			string t = evaluate(s.substr(k2, k - k2 - 1));
			for (int j = 0; j < num; j++) {
				res = res + t;
			}
			i = k - 1;
		}
		else { // alphabet
			res = res + string(1, s[i]);
		}
	}
	return res;
}
int main() {
	string s;
	while (cin >> s) {
		while (s.find_first_of('<') != string::npos) {
			for (int i = 0; i < s.size(); i++) { // deal with < operation
				if (s[i] == '<') {
					string temp;
					int len = 1;
					if (s[i - 1] == ']') { // n[s] operation 
						// find left square bracket
						int j = i - 2;
						for (int op = 1; op != 0; j--) {
							if (s[j] == ']') ++op;
							else if (s[j] == '[') --op;
						}
						while (s[j] >= '0' && s[j] <= '9') {
							j--;
							if (j == -1)break;

						}
						++j;
						temp = s.substr(j, i - j);
						len = temp.length();
					}
					else {
						temp = string(1, s[i - 1]);
					}
					if (s[i + 1] >= '0' && s[i + 1] <= '9') { // n[s] operation find right square bracket and insert
						int j = i + 1;
						while ((s[j] >= '0' && s[j] <= '9'))++j;
						++j;
						for (int op = 1; op != 0; j++) {
							if (s[j] == '[') ++op;
							else if (s[j] == ']') --op;
						}
						s.insert(j, temp);
					}
					else { // single char
						s.insert(i + 2, temp);
					}
					s.erase(s.find_first_of('<') - len, len + 1);
					break;
				}
			}
		}
		cout << evaluate(s) << endl;

	}
	return 0;
}