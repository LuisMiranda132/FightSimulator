from pyevolve import G1DList
from pyevolve import GSimpleGA
from pyevolve import G1DBinaryString
from pyevolve import Util
from random import randint as rand_randint, uniform as rand_uniform, choice as rand_choice, randrange as randrange


MAX_SET_SIZE = 5
RULE_SIZE = 152


def eval_func(chromosome):
   score = 0.0
   # iterate over the chromosome
   for value in chromosome:
      if value==0:
         score += 1
   return score/len(chromosome.genomeList)

def init_func(genome, **args):
   the_set = []
   set_size = randrange(1,MAX_SET_SIZE+1)
   for i in xrange(set_size):
      rule = [rand_choice((0,1)) for j in xrange(RULE_SIZE)]
      rule = to_legal(rule);
      the_set = the_set + rule
   genome.genomeList = the_set

def is_legal(rule):
   if rule[-2] == 0 and rule[-1] == 0:
      return False
   else: 
      return True

def to_legal(rule):
   if(not is_legal(rule)):
      n = rand_choice((-2,-1))
      rule[n] = 1
   
   return rule

def gabil_cross(genome, **args):
# def gabil_cross(genome):
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

genome = G1DBinaryString.G1DBinaryString(MAX_SET_SIZE)
genome.initializator.set(init_func)
genome.evaluator.set(eval_func)
ga = GSimpleGA.GSimpleGA(genome)
ga.setGenerations(50)
ga.evolve(freq_stats=10)
print ga.bestIndividual()
