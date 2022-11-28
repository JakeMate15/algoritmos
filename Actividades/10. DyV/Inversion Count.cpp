#include<bits/stdc++.h>

#define pb push_back

using namespace std;

typedef long long ll;

ll conteoDivididas(int a[], int aux[], int inferior, int mitad, int superior){
    int k = inferior, i = inferior, j = mitad+1;
    ll conteoInversiones = 0;

    while(i<=mitad && j<=superior){
        if(a[i]<=a[j]){
            aux[k++] = a[i++];
        }
        else{
            aux[k++] = a[j++];
            conteoInversiones+= (mitad-i+1);
        }
    }

    while(i<=mitad){
        aux[k++] = a[i++];
    }

    for(int i = inferior; i<=superior; i++){
        a[i] = aux[i];
    }

    return conteoInversiones;
}

ll conteoInversiones(int a[], int aux[], int inferior, int superior){
    if(superior<=inferior)  return 0;

    int mitad = (inferior+superior)/2;
    ll invIzq = conteoInversiones(a,aux,inferior,mitad);
    ll invDer = conteoInversiones(a,aux,mitad+1,superior);
    ll conteoDiv = conteoDivididas(a,aux,inferior,mitad,superior);

    return invDer + invIzq + conteoDiv;
}

void sol(){
    int n; 

    cin >> n;
    int numeros[n];
    int aux[n];

    for(int i=0; i<n; i++){
        cin >> numeros[i];
        aux[i] = numeros[i];
    }

    cout << conteoInversiones(numeros,aux,0,n-1) << "\n";


}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while(t--){
        sol();
    }

    return 0;
}