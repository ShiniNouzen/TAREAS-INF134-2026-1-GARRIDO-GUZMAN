# Tarea 2 - Estructuras de Datos (INF-134)

## Integrantes
* **Martín Guzmán** -Rol:202473103-3
* **Axel Garrido**- Rol:

## Especificaciones Técnicas
* **Sistema Operativo:** Ubuntu (Linux)
* **Lenguaje:** C++11
* **Compilador:** g++ (GCC)

## Descripción del Funcionamiento
El código implementa un Árbol Binario modificado como TDA Linea para gestionar los datos de un editor de texto. En vez de guardar la información en un solo arreglo y sufrir el costo O(n) al desplazar posiciones, el texto se divide y almacena en fragmentos dentro de los nodos hoja, con un límite máximo de tamaño `w`. 
Los nodos internos no contienen texto, sino que almacenan un "peso" o zancada, equivalente a la suma total de caracteres presentes en su subárbol izquierdo. Esto permite localizar índices de texto rápidamente navegando por las ramas en tiempo logarítmico O(log n) mediante la resta y evaluación de posiciones contra los pesos.

## Instrucciones de Ejecución
1. Abrir la terminal en el directorio del proyecto.
2. Compilar el código fuente: `g++ -Wall -Wextra -std=c++11 -o tarea2 main.cpp`
3. Ejecutar el programa: `./tarea2`
