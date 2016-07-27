#include "write_result.h"

void write_result(int sd_conn, double ms, long long unsigned int it, char met, calc_result_t result) {

    int lines = 0, i = 0;

    char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n";
    char by[] = "<br><br><div id='author'>Hecho por Francisco Revoredo.</div></body>";

    write(sd_conn, rhtml, strlen(rhtml)); //cabecera de respuesta HTML

    switch (met) {
        case 'a':
        {
            lines = 6;
            char httplines[lines][LINEMAX];

            snprintf(httplines[0], LINEMAX, "<head><title>Cálculo de Pi (Simpson)</title><link rel='stylesheet' type='text/css' href='./style.css'></head><body id='body_calc'><h2>Calculo de Pi (Simpson)</h2>");
            snprintf(httplines[1], LINEMAX, "<b>Cantidad de iteraciones&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:</b> %llu <br>", it);
            snprintf(httplines[2], LINEMAX, "<b>El Valor de Pi es &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:</b> 3.141592653589793238462<br>");
            snprintf(httplines[3], LINEMAX, "<b>El Valor Calculado de Pi es&nbsp;&nbsp;:</b> %.21Lf <br>", result.exact);
            snprintf(httplines[4], LINEMAX, "<b>El tiempo de cálculo fue de&nbsp;:</b> %f segundos. <br><br>", ms);
            snprintf(httplines[5], LINEMAX, "<div id='volver'><a href='index.html'>Volver</a></div>");

            for (i = 0; i < lines; i++) {
                write(sd_conn, httplines[i], strlen(httplines[i]));
            }
        }
            break;
        case 'b':
        {
            lines = 6;
            char httplines[lines][LINEMAX];

            snprintf(httplines[0], LINEMAX, "<head><title>Cálculo de Pi (Montecarlo)</title><link rel='stylesheet' type='text/css' href='./style.css'></head><body id='body_calc'><h2>Calculo de Pi (Montecarlo)</h2>");
            snprintf(httplines[1], LINEMAX, "<b>Cantidad de iteraciones&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:</b> %llu <br>", it);
            snprintf(httplines[2], LINEMAX, "<b>El Valor de Pi es &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:</b> 3.141592653589793238462<br>");
            snprintf(httplines[3], LINEMAX, "<b>El Valor Calculado de Pi es&nbsp;&nbsp;:</b> %.21Lf <br>", result.exact);
            snprintf(httplines[4], LINEMAX, "<b>El tiempo de cálculo fue de&nbsp;:</b> %f segundos. <br><br>", ms);
            snprintf(httplines[5], LINEMAX, "<div id='volver'><a href='index.html'>Volver</a></div>");

            for (i = 0; i < lines; i++) {
                write(sd_conn, httplines[i], strlen(httplines[i]));
            }
        }
            break;
    }

    write(sd_conn, by, strlen(by));
    write(sd_conn, "\n\n", 2);

    return;
}
