#include "Neurona.h"

int main(){
   vector<float> pesos;
   pesos.push_back(0.0f);
   pesos.push_back(0.0f);
   pesos.push_back(0.0f);

   vector<float> trueTrue;
   trueTrue.push_back(1.0f);
   trueTrue.push_back(1.0f);
   trueTrue.push_back(1.0f);

   vector<float> trueFalse;
   trueFalse.push_back(1.0f);
   trueFalse.push_back(1.0f);
   trueFalse.push_back(-1.0f);

   vector<float> falseTrue;
   falseTrue.push_back(1.0f);
   falseTrue.push_back(-1.0f);
   falseTrue.push_back(1.0f);

   vector<float> falseFalse;
   falseFalse.push_back(1.0f);
   falseFalse.push_back(-1.0f);
   trueFalse.push_back(-1.0f);
   
   vector<ejemplo> ejs;
   ejs.push_back({trueTrue,1.0f});
   ejs.push_back({trueFalse,-1.0f});
   ejs.push_back({falseTrue,-1.0f});
   ejs.push_back({falseFalse,-1.0f});

   Perceptron p(pesos);
   p.aprender(ejs,0.01f);

   cout << p.resolver(trueTrue) << endl;
   cout << p.resolver(trueFalse) << endl;
   cout << p.resolver(falseTrue) << endl;
   cout << p.resolver(falseFalse) << endl;

   /*Neurona n(pesos);
   n.aprender(ejs,0.1f);

   cout << n.resolver(trueTrue) << endl;
   cout << n.resolver(trueFalse) << endl;
   cout << n.resolver(falseTrue) << endl;
   cout << n.resolver(falseFalse) << endl;
*/
   return 0;
}
