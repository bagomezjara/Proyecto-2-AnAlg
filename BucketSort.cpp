#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void bucketSort(int arr[], int n){
    vector<int> v[10];
    for(int i=0;i<n;i++){
        int temp=(arr[i]-1)/10;
        v[temp].push_back(arr[i]);
    }
    for(int i=0;i<10;i++){
        sort(v[i].begin(),v[i].end());
    }
    int cont=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<v[i].size();j++){
            arr[cont++]=v[i][j];
        }
    }
}

int main(){
    cout<<"Ingrese la cantidad de elementos: ";
    int n;
    cin>>n;
    cout<<"Ingrese "<<n<<" numeros enteros en el rango de 1 a 100: ";
    int arr[5];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    bucketSort(arr,n);

    cout<<"El arreglo ordenado es: "<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<< " ";
    }
    return 0;
}
