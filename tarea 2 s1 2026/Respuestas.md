# Respuestas a Preguntas Teóricas - Tarea 2 EDD

**Pregunta 1: ¿Cuál es la complejidad de insertar un elemento?**
En promedio es O(log n). Al recorrer el árbol usas los pesos para descartar ramas, por lo que vas dividiendo la búsqueda a la mitad. Al llegar a la hoja, insertar el carácter y correr el resto toma un tiempo O(w), pero como 'w' es una constante, se asume como O(1). En el peor caso, si el árbol se degenera y queda como una lista, la complejidad empeora a O(n).

**Pregunta 2: ¿Cuál es la complejidad de eliminar un elemento?**
Es igual que al insertar: O(log n) en promedio. Te demoras O(log n) bajando por los nodos internos hasta encontrar la hoja correcta. Una vez encontrada, borrar el carácter y reacomodar el string toma un tiempo O(w), que es constante. Al igual que en la inserción, si el árbol pierde su balance, el peor caso cae a O(n).

**Pregunta 3: ¿En qué afecta la buena selección del valor de límite de tamaño w del string contenido en las hojas?**
De "w" depende que tan rápido encuentra y que tanta memoria ocupa el arbol. 
* Si 'w' es muy grande: Tienes pocos nodos pero arreglos muy largos. Buscar es rápido, pero al insertar o borrar tienes que mover demasiados caracteres, acercando el costo a O(n).
* Si 'w' es muy chico: Los arreglos son cortos, pero el árbol se llena de nodos y crece mucho en altura. Gasto más memoria guardando punteros y el recorrido hacia abajo es mas lento por la cantidad de niveles que tiene que recorrer.

**Pregunta 4: ¿Suponiendo que todas las inserciones ocurren en un lado del árbol, la complejidad seguirá siendo la expresada normalmente? ¿En caso de que no, cómo podría ser arreglada?**
No, comienza a parecerse a un arbol degenerado. Si insertas todo por el mismo lado (por ejemplo, escribiendo siempre al final de la línea), el árbol no se ramifica y crece hacia un solo lado. Su altura pasa a ser 'n', así que las operaciones pasan de O(log n) a O(n). 
Para arreglar esto, habría que hacer un codigo de autobalanceo que rote los nodos similares a los realizados en arboles AVL.

**Fuentes Citadas:**
* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press. (Capítulo 12: Binary Search Trees).
**Fuentes Citadas:**
* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press. (Capítulo 12: Binary Search Trees).
