#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Yatecito{
    public:
        int periodo;
        bool visitado;
        Yatecito(){
            periodo = 0;
            visitado = 0;
        }
        void visitar(){
            visitado = true;
        }        
};
class Yate{
    public:
        int capacidad;
        int tripulacion;
        int cap_visita;
        int posicionYate;
        bool host;
        vector <Yatecito> otrosyates;
        Yate(int cantidad){
            host = false;
            vector <Yatecito> yates(cantidad) ;
            // cout << "Creado uwu" << endl;
            otrosyates = yates;
            // for (int i = 0; i < cantidad; i++){
            //     cout << yates[i].periodo << endl;
            // }
            // *otrosyates = Visita();
        }
        void PrintInfoYate(){
            cout << "Yate " << posicionYate+1 ;
            cout << " Capacidad: " << capacidad;
            cout <<  " Tripulacion: "<< tripulacion <<endl;
        }
        void PrintYates(){
            cout << posicionYate+1;
            if (host){
                cout<< " Anfitrión:\t ";
            }
            else{
                cout << " Visita:\t ";
            }
            for (int i = 0; i < otrosyates.size();i++){
                cout << otrosyates[i].periodo;
            }
            cout << endl;
        }
        void visita(int i){
            otrosyates[i].visitar();
        }
};

int main(void){
    
    // Carga de la instancia en memoria
    vector <Yate> yates;
    ifstream configfile;
    configfile.open("InstanciasPPP/InstanciasCSPLib/Ian01.txt", std::ifstream::in);
    string line;
    int cantidadYates;
    int periodos;
    if(configfile.is_open()){
        getline(configfile,line);
        cantidadYates = stoi(line);
        getline(configfile,line);
        periodos = stoi(line);
        for (int i = 0; i<cantidadYates;i++){
            yates.push_back(Yate(cantidadYates));
            yates[i].posicionYate = i;
        }
        int count = 0;
        while(getline(configfile,line,';')){
            string capacidad;
            capacidad = line.substr(0,line.find(','));
            string tripulacion = line.substr(line.find(',')+1,string::npos);
            yates[count].capacidad= stoi(capacidad);
            yates[count].tripulacion= stoi(tripulacion);
            yates[count].cap_visita = yates[count].capacidad -yates[count].tripulacion;
            cout << "Capacidad: "+ capacidad << endl;
            cout << "Tripulacion: " + tripulacion << endl;
            count++;
        }
    }
    else{
        cout<< "La wea no se abrio :c" << endl;
    }

    // Fin de carga
    for (int i = 0; i<cantidadYates;i++){
        yates[i].PrintInfoYate();
    }

    return 1;
}