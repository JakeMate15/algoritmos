#include<bits/stdc++.h>


using namespace std;
typedef pair<float,float> punto;

float dist2Puntos(punto p1, punto p2){
    return sqrt(
                pow(p1.first-p2.first,2) +
                pow(p1.second-p2.second,2)
            );
}

bool ordPorY(const punto &a, const punto &b){
    return (a.second < b.second);
}

float masCercanosLineaCentral(punto puntos[], int n, float d){
    float min = d;
    float dist;

    sort(puntos,puntos+n,ordPorY);
    
    for(int i=0; i<n; ++i){
        for(int j=i+1; j<n && (puntos[j].second - puntos[i].second) < min; ++j){
            dist = dist2Puntos(puntos[i],puntos[j]);
            if( dist<min ){
                min = dist;
            }
        }
    }

    return min;
}

float particion(punto puntos[], int n){

    if(n<=3){
        float min = FLT_MAX;
        float distMin;

        for(int i = 0; i<n; i++){
            for(int j=i+1; j<n; j++){
                distMin = dist2Puntos(puntos[i],puntos[j]);
                if(distMin < min)   min = distMin;
            }
        }

        return min;
    }

    int mitad = n/2;
    punto puntoMedio = puntos[mitad];

    float cumuloIzq = particion(puntos,mitad);
    float cumuloDer = particion(puntos+mitad,n-mitad);

    float dMin = min(cumuloDer,cumuloIzq);

    punto puntosX[n];
    int j = 0;
    for(int i=0; i<n; i++){
        if(abs(puntos[i].first - puntoMedio.first) < dMin){
            puntosX[j] = puntos[i];
            j++;
        }
    }

    return min(dMin,masCercanosLineaCentral(puntosX,j,dMin));
}


float estrellasMasCercanas(punto puntos[], int n){
    sort(puntos,puntos+n);

    return particion(puntos,n);
}


int main(){
    int n;
    float x,y;

    cin >> n;
    punto puntos[n];

    
    for(int i=0; i<n; i++){
        cin >> x >> y;
        puntos[i].first = x;
        puntos[i].second = y;
    } 

    cout << setprecision(3) << fixed;
    cout << estrellasMasCercanas(puntos,n) << endl;

    return 0;
}