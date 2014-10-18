#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include<math.h>
using namespace std;

//Typedef para los ejemplos
typedef pair< vector<double> ,double > ejemplo;

class Neurona{
   public:
      vector<double> pesos;
      Neurona(vector<double> w): pesos(w) {}
      virtual void aprender(vector<ejemplo>,double) = 0;
      virtual double resolver(vector<double>) = 0;
};


//****************CLASE PERCEPTRON**************
class Perceptron : public Neurona {
   public:
      vector<double> pesos;
      Perceptron(vector<double> w): Neurona(w) {}
      void aprender(vector<ejemplo>, double);
      double resolver(vector<double>);
};

double Perceptron::resolver(vector<double> input){
   double output = 0;
   for(int i=0;i<input.size();++i){
      output += pesos[i] * input[i];
   }
   if(output > 0) return 1;
   else return -1;
}

void Perceptron::aprender(vector<ejemplo> ejemplos, double tasa){
   random_device rd;
   default_random_engine generator(rd());
   uniform_real_distribution<double> distribution(0.0f,1.0f);

   vector<double> delta(pesos);

   for(int i=0;i<pesos.size();++i){
      pesos[i] = distribution(generator);
   }

   int solved = 0;
   double t_e;
   int it = 0;
   while(solved != ejemplos.size()){
      solved = 0;
      t_e = 0.0f;
      for(int i=0;i<ejemplos.size();++i){
	 double o = resolver(ejemplos[i].first);
	 double e = ejemplos[i].second - o;
	 if(o == ejemplos[i].second) ++solved;
	 for(int j=0;j<pesos.size();++j){
	    pesos[j] += tasa*e*ejemplos[i].first[j];
	 }
	 t_e += e*e;
      }
      t_e /= 2.0f;
      //cout << it++ << "   " << t_e << endl;
   }
}

//*******************FIN DEL PERCEPTRON*********************

//****************CLASE ADALINE**************
class Adaline : public Neurona{
   public:
      Adaline(vector<double> w): Neurona(w) {}
      void aprender(vector<ejemplo>, double);
      double resolver(vector<double>);
};

double Adaline::resolver(vector<double> input){
   double output = 0;
   for(int i=0;i<input.size();++i){
      output += pesos[i] * input[i];
   }
   return output; 
}

void Adaline::aprender(vector<ejemplo> ejemplos, double tasa){
   random_device rd;
   default_random_engine generator(rd());
   uniform_real_distribution<double> distribution(0.0f,1.0f);

   for(int i=0;i<pesos.size();++i){
      pesos[i] = distribution(generator);
   }

   double t_e = 15.0f;
   int it = 1;
   while(abs(t_e) > 14.694f){
      t_e = 0.0f;
      for(int i=0;i<ejemplos.size();++i){
	 double o = resolver(ejemplos[i].first);
	 double e = o * (ejemplos[i].second - o);
	 for(int j=0;j<pesos.size();++j){
	    pesos[j] += tasa*e*ejemplos[i].first[j];
	 }
	 t_e += e*e;
      }
      t_e /= 2.0f;
      cout << it++ << "   " << t_e << endl;
   }
}

//*******************FIN DE ADALINE*********************

//****************CLASE SIGMOIDAL**************
class Sigmoidal : public Neurona{
   public:
      Sigmoidal(vector<double> w): Neurona(w) {}
      void aprender(vector<ejemplo>, double);
      double resolver(vector<double>);
};

double Sigmoidal::resolver(vector<double> input){
   double output = 0;
   for(int i=0;i<input.size();++i){
      output += pesos[i] * input[i];
   }
   double o = 1.0/(1.0 + exp(-output));
   //cout << o << endl;
   return o;
}

void Sigmoidal::aprender(vector<ejemplo> ejemplos, double tasa){
   random_device rd;
   default_random_engine generator(rd());
   uniform_real_distribution<double> distribution(0.0,1.0);

   for(int i=0;i<pesos.size();++i){
      pesos[i] = distribution(generator);
   }

   double t_e = 15.0;
   int it = 1;
   while(abs(t_e) > 14.694){
      t_e = 0.0;
      for(int i=0;i<ejemplos.size();++i){
	 double o = resolver(ejemplos[i].first);
	 double e = (ejemplos[i].second - o);
	 for(int j=0;j<pesos.size();++j){
	    pesos[j] += tasa*e*ejemplos[i].first[j];
	 }
	 t_e += e*e;
      }
      t_e /= 2.0;
      cout << it++ << "   " << t_e << endl;
   }
}

//*******************FIN DE LA NEURONA*********************
