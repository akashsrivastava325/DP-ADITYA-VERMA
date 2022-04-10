#include <bits/stdc++.h>
using namespace std;

int tabulation(vector<int> value, vector<int> weight, int capacity, int n) {

	/*
	Few Questions:
	1. How to approch?
		Step 1: Find out how many choices are there.
		Step 2: Think of a recursive solution.
		Step 3: Convert the recursive solution into the tabulation.


		Parts of recursive solution:
		1. Base Case
		2. Choices calls.



		How do we read a recursive code (on the very first stack)?
		int knapsack(vector<int> value, vector<int> weight, int capacity, int n) {
			int choice_1 = knapsack(value, weight, capacity, n - 1);
			if(capacity >= weight[n - 1]) {
				int choice_2 = value[n - 1] + knapsack(value, weight, capacity - weight[n - 1], n - 1);
				return max(choice_1, choice_2);
			}

			return choice_1;
		}

		Here don't go into the backend part (like, how recursion is working and all)..
		Main function sends the full problem...
		The knapsack function on the very first stack calling two function here..
		choice_1 expects the maximum value "when we do not pick the items".
		choice_2 expects the maximum value "when we pick the items".

		And we return the maximum value of choice_1 and choice_2 to main function.



		Similary in the tabulation method, we ask for the ans in the below given way.

		we need to find out the dp[n][capacity] aka value "When including all the n elements for the capacity of knapsack 'capacity'".
		int choice_1 = dp[n - 1][capacity]; // choice_1 expects the answer for the n - 1 elements for the capacity "capacity" of knapsack. In other words, we moved out without picking the element. Or say, we did not pick the element in choice_1, in choice_2 we'll pick the element.
		int choice_2 = value[n - 1] + dp[n - 1][capacity - weight[n - 1]]; => Here we're picking the element. For n - 1 element and for capcaity = capacity - weight[n - 1].
		dp[n][capacity] = max(choice_1, choice_2);
	*/

	vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, -1));

	// Filling the subproblems---

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < capacity; j++) {
			if (i == 0 || j == 0) {
				dp[i][j] = 0;
			}
			else {
				//First i elements are given and capacity of the bag is given j.
				int choice_1 = dp[i - 1][j];
				if (weight[i] <= j /* check if the capacity of the bag is j so check the ith item can be stored into the bag with capacity j or not*/) {
					int choice_2 = value[i - 1] + dp[i - 1][j - weight[i]];
					dp[i][j] = max(choice_2, choice_1);
				}
				else {
					dp[i][j] = choice_1;
				}
			}
		}
	}

	dp[n][capacity] = max(dp[n - 1][capacity], value[n - 1] + dp[n - 1][capacity - weight[n - 1]]);
	return dp[n][capacity];
}


using namespace std;
int main() {

	int n;
	cin >> n; // number of items;

	vector<int> value(n); // values of n items.
	vector<int> weight(n); // weights of the given n items.

	for (int i = 0; i < n; i++) {
		cin >> value[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> weight[i];
	}

	int capacity;
	cin >> capacity; //capacity of knapsack.

	cout << tabulation(value, weight, capacity, n);
}