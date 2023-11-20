#include "head.h"

int main() {

	char *data = getenv("QUERY_STRING");
	char ** neded_data = allocation_neded_data(neded_data);
	init_cgi_html();
	neded_data = split(neded_data , data);
	int error = 0;
	error = detect_error(neded_data);
	redirection_error_1(neded_data , data , error);

    return 0;
}

