#include <iostream>

using namespace std;

#define MAX 10000

const int n = 7;
double p[n + 1] = {0,0.04,0.06,0.08,0.02,0.10,0.12,0.14};
double q[n + 1] = {0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};

// const int n = 5;
// double p[n + 1] = {0,0.15,0.10,0.05,0.10,0.20};
// double q[n + 1] = {0.05,0.10,0.05,0.05,0.05,0.10};

int root[n + 1][n + 1];//Record the root node of the optimal subtree
double e[n + 2][n + 2];//Record the expected cost of the subtree
double w[n + 2][n + 2];//Record the probability sum of the subtree

void optimal_binary_search_tree(double *p,double *q,int n)
{
//The result is stored in e.

for (int i=1;i<=(n+1);++i){
    e[i][i-1]=q[i-1];
    w[i][i-1]=q[i-1];
}
for (int m=1;m<=n;++m){
    for(int i=1;i<=n-m+1;++i){
        int j=i+m-1;
        e[i][j]=MAX;
        w[i][j]=w[i][j-1]+p[j]+q[j];
        for(int root_=i;root_<=j;++root_){
            double value=e[i][root_-1]+e[root_+1][j]+w[i][j];
            if(value<e[i][j]){
                e[i][j]=value;
                root[i][j]=root_;
            }
        }
    }
}



}

/*
You can print the structure of the optimal binary search tree based on root[][]
The format of printing is as follows:
k2 is the root
k1 is the left child of k2
d0 is the left child of k1
d1 is the right child of k1
k5 is the right child of k2
k4 is the left child of k5
k3 is the left child of k4
d2 is the left child of k3
d3 is the right child of k3
d4 is the right child of k4
d5 is the right child of k5
*/

int leave=0;
void construct_optimal_bst(int i,int j,bool dir)
{
//You can adjust the number of input parameters
//  dir==0 left,  dir==1 right

if(i==j){
    if(dir==0){
    cout<<"k"<<root[i][j]<<" is the left child of k"<<j+1<<endl;
    }else if(dir==1){
        cout<<"k"<<root[i][j]<<" is the right child of k"<<i-1<<endl;
    }
    cout<<"d"<<leave<<" is the left child of k"<<root[i][j]<<endl;
    leave++;
    cout<<"d"<<leave<<" is the right child of k"<<root[i][j]<<endl;
    leave++;
    return;
}

if((i==1) && (j==n)){
    cout<<"k"<<root[1][n]<<" is the root"<<endl;
}else if(dir==0){
    cout<<"k"<<root[i][j]<<" is the left child of k"<<j+1<<endl;
}else if(dir==1){
    cout<<"k"<<root[i][j]<<" is the right child of k"<<i-1<<endl;
}
int r=root[i][j];
//cout<<"ROOT: "<<r<<endl;
if(i<=(r-1)){
    construct_optimal_bst(i,r-1,0);
}else{
    cout<<"d"<<leave<<" is the left child of k"<<r<<endl;
    leave++;
} 
if((r+1)<=j){
    construct_optimal_bst(r+1,j,1);
}else{
    cout<<"d"<<leave<<" is the right child of k"<<r<<endl;
    leave++;
}

return;

}

int main()
{
    optimal_binary_search_tree(p,q,n);
    cout<<"The cost of the optimal binary search tree is: "<<e[1][n]<<endl;
    cout << "The structure of the optimal binary search tree is: " << endl;
    construct_optimal_bst(1,n,0);
}


