#include<iostream>
#include<vector>
#include<random>
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

   int solved = 0;;
   float error;
   int it = 0;
   while(solved != ejemplos.size()){
      for(int i=0;i<delta.size();++i){
	 delta[i] = 0.0f;
      }
      error = 0.0f;
      solved = 0;
      for(int i=0;i<ejemplos.size();++i){
	 float o = resolver(ejemplos[i].first);
	 if(o == ejemplos[i].second) ++solved;
	 for(int j=0;j<pesos.size();++j){
	    delta[j] += tasa*(ejemplos[i].second - o)*ejemplos[i].first[j];
	    error += (ejemplos[i].second - o) * (ejemplos[i].second - o);
	 }
      }
      for(int i=0;i<pesos.size();++i){
	 pesos[i] += delta[i];
      }
      cout << it++ << "   " << error/2.0f << endl;
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

   vector<float> delta(pesos);

   for(int i=0;i<pesos.size();++i){
      pesos[i] = distribution(generator);
   }

   int solved = 0;
   float error,last_error;
   error = 0.0f;
   last_error = 1.0f;
   int it = 1;
   while(error != last_error){
      last_error = error;
      error = 0.0f;
      for(int i=0;i<delta.size();++i){
	 delta[i] = 0.0f;
      }
      solved = 0;
      for(int i=0;i<ejemplos.size();++i){
	 float o = resolver(ejemplos[i].first);
	 if(o == ejemplos[i].second) ++solved;
	 for(int j=0;j<pesos.size();++j){
	    delta[j] += (tasa/it)*(ejemplos[i].second - o)*ejemplos[i].first[j];
	    error += (ejemplos[i].second - o) * (ejemplos[i].second - o);
	 }
      }
      for(int i=0;i<pesos.size();++i){
	 pesos[i] += delta[i];
      }
      cout << it++ << "   " << error/2.0f << endl;
   }
}

//*******************FIN DE LA NEURONA*********************
