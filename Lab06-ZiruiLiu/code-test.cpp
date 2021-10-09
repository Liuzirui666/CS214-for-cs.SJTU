#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int total=0;

int alpha(char c1, char c2) {
	return abs(c1 - c2);
}

vector<int> grade(string X, string Y, int delta, bool rev)
{
	int m = static_cast<int>(X.length());
	int n = static_cast<int>(Y.length());
	vector<int> result(n + 1, 0);
	for (int i = 0; i <= n; ++i){
		result[i]=i*delta;
	}
 
	if (rev)
	{
		reverse(X.begin(), X.end());
		reverse(Y.begin(), Y.end());
	}
 
	for (int i = 1; i <= m; ++i)
	{
		int prev = result[0];
		result[0] += delta;
		for (int j = 1; j <= n; ++j)
		{
			int cost = 0;
			cost=prev+alpha(X[i-1],Y[j-1]);
			cost = min(cost, delta + result[j]);
			cost = min(cost, delta + result[j - 1]);
			prev = result[j];
			result[j] = cost;
		}
	}
	return result;
}
 
pair<string, string> DP(string X, string Y, int delta,int &total)
{
	int m = X.length();
	int n = Y.length();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
	for (int i = 0; i <= m; ++i)
		dp[i][0] = i * delta;
	for (int j = 0; j <= n; ++j)
		dp[0][j] = j * delta;
 
	for (int i = 1; i <= m; ++i)
	{
		//dp[i][0] = dp[i - 1][0] + delta;
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = dp[i - 1][j - 1] + alpha(X[i-1 ], Y[j-1]);
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + delta);
			dp[i][j] = min(dp[i][j], dp[i][j - 1] + delta);
		}
	}
	//cout<<"delta:  "<<delta<<endl;
	//cout<<dp[m][n]<<endl;
 
	int i = m, j = n;
	vector<string> alignment(2);
	// getting back to check the path of connecting couples
	while (i >= 1 || j >= 1)
	{
		if ((i > 0 && dp[i][j] == delta + dp[i - 1][j]) || j == 0)
		{
			cout<<"X[i-1]: "<<X[i-1]<<"    "<<"Y[j-1]: "<<"-"<<endl;
			cout<<"total= "<<total<<"+"<<delta<<endl;
			total+=delta;
			alignment[0].push_back(X[i - 1]);
			alignment[1].push_back('-');
			--i;
		}
		else if ((j > 0 && dp[i][j] == delta + dp[i][j - 1]) || i == 0)
		{
			cout<<"X[i-1]: "<<"-"<<"    "<<"Y[j-1]: "<<Y[j-1]<<endl;
			cout<<"total= "<<total<<"+"<<delta<<endl;
			total+=delta;
			alignment[0].push_back('-');
			alignment[1].push_back(Y[j - 1]);
			--j;
		}
		else if (dp[i][j] == dp[i - 1][j - 1] + alpha(X[i-1],Y[j-1]) || dp[i][j] == dp[i - 1][j - 1])
		{
			//cout<<"i: "<<i<<"    "<<"j: "<<j<<endl;
			cout<<"X[i-1]: "<<X[i-1]<<"    "<<"Y[j-1]: "<<Y[j-1]<<endl;
			cout<<"total = "<<total<<"+"<<alpha(X[i-1],Y[j-1])<<endl;
			total+=alpha(X[i-1],Y[j-1]);
			alignment[0].push_back(X[i - 1]);
			alignment[1].push_back(Y[j - 1]);
			--i, --j;
		}
	}
	reverse(alignment[0].begin(), alignment[0].end());
	reverse(alignment[1].begin(), alignment[1].end());
 
	return {alignment[0], alignment[1]};
}
//    ATC-GCGTA
//    ACCTGACT-
 
int argmax_(vector<int> scoreL, vector<int> scoreR)
{
	int n = static_cast<int>(scoreL.size());
	int minimum = INT_MAX, index = 0;
	//  ymid = arg max ScoreL + rev(ScoreR)
	reverse(scoreR.begin(), scoreR.end());
	
	for (int i = 0; i < n; ++i)
	{
		if (scoreL[i] + scoreR[i] < minimum)
		{
			minimum = scoreL[i] + scoreR[i];
			index = i;
		}
	}
	return index;
}
 
pair<string, string> Hirschberg(string X, string Y, int delta,int &total)
{
	int m = static_cast<int>(X.length());
	int n = static_cast<int>(Y.length());
 
	string Sub_1, Sub_2;
 
	if (m == 0)
	{
		cout<<"X[i-1]: "<<"-"<<"    "<<"Y[j-1]: "<<Y<<endl;
		cout<<"total= "<<total<<"+"<<n*delta<<endl;
		total+=(delta*n);
		return{ string(n, '-'), Y };  //return n times - .
	}
	else if (n == 0)
	{
		cout<<"X[i-1]: "<<X<<"    "<<"Y[j-1]: "<<"-"<<endl;
		cout<<"total= "<<total<<"+"<<delta*m<<endl;
		total+=(delta*m);
		return{ X, string(m, '-') };  // same
	}
	else if (m == 1 || n == 1)
	{
		//cout<<"total= "<<total<<"+"<<alpha(X[0],Y[0])<<endl;
		//total+=alpha(X[0],Y[0]);
		return DP(X, Y, delta,total);
	}
	else
	{
		int xmid = m / 2;
		string X_left = X.substr(0, xmid);   // substr( start_point, size_to_be_copied)
		string X_right = X.substr(xmid, m - xmid);
		int ymid = argmax_(grade(X_left, Y, delta, false), grade(X_right, Y, delta, true));
		string Y_left = Y.substr(0, ymid);
		string Y_right = Y.substr(ymid, n - ymid);

		pair<string, string> result1 = Hirschberg(X_left, Y_left, delta,total);
		pair<string, string> result2 = Hirschberg(X_right, Y_right, delta,total);
 
		Sub_1 = result1.first + result2.first;
		Sub_2 = result1.second + result2.second;
	}
	return { Sub_1, Sub_2 };
}
  
 
int main()
{
//	string X = "CTACCG";
//	string Y = "TACATG";

    //   ATCGCGTA
    //   ACCTGACT

    string X="ATCGCGTA";
    string Y="ACCTGACT";
 
	string X1 = "AGTACGCA";
	string Y1 = "TATGC";

	string X2="CMQHZZRIQOQJOCFPRWOUXXCEMYSWUJTAQBKAJIETSJPWUPMZLNLOMOZNLTLQ";
	string Y2="SUYLVMUSDROFBXUDCOHAATBKNAAENXEVWNLMYUQRPEOCJOCIMZ";
	//int total;
	auto result1 = Hirschberg(X, Y, 13,total);
	cout << "X: " << X << endl;
	cout << "Y: " << Y << endl;
	cout << "the alignment for X and Y:" << endl;
	cout << result1.first << endl;
	cout << result1.second << endl;
	cout<<"TOTAL cost: "<<total<<endl;

	cout << "--------------------------------------------------" << endl;
	total=0;
	auto result2 = Hirschberg(X1, Y1, 13,total);
	cout << "X1: " << X1 << endl;
	cout << "Y1: " << Y1 << endl;
	cout << "the alignment for X1 and Y1:" << endl;
	cout << result2.first << endl;
	cout << result2.second << endl;
	cout<<"TOTAL cost: "<<total<<endl;

	cout << "--------------------------------------------------" << endl;
	total=0;
	auto result3 = Hirschberg(X2, Y2, 13,total);
	cout << "X1: " << X2 << endl;
	cout << "Y1: " << Y2 << endl;
	cout << "the alignment for X1 and Y1:" << endl;
	cout << result3.first << endl;
	cout << result3.second << endl;
	cout<<"TOTAL cost: "<<total<<endl;
    //
	//DP(X,Y,13);
	

	return 0;
}