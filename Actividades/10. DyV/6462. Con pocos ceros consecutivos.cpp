#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

unordered_map<int,ll> resultados;

ll cadenasCon3Ceros(int n){
    if(resultados.find(n) != resultados.end()){
        return resultados[n];
    }

    if(n<=2)    return 0;
    if(n==3)    return 1;

    resultados[n] = cadenasCon3Ceros(n-1)+cadenasCon3Ceros(n-2)+cadenasCon3Ceros(n-3) + pow(2,n-3);

    return resultados[n];
}

ll cantCerosConsecutivos(int n){
    return pow(2,n) - cadenasCon3Ceros(n);
}

int main(){
    int n;
    cin >> n;

    cout << cantCerosConsecutivos(n) << "\n";

    return 0;
}