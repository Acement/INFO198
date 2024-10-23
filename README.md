## INFO198_SO.cpp

## Descripcion
Programa propuesto en el curso INFO198 Sistemas Operativos donde se creara un sistema operativo a lo largo del semestre, donde se podra ejecutar ingresando varaiables descritas mas abajo.

Este programa fue creado usando C++.

## Requisitos
* Ubuntu 22.04 o superior
* g++ 17 o superior
* git 2.34.1 o superior
* Python 3.12.3 o superior
* pip 24.0 o superior
* Librerias para python:
  - python-decouple

## Instalación
En la carpeta donde se desea guarda el programa, abrir la terminal y ejecutar el siguiente comando git:

```cmd 
  git clone https://github.com/Acement/INFO198.git
```

Luego de clonar el repositorio, mover la terminal a la carpeta usando el siguiente comando:

```cmd
  cd INFO198/
```

Despues Setear las variables de entorno dentro del archivo .env:

```cmd
  USER_FILE_PATH='<Direccion del archivo de usuarios>'
  CANTIDAD_THREAD='<Cantidad de threads que se quiere utilizar en numeros>'
  MAPA_ARCHIVOS='<Direccion donde se quiera guardar el mapa de archivos>'
  STOP_WORDS='<Direccion del archivo stop word>'
  INPUT_DIR='>Direccion de la carpeta de archivos de entrada>'
  EXTENSION='<Extencion de los archivos de entrada>'
  OUTPUT_DIR='<Direccion de la carpeta donde se quiera guardar los archivos con el conteo de palabras>'
  INVERTED_INDEX='<Direccion del archivo invertedIndex,index>'
  ARRAY_THREADS='<Arreglo con la cantidad de threads a usar(1,2,4,...) separados por una coma>'
  REPETICIONES='<Cantidad de repeticiones que realizara la funcion analisis de performance>'
  DATOS='<Direccion donde se guarda los tiempos al realizar la funcion analisis de performance>'
  GRAFICO='<Direccion donde se guarda la imagen png con el grafico comparativo>'
```

Por ultimo compilar el programa con el siguiente comando:

```cmd
  make
```

## Ejecucion

Para ejecutar el programa, abrir una terminal en la carpeta donde se ubica este y ingresar el siguiente comando:

```cmd
  ./prog -u <Usuario> -p <Contraseña> -t <Texto> -v <Vector de numeros (1;2;3;4)> -n <Numero>
```


* Tipos de usuarios:

Usuario Generico: Puede usar el sistema sin tener los permisos para manejar los los otros usuarios
Admin: Ademas de usar el sistema puede listar, agregar y quitar usuarios


* Tabla de usuarios

| Argumento | Descripcion |
| -------- | ----------- |
| u | Especifica el usuario |
| p | Especifica la contraseña del usuario |
| t | Especifica un texto ingresado |
| v | Especifica un vector de numeros |
| n | Especifica un numero entero |

---Precaucion--- 
t y v necesitan ingresarse con comillas


* Mapa de libros:

Se guarda como:
```cmd
map.txt
```
Dentro se ve como:


```cmd
Nombre, ID
```
Donde:
| Argumento | Descripcion |
| -------- | ----------- |
| Nombre | Es el nombre que tiene el archivo de texto |
| ID | Numero asignado al realizar conteo de palabras del archivo de texto |

Se guarda dentro de la carpeta data


* Archivos de salida de conteo de palabra:

Se guarda como:

```cmd
ID.txt
```
ID es el mismo que en la seccion de arriba

Dentro se ve como:

```cmd
Palabra; Cantidad
```
Donde:
| Argumento | Descripcion |
| -------- | ----------- |
| Palabra | Es la palabra que se extrajo del archivo de texto |
| Cantidad | Es la cantidad de veces que la palabra esta dentro del archivo e texto |

Se guardan dentro de la carpeta word count


* Indice Invertido:

```cmd
invertedIndex.index
```
Dentro se ve como:

```cmd
Palabra;(ID1,Cantidad1);(ID2,Cantidad2);...
```
Donde:
| Argumento | Descripcion |
| -------- | ----------- |
| Palabra | La palabra dentro de los archivos de texto |
| IDN | Es la ID de uno de los archivo de texto |
| CantidadN | Es la cantidad de veces que la palabra se encuentra dentro del archivo de texto IDN|

Se guarda dentro de la carpeta data



## Funciones

* Ingreso automatica de variables de entorno:
El programa es capaz de ingresar al sistema variables de entorno guardadas en .env

* Ingreso de usuarios:
El programa puede ingresar Usuarios y contraseñas, con lo cual puede aceptar o negar el ingreso al Sistema

* Listar Usuarios:
El programa puede mostrar una lista de los usuarios que estan dentro de la base de datos

* Eliminar Usuarios:
El programa puede eliminar usuarios dentro de la base de datos, no se pueden eliminar usuarios administradores

* Menu:
El programa muestra un menu con opciones donde se puede elegir acciones dependiendo de la entrada de valores

* Detectar Palindrome:
El programa verifica si el texto ingresado por el usuario es un palindome

* Contar Vocales:
El programa puede contar las vocales dentro de el texto ingresado por el usuario

* Contar Letras:
El programa puede contar las letras dentro de el texto ingresado por el usuario

* Promedio y sumatoria de un vector:
El programa puede calcular la sumatoria y el promedio de un vector ingresado por el usuario

* Calcular Funcion:
El programa puede calcular el resulta de una funcion usando un numer ingresado por el usuario

* Contar Palabras: 
El programa cuenta las veces que se repite cada palabra en un archivo.

* Analisis de performance
El programa puede testear la performance, usando la funcion contar palabras y diferentes cantidades de threads, luego los guarda en un grafico

* Procesar Archivos:
El programa procesa todos los archivos de una extension de una carpeta y guardar los conteos de palabras en otra carpeta.

* Indice invertido:
El programa genera un archivo con las ocurrencia de palabras en los distintos archivos de entrada
