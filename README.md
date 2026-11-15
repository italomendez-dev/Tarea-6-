# Tarea-6
# Tarea 6: Árboles y Grafos Curso: Programación III  

Implementación de un BST iterativo, un Red-Black Tree y algoritmos
iterativos DFS y BFS

## Archivos

- ejercicio1.cpp: BST iterativo y análisis de degradación.
- ejercicio2.cpp: Red-Black Tree y comparación con BST.
- ejercicio3.cpp: búsqueda de un camino raíz-hoja con suma K.
- ejercicio4.cpp: árbol completo, ancho máximo y profundidad mínima.

## Convenciones

La altura se mide en aristas:

- Un árbol vacío tiene altura -1.
- Un árbol con un solo nodo tiene altura 0.
- La raíz tiene profundidad 0.
- La profundidad mínima del árbol vacío se representa con -1.

Los árboles de búsqueda no insertan valores duplicados.

## Ejercicio 1: BST iterativo

Se implementan:

- Inserción iterativa.
- Eliminación iterativa.
- Recorrido in-order utilizando std::stack.
- Cálculo iterativo de altura.

La eliminación considera tres casos:

1. Nodo sin hijos: se elimina directamente.
2. Nodo con un hijo: su enlace se reemplaza por el hijo.
3. Nodo con dos hijos: se copia el sucesor in-order y se elimina
   dicho sucesor. El sucesor es el menor del subárbol derecho.

### Prueba

Se insertan los valores del 1 al 20 en orden ascendente.
Luego se eliminan los valores 5 y 15.

Resultados:

- Altura inicial: 19.
- Altura después de eliminar: 17.
- In-order: 1 2 3 4 6 7 8 9 10 11 12 13 14 16 17 18 19 20.

### Demostración de la degradación

Sean n claves distintas insertadas en orden estrictamente ascendente:

x1 < x2 < ... < xn.

Por inducción, después de insertar k claves, el BST es una cadena
de k nodos conectados mediante hijos derechos.

Caso base: para k = 1 existe solamente la raíz.

Paso inductivo: si el árbol con k claves es una cadena derecha,
x(k+1) es mayor que todas las claves existentes. Por lo tanto,
su inserción recorre los k nodos y lo agrega al extremo derecho.
La nueva cadena tiene k + 1 nodos.

En consecuencia:

h(n) = n - 1.

Buscar la clave máxima requiere visitar n nodos. Insertar una nueva
clave mayor que todas también requiere recorrer n nodos.
Eliminar la clave máxima requiere localizarla recorriendo la cadena.

Por tanto, estas operaciones tienen costo Θ(n) en el peor caso,
en lugar de garantizar O(log n).

El costo total de construir el árbol con n inserciones ascendentes es:

Σ desde k = 1 hasta n de (k - 1)
= n(n - 1) / 2
= Θ(n²).

### Complejidad

- Inserción: O(h).
- Eliminación: O(h).
- Recorrido in-order: O(n), con espacio auxiliar O(h + 1).
- Cálculo de altura: O(n), con espacio auxiliar O(h + 1).

## Ejercicio 2: Red-Black Tree

La inserción comienza como en un BST y agrega el nuevo nodo rojo.

Después se corrigen los posibles incumplimientos:

- Si el padre es negro, no se necesita corregir.
- Si el padre y el tío son rojos, se recolorean.
- Si el padre es rojo y el tío es negro o nulo, se utilizan
  rotaciones y recoloración.
- Al finalizar, la raíz se pinta de negro.

Se implementan rotación izquierda y rotación derecha.

### Verificación formal

El método esValido comprueba:

1. Cada nodo tiene uno de dos colores, representados mediante bool.
2. La raíz es negra.
3. Ningún nodo rojo tiene un hijo rojo.
4. Los caminos hacia hojas nulas tienen igual cantidad de negros.
5. Las hojas nulas se consideran negras.

Además, verifica el orden del BST y los enlaces hacia los padres.

El verificador devuelve la altura negra de cada subárbol.
Si las alturas negras de sus hijos no coinciden, devuelve -1
para indicar que existe una propiedad incumplida.

### Comparación experimental

Se insertan los mismos valores del 1 al 20 en orden ascendente,
sin eliminaciones en ninguno de los dos árboles.

Resultados obtenidos:

- Altura del BST: 19.
- Altura del Red-Black Tree: 5.
- Propiedades válidas después de cada inserción: true.

La comparación utiliza los árboles antes de las eliminaciones
del ejercicio 1 para mantener la misma cantidad de elementos.

Se imprime el recorrido pre-order de ambos árboles.
En el Red-Black se muestra R para rojo y N para negro.
NIL representa un hijo nulo.

Los marcadores NIL permiten reconstruir la estructura exacta
a partir del recorrido pre-order.

### Demostración de altura logarítmica

Sea b(x) la cantidad de nodos negros desde x hasta una hoja NIL,
sin contar x, pero incluyendo NIL.

Todos esos caminos tienen la misma cantidad de negros.

Demostraremos que el subárbol de x contiene al menos:

2^b(x) - 1 nodos internos.

Caso base: un nodo NIL tiene b = 0 y contiene 0 nodos internos:

0 = 2^0 - 1.

Paso inductivo: si x tiene altura negra b, cada hijo tiene altura
negra b o b - 1, dependiendo de su color.

Aplicando la hipótesis inductiva a ambos hijos:

n(x) >= 1 + 2(2^(b - 1) - 1)
     = 2^b - 1.

Por lo tanto, para la raíz:

n >= 2^b - 1

b <= log2(n + 1).

Además, no pueden existir dos nodos rojos consecutivos.
En un camino desde la raíz negra hasta NIL hay como máximo
tantos nodos rojos como negros.

Si h es la altura en aristas hasta un nodo interno:

h <= 2b.

Finalmente:

h <= 2 log2(n + 1).

Por tanto:

h = O(log n).

### Complejidad

- Inserción y corrección: O(log n).
- Cada rotación: O(1).
- Verificación completa: O(n).
- Cálculo de altura: O(n).
- Recorrido pre-order: O(n).

La prueba verifica todo el árbol después de cada inserción.
Ese chequeo adicional cuesta O(n) por inserción; no forma parte
del costo O(log n) de insertar y corregir.

## Ejercicio 3: DFS iterativo avanzado

Se busca un camino desde la raíz hasta una hoja cuya suma sea K.

Se utilizan exclusivamente estructuras std::stack y no hay recursión.

Cada estado guarda:

- El nodo que se procesará.
- La suma de sus antecesores.
- Un indicador de entrada o salida.

Al entrar a un nodo se agrega su valor al camino.
Al terminar de explorar sus hijos se retira del camino.

Solo se acepta una suma igual a K cuando el nodo es una hoja.

No se descartan caminos por superar K, por lo que el algoritmo
también permite valores negativos.

### Justificación de DFS

La pila conserva el orden de exploración en profundidad.

Por el orden LIFO, el evento de salida de un nodo se procesa después
de todos los eventos de sus descendientes. Por eso, al entrar a un
nodo, la pila camino contiene exactamente sus antecesores.

Al agregar su valor, camino representa el recorrido raíz-nodo y
la suma almacenada coincide con la suma de ese recorrido.

Cada nodo se visita una vez. En consecuencia, se consideran todas
las hojas y todos los posibles caminos raíz-hoja.

DFS resulta adecuado porque permite mantener el camino actual
y retroceder al terminar una rama.

### Prueba

Para K = 22:

5 -> 4 -> 11 -> 2

La suma es:

5 + 4 + 11 + 2 = 22.

Para K = 100 no existe un camino válido.

### Complejidad

- Tiempo: O(n) en el peor caso.
- Espacio auxiliar: O(h + 1).

Cada nodo genera un evento de entrada y uno de salida.
Las pilas conservan el camino activo y las ramas pendientes.

## Ejercicio 4: BFS iterativo avanzado

Se utiliza exclusivamente std::queue como estructura auxiliar.
Ninguna función utiliza recursión.

### Árbol completo

Un árbol es completo si todos sus niveles están llenos,
excepto posiblemente el último, que debe llenarse de izquierda
a derecha.

BFS procesa las posiciones por nivel y de izquierda a derecha.

Una vez encontrada una posición nula, ninguna posición posterior
puede contener un nodo.

El algoritmo activa la variable hueco al encontrar el primer nulo.
Si después aparece un nodo, el árbol no es completo.

Esta condición es equivalente a que no existan espacios vacíos
antes de un nodo en el orden por niveles.

### Ancho máximo

El ancho de un nivel es la cantidad de nodos existentes en él.

Al comenzar cada iteración externa, la cola contiene exactamente
los nodos del nivel actual.

Se guarda su tamaño y se procesan únicamente esos nodos.
Sus hijos quedan en la cola para la siguiente iteración.

El mayor tamaño registrado es el ancho máximo del árbol.

### Profundidad mínima

BFS visita los nodos en orden no decreciente de profundidad.

Por tanto, la primera hoja encontrada tiene la menor profundidad
entre todas las hojas del árbol.

El contador nivel indica la cantidad de aristas desde la raíz.

### Pruebas

Árbol A:

- Raíz 1.
- Hijos de 1: 2 y 3.
- Hijos de 2: 4 y 5.

Resultados:

- Completo: true.
- Ancho máximo: 2.
- Profundidad mínima: 1.

Árbol B:

- Raíz 1.
- Hijos de 1: 2 y 3.
- El nodo 2 tiene hijo derecho 4, pero no hijo izquierdo.

Resultados:

- Completo: false.
- Ancho máximo: 2.
- Profundidad mínima: 1.

Árbol vacío:

- Completo: true.
- Ancho máximo: 0.
- Profundidad mínima: -1.

### Complejidad

Cada algoritmo visita como máximo O(n) nodos o posiciones.

- Tiempo por algoritmo: O(n).
- Espacio auxiliar: O(w), donde w es el ancho máximo,
  para un árbol no vacío.
