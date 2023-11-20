#include "head.h"

void init_cgi_html(){
	printf("Content-Type: text/html\n\n");
}
void css_mikajy(){
	printf(
		"body{"
        	    "background-image: url(../photo/background_mikajy.png);"
        	    "background-position: center;"
        	    "margin: 0;"
        	"}"
		".div_body{"
			"display:flex;"
		"}"
		"td{"
			"border : 2px solid black;"
			"width:400px;"
			"height:40px;"
			"align-items:center;"
			"background-color:#ffffffcb;"
		"}"
		".div_calcul{"
			"position:relative;"
			"left:600px;"
			"top:20px;"
		"}"
	".inp{"
            "background-color: #ffffffcb;"
            "border : 2px solid black;"
            "outline: none;"
            "height:40px;"
            "width: 450px;"
            "border-radius: 30px;"
            "padding-left:20px;"
           "margin-top: 10px;"
        "}"
        ".div_nav{"
            "display: flex;"
		"position:fixed;"
            "flex-direction: column;"
           "justify-content: center;"
          "align-items: center;"
		"padding:40px;"
        "}"
        ".logo_mikajy{"
            "background-image: url(../photo/MIKAJY_logo_principale-removebg-preview.png);"
            "width: 300px;"
            "height: 300px;"
            "background-size: cover;"
            "background-position: center;"
        "}"
        ".s_button{"
            "background-color: #ffffffcb;"
            "border : 2px solid black;"
            "height: 45px;"
            "margin: 10px;"
            "border-radius: 30px;"
            "width: 120px;"
        "}"
        ".s_button:hover{"
            "background-color: #202124c4;"
            "color: #ffffff;"
        "}"
        ".div_button{"
            "display: flex;"
        "}"
        ".form_class{"
            "display: flex;"
            "flex-direction: column;"
        "}"
	".solution{"
		"border:2px solid black;"
		"margin:5px;"
		"height:40px;"
		"display:flex;"
		"justify-content:center;"
		"align-items:center;"
		"background-color:#202124c4;"
		"color:white;"
	"}"
	".begin{"
		"background-color:#202124c4;"
	"}"
	".label{"
            "font-family: 'Courier New', Courier, monospace;"
            "display:flex;"
	    "justify-content:center;"
        "}"
	);
}
void html_mikajy(char ** neded_data, char * data){
        printf("<!DOCTYPE html>"
		"<html lang=\"en\">"
		"<head>"
    		"<meta charset=\"UTF-8\">"
    		"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
    		"<title>Mikajy - Calcul</title>");
	printf("<style>");
	css_mikajy();
	printf("</style>");
	printf("</head>");
	printf("<body>");
	printf("<div class=\"div_body\">");
	printf(
	"<div class=\"div_nav\">"
        "<a href=\"../index.html\"><div class=\"logo_mikajy\"></div></a>"
        "<form action=\"../cgi/mikajy.cgi\" class=\"form_class\" method=\"get\">"
            "<input type=\"text\" placeholder=\"a\" class=\"inp\" name=\"a\">"
            "<input type=\"text\" placeholder=\"b\" class=\"inp\" name=\"b\">"
            "<select name=\"eps\"  class=\"inp\">"
                "<option value=\"0.00001\">10^-5</option>"
                "<option value=\"0.0000001\">10^-7</option>"
                "<option value=\"0.0000000001\">10^-10</option>"
            "</select>"
            "<div class=\"div_button\">"
                "<button type=\"submit\" class=\"s_button\" value=\"1\" name=\"button\">Dichotomie</button>"
                "<button type=\"submit\" class=\"s_button\" value=\"2\" name=\"button\">Secante</button>"
                "<button type=\"submit\" class=\"s_button\" value=\"3\" name=\"button\">Tangente</button>"
            "</div>"
        "</form>"
    "</div>"
	);
	printf("<div class=\"div_calcul\">");
	if (data != NULL) {
        	redirection_calcul(neded_data);
	} else {
                printf("Aucune donnée GET reçue.");
        }
	printf("</div>");
	printf("</div>");
	printf("</body>");
	printf("</html>");
}
void redirection_calcul(char ** neded_data){

	double a = atof(neded_data[1]);
        double b = atof(neded_data[3]);
        double eps = atof(neded_data[5]);
	if(atoi(neded_data[7]) == 1){dichotomie(a , b , eps);}
	if(atoi(neded_data[7]) == 2){secante(a , b , eps);}
	if(atoi(neded_data[7]) == 3){tangente(a , b , eps);}
}
char ** allocation_neded_data(char ** data){
	data = malloc(10 * sizeof(char *));
	for(int i = 0 ; i < 10 ; i ++){
		data[i] = malloc(256);
	}
	return data;
}

char ** split(char ** neded_data , char * data){
	int k = 0;
	int l = 0;
	for(int i = 0 ; i < strlen(data) ; i++){
		if(data[i]== '='||data[i] == '&'){
			k++;l=0;
		}
		else{
			neded_data[k][l] = data[i];
			l++;
		}
	}
	return neded_data;
}

int detect_error(char ** neded_data){
	int error = 0;
	for(int i = 0 ; i < strlen(neded_data[1]) ; i++){
		if(neded_data[1][i] < '0' || neded_data[1][i] > '9'){
			error = 1;
		}
	}
	for(int i = 0 ; i < strlen(neded_data[3]) ;i++){
		if(neded_data[3][i] < '0' || neded_data[3][i] > '9'){
			error = 2;
		}
	}
	return error;
}

void redirection_error_1(char ** neded_data , char * data , int error){
	if (error == 1 || error == 2){
		printf("Error : %d",error);
	}
	if(error == 0){
		html_mikajy(neded_data , data);
	}
}

void dichotomie(double a , double b , double eps){
	double s = 0;
	printf("<h3 class=\"label\">Dichotomie</h3>");
	printf("<table>");
	printf("<tbody>");
	printf("<tr class=\"begin\"> <td>a</td><td>b</td></tr>");
	while(fabs(b - a) > eps){
		if(f(s) * f(a) > 0){
			a = s;
			s+=(b-a)/2;
		}
		else if(f(s) * f(b) > 0){
			b = s;
			s-=(b-a)/2;
		}
		printf("<tr>");
		printf(" <td>%f</td> <td>%f</td> " , b , a);
		printf("</tr>");
	}
	printf("</table>");
	printf("</tbody>");
	printf("<div class=\"solution\">La solution finale est %.10f</div>",s);
}
void secante(double a , double b , double eps){
	double s = b;
	printf("<h3 class=\"label\">Secante</h3>");
        printf("<table>");
        printf("<tbody>");
        printf("<tr class=\"begin\"> <td>a</td><td>b</td></tr>");
	while(f(s) > eps){
                s = a - (f(a) * (a - b))/(f(a) - f(b));
                b = s;
		printf("<tr>");
                printf("<td>%f</td> <td>%f</td>\n" , a , b);
		printf("</tr>");
        }
	printf("</table>");
        printf("</tbody>");
        printf("<div class=\"solution\">La solution finale est %.10f</div>",s);

}
void tangente(double a , double b , double eps){
	double s = b;
        printf("<h3 class=\"label\">Tangente</h3>");
        printf("<table>");
        printf("<tbody>");
        printf("<tr class=\"begin\"> <td>a</td><td>b</td></tr>");
	while(fabs(f(s)) > eps){
                s = a - f(a)/f_p(a);
                a = s;
		printf("<tr>");
                printf(" <td>%f</td> <td>%f</td> \n",a,b);
		printf("</tr>");
        }
        printf("</table>");
        printf("</tbody>");
        printf("<div class=\"solution\">La solution finale est %.10f</div>",s);
}
double f(double x){
	return log(x) - 1;
}
double f_p(double x){
	return 1/x;
}
