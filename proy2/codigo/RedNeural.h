#ifndef REDNEURAL_H
#define REDNEURAL_H
#include "utilities.h"

class RedNeural{
   public:
      //Numeros en las capas
      int input;
      int hidden;
      int output;

      //Arreglos de valores de la capa input a la interna
      double* inputs;
      double** pesosIH;
      double* sumasIH;
      double* biasIH;
      double* outputsIH;

      //Arreglos de valores de la capa interna a la output
      double** pesosHO;
      double* sumasHO;
      double* biasHO;
      double* outputs;

      //Trebles
      double* trebleOutput;
      double* trebleHidden;

      //Metodos
      RedNeural(int,int,int);
      double aprenderSingle(double*,double*,double);
      double* resolver(double*);
      double* aprender(double**,double**,double,int);

      static double sigmoidal(double x);
};

#endif
