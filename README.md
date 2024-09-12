# INFO198_SO.cpp

## Descripcion
Programa propuesto en el curso INFO198 Sistemas Operativos donde se creara un sistema operativo a lo largo del semestre, donde se podra ejecutar ingresando varaiables descritas mas abajo.

Este programa fue creado usando C++.

## Requisitos
* Ubuntu 22.04 o superior
* g++ 17 o superior
* git 2.34.1 o superior

## Instalación
En la carpeta donde se desea guarda el programa, abrir la terminal y ejecutar el siguiente comando git:

```cmd 
  git clone https://github.com/Acement/INFO198.git
```

Luego de clonar el repositorio, mover la terminal a la carpeta usando el siguiente comando:

```cmd
  cd INFO198/
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

| Argumento | Descripcion |
| -------- | ----------- |
| u | Especifica el usuario |
| p | Especifica la contraseña del usuario |
| t | Especifica un texto ingresado |
| v | Especifica un vector de numeros |
| n | Especifica un numero entero |

---Precaucion--- 
t y v necesitan ingresarse con comillas

## Funciones

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

* Procesar Archivos:
El programa procesa todos los archivos de una extension de una carpeta y guardar los conteos de palabras en otra carpeta.
