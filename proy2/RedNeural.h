#include "Neurona.h"
using namespace std;

typedef vector<Neurona*> capa;
typedef vector< vector<float> > salida;
typedef pair<vector<float>, vector<float> > ejemplo2;

class RedNeural{
   public:
      vector<capa> capas;
      RedNeural(vector<capa> c): capas(c) {};
      void aprender(vector<ejemplo2>, float);
      salida resolver(vector<float>);
      float getSum(capa, vector<float>);
};

salida RedNeural::resolver(vector<float> input){
   salida output;
   vector<float> t1;
   for(int i=0;i<capas[0].size();++i){
      t1.push_back(capas[0][i]->resolver(input));
   }
   output.push_back(t1);

   for(int i=1;i<capas.size();++i){
      vector<float> temp;
      for(int j=0;j<capas[i].size();++j){
	 temp.push_back(capas[i][j]->resolver(output[i-1]));
      }
      output.push_back(temp);
   }

   return output;
}

void RedNeural::aprender(vector<ejemplo2> ejemplos, float tasa){
   random_device rd;
   default_random_engine gen(rd());
   uniform_real_distribution<float> distribution(0.0f,1.0f);

   vector<float> treble_k;
   salida treble_h;

   for(int i=0;i<capas.size();++i){
      vector<float> t2;
      for(int j=0;j<capas[i].size();++j){
	 if(i == capas.size()-1) treble_k.push_back(0.0f);
	 else t2.push_back(0.0f);
	 for(int k=0;k<capas[i][j]->pesos.size();++k){
	    capas[i][j]->pesos[k] = distribution(gen);
	 }
      }
      if(i != capas.size()-1) treble_h.push_back(t2);
   }

   float t_e = 10.0f;
   while(abs(t_e) > 0.1f){
      t_e = 0.0f;
      for(int i=0;i<ejemplos.size();++i){
	 salida o = resolver(ejemplos[i].first);
	 vector<float> t_k = ejemplos[i].second;
	 for(int j=0;j<capas[capas.size()-1].size();++j){
	    float o_k = o[capas.size()-1][j];
	    treble_k[j] = o_k*(1-o_k)*(t_k[j]-o_k);
	    t_e += (t_k[j]-o_k)*(t_k[j]-o_k);
	 }
	 for(int j=0;j<capas.size()-1;++j){
	    for(int k=0;k<capas[j].size();++k){
	       float o_h = o[j][k];
	       treble_h[j][k] =
		  o_h*(1-o_h)*getSum(capas[capas.size()-1],treble_k);
	    }
	 }
	 for(int j=0;i<capas.size();++i){
	    for(int k=0;j<capas[j].size();++j){
	       if(j == 0) capas[j][k]->pesos[k] =
		  tasa*treble_h[j][k]*ejemplos[i].first[k]; 
	       else capas[j][k]->pesos[k] = 
		  tasa*treble_h[j][k]*o[j-1][k];
	    }
	 }
      }
      t_e /= 2.0f;
   }

}

float RedNeural::getSum(capa c, vector<float> t){
   float res = 0.0f;

   for(int i=0;i<c.size();++i){
      for(int j=0;j<c[i]->pesos.size();++j){
	 res += c[i]->pesos[j] * t[i];
      }
   }
   return res;
}
