from pyevolve import G1DList
from pyevolve import GSimpleGA
from pyevolve import G1DBinaryString
from pyevolve import Util
from pyevolve import Selectors
from random import randint as rand_randint, uniform as rand_uniform, choice as rand_choice, randrange as randrange
import sys


MAX_SET_SIZE = 3
RULE_SIZE = 36
INITIAL_POP = 10
TRAINING_SET = []
i = 0

##################################Atributos######################################
def attr1(num):
   num = float(num)
   if num < 4:
      return '1000000'
   if num < 5:
      return '0100000'
   if num < 5.5:
      return '0010000'
   if num < 6:
      return '0001000'
   if num < 6.5:
      return '0000100'
   if num < 7:
      return '0000010'
   return '0000001'

def attr2(num):
   num = float(num)
   if num < 2:
      return '1000000'
   if num < 2.6:
      return '0100000'
   if num < 2.8:
      return '0010000'
   if num < 3:
      return '0001000'
   if num < 3.2:
      return '0000100'
   if num < 4:
      return '0000010'
   return '0000001'

def attr3(num):
   num = float(num)
   if num < 0.6:
      return '10000000000'
   if num < 1:
      return '01000000000'
   if num < 1.5:
      return '00100000000'
   if num < 2:
      return '00010000000'
   if num < 3:
      return '00001000000'
   if num < 3.5:
      return '00000100000'
   if num < 4:
      return '00000010000'
   if num < 4.5:
      return '00000001000'
   if num < 5:
      return '00000000100'
   if num < 6:
      return '00000000010'
   return '00000000001'

def attr4(num):
   num = float(num)
   if num < 0.2:
      return '100000000'
   if num < 0.4:
      return '010000000'
   if num < 0.6:
      return '001000000'
   if num < 0.8:
      return '000100000'
   if num < 1:
      return '000010000'
   if num < 1.5:
      return '000001000'
   if num < 2:
      return '000000100'
   if num < 2.5:
      return '000000010'
   return '000000001'

def attr5(num):
   num = int(num)
   if num==1:
      return '00'
   if num==2:
      return '10'
   return '01'

###############################Inicializacion#####################################
def init_func(genome, **args):
   the_set = []
   set_size = randrange(1,MAX_SET_SIZE+1)
   for i in xrange(set_size):
      rule = [rand_choice(('0','1')) for j in xrange(RULE_SIZE)]
      the_set = the_set + rule
   genome.genomeList = the_set

#################################Fitness#########################################
def match(chromosome,sample,opt=0):
   s = long(sample,2)
   c = ''.join(chromosome.genomeList)
   for i in range(0,len(c),RULE_SIZE):
      if(opt == 1):
	 print "rule  : " + c[i:i+RULE_SIZE]
	 print "sample: " + sample
      if (long(c[i:i+RULE_SIZE],2) & s) == s:
	 return True
   return False

def standard_fitness(chromosome):
   score = 0
   for sample in TRAINING_SET:
      if(match(chromosome,sample)):
	 score+=1
   return pow(score,2)

def size_fitness(chromosome):
   score = 0
   for sample in TRAINING_SET:
      if(match(chromosome,sample)):
	 score+=1
   return int(float(pow(score,2)) + 1.0/(pow(len(chromosome.genomeList)/RULE_SIZE,2)))

##############################Crossover##########################################
def gabil_cross(genome, **args):
   sister = None
   brother = None
   gMom = args["mom"]
   gDad = args["dad"]

   # gMom = ['1','0','1','0','1','0']
   # gDad = ['0','1','0','1','0','1','0','1','0','1','0','1']

   if(len(gMom)>len(gDad)):
      dummy = gMom
      gMom = gDad
      gDad = dummy
      
   cuts = [rand_randint(1,len(gMom)-1),rand_randint(1, len(gMom)-1)]

   if cuts[0] > cuts[1]:
      Util.listSwapElement(cuts, 0, 1)

   # print cuts
   newcuts = map(lambda x:divmod(x,RULE_SIZE)[1],cuts)
   # print newcuts
   # print str(gMom) +"\t<3\t"+ str(gDad)

   while True:
      dpos = rand_randint(0,(len(gDad)/RULE_SIZE)-1)
      dummy0 = newcuts[0]+dpos*RULE_SIZE
      dpos = rand_randint(0,(len(gDad)/RULE_SIZE)-1)
      dummy1 = newcuts[1]+dpos*RULE_SIZE

      if dummy0 < dummy1:
         newcuts[0] = dummy0
         newcuts[1] = dummy1
         break

   # print newcuts
   
   sister = gMom.clone()
   sister.resetStats()
   # sister = gMom[:]
   # sister[cuts[0]:cuts[1]] = gDad[cuts[0]:cuts[1]]
   sister.genomeList = gMom[:cuts[0]] + gDad[newcuts[0]:newcuts[1]] + gMom[cuts[1]:]

   brother = gDad.clone()
   brother.resetStats()
   # brother = gDad[:]
   # brother[cuts[0]:cuts[1]] = gMom[cuts[0]:cuts[1]]
   brother.genomeList = gDad[:newcuts[0]] + gMom[cuts[0]:cuts[1]] + gDad[newcuts[1]:]
   return (sister, brother)

################################Mutacion#########################################
def gabil_mutation(genome, **args):
  
   if args["pmut"] <= 0.0: return 0
   stringLength = len(genome)
   mutations = args["pmut"] * (stringLength)

   if mutations < 1.0:
      mutations = 0
      for it in xrange(stringLength):
	 if Util.randomFlipCoin(args["pmut"]):
	    if genome.genomeList[it] == '0': genome.genomeList[it] = '1'
	    else: genome.genomeList[it] = '0'
	    mutations+=1
   else:
      for it in xrange(int(round(mutations))):
	 which = rand_randint(0,stringLength-1)
	 if genome.genomeList[which] == '0': genome.genomeList[which] = '1'
	 else: genome.genomeList[which] = '0'

   return int(mutations)

####################################Main#########################################
###Definir el conjunto de entrenamiento###
if len(sys.argv) != 7:
   response = "usage: python gabil.py <trainingFile>"
   response += " <sampleFile> <selector> <fitness>"
   response += " <mutationRate> <crossoverRate>\n"
   response += "selector must be either 1(Rank) or 2(Roulette)\n"
   response += "fitness must be either 1(Standard) or 2(Size)"
   print response
   sys.exit()


f = open(sys.argv[1],'r')
for line in f:
   l = line.split(" ")
   t = ""
   t = t + attr1(l[0])
   t = t + attr2(l[1])
   t = t + attr3(l[2])
   t = t + attr4(l[3])
   t = t + attr5(l[4])
   TRAINING_SET = TRAINING_SET + [t]

genome = G1DBinaryString.G1DBinaryString(MAX_SET_SIZE)
genome.initializator.set(init_func)

if(int(sys.argv[4]) == 1): genome.evaluator.set(standard_fitness)
else: genome.evaluator.set(size_fitness)

genome.crossover.set(gabil_cross)
genome.mutator.set(gabil_mutation)
ga = GSimpleGA.GSimpleGA(genome)
ga.terminationCriteria.set(GSimpleGA.FitnessStatsCriteria)

if(int(sys.argv[3]) == 1): ga.selector.set(Selectors.GRankSelector)
else: ga.selector.set(Selectors.GRouletteWheel)
ga.setMutationRate(float(sys.argv[5]))
ga.setCrossoverRate(float(sys.argv[6]))
ga.setGenerations(100)
ga.setPopulationSize(INITIAL_POP)
ga.evolve(freq_stats=0)

f.close()
f = open(sys.argv[2],'r')
SAMPLE_SET = []
for line in f:
   l = line.split(" ")
   t = ""
   t = t + attr1(l[0])
   t = t + attr2(l[1])
   t = t + attr3(l[2])
   t = t + attr4(l[3])
   t = t + attr5(l[4])
   SAMPLE_SET = SAMPLE_SET + [t]

score = 0
for sample in SAMPLE_SET:
   if(match(ga.bestIndividual(),sample)):
      score+=1

#response = "Porcentaje de casos correctamente clasificados"
#response += " (del 30% de los datos de la base): " 
#response += str((float(score)/len(SAMPLE_SET)) * 100) + " por ciento"
#print response

#print ' '.join(ga.bestIndividual().genomeList)
print float(score)/len(SAMPLE_SET)

f.close()
