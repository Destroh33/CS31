#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value) {
	if (n < 0) {
		return -1;
	}//invalid n case
	for (int x = 0; x < n; x++) {
		a[x] = a[x] + value;
	}
	return n;
}
int lookup(const string a[], int n, string target) {
	if (n < 0) {
		return -1;
	}//invalid n case
	for (int x = 0; x < n; x++) {
		if (a[x] == target) {
			return x;
		}
	}
	return -1;
}
int positionOfMax(const string a[], int n) {
	if (n <= 0) {
		return -1;
	}//invalid n case (can't be a max if there is no elements)
	string max = a[0];
	int maxInd = 0;
	for (int x = 0; x < n; x++) {
		if (a[x] > max ) {
			max = a[x];
			maxInd = x;
		}
	}
	return maxInd;
}
int rotateLeft(string a[], int n, int pos) {
	if (n < 0 || pos>=n || pos<0 ) {//invalid n case (also catches n=0 case because pos has to be out of bounds if n is 0)
		return -1;
	}
	string start = a[pos];
	for (int x = pos; x+1 < n; x++) {
		a[x] = a[x + 1];
	}
	a[n - 1] = start;
	return pos;
}
int countRuns(const string a[], int n) {
	if (n < 0) {
		return -1;
	}
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	// starter cases to catch invalid n and to ensure the array length is large enough to get 2 indices at once
	int rc = 1;
	string s = a[0];
	for (int x = 1; x < n; x++) {
		if (a[x] != s) {
			rc++;
			s = a[x];
		}
	}
	return rc;
}
int flip(string a[], int n) {
	if (n < 0) {
		return -1;
	}//invalid n case
	for (int x = 0; x < (n/2); x++) {
		string temp = a[x];
		a[x] = a[(n - 1) - x];
		a[(n - 1) - x] = temp;
	}
	return n;
}
int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) { // invalid n case
		return -1;
	}
	int less = 0;
	if (n1 < n2) { // decides which n to use as bounds for the loop
		less = n1;
	}
	else {
		less = n2;
	}
	for (int x = 0; x < less; x++) {
		if (a1[x] != a2[x]) {
			return x;
		}
	}
	return less;
}
int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2<0 || n2>n1) { //invalid n cases
		return -1;
	}
	if (n2 == 0) {// if a2 is an empty array, then it automatically exists as a subsequence
		return 0;
	}
	for (int x = 0; x+n2 <= n1; x++) {
		int tempS = 0;
		for (tempS = 0; tempS < n2; tempS++) {
			if (a1[x + tempS] != a2[tempS]) {
				break;
			}
		}
		if (tempS == n2) {
			return x;
		}
	}
	return -1;
}
int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) {//invalid n case
		return -1;
	}
	for (int x = 0; x < n1; x++) {
		for (int y = 0; y < n2; y++) {
			if (a1[x] == a2[y]) {
				return x;
			}
		}
	}
	return -1;
}
int separate(string a[], int n, string separator) {
	if (n < 0) {
		return -1;
	}
	for (int x = 0; x < n; x++) {// sorts the array lexicographically
		for (int y = x + 1; y < n; y++) {
			if (a[x] > a[y]) {
				string temp = a[x];
				a[x] = a[y];
				a[y] = temp;
			}
		}
	}
	for (int x = 0; x < n; x++) {	//checks where separator fits in the sorted array
		if (separator <= a[x]) {
			return x;
		}
	}
	return n;
}

int main()
{
	string h[7] = { "melania", "kamala", "donald", "tim", "", "doug", "jd" };
	string g[4] = { "melania", "kamala", "jd", "usha" };
	//lookup tests
	assert(lookup(h, 7, "doug") == 5);//can find string
	assert(lookup(h, 7, "donald") == 2);//can find string in smaller array
	assert(lookup(h, 2, "donald") == -1);//can't find string
	assert(lookup(h, -1, "doug") == -1);//invalid n
	assert(lookup(h, 0, "melania") == -1);//0 length array, can't find melania
	//position of max tests
	assert(positionOfMax(h, 7) == 3);//max value can be found
	assert(positionOfMax(h, 0) == -1);//no max value in empty array
	assert(positionOfMax(h, -1) == -1);//invalid n
	//rotate Left tests
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jd" && g[3] == "kamala");//rotate left works
	assert(rotateLeft(h, 0, 0) == -1);//rotating left nothing doesn't make sense
	assert(rotateLeft(g, -1, 4) == -1);//invald n
	//count runs tests
	string d[5] = { "kamala", "kamala", "kamala", "tim", "tim" };
	assert(countRuns(d, 5) == 2);// runs counted correctly (repeated values)
	assert(countRuns(h, 7) == 7);// runs counted correctly (unrepeated values)
	assert(countRuns(h, 0) == 0);// 0 runs counted in empty array
	assert(countRuns(d, -1) == -1);// invalid n
	//flip tests
	string f[3] = { "jd", "donald", "gwen" };
	assert(flip(f, 3) == 3 && f[0] == "gwen" && f[2] == "jd");// flips correctly
	assert(flip(f, 0) == 0);// flipping empty array is empty array 
	assert(flip(f, -1) == -1);// invalid n
	//differ tests
	string a[7] = { "melania", "kamala", "donald", "tim", "", "doug", "jd" };//ensures the tests work with emptry strings as well
	string b[4] = { "melania", "kamala", "jd", "usha" };
	assert(differ(a, 4, b, 4) == 2);//differ correctly with same length arrays
	assert(differ(a, 7, b, 4) == 2);//differ correctly with different length arrays (first>second)
	assert(differ(b, 4, a, 7) == 2);//differ correctly with different length arrays (second>first)
	assert(differ(b, 4, b, 4) == 4);//same arrays so no difference
	assert(differ(a, 4, b, 0) == 0);//differ correctly with empty array
	assert(differ(a, 4, b, -1) == -1);//invalid n
	assert(differ(a, -1, b, 4) == -1);//invalid n
	//subsequence tests
	assert(subsequence(a, 7, b, 2) == 0);//subsequence exists and is found
	assert(subsequence(a, 1, b, 2) == -1);//subsequence length is > array length
	assert(subsequence(a, 7, f, 3) == -1);//subsequence never found in array
	assert(subsequence(a, -1, b, 2) == -1);//invalid n
	assert(subsequence(a, 1, b, -2) == -1);//invalid n
	assert(subsequence(a, 7, b, 0) == 0);//empty subsequence exists in all sequences
	//lookup any tests
	string c[3] = { "jd", "donald", "gwen" };
	assert(lookupAny(a, 7, c, 3) == 2);//working lookup any (donald found)
	assert(lookupAny(a, 7, c, 0) == -1);//no strings in empty array so nothing found
	assert(lookupAny(a, 0, c, 3) == -1);//can't find a string in an empty array
	assert(lookupAny(a, -1, c, 3) == -1);//invalid n
	assert(lookupAny(a, 1, c, -3) == -1);//invalid n
	//separate tests
	assert(separate(a, 7, "jd") == 3);//working separate with separator in array
	assert(separate(a, 7, "je") == 4);//working separate with separator not in array
	assert(separate(a, 0, "jd") == 0);//n returned because no elements are less than separator because there are no elements
	assert(separate(a, -1, "jd") == -1);//invalid n
	assert(separate(a, 7, "zzzz") == 7);//separator is at the end
	string q[5] = { "a", "b", "c", "d","e" };
	assert(separate(q, 5, "") == 0);//separator is at the beginning
	cout << "All tests succeeded" << endl;
}