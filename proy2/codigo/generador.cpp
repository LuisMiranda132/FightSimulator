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

    // for(int x=0;x<21;x++){
    //     for(int y=0;y<21;y++){
    //         result = (x-10.0f)*(x-10.0f) + (y-10.0f)*(y-10.0f);    
    //         if(result==49)
    //             cout<<x<<" "<<y<<" "<< -1 <<" "<< result << endl;
    //     }
    // }
    
    while(dentro+fuera!=0){
        x = distribution(generator);
        y = distribution(generator);

        result = (x-10.0f)*(x-10.0f) + (y-10.0f)*(y-10.0f);
        //cout<<result;
                
        if(result > 49.0f && fuera){
            fuera--;
            //cout<<"\t"<<1<<endl;
            cout<<x<<" "<<y<<" "<<  1 <<" "<<endl;//<< result << endl;
        }else if(result <= 49.0f && dentro){
            dentro--;
            //cout<<"\t"<<-1<<endl;
            cout<<x<<" "<<y<<" "<< -1 <<" "<<endl;//<< result << endl;
        }
        
    }
}
