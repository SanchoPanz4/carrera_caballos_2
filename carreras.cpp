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
#include <chrono>//para los sleep en las threads
#include <string>


	hipodromo::hipodromo(int pos_y_ingreso,int pos_x_ingreso, Caballo caballos_ingreso[7])
    {
        n_caballos=7;//comienza con 7 por defecto
        
        //valores minimos x e y
        largo_x=48; //largo minimo 30 + 18 espacio para info
        largo_y=(n_caballos+1)*2+1;//dos espacios por caballo mas el espacio para la sumatoria

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
	sumatoria_metros=0;
	sumatoria_vueltas=0;


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
            std::string texto;
	    //imprime en la ventana para que el numero cambie
	    texto="Largo pista "+ std::to_string(largo_x - 18);
	    mvwprintw(menuwin, 4, (50 - texto.length()) / 2, texto.c_str());
	    wrefresh(menuwin);
            int input=(int)wgetch(pista);

	    switch (input)
            {
                case KEY_LEFT:
                    quitar_largo(); // quita un largo
		    texto="Largo pista "+ std::to_string(largo_x - 18);
		    mvwprintw(menuwin, 4, (50 - texto.length()) / 2, texto.c_str());
		    wrefresh(menuwin);
		    break;

                case KEY_RIGHT:
                    add_largo();
		    texto="Largo pista "+ std::to_string(largo_x - 18);
		    mvwprintw(menuwin, 4, (50 - texto.length()) / 2, texto.c_str());
		    wrefresh(menuwin);
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
        

         

        int min_x_pantalla=49; //largo minimo de pista 30 + lo que quita los numeros
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

    void hipodromo::mover_caballo(Caballo &caballo_que_se_mueve) {

        caballo_que_se_mueve.posicion_x++;     // Actualizacion de posicion Caballo x

    mvwprintw(pista,caballo_que_se_mueve.posicion_y,caballo_que_se_mueve.posicion_x,"%c",caballo_que_se_mueve.caracter);    //Reimpresion de posicion de x
    mvwprintw(pista,caballo_que_se_mueve.posicion_y,caballo_que_se_mueve.posicion_x-1," ");  //borrado de paso de x por la pista
    mvwprintw(pista,caballo_que_se_mueve.posicion_y, 1, "%4dm V:%2d |", caballo_que_se_mueve.metros_recorridos, caballo_que_se_mueve.vueltas_realizadas);
    };


    // comenzar carrera
void hipodromo::carrera()
{
    sumatoria_metros=0;//setea a 0 sumatorias para empezar
    sumatoria_vueltas=0;
    wclear(pista);
    box(pista,0,0);
    wrefresh(pista);
    std::vector<std::thread> threads;//se va a usar un vector para threads para elegir dinamicamente cuantas se inician
    //Imprime los caballos en su posicion inicial
    for(int i=0;i<n_caballos;i++)
    {
        caballos[i].posicion_x = 1 + 15; //+15 es para el desplazamiento por el texto con informacion
        caballos[i].metros_recorridos = 0;
    }

    noecho(); //No retorno al pulsar tecla

    //Imprime lineas de pista
    for(int i=2;i<largo_y-2;i=i+2)
    {
        for(int j=15;j<largo_x-1;j++) //int j=15 es por el desplazamiento debido al texto con info
        {
            mvwprintw(pista,i,j,"-");
        }
    }
    wrefresh(pista);
    threads.reserve(7);//se guarda espacio para max 7 caballos
    for (int i = 0; i < n_caballos; i++)
    {
        threads.push_back(std::thread(&hipodromo::carrera_hilo,this,caballos[i])); // se le añade threads declarandolas con el constructor
										   // la forma del constructor es
										   // thread(funcion,objeto donde corre, argumentos de la funcion)
										   // ahora cada thread corre con la funcion carrera_hilo y con el caballo i
    }
    for (int i = 0; i < n_caballos; i++)
    {
        if(threads.at(i).joinable())//revisamos que se puedan unir con joinable en todas las threads
        {   
            threads.at(i).join();//si se pueden unir es porque estan andando y esperamos que terminen para seguir el programa
        }
    }
};


void hipodromo::carrera_hilo(Caballo caballo_que_corre)
{
srand(time(NULL) * (int)caballo_que_corre.caracter); // Valor semilla sea distinto por cada caballo
caballo_que_corre.vueltas_realizadas=1;//vueltas comienzan desde 1
while (caballo_que_corre.vueltas_realizadas <= vueltas_a_correr)//mientras no haya cumplido las vueltas
{
    int random = (rand() % 100) + 1;
    if (random <= caballo_que_corre.suerte)
    {
        mutex_caballo.lock();               //se bloquea acceso a las funciones para evitar que cada caballo intente imprimir en pantalla al mismo tiempo
	sumatoria_metros++;//se le añade el metro recorrido
        caballo_que_corre.metros_recorridos++;//caballo corre 1 metro
        mover_caballo(caballo_que_corre);   // mueve Caballo
	mvwprintw(pista,15, 1, "%4dm V:%2d |",sumatoria_metros,sumatoria_vueltas);//imprime actualizacion
        wrefresh(pista);
	if(caballo_que_corre.posicion_x==pos_llegada_x)//en cuanto cumpla la vuelta
	{
	    caballo_que_corre.vueltas_realizadas++;
	    sumatoria_vueltas++;//se suma vuelta hecha

	    //compensan adicion extra de un metro al hacer mas de una vuelta
	    //sumatoria_metros--;
	    caballo_que_corre.metros_recorridos--;						  

	    resetear_caballo(caballo_que_corre);//lo devuelve al inicio
        if (vueltas_a_correr > 1){
            int metros_extra = sumatoria_vueltas - n_caballos;
            mvwprintw(pista,15, 1, "%4dm V:%2d |",sumatoria_metros- metros_extra,sumatoria_vueltas);//imprime actualizacion
        } else {
            mvwprintw(pista,15, 1, "%4dm V:%2d |",sumatoria_metros,sumatoria_vueltas);//imprime actualizacion
        }
        
	    
	    wrefresh(pista);
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
int hipodromo::get_largo_pista(){
    int largo= this->largo_x-18;
    return largo;//18 es el tamaño que se le da a los metros+vuelta

}
