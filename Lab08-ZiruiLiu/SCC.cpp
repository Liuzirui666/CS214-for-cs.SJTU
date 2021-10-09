#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
const int maxn = 1e5;
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/
bool visit[maxn];
stack<int> stack1;
vector<int> Graph[maxn];
int DFN[maxn], Low[maxn], connect[maxn];
int index_ = 0, num = 0;
void calculate(int u)
{
    Low[u] = DFN[u] = ++index_;
    visit[u] = true; 
    stack1.push(u);
    for (int v : Graph[u])
    {
        if (DFN[v] == 0)
        { 
            calculate(v);
            Low[u] = min(Low[u], Low[v]);
        }
        else if (visit[v])
        {
            Low[u] = min(Low[u], DFN[v]);
        }
        
    }
    if (Low[u] == DFN[u])
    {
        num++;
        while (visit[u])
        {
            int v = stack1.top();
            stack1.pop();
            visit[v] = false;
            connect[v] = num;
        }
    }
}
int SCC(int n, const vector<pair<int, int>> &edge)
{
    for (auto iterator = edge.cbegin(); iterator != edge.cend(); iterator++)
    {
        Graph[iterator->first].push_back(iterator->second);
    }
    for (int u = 0; u < n; u++)
    {
        if (connect[u] == 0)
        {
            calculate(u);
        }
    }
    return num;
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m, n;
    vector<pair<int, int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    cout << fin.is_open() << endl;
    fin >> n >> m;
    cout << n << " " << m << endl;
    int tmp1, tmp2;
    for (int i = 0; i < m; i++)
    {
        fin >> tmp1 >> tmp2;
        edge.push_back(pair<int, int>(tmp1, tmp2));
    }
    fin.close();
    int ans = SCC(n, edge);
    cout<<"Test Answer:  "<<ans<<endl;
    fout.open("SCC.out");
    fout << ans << '\n';
    fout.close();
    return 0;
}
