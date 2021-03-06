# Trabajo Final Computación 2 - Universidad de Mendoza




- **Alumno**: Francisco J. Revoredo (5810) (Ingeniería en Informática)
- **Año**: 2015
- **Materia**: Computación 2 

---

### Descripción del Proyecto:
Software para cálculos paralelizables, distribuidos en un número arbitrario de threads.
La interfaz de usuario está montanda en un servidor web (C), con soporte Html+CSS, por lo que la interfaz de usuario
es casi totalmente independiente de la lógica de programación. El puerto para ingresar es el 5000 (Ejemplo localhost:5000).
Las consultas al servidor se manejan de forma concurrente con multiprocesamiento, y a su vez cada proceso
crea una cantidad de hilos (arbitraria) para realizar los cálculos paralelizables.

---

### Criterio de Selección de los Algoritmos:
Teniendo en cuenta la ley de Amdahl, la mejora que se puede obtener en el tiempo de cómputo de determinado algoritmo depende de la
 cantidad de código paralelizable de dicho algoritmo. Sabiendo esto, se eligieron algoritmos que contienen un porcentaje total 
o casi total de código paralelizable, conocidos como "Algoritmos perfectamente paralelos". Esto quiere decir que no existen dependencias de los datos, lo que tendería a serializar los cálculos.

---

### Lista de Cálculos Disponibles

1. **Cálculo de Pi por Regla de Simpson**
2. **Cálculo de Pi por Montecarlo**

---

### Descripción de los Métodos y su Implementación



- **Cálculo de Pi por Regla de Simpson**

 ![alt text](https://github.com/franrevoredo/final-compu2/blob/master/img/simpson.jpg "Simpson")

La regla de simpson es un método de integración numérica para obtener la aproximación
 de una integral.
Sabiendo que la integral entre 0 y 1 de [4/(1+x²)] es igual a Pi, 
solamente hay dividir el intervalo de integración entre el total de threads involucrados 
y hacer que cada thread calcule un intervalo definido de la integral en cuestión. Una vez obtenido cada resultado parcial 
con sumar todos los resultados parciales se obtiene la aproximación de pi.
(Nota: Cada thread debe calcular la integral en un intervalo único, y la suma de todos los intervalos debe ser el intervalo original de la integral para que el cálculo sea correcto.)


- **Cálculo de Pi por Montecarlo**

![alt text](https://github.com/franrevoredo/final-compu2/blob/master/img/montecarlo.jpg "Montecarlo")

Los métodos montecarlo son algoritmos que se basan en muestras aleatorias 
(suelen ser pseudo-aleatorias para simplificar los cálculos) para obtener aproximaciones numéricas. 
Sabiendo esto, podemos aproximar el valor de Pi partiendo de un circulo de radio 1 dentro de un cuadrado de lado 2 .
A partir de puntos al azar (uniformemente distribuidos) dentro del cuadrado, la probabilidad de que dicho punto
caiga dentro del area del circulo es de Pi/4 (Es la razón entre las áreas). Entonces contado la frecuencia
del suceso y multiplicandola por cuatro podemos obtener una aproximación de Pi. Entre mayor sea la muestra, más preciso va a ser el resultado.
Se puede dividir la muestra total en cada thread y realizar experimentos independientes en cada thread. Para que
los experimentos sean verdaderamente independientes es necesario que cada thread tenga un generador pseudoaleatorio independiente en cada thread.
Para esto, el seed que se le debe asignar al generador (rand_r(&seed)) de cada thread, debe ser distinto. Para solucionar
este problema de seeds distintas para un numero no determinado de threads (y sabiendo que los "thread id" proporcionados por pthread_self()
 son unsigned int al igual que las seeds) utilizamos como seed el "thread id" que el proceso le asigna a cada thread.
Una vez cada thread calculó el el numero de ocurrencias parcial, el thread principal es el encargado de calcular la frecuencia a partir del tamaño
 de la muestra y de la suma de las ocurrencias parciales. Luego, con solo multiplicar esta frecuencia por cuatro, obtenemos nuestra aproximación final a Pi.


