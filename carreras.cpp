#include "carreras.hpp"
#ifdef _WIN32
#include <windows.h>        //Uso de sleep en windows
#endif
#ifdef __linux__
#include <unistd.h>
#endif
#include <cstdlib>          //Uso de Rand
#include <ctime>
#include <thread> //uso de thread de c++ en vez de pthreads para mejor compatibilidad con las clases 
#include <chrono>
#include <string>


	hipodromo::hipodromo(int pos_y_ingreso,int pos_x_ingreso, Caballo caballos_ingreso[7])
    {
        n_caballos=7;//comienza con 7 por defecto
        
        //valores minimos x e y
        largo_x=48; //largo minimo 30 + 18 espacio para info
        largo_y=n_caballos*2+1;

	    vueltas_a_correr=1;
        pos_x=pos_x_ingreso;
        pos_y=pos_y_ingreso;
        
        pista=newwin(largo_y,largo_x,pos_y,pos_x);//se crea ventana 
        refresh();
        box(pista,0,0);
        wrefresh(pista);//muestra pista
        for(int i=0;i<n_caballos;i++)
        {
            caballos[i]=caballos_ingreso[i];
        }
        
        pos_llegada_x=getmaxx(pista)-2;//llegada por defecto es el anterior a llegar al borde

    };//constructor, toma arreglo 7 caballos y posicion de hipodromo en pantalla
    std::vector<Caballo> hipodromo::ganador(){
        return ganadores;
    };
	//modificar cantidad caballos
	void hipodromo:: mod_caballo_cantidad(int nuevo_n){
        n_caballos=nuevo_n; //numero de caballos a mostrar
    };
	//modificar tamaño pista
    
	int hipodromo:: mod_largo(WINDOW *menuwin){
        
        keypad(pista,true);//activa flechas para largo
        bool loop = true;
        while(loop)
        {
            int input=(int)wgetch(pista);

            std::string texto;
            switch (input)
            {
                case KEY_LEFT:
                texto="Largo pista "+ std::to_string(largo_x - 18);
                 mvwprintw(menuwin, 4, (50 - texto.length()) / 2, texto.c_str());
                 wrefresh(menuwin);
                    quitar_largo(); // quita un largo
                    break;

                case KEY_RIGHT:
                texto="Largo pista "+ std::to_string(largo_x - 18);
                 mvwprintw(menuwin, 4, (50 - texto.length()) / 2, texto.c_str());
                 wrefresh(menuwin);
                    add_largo();
                    break; // añade un largo

                case 'E'://valor ascii E
                    loop = false;
                    break;
                case 'e'://valor ascii e
                    loop = false;
                    break;
                default:
                    break;
            }
        }
        keypad(pista,false);//desactiva flechas pista
        return largo_x;
    };
    void hipodromo::add_largo() {
        
        int max_x_pantalla=getmaxx(stdscr);//largo maximo 
        if(largo_x<max_x_pantalla-11)//si no se pasa de tamaño pantalla, getmaxx - 10  es el borde de la pantalla
        {
            largo_x++;
            pos_llegada_x++;
            wresize(pista,largo_y,largo_x);
            //refresh();
            wclear(pista);//limpia la linea que queda atras
            wrefresh(pista);
            box(pista,0,0);
            
            wrefresh(pista);//aparece caja

        }

        //si se pasa no hace nada

    };    // llamar solo cuando se quiera añadir 1 espacio horizontal
    void hipodromo::quitar_largo() {
        

         

        int min_x_pantalla=30;
        //largo minimo 30
        if(largo_x-min_x_pantalla>=0)//si es negativo es  menor al minimo
        {
            mvwvline(pista,0,largo_x-1,' ',getmaxy(pista));//imprime espacios blancos donde estaba el borde
            wrefresh(pista);
            largo_x--;
            pos_llegada_x--;
            wresize(pista, largo_y, largo_x);
            //refresh();
            wrefresh(pista);
            box(pista, 0, 0);
            wrefresh(pista); // aparece caja
        }

    }; // llamar solo cuando se quiera quitar 1 espacio horizontal

    void hipodromo::mover_caballo(Caballo caballo_que_se_mueve) {
    mvwprintw(pista,caballo_que_se_mueve.posicion_y,caballo_que_se_mueve.posicion_x,"%c",caballo_que_se_mueve.caracter);    //Reimpresion de posicion de x
    mvwprintw(pista,caballo_que_se_mueve.posicion_y,caballo_que_se_mueve.posicion_x-1," ");  //borrado de paso de x por la pista
    mvwprintw(pista,caballo_que_se_mueve.posicion_y, 1, "%4dm V:%2d |", caballo_que_se_mueve.metros_recorridos, caballo_que_se_mueve.vueltas_realizadas);
    };


    // comenzar carrera
void hipodromo::carrera()
{
    wclear(pista);
    box(pista,0,0);
    wrefresh(pista);
    std::vector<std::thread> threads;
    //Imprime los caballos en su posicion inicial
    for(int i=0;i<n_caballos;i++)
    {
        caballos[i].posicion_x = 1 + 15; //+15 es para el desplazamiento por el texto con informacion
        caballos[i].metros_recorridos = 0;
    }

    noecho(); //No retorno al pulsar tecla

    //Imprime lineas de pista
    for(int i=2;i<largo_y;i=i+2)
    {
        for(int j=15;j<largo_x-1;j++) //int j=15 es por el desplazamiento debido al texto con info
        {
            mvwprintw(pista,i,j,"-");
        }
    }
    wrefresh(pista);
    threads.reserve(7);
    for (int i = 0; i < n_caballos; i++)
    {
        threads.push_back(std::thread(&hipodromo::carrera_hilo,this,caballos[i]));
    }
    for (int i = 0; i < n_caballos; i++)
    {
        if(threads.at(i).joinable())
        {   
            threads.at(i).join();
        }
    }
};


void hipodromo::carrera_hilo(Caballo caballo_que_corre)
{
srand(time(NULL) * (int)caballo_que_corre.caracter); // Valor semilla sea distinto por cada caballo
caballo_que_corre.vueltas_realizadas=1;
while (caballo_que_corre.vueltas_realizadas <= vueltas_a_correr)//mientras no haya cumplido las vueltas
{
    int random = (rand() % 100) + 1;
    if (random <= caballo_que_corre.suerte)
    {
        caballo_que_corre.posicion_x++;     // Actualizacion de posicion Caballo x
        caballo_que_corre.metros_recorridos++;
        mutex_caballo.lock();               //se bloquea acceso a las funciones para evitar que cada caballo intente imprimir en pantalla al mismo tiempo
        mover_caballo(caballo_que_corre);   // mueve Caballo
        wrefresh(pista);
	if(caballo_que_corre.posicion_x==pos_llegada_x-1)//en cuanto cumpla la vuelta
	{
	    caballo_que_corre.vueltas_realizadas++;
	    resetear_caballo(caballo_que_corre);//lo devuelve al inicio
	}
        mutex_caballo.unlock();
    }
std::this_thread::sleep_for(std::chrono::milliseconds(50));
}
//mutex para que accedan uno a la vez a arreglo de ganadores
//como es semaforo binario el orden se mantiene 
//porque tiene una fila
mutex_ganadores.lock();
ganadores.push_back(caballo_que_corre);
mutex_ganadores.unlock();
    return ;
}

void hipodromo:: limpiar_ganadores()
{
    //elimina los elementos
    ganadores.clear();

    ganadores.shrink_to_fit();//para evitar que quede memoria suelta por ahi
    return;
}
void hipodromo:: resetear_caballo(Caballo &caballo_reseteado)
{
	mvwprintw(pista,caballo_reseteado.posicion_y,caballo_reseteado.posicion_x," ");//borra caballo que llego para mandarlo al inicio
        caballo_reseteado.posicion_x = 15;//devuelve caballo al inicio
	mvwprintw(pista,caballo_reseteado.posicion_y,caballo_reseteado.posicion_x,"%c",caballo_reseteado.caracter);    //Reimpresion de posicion de x
	wrefresh(pista);
}
void hipodromo:: mod_vueltas(int vueltas){
    if(vueltas ==0)//no permite que sean 0, no las cambia si se coloca
	return;
    vueltas_a_correr=vueltas;
    return;
};
