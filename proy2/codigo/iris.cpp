#include <fstream>
#include "RedNeural.h"
#include <string.h>
using namespace std;

int main(int argc, char *argv[]){
   
   //Corrida: ./iris.out <archivoEntrenamiento> <archivoTesting>
   //<cantidadEntrenamiento> <cantidadTesting> <neuronasInternas>
   //<Binario|Clase> <Tasa de aprendizaje>

   ifstream infile(argv[1]);
   ifstream datafile(argv[2]);
   int numEjemplos = atoi(argv[3]);
   int numInterna = atoi(argv[5]);
   int numInput = 4;
   string argv5 = argv[6];
   int numOutput = (argv5 == "Binario" ? 1 : 3);
   double** inputs = Utilities::crearMatriz(numEjemplos,numInput);
   double** targets;

   targets = (numOutput == 1 ? 
      Utilities::crearMatriz(numEjemplos,1) : 
      Utilities::crearMatriz(numEjemplos,3));
   double a,b,c,d;
   char c1,c2,c3,c4;
   int i=0;
   string s;

   while(infile >> a >> c1 >> b >> c2 >> c >> c3 >> d >> c4 >> s){
      inputs[i][0] = a;
      inputs[i][1] = b;
      inputs[i][2] = c;
      inputs[i][3] = d;
      targets[i][0] = (s == "Iris-setosa" ? 1.0 : 0.0);
      if(numOutput == 3){
	 targets[i][1] = (s == "Iris-versicolor" ? 1.0 : 0.0);
	 targets[i][2] = (s == "Iris-virginica" ? 1.0 : 0.0);
      }
      ++i;
   }
	 
   double tasa;
   sscanf(argv[7],"%lf",&tasa);
   RedNeural red(numInput,numInterna,numOutput);
   red.aprender(inputs,targets,tasa,numEjemplos);

   free(inputs);
   free(targets);
   int numDatos = atoi(argv[4]);
   inputs = Utilities::crearMatriz(numDatos,4);
   targets = Utilities::crearMatriz(numDatos,numOutput);

   i=0;
   while(datafile >> a >> c1 >> b >> c2 >> c >> c3 >> d >> c4 >> s){
      inputs[i][0] = a;
      inputs[i][1] = b;
      inputs[i][2] = c;
      inputs[i][3] = d;
      targets[i][0] = (s == "Iris-setosa" ? 1.0 : 0.0);
      if(numOutput == 3){
	 targets[i][1] = (s == "Iris-versicolor" ? 1.0 : 0.0);
	 targets[i][2] = (s == "Iris-virginica" ? 1.0 : 0.0);
      }
      ++i;
   }

   double success = 0.0;;
   for(int i=0;i<numDatos;++i){
      double* res = red.resolver(inputs[i]);
      //cout << "Caso " << i+1 << " Tipo " << argv[6] << endl;
      int rs;
      int ts;
      if(numOutput == 1){
	 rs = (res[0] >= 0.5 ? 1 : 0);
	 ts = (int) targets[i][0];
	 //cout << rs << " vs " << ts << endl << endl;
	 if(rs == ts) ++success;
      }else{ 
	 rs = (res[0] > res[1] ? 
	 (res[0] > res[2] ? 1 : 3) :
	 (res[1] > res[2] ? 2 : 3));
	 ts = (targets[i][0] > targets[i][1] ?
	    (targets[i][0] > targets[i][2] ? 1 : 3) :
	    (targets[i][1] > targets[i][2] ? 2 : 3));
	 //cout << rs << " vs " << ts << endl << endl;
	 if(rs == ts) ++success;
      }
   }

   //cout << "Tasa de correctitud en caso " << argv[6] << " con " <<
   //(((double)numEjemplos)/150.0) * 100.0 << " por ciento de los datos "
   //<< "y " << numInterna << " neuronas en la capa interna es de " << 
   //success/((double)numDatos) * 100.0 << " por ciento" << endl;

   cout << ((double)numEjemplos)/150 << " " << success/((double)numDatos) << endl;

   return 0;
}

