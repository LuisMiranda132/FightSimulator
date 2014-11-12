Instrucciones:

Para poder correr el proyecto se necesita pyevolve. Para instalarlo:

sudo apt-get install python-pyevolve

Para correr el proyecto:

python gabil.py <archivoEntrenamiento> <archivoValidacion> <selector> <fitness> <tasaMutacion> <tasaCrossover>
selector y fitness deben ser 1(Rank/Fitness Standard) o 2(Ruleta/Penalizar Tamaño)

Se incluyen archivos de entrenamiento(iris70.data) y validación(iris30.data) con
el formato correcto.

El programa retorna el mejor individuo y el porcentaje de éxito
