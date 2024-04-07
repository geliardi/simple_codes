from math import sqrt

#Objetivo: Encontrar todos os números primos de 1... 10000
#O que são?
# N >= 2, N%N == 0

#Definir uma função pra testar se é primo
def eprimo(valor: int) -> bool:    
    if valor > 2 and valor%2 != 0:
        #Se ele passar por essa condição..
        for f in range(3, int(sqrt(valor)+1), 2):            
            if valor%f == 0:
                return False
        #Se passar por todos os testes...
        return True
    return valor == 2 #Se valor for igual, é primo, mas se não...

limite = 10000
primes = []
for i in range(1, limite):
    if eprimo(i):
        primes += [i]

#Agora se deu certo ehhhee
print(primes)
#Considerações
  
#Cython -> C        

