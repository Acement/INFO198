# INFO198_SO.cpp

## Descripcion
Programa propuesto en el curso INFO198 Sistemas Operativos donde se creara un sistema operativo a lo largo del semestre, donde se podra ejecutar ingresando varaiables descritas mas abajo.

Este programa fue creado usando C++.

## Requisitos
* Ubuntu 22.04 o superior
* g++ 11.4.0 o superior
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
  g++ -I./include -o prog ./src/*.cpp INFO198_SO.cpp
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


