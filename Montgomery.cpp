#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include <iostream>

#include <assert.h>
using namespace std;

void convert_montgomery(mpz_t R, mpz_t N, mpz_t numero,mpz_t numero_montgomery );
void multiplicar_montgomery(mpz_t R, mpz_t N, mpz_t numero_montgomery_dos,mpz_t numero_montgomery_uno, mpz_t resultado_montgomery );
void convert_normal(mpz_t R, mpz_t N, mpz_t numero,mpz_t numero_montgomery );
int main(){
    mpz_t R, N;
    mpz_t numero_uno, numero_dos;
    mpz_t numero_montgomery_uno, numero_montgomery_dos;
    mpz_t resultado, resultado_montgomery;

    mpz_init(R);
    mpz_init(N);
    
    mpz_init(numero_uno);
    mpz_init(numero_dos);

    mpz_init(numero_montgomery_uno);
    mpz_init(numero_montgomery_dos);


    mpz_init(resultado);
    mpz_init(resultado_montgomery);

    

    mpz_init_set_str(N, "1073741827", 10); // Generador: 2
    mpz_init_set_str(R, "4294967296", 10);   // Número primo: 353
    mpz_init_set_str(numero_uno, "2", 10);   // Número primo: 353
    mpz_init_set_str(numero_dos, "3", 10);   // Número primo: 353


    convert_montgomery(R, N, numero_uno, numero_montgomery_uno );
    convert_montgomery(R, N, numero_dos, numero_montgomery_dos );
    multiplicar_montgomery(R, N, numero_montgomery_dos, numero_montgomery_uno, resultado_montgomery );
    convert_normal(R, N, resultado, resultado_montgomery );


    printf("--------------------------Ejemplo -------------------------------\n");

    printf("N: %s\n", mpz_get_str(NULL, 0, N));
    printf("R: %s\n", mpz_get_str(NULL, 0, R));
    printf("numero_uno: %s\n", mpz_get_str(NULL, 0, numero_uno));
    printf("numero_dos: %s\n", mpz_get_str(NULL, 0, numero_dos));
    printf("numero_montgomery_uno: %s\n", mpz_get_str(NULL, 0, numero_montgomery_uno));
    printf("numero_montgomery_dos: %s\n", mpz_get_str(NULL, 0, numero_montgomery_dos));
    printf("resultado_montgomery: %s\n", mpz_get_str(NULL, 0, resultado_montgomery));
    printf("resultado: %s\n", mpz_get_str(NULL, 0, resultado));
    printf("\n");



    
    // cifrar_mensaje(mensaje, clave_publica_bob, primo, encrypted);
    
    // cifrar_mensaje(encrypted, clave_privada_bob, primo, decrypted);

    // printf("Mensaje practicar: %s\n", mpz_get_str(NULL, 0, mensaje));
    // printf("Mensaje cifrado por alice: %s\n", mpz_get_str(NULL, 0, encrypted));
    // printf("Mensaje descifrado por bob: %s\n", mpz_get_str(NULL, 0, decrypted));
    return 0;

}








void convert_montgomery(mpz_t R, mpz_t N, mpz_t numero,mpz_t numero_montgomery ){
   
    mpz_mul(numero_montgomery, numero, R);

    mpz_mod(numero_montgomery,numero_montgomery,N);

}


void multiplicar_montgomery(mpz_t R, mpz_t N, mpz_t numero_montgomery_dos,mpz_t numero_montgomery_uno, mpz_t resultado_montgomery ){
    mpz_t q;
    mpz_t menos_uno;
    mpz_init(q);
    mpz_init(menos_uno);
    mpz_set_si(menos_uno, -1);

    mpz_mul(resultado_montgomery, numero_montgomery_uno, numero_montgomery_dos);
    
    mpz_invert(q,N,R);
    printf("q: %s\n", mpz_get_str(NULL, 0, q));
    
    mpz_mul(q,q,resultado_montgomery);
    mpz_mul(q,q,menos_uno);
    mpz_mod(q,q,R);
    printf("u: %s\n", mpz_get_str(NULL, 0, q));

    mpz_mul(q,q,N);
    mpz_add(resultado_montgomery, resultado_montgomery, q);
    mpz_div(resultado_montgomery, resultado_montgomery, R);

    printf("z: %s\n", mpz_get_str(NULL, 0, resultado_montgomery));

    mpz_clear(q);
    mpz_clear(menos_uno);
}

void convert_normal(mpz_t R, mpz_t N, mpz_t numero,mpz_t numero_montgomery ){
    mpz_t R_menos;
    
    mpz_invert(R_menos,R,N);
    
    mpz_mul(numero, numero_montgomery, R_menos);

    mpz_mod(numero,numero,N);

    mpz_clear(R_menos);
}