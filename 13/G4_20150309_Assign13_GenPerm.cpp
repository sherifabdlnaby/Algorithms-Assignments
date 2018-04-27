// GROUP:   4
// ID:      20150309
// Assign:  13
// Assign:  GenPerm
// UVA:     216
// Name:    Sherif Abdel-Naby
// UVA Username: sherifabdlnaby

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>      // use built-in sqrt()
#include <iostream>
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_COMPUTERS 8

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point{int x,y;};
double Dist(Point& a, Point& b){ return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// number of computers (input)
int		n;

// locations of computers (input)
Point	com[MAX_COMPUTERS];

// dist[i][j]=distance from com[i] to com[j] (pre-computed)
double	dist[MAX_COMPUTERS][MAX_COMPUTERS];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// best value until now
double best_val = INT32_MAX;

// best solution until now (a permutation)
int	best_sol[MAX_COMPUTERS];

// s is current permutation. s[i]=index of the ith computer in this permutation.
int	s[MAX_COMPUTERS];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// evaluate the permutation s, then update best_val and best_sol if necessary
void UpdateSol(){
    double currDist = 0 ;

    //calculate permutation distance
    for(int i = 0; i < n-1; ++i)
        currDist += dist[s[i]][s[i+1]];

    //minimize
    if(currDist < best_val)
    {
        // update best value;
        best_val = currDist;

        // save new sol;
        for(int i = 0; i < n; i++)
            best_sol[i] = s[i];
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// backtrack using swaps
void Backtrack0(int i){
    // base case;
    if(i == n)
        UpdateSol();
    else
    {
        for (int j = i; j < n; ++j) {
            swap(s[i], s[j]);
            Backtrack0(i+1);
            swap(s[i], s[j]);
        }
    }
    return;
}

// do necessary initializations and call Backtrack0()
void Compute0()
{
    //initialize;
    for(int i = 0; i < n; ++i)
        s[i] = i;

    Backtrack0(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// v[i] = true if com[i] already taken in the permutation
bool v[MAX_COMPUTERS];

// backtrack using the v[] array
void Backtrack1(int i){
    if(i == n)
    {
        UpdateSol();
    }
    else {
        for (int j = 0; j < n; ++j)
        {
            if (v[j])
                continue;

            s[i] = j;

            v[j] = true;

            Backtrack1(i + 1);

            v[j] = false;
        }
    }
}

// do necessary initializations and call Backtrack1()
void Compute1(){
    // initialize
    for(int i = 0; i < n; ++i)
        v[i] = false;

    Backtrack1(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Dancing Links:
int F[MAX_COMPUTERS+1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_COMPUTERS+1]; // B[0]=n, B[1]=0
void Remove(int i) {F[B[i]]=F[i]; B[F[i]]=B[i];}
void Restore(int i) {B[F[i]]=i; F[B[i]]=i;}
void InitDancingLinks(int n)
{
	int i;
	for(i=0;i<n;i++)
        F[i]=i+1; F[n]=0;
	for(i=n;i>0;i--)
        B[i]=i-1; B[0]=n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// backtrack using dancing links
void Backtrack2(int i){
    if(i == n)
        UpdateSol();
    else
    {
        int idx = F[0];
        while(idx != 0)
        {
            Remove(idx);
            s[i] = idx-1;
            Backtrack2(i+1);
            Restore(idx);

            //iterate
            idx = F[idx];
        }
    }
    return;
}

// do necessary initializations and call Backtrack2()
void Compute2(){
    InitDancingLinks(n);
    Backtrack2(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComputeCore()
{
	// do necessary initializations of dist[][] and best_val

    //INT_MAX as we're minimizing;
    best_val = 0x7FFFFFFF;


    //calculate dist[][]
    for (int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            dist[i][j] = Dist(com[i], com[j]) + 16.0f;


	Compute0();
	//Compute1();
	//Compute2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// get input and then call ComputeCore(); then print output
void Compute(){
    int t = 0;
    cin >> n;
    while(n != 0)
    {
        //INPUT
        for(int i = 0; i < n; ++i)
            cin >> com[i].x >> com[i].y;

        //COMPUTE
        ComputeCore();

        //OUTPUT
        cout << "**********************************************************" << endl;
        cout << "Network #" << ++t << endl;
        for(int i = 0; i < n-1; ++i)
        {
            Point a = com[best_sol[i]];
            Point b = com[best_sol[i+1]];
            cout << "Cable requirement to connect (" << fixed << setprecision(2) << a.x << "," << a.y
                 << ") to (" << b.x << "," << b.y << ") is "
                 << dist[best_sol[i]][best_sol[i+1]] << " feet." << endl;
        }
        cout << fixed << setprecision(2) << "Number of feet of cable required is " << best_val << "." << endl;

        //new testcase
        cin >> n;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign13_00216.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
