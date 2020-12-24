#include <iostream>
#include <vector>

using namespace std;

class Visita{
    public:
        int periodo;
        bool visitado;
        Visita(){
            periodo = 0;
            visitado = 0;
        }
};

class Yate{
    public:
        int posicionYate;
        bool host;
        vector <Visita> otrosyates;
        Yate(int cantidad){
            host = false;
            vector <Visita> yates(cantidad) ;
            // cout << "Creado uwu" << endl;
            otrosyates = yates;
            // for (int i = 0; i < cantidad; i++){
            //     cout << yates[i].periodo << endl;
            // }
            // *otrosyates = Visita();
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
};

int main(void){
    cout << "Hello World" << endl;
    vector <Yate> yates;
    Yate *yate;
    int cantidadYates = 11;
    for (int i = 0; i<cantidadYates;i++){
        yates.push_back(Yate(cantidadYates));
        yates[i].posicionYate = i;
    }
    yates[1].host = true;
    yates[10].host = true;

    for (int i = 0; i<cantidadYates;i++){
        yates[i].PrintYates();
    }

    // Yate *yates= new Yate(3);
    // yates->PrintYates();

    return 1;
}