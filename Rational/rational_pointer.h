/*
  TITLE: PROGRAMMING II LABS                   SUBTITLE: P0

AUTHOR 1: Lucas Marqués Núñez    LOGIN 1: lucas.marques@udc.es

AUTHOR 2: Xabier Guitián López    LOGIN 2: x.guitian@udc.es

 GROUP: 2.4                                                            DATE: 02/02/2024
*/

#ifndef RATIONAL_POINTER_H
#define RATIONAL_POINTER_H
typedef struct Data* Rational;
struct Data {
    int num;
    int den; };
Rational createRational(int n, int d);
int numerator(Rational r);
int denominator(Rational r);
Rational sum(Rational r1, Rational r2);
#endif // RATIONAL_POINTER_H