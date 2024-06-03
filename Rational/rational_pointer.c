/*
  TITLE: PROGRAMMING II LABS                   SUBTITLE: P0

AUTHOR 1: Lucas Marqués Núñez    LOGIN 1: lucas.marques@udc.es

AUTHOR 2: Xabier Guitián López    LOGIN 2: x.guitian@udc.es

 GROUP: 2.4                                                            DATE: 02/02/2024
*/

#include <stdlib.h>
#include "rational_pointer.h"

// Operacion para crear un racional
Rational createRational(int n, int d) {
    Rational temp;
    temp= malloc(sizeof(*temp));
    temp->num= n;
    temp->den= d;
    return temp;
}
// Operacion que retorna el numerador de un racional
int numerator(Rational r) {
    return r->num;
}
// Operacion que retorna el denominador de un racional
int denominator(Rational r) {
    return r->den;
}
// Operacion que retorna la suma de dos racionales
Rational sum(Rational r1, Rational r2) {
    Rational s;
    s= malloc(sizeof(*s));
    s->num= r1->num * r2->den + r2->num * r1->den;
    s->den= r1->den * r2->den;
    return s;
}