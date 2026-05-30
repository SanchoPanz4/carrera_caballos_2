#include <curses.h>
#include <string>
#include "carreras.hpp"

using namespace std;
void editar_caballos(hipodromo &hipo_);
void editar_hipodromo(hipodromo &hipo_);
void editar_largo_pista(int &largo_pista,hipodromo &hipo_);
void editar_cantidad_caballos(hipodromo &hipo_);
void editar_suerte_caballos(hipodromo &hipo_);
void editar_valor_suerte(int Caballo, hipodromo &hipo_);

void editar_hipodromo(hipodromo &hipo_)
{
    //clear();
    box(stdscr, 0, 0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //mvprintw(2, (xMax - 16) / 2, "EDITAR PISTA");

    int ancho = 50;
    WINDOW * menuwin = newwin(8, xMax-10 , 12, 5);
    box(menuwin, 0, 0);

    string choices[2] = {"Editar largo de pista","Volver"};
    int choice;
    int highlight = 0;

    keypad(menuwin, true);

    static int largo_pista = 50;

    while(1){
        box(menuwin, 0, 0);
        int ancho = getmaxx(menuwin);
        for (int i = 0; i < 2; i++){
            int x = (ancho - choices[i].length()) / 2;
            if (i == highlight)
            wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i + 2, x, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        wrefresh(menuwin);
        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_UP:
            highlight = (highlight - 1 + 2) % 2;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % 2;
            break;
        case 10:
            if (highlight == 0){
                editar_largo_pista(largo_pista,hipo_);
            }
            else if (highlight ==1 ) {
                delwin(menuwin);
                return;
            }
            break;
        }
    }

    mvwprintw(menuwin, 2, (ancho - 30) / 2, "Aqui se editara el largo de pista");

    wrefresh(menuwin);
    wgetch(menuwin); // esperar tecla
}

void editar_largo_pista(int &largo_pista,hipodromo &hipo_)
{
    //clear();
    box(stdscr, 0, 0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //mvprintw(2, (xMax - 22) / 2, "EDITAR LARGO PISTA");

    WINDOW *menuwin = newwin(8, 50, 12, (xMax - 50) / 2);
    keypad(menuwin, true);

    int valor = largo_pista;
    int choice;

    while (1)
    {
        werase(menuwin);
        box(menuwin, 0, 0);

        string texto = "Use flechas para editar pista";
        mvwprintw(menuwin, 2, (50 - texto.length()) / 2, texto.c_str());
        texto="Presione <E> para salir";
        mvwprintw(menuwin, 3, (50 - texto.length()) / 2, texto.c_str());
        wrefresh(menuwin);
        hipo_.mod_largo();
        
        wrefresh(menuwin);
        delwin(menuwin);
        return;
        
    }
}

void editar_caballos(hipodromo &hipo_)
{
    //clear();
    box(stdscr, 0, 0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //mvprintw(2, (xMax - 20) / 2, "EDITAR CABALLOS");

 
    WINDOW * menuwin = newwin (8, xMax-10, 12, 5);  
    box(menuwin, 0, 0);

    string choices[3] = {"Cantidad de caballos","Suerte de caballos","Volver"};
    int choice;
    int highlight = 0;

    keypad(menuwin, true);

    while(1){
        box(menuwin,0,0);
        int ancho = getmaxx(menuwin);
        for (int i = 0; i < 3; i++){
            int x = (ancho - choices[i].length()) / 2;
            if (i == highlight)
            wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i + 2, x, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        wrefresh(menuwin);
        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_UP:
            highlight = (highlight - 1 + 3) % 3;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % 3;
            break;
        case 10:
            if (highlight == 0)
                editar_cantidad_caballos(hipo_);
            else if (highlight == 1)
                editar_suerte_caballos(hipo_);
            else if (highlight == 2)
                return;
            break;
        }
    }
}

void editar_cantidad_caballos(hipodromo &hipo_)
{
    //clear();
    box(stdscr, 0, 0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //mvprintw(2, (xMax - 28) / 2, "CANTIDAD DE CABALLOS");

    WINDOW * menuwin = newwin(8, 30, 12, (xMax - 30) / 2);
    keypad(menuwin, true);

    int opciones[4] = {2, 3, 4, 5};
    int highlight = 0;
    int choice;

    while (1)
    {
        //werase(menuwin);
        box(menuwin, 0, 0);

        for (int i = 0; i < 4; i++)
        {
            string texto = to_string(opciones[i]);
            int x = (30 - texto.length()) / 2;
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i + 1, x, texto.c_str());
            wattroff(menuwin, A_REVERSE);
        }

        wrefresh(menuwin);
        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_UP:
            highlight = (highlight - 1 + 4) % 4;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % 4;
            break;
        case 10:
            hipo_.mod_caballo_cantidad(opciones[highlight]) ;//toma cantidad seleccionada
            delwin(menuwin);
            
            return; // vuelve a editar_caballos
        }
    }
}

void editar_suerte_caballos(hipodromo &hipo_)
{
    //clear();
    box(stdscr, 0, 0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //mvprintw(2, (xMax - 26) / 2, "SELECCIONAR Caballo");

    WINDOW * menuwin = newwin(8, 30, 12, (xMax - 30) / 2);
    keypad(menuwin, true);

    //static int suerte [5] = {50,50,50,50,50};

    string caballos[6] = {
        "Caballo 1",
        "Caballo 2",
        "Caballo 3",
        "Caballo 4",
        "Caballo 5",
        "Volver"
    };

    int highlight = 0;
    int choice;

    while (1)
    {
        werase(menuwin);
        box(menuwin, 0, 0);

        int ancho = getmaxx(menuwin);

        for (int i = 0; i < 6; i++)//imprime numeros de suerte actual
        {
            string texto;
            if (i < 5)
                texto = caballos[i] + " (" + to_string(hipo_.caballos[i].suerte) + ")";
            else
                texto = caballos[i];
            int x = (ancho - texto.length()) / 2;
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i + 1, x, texto.c_str());
            wattroff(menuwin, A_REVERSE);
        }

        wrefresh(menuwin);
        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_UP:
            highlight = (highlight - 1 + 6) % 6;
            break;

        case KEY_DOWN:
            highlight = (highlight + 1) % 6;
            break;
        case 10:
            if (highlight == 5){
                delwin(menuwin);
                return;
            }
            else{
                editar_valor_suerte(highlight,hipo_);
            }
    break;
        }
    }
}

void editar_valor_suerte(int Caballo,hipodromo &hipo_)
{
    //clear();
    box(stdscr, 0, 0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //mvprintw(2, (xMax - 22) / 2, "EDITAR SUERTE");

    WINDOW * menuwin = newwin(8, 40, 12, (xMax - 40) / 2);
    keypad(menuwin, true);

    int valor = hipo_.caballos[Caballo].suerte; // valor de suerte
    int choice;

    while (1)
    {
        werase(menuwin);
        box(menuwin, 0, 0);

        string texto1 = "Caballo " + to_string(Caballo + 1);
        string texto2 = "Valor: " + to_string(valor);

        mvwprintw(menuwin, 2, (40 - texto1.length()) / 2, texto1.c_str());
        mvwprintw(menuwin, 4, (40 - texto2.length()) / 2, texto2.c_str());

        wrefresh(menuwin);
        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_LEFT:
            if (valor > 1) valor--;
            break;

        case KEY_RIGHT:
            if (valor < 100) valor++;
            break;

        case 10:
            hipo_.caballos[Caballo].suerte= valor; //guardamos la suerte
            return; // vuelve a selección de Caballo
        }
    }
}

int main()
{
    initscr();               //iniciar curses
    noecho();               //no mostrar teclas
    cbreak();               // input inmediato

    //Obtener tamaño de pantalla
    int yMax, xMax;
    getmaxyx (stdscr, yMax, xMax);
    box(stdscr, 0, 0);
    
    //TITULO
    string titulo[] = {
"  ____    _    ____  ____  _____ ____    _    ",
" / ___|  / \\  |  _ \\|  _ \\| ____|  _ \\  / \\   ",
"| |     / _ \\ | |_) | |_) |  _| | |_)  / _ \\  ",
"| |___ / ___ \\|  _ <|  _ <| |___|  _ </ ___ \\ ",
"  \\____/_/   \\_\\_| \\_\\_| \\_\\_____|_| \\/_/   \\_\\",
"   ____    _    ____    _    _     _     ___  ____  ",
"  / ___|  / \\  | __ )  / \\  | |   | |   / _ \\/ ___| ",
" | |     / _ \\ |  _ \\ / _ \\ | |   | |  | | | \\___ \\ ",
" | |___ / ___ \\| |_) / ___ \\| |___| |__| |_| |___) |",
"  \\____/_/   \\_\\____/_/   \\_\\_____|_____\\___/|____/ "
};
int altura_titulo = 10;//altura titulo se va a usar de referencia para coordenadas de todo

    attron(A_BOLD);
    for (int i = 0; i < 10; i++) {
        mvprintw(i + 1, (xMax - titulo[i].length()) / 2, titulo[i].c_str());
    }
    attroff(A_BOLD);

    //crear ventana
    WINDOW * menuwin = newwin (8, xMax-10, altura_titulo + 2 , 5); // (altura, ancho, coordY, coordX)
    box (menuwin ,0,0);
    refresh();
    wrefresh(menuwin);
    
  Caballo arreglo_caballos[5];
    for(int i=0;i<5;i++)
    {
        arreglo_caballos[i].caracter = 65+i;//letras mayusculas como caracter de cabballo
        arreglo_caballos[i].posicion_x = 1;
        arreglo_caballos[i].posicion_y = i*2+1;
        arreglo_caballos[i].suerte = 50;
    }
    hipodromo hipo((altura_titulo+2+8)+2,5,arreglo_caballos);
    

    keypad(menuwin, true);   // habilitar flechas
    

    string choices [4] = {"Competir", "Editar Caballo", "Editar Hipodromo", "Salir"};
    int choice;
    int highlight = 0;
    WINDOW * resultado = newwin (5, 22, (altura_titulo+2+8)+2+15,5); // ventana que imprime resultado
    

    while(1){
        box(menuwin,0,0);

        int ancho = getmaxx(menuwin);
        for (int i = 0; i < 4 ; i++){
            int x = (ancho - choices[i].length()) / 2;
            if(i==highlight)
            wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, x, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_UP:
            highlight = (highlight - 1 + 4) % 4;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % 4;
            break;
        default:
            break;
        }
        if (choice == 10){
            switch (highlight){
                case 0:
                hipo.carrera();
               
                mvwprintw(resultado,1,1,"Caballo Ganador: %c",hipo.ganador());
                mvwprintw(resultado,2,1,"Suerte Ganador: %d",hipo.caballos[hipo.gana].suerte);
                box(resultado,0,0);
                wrefresh(resultado);
                break;
                
                case 1:
                editar_caballos(hipo);
                break;
                
                case 2:
                editar_hipodromo(hipo);
                break;
                
                case 3:
                endwin();
                return 0;
            }
        }
    }




    getch();
    endwin();

    return 0;
}