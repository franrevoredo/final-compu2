#include "write_result.h"

void write_result(int sd_conn, double ms, long long unsigned int it, char met, calc_result_t result) {

    int lines = 0, i = 0;

    char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n";
    char ini[] = "<html> <head> <meta charset='utf-8'> <meta name='viewport' content='width=device-width, initial-scale=1'> <script type='text/javascript' src='http://cdnjs.cloudflare.com/ajax/libs/jquery/2.0.3/jquery.min.js'></script> <script type='text/javascript' src='http://netdna.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js'></script> <link href='http://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.3.0/css/font-awesome.min.css' rel='stylesheet' type='text/css'><link href='./css/resultado.css' rel='stylesheet' type='text/css'><link href='http://pingendo.github.io/pingendo-bootstrap/themes/default/bootstrap.css' rel='stylesheet' type='text/css'> <link rel='icon' href='/favicon.ico' type='image/x-icon'><title>Resultado</title> </head> <body> <div class='navbar navbar-default navbar-static-top'> <div class='container'> <div class='navbar-header'> <button type='button' class='navbar-toggle' data-toggle='collapse' data-target='#navbar-ex-collapse'> <span class='sr-only'>Toggle navigation</span> <span class='icon-bar'></span> <span class='icon-bar'></span> <span class='icon-bar'></span> </button> <a class='navbar-brand' href='#'>Trabajo Final</a> </div> <div class='collapse navbar-collapse' id='navbar-ex-collapse'> <ul class='nav navbar-nav navbar-right'> <li> <a href='index.html'>Página Principal</a> </li> <li> <a href='desc.html'>Descripción del Proyecto</a> </li> </ul> </div> </div> </div> <div class='section'> <div class='container'> <div class='col-md-12'>";
    char fin[] = "</div></div><footer class='section section-primary'><div class='container'><div class='row'><div class='col-sm-6'><h1>Trabajo Final Computación 2</h1><p>Software para cálculos paralelizables, distribuidos en un número arbitrario de threads. La interfaz de usuario está montanda en un servidor web (C),con soporte Html+CSS.</p> </div> <div class='col-sm-6'> <p class='text-info text-right'> <br> <br> </p> <div class='row'> <div class='col-md-12 hidden-lg hidden-md hidden-sm text-left'> <a href='#'><i class='fa fa-3x fa-fw fa-instagram text-inverse'></i></a> <a href='#'><i class='fa fa-3x fa-fw fa-twitter text-inverse'></i></a> <a href='#'><i class='fa fa-3x fa-fw fa-facebook text-inverse'></i></a> <a href='#'><i class='fa fa-3x fa-fw fa-github text-inverse'></i></a> </div> </div> <div class='row'> <div class='col-md-12 hidden-xs text-right'> <a href='https://github.com/franrevoredo/final-compu2'><i class='fa fa-3x fa-fw fa-github text-inverse'></i></a> </div> </div> </div> </div> </div> </footer> </div><script>$(document).ready(function() { $('#volver').click(function() { window.location.href = 'index.html';}); });</script> </body></html>";

    write(sd_conn, rhtml, strlen(rhtml)); //cabecera de respuesta HTML

    write(sd_conn, ini, strlen(ini));

    switch (met) {
        case 'a':
        {
            lines = 6;
            char httplines[lines][LINEMAX];

            snprintf(httplines[0], LINEMAX, "<div class='alert alert-info' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button><strong>Listo!</strong> Operación completada en %f segundos.</div>", ms);
            snprintf(httplines[1], LINEMAX, "<h2 class='display-4'>Calculo de Pi (Simpson)</h2>");
            snprintf(httplines[2], LINEMAX, "<table><tr><td class='fijo'>Cantidad de iteraciones:</td><td> %llu </td></tr>", it);
            snprintf(httplines[3], LINEMAX, "<tr><td class='fijo'>El Valor de Pi es:</td><td> 3.141592653589793238462</td></tr>");
            snprintf(httplines[4], LINEMAX, "<tr><td class='fijo'>El Valor Calculado de Pi es:</td><td> %.21Lf </td></tr></table>", result.exact);
            snprintf(httplines[5], LINEMAX, "<br><div><input type='button'  class='btn btn-primary' id='volver' value='Volver' /></div><br>");

            for (i = 0; i < lines; i++) {
                write(sd_conn, httplines[i], strlen(httplines[i]));
            }
        }
            break;
        case 'b':
        {
            lines = 6;
            char httplines[lines][LINEMAX];

            snprintf(httplines[0], LINEMAX, "<div class='alert alert-info' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button><strong>Listo!</strong> Operación completada en %f segundos.</div>", ms);
            snprintf(httplines[1], LINEMAX, "<h2 class='display-4'>Calculo de Pi (Montecarlo)</h2>");
            snprintf(httplines[2], LINEMAX, "<table><tr><td class='fijo'>Cantidad de iteraciones:</td><td> %llu </td></tr>", it);
            snprintf(httplines[3], LINEMAX, "<tr><td class='fijo'>El Valor de Pi es:</td><td> 3.141592653589793238462</td></tr>");
            snprintf(httplines[4], LINEMAX, "<tr><td class='fijo'>El Valor Calculado de Pi es:</td><td> %.21Lf </td></tr></table>", result.exact);
            snprintf(httplines[5], LINEMAX, "<br><div><input type='button'  class='btn btn-primary' id='volver' value='Volver' /></div><br>");

            for (i = 0; i < lines; i++) {
                write(sd_conn, httplines[i], strlen(httplines[i]));
            }
        }
            break;
    }

    write(sd_conn, fin, strlen(fin));
    write(sd_conn, "\n\n", 2);

    return;
}
