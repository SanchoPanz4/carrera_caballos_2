#include <curses.h>
#include <mutex>
#include <vector>

class Caballo{

    public :
    int posicion_x;
	int posicion_y;
    int suerte;
    char caracter;
};

class hipodromo{
    private:
	int n_caballos;
	int pos_x;						//posicion de la ventana
	int pos_y;						//posicion ventana
	int largo_x;					//largo pista
	int largo_y;					//ancho pista
	std::mutex mutex_caballo; 		//declaramos un mutex para evitar choques a la hora de mover el caballo
	WINDOW *pista;
	int pos_llegada_x;
	std::mutex mutex_ganadores; 	//mutex que va a servir para que los caballos vayan entrando de a uno al vector ganadores, el orden se mantiene
	std::vector<Caballo> ganadores;	//arreglo dinamico que va a guardar caballos
	int vueltas_a_correr;//deben ser mayor igual a 1
	public:
	Caballo caballos[7];
	hipodromo(int pos_y,int pos_x, Caballo caballos_ingreso[7]);	//constructor, toma arreglo 7 caballos y posicion de hipodromo en pantalla
	std::vector<Caballo> ganador();									//devuelve el vector entero de ganadores

	void mod_caballo_cantidad(int nuevo_n);	//modificar cantidad caballos
	int mod_largo();						//modificar tamaño pista
	void add_largo();						//llamar solo cuando se quiera añadir 1 espacio horizontal
	void quitar_largo();					//llamar solo cuando se quiera quitar 1 espacio horizontal
	void mover_caballo(Caballo caballo_que_se_mueve);
	void carrera(); 	//comenzar carrera, contiene el loop de la carrera , al final ordena en orden de llegada a los caballos.
	void carrera_hilo(Caballo caballo_que_corre);
	void limpiar_ganadores();
	void resetear_caballo(Caballo &caballo_reseteado);//resetea caballo a inicio
	void mod_vueltas(int vueltas);//modifica las vueltas a realizar
};
