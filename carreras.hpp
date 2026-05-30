#include <curses.h>

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
	int pos_x;//posicion de la ventana
	int pos_y;//posicion ventana
	int largo_y;
	int largo_x;
	WINDOW *pista;
	int pos_llegada_x;

    public:
	int gana;
	Caballo caballos[5];
	hipodromo(int pos_y,int pos_x, Caballo caballos_ingreso[5]);//constructor, toma arreglo 5 caballos y posicion de hipodromo en pantalla
	char ganador();

	//modificar cantidad caballos
	void mod_caballo_cantidad(int nuevo_n);
	//modificar tamaño pista
	void mod_largo();
	void add_largo();//llamar solo cuando se quiera añadir 1 espacio horizontal
	void quitar_largo();//llamar solo cuando se quiera quitar 1 espacio horizontal

	void mover_caballo(Caballo caballo_que_se_mueve);
	//comenzar carrera
	void carrera(); //contiene el loop de la carrera , al final ordena en orden de llegada a los caballos.
	



	
};
