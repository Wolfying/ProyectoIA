#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Yatecito{
    public:
        int hostNumber;
        int periodo;
        Yatecito(int Number){
            periodo = 0;
            hostNumber = Number;
        }
        Yatecito(){
            periodo = 0;
            hostNumber = 0;
        }
        void visitar(int num){
            periodo = num;
        }        
};
class Host{
        public:
            int cap_actual;
            int cap_host;
            int posicionYate;
            vector <int> visitantes;
            Host(int pos, int cap, int trip){
                posicionYate=pos;
                cap_actual = cap-trip;
                cap_host = cap-trip;
                // cout << "Creado uwu" << endl;
                // for (int i = 0; i < cantidad; i++){
                //     cout << yates[i].periodo << endl;
                // }
                // *otrosyates = Visita();
            }
            void PrintInfoHost(){
                cout << "Yate " << posicionYate << endl;
                cout << "Capacidad Actual: " << cap_actual<< endl;
            }           
};

class Yate{
    public:
        int capacidad;
        int tripulacion;
        int posicionYate;
        bool isHost;
        Yate(int cap, int trip, int pos){
            capacidad = cap;
            tripulacion = trip;
            posicionYate = pos;
            isHost = 0;
        }
        void PrintInfoYate(){
            cout << "Yate " << posicionYate+1 ;
            cout << " Capacidad: " << capacidad;
            cout <<  " Tripulacion: "<< tripulacion <<endl;
        }
        bool getIsHost(){
            return isHost;
        }
};

class Invitados{
    public:
        int posicionYate;
        int tripulacion;
        vector <Yatecito> otrosyates;
        Invitados(vector <Yatecito> Hosts, int posYate, int trip){
            // cout << "Creado uwu" << endl;
            otrosyates = Hosts;
            posicionYate = posYate;
            tripulacion = trip;
            // for (int i = 0; i < cantidad; i++){
            //     cout << yates[i].periodo << endl;
            // }
            // *otrosyates = Visita();
        }        
        void PrintYates(){
            cout << "ID Yate ";
            cout << posicionYate << " \t";
            for (int i = 0; i < otrosyates.size();i++){
                cout << otrosyates[i].periodo << " ";
            }
            cout << endl;
        }        
        void visita(int i, int periodo){
            otrosyates[i].visitar(periodo);
        }
};

vector <Invitados> invitados;   //global
vector <Yate> yates;            //global
vector <Host> hosts;            //global
vector <vector <int>> visitas;  //global

//host_actual: posicion en vector hosts; invitado: id del yate invitado (posyate)
int checkJuntaPeriodo(int host_actual, int invitado){
    vector <int> visitantes = hosts[host_actual].visitantes;
    for (int i = 0; i < visitantes.size(); i++){
        if (visitas[invitado][visitantes[i]]==1 or visitas[visitantes[i]][invitado]==1){
            return 1;
        }
    }
    return 0;
}
void checkVisitasHost(int host_actal, int invitado){
    vector <int> visitantes = hosts[host_actal].visitantes;
    for (int i = 0; i < visitantes.size(); i++){
        visitas[invitado][visitantes[i]]=1;
        visitas[visitantes[i]][invitado]=1;        
    }
}
void uncheckVisitasHost(int host_actal, int invitado){
    vector <int> visitantes = hosts[host_actal].visitantes;
    for (int i = 0; i < visitantes.size(); i++){
        visitas[invitado][visitantes[i]]=0;
        visitas[visitantes[i]][invitado]=0;        
    }
}

vector<vector<int>> dumpVisitantesHosts(){
    vector<vector<int>> backup;
    for (int i = 0; i < hosts.size();i++){
        backup[i]=hosts[i].visitantes;
    }
    return backup;
} 

void backupVisitanteshosts(vector<vector<int>> backup, vector<int> capacidades){
    for (int i = 0; i < hosts.size();i++){
        hosts[i].visitantes=backup[i];
        hosts[i].cap_actual = capacidades[i];
    }
}

void Backtracking (int periodo, int invitado){
    vector <Yatecito> hostsavisitar = invitados[invitado].otrosyates;
    int hostpos;
    int invpos = invitados[invitado].posicionYate;
    vector<vector <int>> backup;
    vector<int> capacidades;
    for(int i = 0; i< hostsavisitar.size();i++){
        hostpos = hosts[i].posicionYate;
        
        if(invitados[invitado].tripulacion <= hosts[i].cap_actual ){
            if (visitas[invpos][hostpos]==0){
                if(!checkJuntaPeriodo(i,invpos)){
                    invitados[invitado].otrosyates[i].periodo=periodo;
                    visitas[invpos][hostpos]=1;
                    checkVisitasHost(i,invpos);
                    hosts[i].visitantes.push_back(invpos);
                    hosts[i].cap_actual-=invitados[invitado].tripulacion;
                    if(invitado == invitados.size()-1){
                        backup = dumpVisitantesHosts();
                        for (int i = 0; i < hosts.size();i++){
                            hosts[i].visitantes.clear();
                            capacidades[i]=hosts[i].cap_actual;
                            hosts[i].cap_actual = hosts[i].cap_host;
                        }
                        Backtracking(periodo+1,0);
                        backupVisitanteshosts(backup, capacidades);
                        uncheckVisitasHost(i,invpos);
                        invitados[invitado].otrosyates[i].periodo=0;
                        visitas[invpos][hostpos]=0;
                        checkVisitasHost(i,invpos);
                        hosts[i].visitantes.pop_back();
                        hosts[i].cap_actual+=invitados[invitado].tripulacion;
                    }
                    if(invitado < invitados.size()-1){
                        Backtracking(periodo, invitado+1);
                        uncheckVisitasHost(i,invpos);
                    }
                }
            }
        }
    }
    return;
}

int main(void){
    // Carga de la instancia en memoria    
    vector <Yatecito> HostsVisitados;    
    Yatecito HostaVisitar;
    ifstream configfile;
    ifstream PPP;
    int capacidad;
    int tripulacion;
    int posyate;
    PPP.open("InstanciasPPP/Configuraciones/PPP.txt", std::ifstream::in);
    configfile.open("InstanciasPPP/Configuraciones/config1.txt", std::ifstream::in);
    string line;
    int cantidadYates;
    int periodos;
   
    if(PPP.is_open()){
        getline(PPP,line);
        cantidadYates = stoi(line);
        cout << "Cantidad de yates: " << cantidadYates << endl;
        getline(PPP,line);
        periodos = stoi(line);
        cout << "Cantidad de periodos: " << periodos << endl;
        int count = 0;
        while(getline(PPP,line,';')){
            capacidad = stoi(line.substr(0,line.find(',')));
            tripulacion = stoi(line.substr(line.find(',')+1,string::npos));
            posyate = count +1;
            // cout << "La posicion del yate es: " << posyate << endl;
            yates.push_back(Yate(capacidad,tripulacion,posyate));
            // cout << "Capacidad: "+ capacidad << endl;
            // cout << "Tripulacion: " + tripulacion << endl;
            count++;
        }
    }
    else{
        cout<< "La wea no se abrio :c" << endl;
    }

    if(configfile.is_open()){    
        while(getline(configfile,line,' ')){
            int hostnum;            
            hostnum = stoi(line);
            // cout<< hostnum << endl;
            HostaVisitar = Yatecito(hostnum);
            HostsVisitados.push_back(HostaVisitar);
            capacidad = yates[hostnum-1].capacidad;
            tripulacion = yates[hostnum-1].tripulacion;
            yates[hostnum-1].isHost = 1;
            hosts.push_back(Host(hostnum, capacidad,tripulacion));
        }
    }
    else{
        cout<< "La wea no se abrio :c" << endl;
    }
    // Fin de carga
    
    for( int i = 0; i < cantidadYates; i++){
        
        // cout << endl;
        if (!yates[i].getIsHost()){
            invitados.push_back(Invitados(HostsVisitados,yates[i].posicionYate, yates[i].tripulacion));
        }
    }

    // for (int i = 1; i<= periodos; i++){
    //     for (int j = 0; j < cantidadYates ; j++){
    //     }
    // }
    
    for (int i = 0; i<hosts.size();i++){
        hosts[i].PrintInfoHost();
    }
    return 1;
}