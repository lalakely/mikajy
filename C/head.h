#ifndef VAR
#define VAR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void init_cgi_html();
void html_mikajy(char ** neded_data,char * data);
char ** allocation_neded_data(char ** data);
char ** split(char ** neded_data , char * data);
int detect_error(char ** neded_data);
void redirection_error_1(char **neded_data , char * data , int error);
void dichotomie(double a , double b , double eps);
void secante(double a , double b , double eps);
void tangente(double a , double b , double eps);
double f(double x);
void css_mikajy();
double f_p(double x);
void redirection_calcul(char ** neded_data);
#endif
