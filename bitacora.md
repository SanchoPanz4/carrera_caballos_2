# Tarea 1
## Dia 10/04
- La reunion fue hecha mediante Discord
- Se logra hacer funcionar libreria pdcurses en Windows (implementacion de Ncurses para varias plataformas)
- Se define funciones a programar:
    - Hipodromo: Muestra el hipodromo en pantalla
    - Caballos: Define cuando se mueve, se va a usar funcion rand() de stdlib para decidir
    - Carrera: Por decidir
    - Ganador: Decide posicion de los caballos
- Familiarizarse con libreria pdcurses
## 12/04
- Se hace bocetos para la aplicacion y como se va a ver
- Se decide usar clases para algunos elementos
- Se decide hacer archivos de cabezera para elementos separados.
## 16/04
- Se define archivos de cabecera para las clases
- Se implementan ciertas funciones
- Se terminan menu y carrera, falta juntarlos con las clases
- La reunion fue hecha mediante discord
## 17/04
- Se junta todo lo hecho en main y carreras.cpp
- Reunion Hecha mediante discord

# Tarea 2


## 30/05
- Se decidio uso de libreria thread de C++ en vez de pthreads ya que es mas simple trabajar con clases que se usaron antes.
- se implemento carrera caballos corriendo en distintos hilos, se corrompia la pantalla por alguna razon
## 03/06 
- Se arreglo problema de hilos con un  mutex para que accedan a las funciones de impresion de ncurses una a la vez y evitar corrupcion
## 04/06
- Implementado nueva forma de decidir ganadores considerando que cada caballo es un hilo
## 05/06
- Se implementa vueltas, su contador y los metros que han corrido los caballos 
- Se ajusta maximo de caballos de 5 a 7
- Se implementa que se muestren metros largo de pista al cambiarla
