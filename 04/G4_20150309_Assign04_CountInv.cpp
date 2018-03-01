// GROUP:   4
// ID:      20150309
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    SHERIF MOHAMED ABDEL-NABY

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInvMerge(long long* a, int n) {
	long long cpyArr[n];
	int mid = n/2;
	int i = 0;
	int j = mid;
    long long count = 0;

	for (int k = 0; k < n; ++k) {
		if (j > n-1)
			cpyArr[k] = a[i++];
		else if (i >= mid)
			cpyArr[k] = a[j++];
		else if (a[i] <= a[j])
			cpyArr[k] = a[i++];
		else if (a[i] > a[j]) {
            //Inversion found! (ElseIf condition unnecessary, just for Illustration)
			count += mid - i;
			cpyArr[k] = a[j++];
		}
	}

	//Copying back to Original Array...
    long long x = 0;
	for (int l = 0; l < n; ++l) {
		a[x++] = cpyArr[l];
	}

	return count;
}

long long CountInv(long long* a, int n) {
	if (n <= 1)
		return 0;
    int mid = n/2;
	long long x = CountInv(a, mid);			//Right side inner inversions count
	long long y = CountInv(a + mid,  mid + (n%2));       //Left side inner inversions count
	long long z = CountInvMerge(a, n);    		        //Inversions count between the two sides.
	return x + y + z;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int n;
    cin >> n;
    while(n)
    {
        long long arr[n];

        for (int i = 0; i < n; ++i)
            cin >> arr[i];

        cout << CountInv(arr, n) << endl;

        cin >> n;
    }


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
