# ProyectoIA
Proyecto implementacion Backtracking GBJ para PPP

Andrés Herrera      201473593-6     andres.herrera.14@sansano.usm.cl

## Como ejecutar

Para compilar, ejecutar el comando `make` en consola.

Para la ejecucion, ejecutar el comando `make run {configuracion}`, donde {configuracion} es el nombre de algun archivo de configuracion en InstanciasPPP/Configuraciones, como ejemplo: config.txt.

Es posible eliminar archivos intermedios, para realizar este procedimiento, ejecutar el comando `make clean`

Si se quieren eliminar los archivos post compilacion, como el ejecutable, se puede realizar ejecutando el comando `make cleanall`

## Funcionamiento y modificacion de Problema

Para ver el estado actual del algoritmo, es necesario finalizar este. Al hacerlo se imprime el estado actual, junto con los indicadores.

Los archivos de configuraciones deben tener los yates anfitriones separados por espacio, de la siguiente forma:

config.txt

1 2 3 4 5 6 7

Si se desea utilizar capacidades, cantidades distintas de yates o distinta cantidad de periodos, se debe modificar el archivo PPP.txt.

Se realizó solo el problema completo, no se me ocurrió de que forma implementar la seccion sin asignar anfitriones.