#include "Neurona.h"
using namespace std;

typedef vector<Neurona*> capa;
typedef vector< vector<double> > salida;
typedef pair<vector<double>, vector<double> > ejemplo2;

class RedNeural{
   public:
      vector<capa> capas;
      RedNeural(vector<capa> c): capas(c) {};
      void aprender(vector<ejemplo2>, double);
      salida resolver(vector<double>);
      double getSum(capa, vector<double>,int);
};

salida RedNeural::resolver(vector<double> input){
   salida output;
   vector<double> t1;
   t1.push_back(1.0);
   for(int i=0;i<capas[0].size();++i){
      t1.push_back(capas[0][i]->resolver(input));
      //cout << t1[i] << endl;
   }
   //cout << t1[capas[0].size()-1] << endl;
   output.push_back(t1);

   for(int i=1;i<capas.size();++i){
      vector<double> temp;
      for(int j=0;j<capas[i].size();++j){
	 temp.push_back(capas[i][j]->resolver(output[i-1]));
      }
      output.push_back(temp);
   }

   return output;
}

void RedNeural::aprender(vector<ejemplo2> ejemplos, double tasa){
   random_device rd;
   default_random_engine gen(rd());
   uniform_real_distribution<double> distribution(-1.0,1.0);

   vector<double> treble_k;
   salida treble_h;

   for(int i=0;i<capas.size();++i){
      vector<double> t2;
      for(int j=0;j<capas[i].size();++j){
	 if(i == capas.size()-1) treble_k.push_back(0.0);
	 else t2.push_back(0.0);
	 for(int k=0;k<capas[i][j]->pesos.size();++k){
	    capas[i][j]->pesos[k] = distribution(gen);
	    //cout << capas[i][j]->pesos[k] << endl;
	 }
      }
      if(i != capas.size()-1) treble_h.push_back(t2);
   }

   double t_e = 10.0;
   for(int it=0;it < 5000;++it){
      t_e = 0.0;
      for(int i=0;i<ejemplos.size();++i){
	 salida o = resolver(ejemplos[i].first);
	 vector<double> t_k = ejemplos[i].second;
	 //cout << "Ejemplo " << i+1 << endl;
	 for(int j=0;j<capas[capas.size()-1].size();++j){
	    double o_k = o[capas.size()-1][j];
	    //cout << o_k << " vs " << t_k[j] << endl;
	    treble_k[j] = o_k*(1-o_k)*(t_k[j]-o_k);
	    t_e += (t_k[j]-o_k)*(t_k[j]-o_k);
	    //cout << treble_k[j] << endl;
	    //cout << t_e << endl;
	 }
	 for(int j=0;j<capas.size()-1;++j){
	    for(int k=0;k<capas[j].size();++k){
	       double o_h = o[j][k];
	       double s = getSum(capas[j+1],treble_k,k);
	       //cout << s << endl;
	       treble_h[j][k] = o_h*(1-o_h)*s;
	       //cout << treble_h[j][k] << endl;
	    }
	 }
	 for(int j=0;j<capas.size();++j){
	    for(int k=0;k<capas[j].size();++k){
	       if(j == 0){
		  for(int l=0;l<capas[j][k]->pesos.size();++l){
		     capas[j][k]->pesos[l] =
		     tasa*treble_h[j][k]*ejemplos[i].first[l];
		  }
	       }else if(j != capas.size()-1){
		  for(int l=0;l<capas[j][k]->pesos.size();++l){
		     capas[j][k]->pesos[l] = 
		     tasa*treble_h[j][k]*o[j-1][l];
		  }
	       }else{
		  for(int l=0;l<capas[j][k]->pesos.size();++l){
		     capas[j][k]->pesos[l] = tasa*treble_k[k]*o[j-1][l];
		  }
	       }
	    }
	 }
      }
      t_e /= 2.0;
      //cout << t_e << endl;
   }

}

double RedNeural::getSum(capa c, vector<double> t,int k){
   double res = 0.0;

   for(int i=0;i<c.size();++i){
      res += (c[i]->pesos[k+1])*t[i];
   }
   return res;
}
