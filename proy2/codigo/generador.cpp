#include<iostream>
#include<random>
using namespace std;

int main(int argc, char *argv[])
{
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<float> distribution(0.0f,20.0f);
    float x, y;
    
    if(argc != 2){
        cout<<"\t generador <num de casos a generar>"<<endl;
        exit(-1);
    }

    int n = atoi(argv[1]);
    float result;
    int dentro = n/2;
    int fuera = n-dentro;
       
    while(dentro+fuera!=0){
        x = distribution(generator);
        y = distribution(generator);

        result = pow(x-10.0f,2.0f) + pow(y-10.0f,2.0f);

        if(result > 49.0f && fuera){
            fuera--;
            cout<<x<<" "<<y<<" "<< 1 << endl;
        }else if(dentro){
            dentro--;
            cout<<x<<" "<<y<<" "<< -1 << endl;
        }
        
    }
}
