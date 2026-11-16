# Tarea-6
# Árboles y Grafos Curso: Programación III  

Implementación de un BST iterativo, un Red-Black Tree y algoritmos
iterativos DFS y BFS

## Integrantes
- Italo Mendez
- Nicolas Trillo

## Ejercicio 1(main): BST iterativo

Al insertar n valores distintos en orden ascendente, cada nuevo nodo se agrega como hijo derecho del anterior, formando una cadena de altura h = n − 1. Buscar o insertar un valor mayor que todos los existentes requiere recorrer n nodos; por ello, el costo en el peor caso es Θ(n), y por tanto O(n).

## Ejercicio 2: Red-Black Tree

Si b es la altura negra, un Red-Black contiene al menos 2^b − 1 nodos, por lo que b ≤ log₂(n + 1). Como no existen dos nodos rojos consecutivos, su altura cumple h ≤ 2b ≤ 2log₂(n + 1), garantizando O(log n). Al insertar del 1 al 20, el BST alcanza altura 19 y el Red-Black, 5.

## Ejercicio 3: DFS iterativo

DFS permite explorar cada camino raíz-hoja manteniendo en pilas el camino actual y su suma. Al llegar a una hoja se compara la suma con K; si coincide, se devuelve el camino. Como cada nodo se procesa una cantidad constante de veces, el tiempo es O(n) y el espacio auxiliar es O(h + 1).

## Ejercicio 4: BFS iterativo

BFS procesa los nodos por niveles y de izquierda a derecha: un nodo después de una posición nula indica que el árbol no es completo; la mayor cantidad de nodos en un nivel determina el ancho máximo; y la primera hoja encontrada tiene profundidad mínima porque los niveles se visitan en orden creciente. Cada algoritmo requiere O(n) tiempo y O(w) espacio auxiliar, donde w es el ancho máximo.

## Resultados

Al insertar los valores del 1 al 20 en orden ascendente, el BST alcanza una altura de 19 y el Red-Black una altura de 5.
