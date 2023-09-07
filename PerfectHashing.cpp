#include <bits/stdc++.h>
#include <fstream>
#define p 6669119// definimos p como el numero primo 6669119
using namespace std;
int a=7;// se define como variable global el  entero a igual a 7
int b=11;// se define como variable global el  entero b igual a 11
struct tabla{// se crea la estructura tabla
      int col, ai, bi;// se crean los valores enteros col, ai y bi
      vector<string> vec;// se crea un vector de strings llamado vec
      tabla(){// se crea el constructor de la estructura
              col=ai=bi=0;// se inicializan las varaibles col, ai y bi en 0
      }
      void darTamano(int n){// se crea la funcion darTamano
                    vec.resize(n,"%");// se llama a la funcion resize, se define el tamaño del vector como n y se llena de %
      }
      
};
int cases(char c){// funcion case que nos permite dar los casos en para codificar los genomas
    int cod=0;// se crea la variable entera cod inicializada en 0
    switch(c){// se hace un switch de casos con respecto al char c
                 case 'G':// en caso de que le char sea G
                      cod=0;// el valor de cod sera 0
                      break;// se hace break
                 case 'T':// en caso de que le char sea T
                      cod=1;// el valor de cod sera 1
                      break;// se hace break
                 case 'C':// en caso de que le char sea C
                      cod=2;// el valor de cod sera 2
                      break;// se hace break
                 case 'A':// en caso de que le char sea A
                      cod=3;// el valor de cod sera 3
                      break;// se hace break
                 default:// el caso base
                      cod=-1;// el valor de cod es -1
    }
    return cod;// se retorna el valor de cod
}
int hlv1(int k, int aj, int bj, int m){// funcion hlvl que nos retorna el valor hash
    long long ak= aj*k;// se crea la variable long long ak que tiene el valor de la variable que se entrega por argumento, aj multiplicado por k
    int h=(((ak+bj)%p)%m);// se crea la variable entera h que tiene valor igual al resultado de la ecuacion (((ak+bj)%p)%m) y representa el valor hash
    return abs(h);// se retorn el valor absoluto de la varaible h
}
set<string> kmer(){// funcion kmer que nos retorna el set de kmers de tamaño 15 del genoma
    set<string> kmers;// se crea un set de strings llamado kmers
    ifstream infile;// se crea una estructura ifstream llamada infile
    infile.open("input.txt");// se abre el archivo "input.txt"
    if(infile.fail()){// en el caso de que la estructura falle en abrir el archivo se imprime un mensaje de error
        cout<<"No se pudo abrir el archivo"<<endl;
    }else{
        string s;// se crea un string llamado s
        while(getline(infile, s)){// se inicia un ciclo while que itera hasta que el archivo se termine
            int l=s.length()-15;// se crea una variable entera l con el valor del largo del string s menos 15
            if(l>0){// condicion if donde se entra a la condicion mientras l sea mayor a 0
                for(int i=0;i<=l;i++){// se inicia un ciclo for que itera l veces
                    string k;// se crea un string llamado k
                    int cont=0;// se crea una variable entera llamada cont inicializada en 0
                    copy_n(s.begin()+i, 15, back_inserter(k));// mediante la funcion copy_n se copian los 15 valores de s en k
                    kmers.insert(k);// se inserta k en el set kmers
                }
            }
        }
    }
    return kmers;// se retorn el set de strings kmers
}
int codificar(string s){// funcion coficiar que codifica el valor de los kmers de los genomas
    int cod= cases(s[0]);// se crea la variable entera cod que tiene el valor de la funcion cases sobre el primer caracter del string s
    if(cod<0) return INT_MIN;// en el caso de que el valor de cod sea negativo, se retorna INT_MIN
    for(int i=1;i<15;i++){// se inicia un ciclo for que itera 14 veces
        cod = (cod<<2)| cases(s[i]);// el valor de cod va a ser el valor entero de la concatenacion de los valores binarios definidos en la funcion cases
    }
    return cod;// se retorna el valor cod, que el el valor codificado del kmer del genoma
}
vector<tabla> DoHash1(set<string> s,int a, int b){// funcion DoHash1 que verifica la cantidad de colisiones que ocurren en el vector de tablas
              vector<tabla> v(s.size());// se crea un vector de estructuras tabla, de tamaño igual al tamaño del set de strings ingresado por parametro
              for(auto it = s.begin(); it !=s.end(); ++it){// ciclo for que itera por el tamaño del set de strings s
                  v[hlv1(codificar(*it),a,b,s.size()-1)].col++;// se aumenta las coliciones de la tabla que se encuentra en la posicion dada por el hash
              }
              return  v;// se retorn el vector v
}
/*
funcion getAB que obtiene los valores de a y b para los cuales no hay colisiones internas y la tabla correcta con la suma de los cuadrados de colisiones menor a la cota * n
*/
vector<tabla> getAB(set<string> s, int n){
     int colisiones= INT_MAX;// se crea una variable entera llamada colisiones y se inicializa con el valor INT_MAX
     int cont=0;// se crea una variable entera llamada cont
     vector<tabla> final;// se crea un vector de tablas llamado final
     while(colisiones>n*s.size()){// se inicia un ciclo while que itera mientras colisiones sea mayor que n multiplicado por el tamaño de s, ambos valores entregados por parametro
         colisiones=0;// se le da el valo de 0 a la variable colisiones
         a=1+rand()%p;// se modifica a para que tenga un valor aleatorio entre 1 y p
         b=1+rand()%p;// se modifica b para que tenga un valor aleatorio entre 1 y p
         vector<tabla> v=DoHash1(s,a,b);// se crea un vector de tablas llamado b el cual sera igual al resultado de la funcion DoHash1 sobre los parametros s, a y b respectivamente
         for (auto it = v.begin(); it !=v.end(); ++it){// se inicia un ciclo for que itera por el tamaño de v
             int aux=it->col;// se crea una variable entera aux que tiene el mismo valor que la variable col de v
             aux*=aux;// se multiplica aux por si mismo
             colisiones+=aux;// se le suma el valor de aux al valor de colisiones
         }
         if(colisiones<=n*s.size())final=v;// si la variable colisiones es menos o igual a n por el tamaño de s, el vector final sera igual al vector v
         cont++;// se aumenta el valor de cont
    //     cout<<"la cantidad de veces que se ejecuta es: "<<cont<<endl;
    //imprimimos la cantidad segun lo pedido en el enunciado para poder obtener el numero de elementos*
    }
    return final;// se retorna el vector de tablas final
}
/*
funcion getAiBi que ordena y verifica de tal manera que la tabla no tenga colisiones, mediante expansion de las tablas y manejo de clustering
*/
void getAiBi(vector<tabla> &v){
    int repeticiones =0; 
    for(auto it = v.begin(); it !=v.end(); ++it){// se inicia un ciclo for que recorre el tamaño del vector v
        if(it->col>1){// condicion en la que entra so el entero col asociado a v es mayor a 1
             int colisiones=1;// se crea la variable netera colisiones inicializada en 1
             vector<string> vaux=it->vec;// se crea un vector de strings vaux que es igual al vector vec de v
             it->darTamano(pow(it->col,2));// se llama a la funcion darTamano de v para darle tamaño a la potencia cuadrada de la variable col de v
             while(colisiones>0){// se inicia un ciclo while que itera mientras la variable colisiones sea mayor a 0
                 repeticiones++;
                 fill(it->vec.begin(),it->vec.end(),"%");// se llama a la funcion fill, donde se llena el vector vec con el simbolo %
                 colisiones=0;// se le da el valor 0 a la varaible colisiones
                 it->ai=rand()%p;// se modifica ai para que tenga un valor aleatorio entre 1 y p
                 it->bi=rand()%p;// se modifica bi para que tenga un valor aleatorio entre 1 y p
                 for (auto iter = vaux.begin(); iter !=vaux.end(); ++iter){// se inicia un ciclo for que recorre el tamaño del vector vaux
                     int hashpos=hlv1(codificar(*iter),it->ai,it->bi,it->vec.size());// se crea la variable entera hasshpos que tiene el valor hash del valor codificado del genoma
                     if(it->vec[hashpos]!="%"){// condicion que entra en el caso de que el vector en la posicion hashpos sea distinto a %, osea que este ocupado
                          colisiones=1;// se de la el valor 1 a la variable colisiones
                          break;// se rompe el ciclo for
                     }else it->vec[hashpos]=*iter;// en caso contrario a la condicion anterior el valor de vec en la posicion hashpos sera el valor del puntero a iter
                 }
             }
         }
     }
     //cout<<"repeticiones AiBi: "<<repeticiones<<endl; eliminar comentario si se desea hacer el analisis, este imprime la cantidad total de repeticiones de AiBi 
}
bool find(vector<tabla> v, string s, int n){// funcion find que busca un genoma especifico en las tablas
     cout<<"Buscando el elemento "<<s<<endl;// se imprime un mensaje para que le usuario entienda que se esta buscando el elemento s entregado por parametro
     int aux=hlv1(codificar(s),a,b,n-1);// se crea una variable entera aux con el valor de hash del valor codificado del string s
     if(v[aux].vec.size()==1){// condicion donde se entra en el caso de que el tamaño del vector de la tabla en la posicion aux de v sea igual a 1
         if(v[aux].vec[0]==s){// condicion donde se entra en el caso de que el string en la primera posicion del vector vec de la tabla en la posicion aux de v sea igual al string s
             return true;// en caso de entrar a la condicion se retorna true indicando que se encontro el genoma buscado
         }else return false;// caso contrario se retorna false
     }else if(v[aux].vec.size()>1){// condicion opuesta en caso de que el tamaño del vector de la tabla en la posicion aux de v sea mayor a 1
         if(v[aux].vec[hlv1(codificar(s),v[aux].ai,v[aux].bi,v[aux].vec.size())]==s){// condicion donde se entra en el caso de que el string en la posicion del valor de hashing del
                                                                                    // valor codificado de s del vector vec de la tabla en la posicion aux de v sea igual al string s
             return true;// en caso de cumplirse la condicion se retorna true
         }else return false;//caso contrario se retorna false
     }else return false;// en caso de que no se cumpla ninguna de las condiciones anteriores se retorna false indicando que el genoma buscado no se encuentra en el archivo
}
void assignBuckets(set<string> &s, vector<tabla> &v){// funcion assignBuckets que indica en que bucket debe ir cada vector de tablas para evitar colisiones
     for (auto it = s.begin(); it !=s.end(); ++it){// se inicia un ciclo for que recorre el set de strings s
         int aux=hlv1(codificar(*it),a,b,s.size()-1);// se crea la variable entera aux que tiene el valor del hashing del valor codificado del iterador de s
         if(v[aux].col>=1){// condicion en la cual entra si el valor de la variable col de v en la posicion aux es mayor o igual a 1
              v[aux].vec.push_back(*it);// se hace push_back del valor del iterador se s sobre el vector vec de la tabla en la posicion aux de v
         }
     }
     getAiBi(v);// se llama a la funcion getAiBi con parametro el vector de tablas v
}
int contarColisiones(vector<tabla> v){
    int cont=0;
     for (auto it = v.begin(); it !=v.end(); ++it){
         if(it->col>1){
             cont+=it->col-1;
         }
     }
     return cont;
}
void analisisEspacio(vector<tabla> v){
    long long cont=0;
     for (auto it = v.begin(); it !=v.end(); ++it){
         cont+=sizeof(it->vec)+(3*sizeof(it->col));
     }
     cout<<"el tamano de la estructura es: "<<cont<<endl;
}
int main(){
    srand(time(NULL));
    vector<tabla>v;
    set<string> kmers=kmer();
    int maxcol;
    cout<<"inserte la cota de espacio de los buckets por favor"<<endl;
    cin>>maxcol;
    //double tiempoCrear=0,tiempoBuscar=0;
    //auto startC = chrono::high_resolution_clock::now();
    v=getAB(kmers,maxcol);
    assignBuckets(kmers, v);
    //auto finishC = chrono::high_resolution_clock::now();
    //tiempoCrear=chrono::duration_cast<chrono::nanoseconds> (finishC - startC).count();
    //cout<<"tiempo creacion: "<<tiempoCrear<<endl;
    //auto startB = chrono::high_resolution_clock::now();
    //bool x=find(v,kmers.begin(),kmers.size());
    //auto finishB = chrono::high_resolution_clock::now();
    //tiempoBuscar=chrono::duration_cast<chrono::nanoseconds> (finishB - startB).count();
    //cout<<"tiempo Busqueda: "<<tiempoBuscar<<endl;
    //analisisEspacio(v);
    //cout<<"La cantidad de colisiones es: "<<contarColisiones(v)<<endl;
    string genoma="";
    while(1){
        cout<<"inserte el genoma a buscar o escriba '0' si desea terminar el programa"<<endl;
        cin>>genoma;
        if(genoma=="0") break;
        if(find(v,genoma,kmers.size())){
             cout<<"Encontrado"<<endl;          
        }else cout<<"No encontrado"<<endl;
    }
    kmers.clear();
    v.clear();
    
    return 0;
}
