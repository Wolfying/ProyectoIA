#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
int cantidadPeriodos;
int cantidadSoluciones;
int cantidadInstanciaciones;
int cantidadRetornos;
clock_t start;
vector <int> max_return= {41};
bool me_devuelvo;

void controlc_handler(int s){
    cout << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "               Resultados encontrados                 " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Solucion actual: " << endl;
    for (int i = 0 ; i < invitados.size();i++){
        invitados[i].PrintYates();
    }
    cout << "######################################################" << endl;
    cout << "Maximo Retorno: "<< max_return[0]<<endl;
    clock_t end = clock(); 
    cout << "La cantidad de soluciones encontrada es: "<< cantidadSoluciones <<endl;
    cout << "La cantidad de retornos es: "<< cantidadRetornos <<endl;
    cout << "La cantidad de instanciaciones realizadas es: "<< cantidadInstanciaciones <<endl;
    // Calculating total time taken by the program. 
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "El programa estuvo " << fixed  
         << time_taken << std::setprecision(5); 
    cout << " segundos en ejecucion" << endl;
    cout << "######################################################" << endl;
    exit(1); 

}

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
        backup.push_back(hosts[i].visitantes);
    }
    return backup;
} 

void backupVisitanteshosts(vector<vector<int>> backup, vector<int> capacidades){
    for (int i = 0; i < hosts.size();i++){
        hosts[i].visitantes=backup[i];
        hosts[i].cap_actual = capacidades[i];
    }
}

int Backtracking (int periodo, int invitado){
    if(periodo>cantidadPeriodos){
        for (int i = 0 ; i < invitados.size();i++){
            invitados[i].PrintYates();
        }
        cout << endl <<endl<<endl;
        cantidadSoluciones= cantidadSoluciones + 1;
        me_devuelvo = true;
        cantidadRetornos++;
        return 0;
    }
    if(invitado > invitados.size()){
        cantidadRetornos++;
        return 0;
    }
    vector <Yatecito> hostsavisitar = invitados[invitado].otrosyates;
    int hostpos;
    int invpos = invitados[invitado].posicionYate;
    vector<vector <int>> backup;
    vector<int> capacidades;    
    for(int i = 0; i< hostsavisitar.size()-1;i++){
        hostpos = hosts[i].posicionYate;
        if(invitados[invitado].tripulacion <= hosts[i].cap_actual ){
            // cout<< "uwu"<< endl;
            if (visitas[invpos][hostpos]==0){                
                if(!checkJuntaPeriodo(i,invpos)){ 
                    invitados[invitado].otrosyates[i].periodo=periodo;
                    visitas[invpos][hostpos]=1;
                    checkVisitasHost(i,invpos);
                    hosts[i].visitantes.push_back(invpos);
                    hosts[i].cap_actual-=invitados[invitado].tripulacion;
                    cantidadInstanciaciones++;
                    if(invitado == invitados.size()-1){
                        backup = dumpVisitantesHosts();                        
                        for (int i = 0; i < hosts.size();i++){
                            hosts[i].visitantes.clear();
                            // cout << "peneeee"<< endl;
                            capacidades.push_back(hosts[i].cap_actual);
                            hosts[i].cap_actual = hosts[i].cap_host;
                        }
                        cout << "Periodo: "<< periodo<<endl;
                        // cout << "Cantidad Soluciones "<< cantidadSoluciones << endl;
                        Backtracking(periodo+1,0);
                        if (me_devuelvo){
                            if (invitado < max_return[0]){
                                max_return[0] = invitado;
                            }
                        }
                        backupVisitanteshosts(backup, capacidades);
                        uncheckVisitasHost(i,invpos);
                        invitados[invitado].otrosyates[i].periodo=0;
                        visitas[invpos][hostpos]=0;
                        hosts[i].visitantes.pop_back();
                        hosts[i].cap_actual+=invitados[invitado].tripulacion;
                    }
                    else if(invitado < invitados.size()-1){
                        Backtracking(periodo, invitado+1);
                        if (me_devuelvo){
                            if (invitado < max_return[0]){
                                max_return[0] = invitado;
                            }
                        }
                        // cout << "Periodo: "<< periodo;    
                        // cout << "\t Invitado: "<<invpos<< endl;
                        uncheckVisitasHost(i,invpos);
                        invitados[invitado].otrosyates[i].periodo=0;
                        visitas[invpos][hostpos]=0;
                        hosts[i].visitantes.pop_back();
                        hosts[i].cap_actual+=invitados[invitado].tripulacion;
                    }
                }
            }
        }
    }
    
    // cout << "Periodo: "<< periodo;    
    // cout << "\t Invitado: "<<invpos<< endl;
    cantidadRetornos++;
    return 0;
}

void generarMatrizVisitantes(int yates){
  for (int i = 0; i <= yates; i++){
    vector<int> v1;
    for (int j = 0; j < yates; j++) { 
      v1.push_back(0);
    }
    visitas.push_back(v1);
  }
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
    configfile.open("InstanciasPPP/Configuraciones/config.txt", std::ifstream::in);
    string line;
    int cantidadYates;
    cantidadRetornos = 0;
    cantidadInstanciaciones=0;
    cantidadSoluciones = 0;
    /* Recording the starting clock tick.*/
    start = clock();    
  
    // unsync the I/O of C and C++. 
    ios_base::sync_with_stdio(false); 
   
    if(PPP.is_open()){
        getline(PPP,line);
        cantidadYates = stoi(line);
        cout << "Cantidad de yates: " << cantidadYates << endl;
        getline(PPP,line);
        cantidadPeriodos = stoi(line);
        cout << "Cantidad de periodos: " << cantidadPeriodos << endl;
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
    
    // for (int i = 0; i<hosts.size();i++){
    //     hosts[i].PrintInfoHost();
    // }
    generarMatrizVisitantes(cantidadYates);
    // for (int i = 0; i< cantidadYates; i++){
    //     cout <<visitas[1][i]<< " ";
    // }
    // cout << endl;

    struct sigaction sigIntHandler;

   sigIntHandler.sa_handler = controlc_handler;
   sigemptyset(&sigIntHandler.sa_mask);
   sigIntHandler.sa_flags = 0;

   sigaction(SIGINT, &sigIntHandler, NULL);

//    pause();

    Backtracking(1,0);

    // Recording the end clock tick. 
    clock_t end = clock(); 
  
    cout << "La cantidad de soluciones encontrada es: "<< cantidadSoluciones <<endl;
    cout << "La cantidad de retornos es: "<< cantidadRetornos <<endl;
    cout << "La cantidad de instanciaciones realizadas es: "<< cantidadInstanciaciones <<endl;
    // Calculating total time taken by the program. 
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by program is : " << fixed  
         << time_taken << std::setprecision(5); 
    cout << " sec " << endl; 
    // for (int i = 0 ; i < invitados.size();i++){
    //     invitados[i].PrintYates();
    // }
    return 1;
}