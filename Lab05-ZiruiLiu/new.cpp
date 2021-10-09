#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#define MAX 100000
/*
Dear TA: 
please see this explanation:  on line 43~45
  this place i don't fully understand what the question means by " average cost",so i
     did it in my way (which is adding all the |x_i-y_j| on the path). If my understanding is wrong, 
     it should also be quite easy to change to another explanation(adding all the dtw (i,j) ?)
     since i have already printed out the path and the dtw(n,m). 
*/

/*
The process to calculate the dynamic can be divided into four steps:
1.Create an empty cost matrix DTW with X and Y labels as amplitudes of the two series to be compared.
2.Use the given state transition function to fill in the cost matrix.
3
.Identify the warping path starting from top right corner of the matrix and traversing to 
bottom left. The traversal path is identified based on the neighbor with minimum value.
i.e., When we reach the point (i, j) in the matrix, the next position is to choose the 
point with the smallest cost among (i-1,j-1), (i,j-1), and (i-1,j),
For the sake of simplicity, when the cost is equal, the priority of the 
selection is (i-1,j-1), (i,j-1), and (i-1,j) in order.

4.Calculate th time normalized distance. We define it as the average cost of the selected points.
*/
using namespace std;
vector<vector<pair<int,int> >> walk;
vector<vector<int>> d;

double nodes=0,cost=0;
double walker(int n,int m){
    if(n<1 || m<1)
        return 0.0;
    int n_=walk[n][m].first;
    int m_=walk[n][m].second;
    walker(n_,m_);
    cout<<n<<"  "<<m<<endl;
    cost+=d[n][m];  //  the place where i got confused about the question
    nodes++;
    return cost/nodes;   //  this place i don't fully understand what the question means by " average cost",
    //so i did it in my way. If my understanding is wrong, it should be quite easy to change to another explanation
    // since i have already printed out the path and the dtw(n,m). 
}

int distance(vector<int> x, vector<int> y) {
    int n = x.size();
    int m = y.size();
    x.resize(30);
    y.resize(30);
    for(int i=n;i>0;--i){
        x[i]=x[i-1];
    }
    x[0]=0;
    for(int i=m;i>0;--i){
        y[i]=y[i-1];
    }
    y[0]=0;

    d.clear();
    walk.clear();
    vector<vector<int>> DTW;
    //vector<vector<int>> d;
    DTW.resize(30);
    d.resize(30);
    walk.resize(30);
    for(int i=0;i<30;++i){
        DTW[i].resize(30);
        d[i].resize(30);            
        walk[i].resize(30);
    }
    
    int ans = 0;
    for(int i=0;i<=n;++i){
        for(int j=0;j<=m;++j){
            DTW[i][j]=MAX;
            d[i][j]=abs(x[i]-y[j]);
        }
    }
    DTW[0][0]=0;
    int value=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            value=d[i][j];
            DTW[i][j]=value+min(min(DTW[i-1][j],DTW[i][j-1]),DTW[i-1][j-1]);
            //   (i-1,j-1), (i,j-1), and (i-1,j)
            if(min(min(DTW[i-1][j],DTW[i][j-1]),DTW[i-1][j-1])==DTW[i-1][j-1]){
                walk[i][j]=make_pair(i-1,j-1);
            }else if(min(min(DTW[i-1][j],DTW[i][j-1]),DTW[i-1][j-1])==DTW[i][j-1]){
                walk[i][j]=make_pair(i,j-1);
            }else if(min(min(DTW[i-1][j],DTW[i][j-1]),DTW[i-1][j-1])==DTW[i-1][j]){
                walk[i][j]=make_pair(i-1,j);
            }
        }
    }
    ans=DTW[n][m];
    cout<<"Path: "<<endl;
    cost=0;
    nodes=0;
    double avg=walker(n,m);
    cout<<"Average: "<<avg<<endl;
    //cout<<n<<"  "<<m<<endl;
    cout<<"Total: ";
    return ans;
}

int distance_w(vector<int> x, vector<int> y,int w) {
    int n = x.size();
    int m = y.size();
    x.resize(30);
    y.resize(30);
    for(int i=n;i>0;--i){
        x[i]=x[i-1];
    }
    x[0]=0;
    for(int i=m;i>0;--i){
        y[i]=y[i-1];
    }
    y[0]=0;

    w=max(w,abs(n-m));

    d.clear();
    walk.clear();
    vector<vector<int>> DTW;
    //vector<vector<int>> d;
    DTW.resize(30);
    d.resize(30);
    walk.resize(30);
    for(int i=0;i<30;++i){
        DTW[i].resize(30);
        d[i].resize(30);            
        walk[i].resize(30);
    }

    int ans = 0;
    for(int i=0;i<=n;++i){
        for(int j=0;j<=m;++j){
            DTW[i][j]=MAX;
            d[i][j]=abs(x[i]-y[j]);
        }
    }
    DTW[0][0]=0;
    for(int i=1;i<=n;++i){
        for(int j=max(1,i-w);j<=min(m,i+w);++j){
            DTW[i][j]=0;
        }
    }

    int value=0;
    for(int i=1;i<=n;++i){
        for(int j=max(1,i-w);j<=min(m,i+w);++j){
            value=d[i][j];
            DTW[i][j]=value+min(min(DTW[i-1][j],DTW[i][j-1]),DTW[i-1][j-1]);
                        //   (i-1,j-1), (i,j-1), and (i-1,j)
            if(min(min(DTW[i-1][j],DTW[i][j-1]),DTW[i-1][j-1])==DTW[i-1][j-1]){
                walk[i][j]=make_pair(i-1,j-1);
            }else if(min(min(DTW[i-1][j],DTW[i][j-1]),DTW[i-1][j-1])==DTW[i][j-1]){
                walk[i][j]=make_pair(i,j-1);
            }else if(min(min(DTW[i-1][j],DTW[i][j-1]),DTW[i-1][j-1])==DTW[i-1][j]){
                walk[i][j]=make_pair(i-1,j);
            }
        }
    }

    ans=DTW[n][m];
    cout<<"Path: "<<endl;
    cost=0;
    nodes=0;
    double avg=walker(n,m);
    cout<<"Average: "<<avg<<endl;
    //cout<<n<<"  "<<m<<endl;
    cout<<"Total: ";
    return ans;
}


int main(){
	vector<int> X,Y;
	cout<<"test case 1"<<endl;
    //ini();
	X = {37,37,38,42,25,21,22,33,27,19,31,21,44,46,28};
	Y = {37,38,42,25,21,22,33,27,19,31,21,44,46,28,28};
    cout<<distance(X,Y)<<endl;
	///clean();
    cout<<"test case 2"<<endl;
	//ini();
    X = {11,14,15,20,19,13,12,16,18,14};
	Y = {11,17,13,14,11,20,15,14,17,14};
	cout<<distance(X,Y)<<endl;
   // clean();

    // vector<int> a,b;
    // cout<<"test case 3"<<endl;
    // //ini();
    // a={8, 9, 1 ,9, 6 ,1 ,3, 5};
    // b={2, 5, 4 ,6 ,7 ,8 ,3 ,7, 7, 2};
    // cout<<"Total: "<<distance(a,b)<<endl;
    // //clean();
    // cout<<"test case 4"<<endl;
    // //ini();
    // a={2, 0, 1, 1, 2, 4, 2, 1, 2, 0};
    // b={1, 1, 2, 4, 2, 1, 2, 0};
    // cout<<"Total: "<<distance(a,b)<<endl;
	//clean();
    //Remark: when you modify the code to add the window constraint, the distance function has thus three inputs: X, Y, and the size of window w.
	
    
    X = {37,37,38,42,25,21,22,33,27,19,31,21,44,46,28};
	Y = {37,38,42,25,21,22,33,27,19,31,21,44,46,28,28};
    cout<<distance_w(X,Y,1)<<endl;
    cout<<distance_w(X,Y,0)<<endl;
	//test case 2
	
    X = {11,14,15,20,19,13,12,16,18,14};
	Y = {11,17,13,14,11,20,15,14,17,14};
	cout<<distance_w(X,Y,1)<<endl;
    cout<<distance_w(X,Y,0)<<endl;

    // a={8, 9, 1 ,9, 6 ,1 ,3, 5};
    // b={2, 5, 4 ,6 ,7 ,8 ,3 ,7, 7, 2};
    // cout<<distance_w(a,b,2)<<endl;

    // a={2, 0, 1, 1, 2, 4, 2, 1, 2, 0};
    // b={1, 1, 2, 4, 2, 1, 2, 0};
    // cout<<distance_w(a,b,2)<<endl;
    
    
    
    return 0;
}
