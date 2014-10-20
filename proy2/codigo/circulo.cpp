#include "RedNeural.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){

    // primero argumento es la cantidad de ejemplos para entrenar y
    // despues la cantidad de neuronas de la capa intermedio
    // un ejemplo de corrida es
    // cat ../input/datos_generados_n500.txt ../input/datos_generados_n10.txt | ./circulo.out 500 2
    
    int n = atoi(argv[2]);
    RedNeural red(2,n,1);

    n = atoi(argv[1]);
    
    double x,y;
    int result;
    double** input;
    double** target;

    input = Utilities::crearMatriz(n,2);
    target = Utilities::crearMatriz(n,1);
        
    for(int i=0;i<n;i++){
        
        if(scanf("%lf %lf %i", &x, &y, &result)!=3){
            cout<<"nope"<<endl;
        }else{

            input[i][0] = x;
            input[i][1] = y;

            target[i][0] = result;
                         
        }

    }
    
    double tasa;
    sscanf(argv[3],"%lf",&tasa);
    red.aprender(input,target,tasa,n);

    //aqui el hace una prueba con los 10 ultimos elementos del conjunto
    //estos 10 no se usan para entrenar

    free(input);
    free(target);

    input = Utilities::crearMatriz(1,2);
    target = Utilities::crearMatriz(1,1);

    float correct =0;
    int tot=0;
            
    ofstream salida;
    salida.open("output.output");
    while(scanf("%lf %lf %i", &x, &y, &result)==3){ 

            input[0][0] = x;
            input[0][1] = y;

            double* temp = red.resolver(input[0]);
                        
            salida << x <<" "<< y <<" "<<(temp[0] < 0.5 ? -1 : 1)<<endl;
            
            (temp[0] < 0.5 ? -1 : 1) == result ? correct++ : correct;
            
            tot++;
            
        }

    cout <<"\t" << correct/tot << endl;
    
        
}

    
