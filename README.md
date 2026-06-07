# Tarea 1 Sistemas Operativos
- Programa en C++ que simula carrera de caballos
- Se requiere terminal con tamaño de pantalla completa para que funcione

## Integrantes
- Cristian Sanchez
- Edinson Ramos
- Esteban Cadiz

## Compilacion
- Programa fue hecho con la libreria ncurses y compilado con gcc en linux, principalmente en Ubuntu.
- Para compilar es necesario ingresar:
```
g++ ./main.cpp ./carreras.cpp -o main -lncurses
```
## Uso 
- Programa se controla con las flechas. Se usa Enter para acceder a las opciones. Cuando se pide input para cambiar algo, ya sea el largo del hipodromo o la suerte de los caballos, se tiene que cambiar con las flechas. En la suerte se guarda con enter el valor.
- La aplicacion se debe abrir desde un terminal como powershell en pantalla completa para que funcione
- En ciertos terminales como powershell se debe colocar el terminal en pantalla completa y luego usar el comando clear para que se actualice el tamaño de este
- En caso de no desplegar los mensajes porque no cabe en la pantalla, se recomienda disminuir el tamaño de la fuente del terminal, por convencion es con ctrl -
- Comando para abrir estando en directorio de proyecto
```
./main
```
