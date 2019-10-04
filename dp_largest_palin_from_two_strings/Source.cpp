#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

int main() {
	string str1, str2, str_combined;
	cout << "Enter string 1 ";
	cin >> str1;
	cout << "Enter string 2 ";
	cin >> str2;

	size_t str1_len = str1.length();
	size_t str2_len = str2.length();
	str_combined = str1 + str2;
	size_t c_len = str_combined.length();

	// Lets try to create DP of combined string O(M + N * M + N)
	// Index of Cell is the range for sub-string
	// Once we have results we know the largest palindrome should be in a range that includes both strings
	vector <vector <bool>> dp(c_len, vector <bool> (c_len, false));

	// Pre - Fill for single char sub-strings. They will always be Palindromes
	for (int i = 0; i < c_len; i++) {
		dp[i][i] = true;
	}

	// Pre - Fill for all j < i as we are not interested in reverse strings 
	for (int i = 0; i < c_len; i++) {
		for (int j = 0; j < c_len; j++) {
			if (j < i) {
				dp[i][j] = false;
			}
		}
	}

	// Pre - Fill for two char
	for (int i = 0; i < c_len - 1; i++) {
		if (str_combined[i] == str_combined[i + 1]) {
			dp[i][i + 1] = true;


		} else {
			dp[i][i + 1] = false;
		}
	}

	// Now lets build our DP with the following invariant
	// for any palindrome > 2 chars
	// (FIRST_LETTER == LAST_LETTER) && (MIDDLE is Palindrome) 
	pair<size_t, size_t> max_range;
	string lp;
	int max_len = INT_MIN;

	for (int j = 2; j < c_len; j++) {
		for (int i = 0; i + j < c_len; i++) {
			int mid_s = i + 1;
			int mid_e = i + j - 1;
			if (str_combined[i] == str_combined[i + j] && dp[mid_s][mid_e]) {
				dp[i][i + j] = true;
				// check if i is in range of str1 and j in str2
				if (i < str1_len && j > str1_len) {
					if (j - i > max_len) {
						max_len = j - i;
						lp = str_combined.substr(i, j + 1);
					}
				}
			}
			else {
				dp[i][i + j] = false;
			}
		}
	}
#if 1
	for (int i = 0; i < c_len; i++) {
		cout << endl;
		for (int j = 0; j < c_len; j++) {
			string is_palin = (dp[i][j] == true) ? ("TRUE ") : ("FALSE ");
			cout << is_palin;
		}
		cout << endl;
	}
#endif
	 
	cout << "Longest Palindrome combined is " << lp << endl;
	return 0;
}