#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
using namespace std;

//Typedef para los ejemplos
typedef pair< vector<float> ,float > ejemplo;


//****************CLASE PERCEPTRON**************
class Perceptron{
   public:
      vector<float> pesos;
      Perceptron(vector<float> w): pesos(w) {}
      void aprender(vector<ejemplo>, float);
      float resolver(vector<float>);
};

float Perceptron::resolver(vector<float> input){
   float output = 0;
   for(int i=0;i<input.size();++i){
      output += pesos[i] * input[i];
   }
   if(output > 0) return 1;
   else return -1;
}

void Perceptron::aprender(vector<ejemplo> ejemplos, float tasa){
   random_device rd;
   default_random_engine generator(rd());
   uniform_real_distribution<float> distribution(0.0f,1.0f);

   vector<float> delta(pesos);

   for(int i=0;i<pesos.size();++i){
      pesos[i] = distribution(generator);
   }

   int solved = 0;
   float t_e;
   int it = 0;
   while(solved != ejemplos.size()){
      solved = 0;
      t_e = 0.0f;
      for(int i=0;i<ejemplos.size();++i){
	 float o = resolver(ejemplos[i].first);
	 float e = ejemplos[i].second - o;
	 if(o == ejemplos[i].second) ++solved;
	 for(int j=0;j<pesos.size();++j){
	    pesos[j] += tasa*e*ejemplos[i].first[j];
	 }
	 t_e += e*e;
      }
      t_e /= 2.0f;
      cout << it++ << "   " << t_e << endl;
   }
}

//*******************FIN DEL PERCEPTRON*********************

//****************CLASE NEURONA**************
class Neurona{
   public:
      vector<float> pesos;
      Neurona(vector<float> w): pesos(w) {}
      void aprender(vector<ejemplo>, float);
      float resolver(vector<float>);
};

float Neurona::resolver(vector<float> input){
   float output = 0;
   for(int i=0;i<input.size();++i){
      output += pesos[i] * input[i];
   }
   return output;
}

void Neurona::aprender(vector<ejemplo> ejemplos, float tasa){
   random_device rd;
   default_random_engine generator(rd());
   uniform_real_distribution<float> distribution(0.0f,1.0f);

   for(int i=0;i<pesos.size();++i){
      pesos[i] = distribution(generator);
   }

   float t_e = 15.0f;
   int it = 1;
   while(abs(t_e) > 14.694f){
      t_e = 0.0f;
      for(int i=0;i<ejemplos.size();++i){
	 float o = resolver(ejemplos[i].first);
	 float e = (ejemplos[i].second - o);
	 for(int j=0;j<pesos.size();++j){
	    pesos[j] += tasa*e*ejemplos[i].first[j];
	 }
	 t_e += e*e;
      }
      t_e /= 2.0f;
      cout << it++ << "   " << t_e << endl;
   }
}

//*******************FIN DE LA NEURONA*********************
