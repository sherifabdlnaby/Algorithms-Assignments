// GROUP:   4
// ID:      20150309
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name1:   SHERIF ABDEL-NABY
// UVA Username: Sherifabdlnaby

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cmath>     // please use the built-in sqrt() function
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
	Type cpyArr[n];
	int mid = n/2;
	int i = 0;
	int j = mid;

	for (int k = 0; k < n; ++k) {
		if (j > n-1)
			cpyArr[k] = a[i++];
		else if (i >= mid)
			cpyArr[k] = a[j++];
		else if (IsBefore(a[i], a[j]))
			cpyArr[k] = a[i++];
		else
			cpyArr[k] = a[j++];
	}

	//Copying back to Original Array...
	int x = 0;
	for (int l = 0; l < n; ++l) {
		a[x++] = cpyArr[l];
	}

	return;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
	if (n <= 1)
		return;
	int mid = n/2;
	MergeSort(a, mid, IsBefore);
	MergeSort(a + mid,  mid + (n%2), IsBefore);
	Merge(a, n, IsBefore);
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point{ double x,y; };
bool IsBeforeX(Point& a, Point& b){ return a.x < b.x; };
bool IsBeforeY(Point& a, Point& b){ return a.y < b.y; };;
double dist(Point& a, Point& b){ return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n){
    if(n == 1)
        return 80000;   //Anything > 10000 to lead to INF.

    if(n == 2)
        return dist(p[0], p[1]);

    if(n == 3)
        return min(dist(p[0], p[1]), min(dist(p[0], p[2]),dist(p[1], p[2])));

    int mid = n/2;
    double rightSection = ClosestPair(p, mid);
    double leftSection  = ClosestPair(p + mid , n - mid);
    double minDistance = std::min(rightSection, leftSection);

    //create the strip
    Point* strip = new Point[n];
    int stripSize = 0;
    for (int i = 0; i < n; ++i)
        if(abs(p[i].x - p[mid].x) < minDistance)
            strip[stripSize++] = p[i];

    //Sort strip according to Y
    MergeSort(strip, stripSize, IsBeforeY);

    double stripMin = minDistance;
    for (int i = 0; i < stripSize; ++i)    // Proven to only check at max 7 iterations.
        for (int j = i+1; j < stripSize && (strip[j].y - strip[i].y) < stripMin; ++j)
                stripMin = min(stripMin , dist(strip[i], strip[j]));

    delete[] strip;

    return std::min(stripMin, minDistance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    cin >> n;
    while(n != 0) {
        Point *points = new Point[n];
        double xt, yt;
        for (int i = 0; i < n; ++i) {
            cin >> xt >> yt;
            points[i] = {xt, yt};
        }

        MergeSort(points, n, IsBeforeX);

        double distance = ClosestPair(points, n);

        if(distance < 10000)
            cout << fixed << setprecision(4) << distance << endl;
        else cout << ("INFINITY") << endl;

        delete[] points;

        //New testcase
        cin >> n;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
