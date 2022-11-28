#include<stdio.h>

using namespace std;

int maxSum(int A[], int n){
    int maxF = INT_MIN, maxEH = 0;

    for(int i=0; i<n; i++){
        maxEH = maxEH + a[i];

        if(maxF < maxEH)    maxF = maxEH;
        if(maxEH < 0)   maxEH = 0;

    }

    return maxF;
}


int main(){
    int n, numeros res;

    cin >> n;
    numeros = new int[n];

    for(int i=0; i<n; i++){
        cin >> numeros[i];
    }
    
    cout << maxSum(numeros,n) << "\n";

    return 0;
}