#include <iostream>
#include <ctime>
#include <string>

/*
Autor: Geliardi S. Oliveira

Algoritmo de teste de primalidade usando miller rabin.

Modo de uso: checar primo <numero>

Para ser usado em linha de comando.
*/

// função rápida de calculo exponencial modular: base^exp % mod
int mod_exp(int base, int exp, int mod){

    int result = 1;
    while (exp > 0) {
        
        // se expoente for impar, multiplica pelo resultado
        if (exp % 2 == 1) { 
            result = (result * base) % mod;
        }
        // base recebe base ao quadrado modulo mod e exp reduz(divide) por 2
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

namespace miller_rabin {

// para verificar primalidade com o algoritmo de miller-rabin
bool is_prime(int num, int tries = 20) {

    // verificações iniciais
    if (num <= 1) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0) return false;   
    
    int spl = num - 1;
    int p = 0;
    
    // convertend (num-1) para uma potencia de 2: spl * 2^p
    while (spl % 2 == 0) {
        spl /= 2;
        p += 1;
    }

    // gerando seed para aleatórios
    srand(time(NULL)); 

    for (int i = 0; i < tries; i++) {

        // gerando uma testemunha aletória e uma tentativa atual
        int wt = (rand() % (num - 3)) + 2; 
        int crr = mod_exp(wt, spl, num);

        // caso tentativa: igual a 1 ou a (num-1)
        if (crr != 1 && crr != num - 1) {
            bool passed = false;
            for (int j = 0; j < p - 1; j++) {
        // num range de 0 a P-1, crie outra tentativa
                crr = mod_exp(crr, 2, num);
                if (crr == num - 1) { // se tentativa é igual a (num-1)
                    passed = true; // ela passou no teste atual
                    break;
                }
            }
            // se todas as tentativas falharam, não é um primo
            if (!passed) return false;
        }}
    return true;
}
} // fim do namespace

int main(int argc, char* argv[]) {

    bool prime;
    
    if (argc < 2) {
        std::cout << "Uso: " << argv[0] << " <numero>\n";
        return 1;
    }

    // primeiro argumento após o nome do programa
    std::string command = argv[1];  

    // verificar se o comando é "prime"
    if (command == "prime") {
        if (argc < 3) {
            std::cout << "Erro: Nenhum numero foi especificado.\n";
            return 1;
        }
        // testar se o numero é primo
        int numero = std::stoi(argv[2]);
        prime = miller_rabin::is_prime(numero);

        // responde sim ou não para essa condição
        std::cout << numero << " PRIMO? " << (prime ? "SIM": "NAO");

    } else {

        std::cout << "Comando desconhecido: " << command << "\n";
    }
    if (prime) return 0;
    if (!prime) return 1;   
}



