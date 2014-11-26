#include "RedNeural.h"
#include <fstream>
#include <map>
using namespace std;

typedef map<char,int> Dict;
//typedef Dict::const_iterator It;

int main(int argc, char *argv[]){

    Dict d;

    d['s']=1;
    d['a']=2;
    d['l']=3;
        
    // el primero argumento es la cantidad de ejemplos para entrenar y
    // despues la cantidad de neuronas de la capa intermedio
    // un ejemplo de corrida es
    // cat <datos para entrenar> <datos para probar> | ./circulo.out <# de datos para entrenar> <# de neuronas>
    
    int n = atoi(argv[2]);
    RedNeural red(2,n,1);

    n = atoi(argv[1]);
    
    double x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14;
    int result;
    double** input;
    double** target;
    double welp;
    char p,e;
    

    
    input = Utilities::crearMatriz(n,2);
    target = Utilities::crearMatriz(n,1);
        
    for(int i=0;i<n;i++){

        cout << scanf("%c %lf %lf %lf %lf %lf %lf %c %lf %lf %lf %lf %i",
                      &p,&x2,&x3,&x4,&x5,&x6,&x7,&e,&x9,&x10,&x11,&x12,&result)<<endl;
        cout<<p<<":"<<d[p]<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<x5<<" "<<x6<<" "<<x7<<" "<<e<<":"<<d[e]<<" "<<x9<<" "<<x10<<" "<<x11<<" "<<x12<<" => "<<result<<endl;
        
        
//        if(scanf("%lf %lf %i %lf", &x, &y, &result, &welp)!=4){
        if(scanf("%c %lf %lf %lf %lf %lf %lf %c %lf %lf %lf %lf %lf %lf %i",
                 &p,&x2,&x3,&x4,&x5,&x6,&x7,&e,&x9,&x10,&x11,&x12,&x13,&x14,&result)!=15){
            cout<<"nope"<<endl;
        }else{
            
            cout<<p<<":"<<d[p]<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<x5<<" "<<x6<<" "<<x7<<" "<<e<<":"<<d[e]<<" "<<x9<<" "<<x10<<" "<<x11<<" "<<x12<<" "<<x13<<" "<<x14<<" => "<<result<<endl;

            input[i][0] = d[p];
            input[i][1] = x2;
            input[i][2] = x3;
            input[i][3] = x4;
            input[i][4] = x5;
            input[i][5] = x6;
            input[i][6] = x7;
            input[i][7] = d[e];
            input[i][8] = x9;
            input[i][9] = x10;
            input[i][10] = x11;
            input[i][11] = x12;
            input[i][12] = x13;
            input[i][12] = x14;            

            cout<<"\t";
            for(int j=0;j<14;j++)
                cout<<input[i][j]<<" ";
            cout<<endl;
            
            target[i][0] = result;

        }

    }
    
//     double tasa;
//     sscanf(argv[3],"%lf",&tasa);
//     red.aprender(input,target,tasa,n);

//     //aqui el hace una prueba con los 10 ultimos elementos del conjunto
//     //estos 10 no se usan para entrenar

//     free(input);
//     free(target);

//     input = Utilities::crearMatriz(1,2);
//     target = Utilities::crearMatriz(1,1);

//     float correct =0;
//     int tot=0;
    
//     ofstream salida;
//     salida.open("output.output");
//     // while(scanf("%lf %lf %i %lf", &x, &y, &result,&welp)==4){ 
//     while(scanf("%lf %lf %i", &x, &y, &result)==3){ 
//             input[0][0] = x;
//             input[0][1] = y;

//             double* temp = red.resolver(input[0]);
                        
//             salida << x <<" "<< y <<" "<<(temp[0] < 0.5 ? -1 : 1)<<endl;
            
//             (temp[0] < 0.5 ? -1 : 1) == result ? correct++ : correct;
            
//             tot++;
            
//         }

//     cout <<"\t" << correct/tot << endl;       
}