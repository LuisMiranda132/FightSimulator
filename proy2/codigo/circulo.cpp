#include "RedNeural.h"

int main(int argc, char *argv[]){

    // primero argumento es la cantidad de ejemplos para entrenar y
    // despues la cantidad de neuronas de la capa intermedio
    // un ejemplo de corrida es
    // cat ../input/datos_generados_n500.txt ../input/datos_generados_n10.txt | ./circulo.out 500 2
    
    int n = atoi(argv[1]);
    double x,y;
    int result;
    // vector<ejemplo2> input, prueba;
    double** input;
    double** target;

    input = Utilities::crearMatriz(n,2);
    target = Utilities::crearMatriz(n,1);
    
//    cout<<"Cargando los ejemplos..." << endl;
        
    for(int i=0;i<n;i++){
        // ejemplo2 in;
        
        if(scanf("%lf %lf %i", &x, &y, &result)!=3){
            cout<<"nope"<<endl;
        }else{
            // in.first.push_back(x);
            // in.first.push_back(y);

            input[i][0] = x;
            input[i][1] = y;

            target[i][0] = result;
                         
            // in.second.push_back(result);

            // input.push_back(in);
        }

//        cout<<input[i][0]<<" , "<<input[i][1]<<" = "<<target[i][0]<<endl;
    }
    
    // vector<double> pesos2, pesosN;
    n = atoi(argv[2]);
    // capa capaInterna,capaOutput;
    // vector<capa> capas;
    
    // pesos2.push_back(0.0);
    // for(int i=0;i<2;++i)
    //     pesos2.push_back(0.0);
    
    // pesosN.push_back(0.0);
    // for(int i=0;i<n;++i){
    //     pesosN.push_back(0.0);
    //     capaInterna.push_back(new Sigmoidal(pesos2));
    // }

    // capaOutput.push_back(new Adaline(pesosN));

    // capas.push_back(capaInterna);
    // capas.push_back(capaOutput);

    // RedNeural red(capas);

    RedNeural red(2,n,1);
    
    // cout<<"done!"<<endl;
    // cout<<"Aprendiendo..."<< endl;
    //red.aprender(input,0.1);
    red.aprender(input,target,0.1,500);
    // cout<<"done!"<<endl;

    //aqui el hace una prueba con los 10 ultimos elementos del conjunto
    //estos 10 no se usan para entrenar
    
    // for(int i=0;i<10;++i){
    //     ejemplo2 in;
        
    //     if(scanf("%lf %lf %i", &x, &y, &result)!=3){
    //         cout<<"nope"<<endl;
    //     }else{            
           
    //         in.first.push_back(1.0);
    //         in.first.push_back(x);
    //         in.first.push_back(y);

    //         in.second.push_back(result);

    //         salida s1 = red.resolver(in.first);

    //         cout<<s1[s1.size()-1][0]<<" = "<<in.second[0]<<endl;
    //     }
    // }
        
}

    
