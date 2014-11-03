from pyevolve import G1DList
from pyevolve import GSimpleGA
from pyevolve import G1DBinaryString
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


genome = G1DBinaryString.G1DBinaryString(MAX_SET_SIZE)
genome.initializator.set(init_func)
genome.evaluator.set(eval_func)
ga = GSimpleGA.GSimpleGA(genome)
ga.setGenerations(50)
ga.evolve(freq_stats=10)
print ga.bestIndividual()
