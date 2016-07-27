#include "http_worker.h"
#include "http_response.h"
#include "checkget.h"
#include "checkext.h"
#include "simpson.h"
#include "montecarlo.h"
#include "parse.h"
#include "write_result.h"

/* Variables Compartidas por los threads */

long double sum = 0.0;

void
http_worker (int sd_conn, struct sockaddr *cli_addr, int thread_num)
{

  //Inicio definicion para los threads
  params_t params;
  pthread_t *threads;
  threads = malloc (thread_num * sizeof (pthread_t));
  pthread_mutex_init (&params.mutex, NULL);
  pthread_cond_init (&params.done, NULL);
  //Fin definicion para los threads

  char urlaux[256] = "";
  http_req_t req;
  int i = 0;
  int len;
  int fd, mime;
  int http_ok = 0;
  char buff[4096];

  /* Variables para los cálculos */
  double ms;
  long double pi = 0.0;
  unsigned long long int coef;
  long double h;
  clock_t begin, end;
  calc_result_t result;
  /* Fin de Variables para los cálculos */

  req = parse (sd_conn);	//Parseamos el request y lo metemos dentro de la estructura

  if (checkget (req.method))
    {				//Se chequea el metodo del request para confirmar que esté bien hecho, sino se devuelve el error.
      write (1, "Ok (Method)\n", 12);
      http_ok++;

      if (req.url[0] == '/' && (strlen (req.url) == 1))
	{			//Si la url está vacía se abre la página por defecto
	  mime = 1;
	  fd = open ("index.html", O_RDONLY, 0777);
	}
      else
	{
	  len = 0;
	  len = strlen (req.url);

	  for (i = 1; i < len; i++)
	    urlaux[i - 1] = req.url[i];	//Se lee la url y se la copia a una variable auxiliar sin el primer caracter "/"

	  mime = checkext (urlaux);	//Se analiza el mime para saber que hacer con el request

	  if (mime == -1)
	    {
	      write (sd_conn, "501 Not Implemented\n", 20);
	      printf ("MIME no valido (%s)\n", urlaux);
	    }
	  else
	    {
	      if (mime < 10)
		{		//Si el mime es menor a diez significa que el request es para abrir un archivo del servidor.
		  fd = open (urlaux, O_RDONLY, 0777);
		}
	    }
	}

      if ((fd < 0) && (mime < 9) && req.url[0] != '/')
	{
	  write (sd_conn, "404 File Not Found\n", 19);
	  perror ("File Not Found");
	}
      else
	{
	  write (1, "Ok (File)\n\n", 11);
	  http_ok++;
	}
    }
  else
    write (sd_conn, "400 Bad request\n", 16);

  if (http_ok == 2)
    met_it = http_response (mime, sd_conn, fd);	//Se analiza el codigo que resulta del analisis del MIME para ver respuesta http se debe devolver al cliente.

  if (met_it.it > 0)
    {				//Si la estructura contiene algún numero de iteraciones, significa que el request es para un cálculo

      memset (buff, 0, sizeof buff);

      begin = clock ();		//Comienzo a medir el tiempo del cálculo

      switch (met_it.met)
	{
	case 'a':
	  coef = met_it.it / thread_num;	//Calculo cuantas iteraciones le corresponde a cada thread del pool.
	  h = 1.0 / (long double) met_it.it;
	  break;
	case 'b':
	  coef = met_it.it / thread_num;	//Calculo cuantas iteraciones le corresponde a cada thread del pool.
	  break;
	}


      params_t *params_array = malloc (thread_num * sizeof (params_t));	//Se crea un puntero para crear una estructura para cada thread.


      for (i = 0; i < thread_num; i++)
	{
	  (params_array + i)->coef = coef;
	  if (met_it.met == 'a')
	    {
	      (params_array + i)->h = h;
	    }
	  (params_array + i)->method = met_it.met;
	  (params_array + i)->thr_id = i + 1;

	  switch (met_it.met)
	    {
	    case 'a':
	      pthread_create (&threads[i], NULL, simpson, &params_array[i]);
	      break;
	    case 'b':
	      pthread_create (&threads[i], NULL, montecarlo,
			      &params_array[i]);
	      break;

	    }

	  for (i = 0; i < thread_num; i++)
	    pthread_join (threads[i], NULL);	//Se espera a que los thread terminen de calcular

	  pthread_mutex_destroy (&params.mutex);	//Se destruye el mutex
	  pthread_cond_destroy (&params.done);

	  switch (met_it.met)
	    {
	    case 'a':
	      pi = sum * h;	//Termino de Calcular Pi
	      result.exact = pi;	//Meto el resultado en la estructura de los resultados
	      break;
	    case 'b':
	      pi = (long double) (sum / met_it.it) * 4;	//Termino de Calcular Pi
	      result.exact = pi;	//Meto el resultado en la estructura de los resultados
	      break;
	    }

	  end = clock ();

	  sum = 0.0;		//Limpio la variable compartida

	  ms = (double) (end - begin) / CLOCKS_PER_SEC;	//Se calcula el tiempo total del cálculo

	  write_result (sd_conn, ms, met_it.it, met_it.met, result);

	}

      free (threads);
      close (fd);
      close (sd_conn);
      return;
    }
}
