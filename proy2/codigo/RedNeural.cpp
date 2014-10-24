#include "RedNeural.h"
using namespace std;

RedNeural::RedNeural(int i, int h, int o){
   random_device rd;
   default_random_engine gen(rd());
   uniform_real_distribution<double> distribution(-0.5,0.5);

   input = i;
   hidden = h;
   output = o;

   inputs = new double[input];
   pesosIH = Utilities::crearMatriz(input,hidden);
   sumasIH = new double[hidden];
   biasIH = new double[hidden];
   outputsIH = new double[hidden];

   pesosHO = Utilities::crearMatriz(hidden,output);
   sumasHO = new double[output];
   biasHO = new double[output];
   outputs = new double[output];

   trebleOutput = new double[output];
   trebleHidden = new double[hidden];

   for(int i=0;i<input;++i){
      for(int j=0;j<hidden;++j){
	 pesosIH[i][j] = distribution(gen);
      }
   }

   for(int i=0;i<hidden;++i){
      for(int j=0;j<output;++j){
	 pesosHO[i][j] = distribution(gen);
      }
      biasIH[i] = distribution(gen);
   }

   for(int i=0;i<output;++i){
      biasHO[i] = distribution(gen);
   }
}

double* RedNeural::aprender(double** inputs, double** targets, double tasa, int numEjemplos){
   double t_e = 10.0;
   int it = 0;
   
   int print = 5;
   float t_eantes = 10;
   float t_edespues = t_eantes-1;
      

   // para el caso del circulo usar 10000000 it
   // para el caso del iris usar 200000 it
   while(abs(t_e) > 0.1 and it < 200000){
//   while(abs(t_e) > 0.1&&it<10000000){
       
       t_eantes = t_e;
       t_e = 0.0;
      for(int i=0;i<numEjemplos;++i){
	 t_e += aprenderSingle(inputs[i],targets[i],tasa);
      }
      t_e /= 2.0;
      ++it;

      t_edespues = t_e;

      
      if(print == 0){
         print=5;
         cout <<it<<" "<< t_e << " " <<endl;
      }else{
         print--;
      }

   }
   return outputs;
}

double RedNeural::aprenderSingle(double* in, double* t, double tasa){
   double* o = resolver(in);
   double t_e = 0.0;

   //Calculando los errores de output
   for(int i=0;i<output;++i){
      double der = outputs[i] * (1-outputs[i]);
      trebleOutput[i] = der * (t[i] - outputs[i]);
      t_e += der*der;
   }

   //Calculando los errores de la capa interna
   for(int i=0;i<hidden;++i){
      double der = outputsIH[i] * (1-outputsIH[i]);
      double temp = 0.0;
      for(int j=0;j<output;++j){
	 temp += trebleOutput[j] * pesosHO[i][j];
      }
      trebleHidden[i] = der * temp;
   }

   //Actualizar pesos de la capa interna
   for(int i=0;i<input;++i){
      for(int j=0;j<hidden;++j){
	 double delta = tasa * trebleHidden[j] * in[i];
	 pesosIH[i][j] += delta;
      }
   }

   //Actualizar bias internos
   for(int i=0;i<hidden;++i){
      double delta = tasa * trebleHidden[i] * 1.0;
      biasIH[i] += delta;
   }

   //Actualizar pesos de la capa output
   for(int i=0;i<hidden;++i){
      for(int j=0;j<output;++j){
	 double delta = tasa * trebleOutput[j] * outputsIH[i];
	 pesosHO[i][j] += delta;
      }
   }

   //Actualizar bias de output
   for(int i=0;i<output;++i){
      double delta = tasa * trebleOutput[i] * 1.0;
      biasHO[i] += delta;
   }

   return t_e;
} 

double* RedNeural::resolver(double* in){
   for(int i=0;i<hidden;++i){
      double temp = 0.0;
      for(int j=0;j<input;++j){
	 temp += in[j] * pesosIH[j][i];
      }
      temp += biasIH[i];
      outputsIH[i] = sigmoidal(temp);
   }
   for(int i=0;i<output;++i){
      double temp = 0.0;
      for(int j=0;j<hidden;++j){
	 temp += outputsIH[j] * pesosHO[j][i];
      }
      temp += biasHO[i];
      outputs[i] = sigmoidal(temp);
   }

   return outputs;
}

double RedNeural::sigmoidal(double x){
   if(x < -45.0) return 0.0;	
   else if(x > 45.0) return 1.0;	
   else return 1.0/(1.0 + exp(-x));
}
