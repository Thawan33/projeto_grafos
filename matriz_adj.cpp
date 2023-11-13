#include <iostream>
using namespace std;

#include <iostream>

// Definindo códigos de cores ANSI
#define RESET   "\033[0m"       /* Reset */
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLD    "\033[1m"       /* Bold */


int** criar_matriz(int lin,int col){
    int **mat;
    mat = new int*[lin];
    for(int i = 0;i<lin;i++){
        mat[i] = new int[col];
    }
    return mat;
}

void preencher_matriz(int** mat,int lin,int col){
    for(int i = 0;i<lin;i++){
        for(int j = 0;j<col;j++){
            mat[i][j] = 0;
        }
    }
}

void imprimir_matriz(int** mat, int lin, int col){
    cout << "  ";
    for(int i=0; i<col; i++){
        cout << BOLD << i << " ";
    }
    cout << RESET;
    cout << endl;
    for(int i=0; i<lin; i++){
        cout << BOLD  << i << RESET << " ";
        for(int j=0; j<col; j++){
            cout<< YELLOW <<mat[i][j]<<" ";
        }
        cout << RESET;
        cout << endl;
    }
}

int fazer_ligacoes(int** grafo,int quant_vertices,bool direcional){
    char resp;
    int quant_arestas,vert_inicial,vert_final;
    int arestas_totais = 0;
    do{
        cout << "Vertice que deseja fazer uma ligacao: ";
        cin >> vert_inicial;
        if(vert_inicial < 0 || vert_inicial > quant_vertices - 1){
            cout << "vertice inexistente!" << endl;
        }else{
            cout << "vertice que deseja ligar: ";
            cin >> vert_final;
            if(vert_final < 0 || vert_final > quant_vertices - 1){
                cout << "vertice inexistente!" << endl;
            }else{
                cout << "quantidade de arestas: ";
                cin >> quant_arestas;
                if(quant_arestas < 0){
                    cout << "numero negativo!" << endl;
                }else{
                    if(direcional){
                        grafo[vert_inicial][vert_final] += quant_arestas;
                        arestas_totais+= quant_arestas;
                        cout << endl << "------ MATRIZ ATUAL ------" << endl;
                        imprimir_matriz(grafo,quant_vertices,quant_vertices);
                        cout << endl;
                    }else{
                        if(vert_inicial != vert_final){
                            grafo[vert_inicial][vert_final] += quant_arestas;
                            grafo[vert_final][vert_inicial] += quant_arestas;
                        }else{
                            grafo[vert_inicial][vert_final] += quant_arestas;
                        }
                        arestas_totais+= quant_arestas;
                        cout << endl << "------ MATRIZ ATUAL ------" << endl;
                        imprimir_matriz(grafo,quant_vertices,quant_vertices);
                        cout << endl;
                    }
                }
            }
        }
        do{
            cout << "deseja continuar? [s] para sim [n] para nao: ";
            cin >> resp;
        }
        while(resp != 's' && resp != 'n');
    }
    while(resp == 's');
    return arestas_totais;
}

//verificações --------------------------------------------------

//1 - Verificar se o grafo é completo
bool grafo_completo(int** grafo,int quant_vertices){
    int cont, vertices_completos = 0;
    for(int i = 0;i<quant_vertices;i++){
        for(int j = 0;j<quant_vertices;j++){
            if(grafo[i][j] > 0 && i != j){
                cont++;
            }
        }
        if(cont == quant_vertices - 1){
            vertices_completos++;
        }
        cont = 0;
    }
    if(vertices_completos == quant_vertices){
        return true;
    }else{
        return false;
    }
}

//2 - Verificar se é um multigrafo
bool multigrafo(int** grafo,int quant_vertices){
    bool mg = false;
    for(int i = 0;i<quant_vertices;i++){
        for(int j = 0;j<quant_vertices;j++){
            if(grafo[i][j] >= 2){
                mg = true;
            }
        }
    }
    return mg;
}

// 3 - Quantos laços existem
int quant_lacos(int** grafo,int quant_vertices){
    int lacos = 0;
    for(int i = 0;i<quant_vertices;i++){
        if(grafo[i][i] >= 1){
            lacos++;
        }
    }
    return lacos;
}

bool vertice_isolado(int** grafo,int quant_vertices){
    int soma;
    for(int i = 0;i<quant_vertices;i++){
        soma = 0;
        for(int j = 0;j<quant_vertices;j++){
            soma += grafo[i][j];
        }
        if(soma == 0){
            return true;
        }
    }
    return false;
}

int vertice_folha(int** grafo,int quant_vertices){
    int cont, quant_vertice_folha = 0;
    for(int i = 0;i<quant_vertices;i++){
        for(int j = 0;j<quant_vertices;j++){
            if(grafo[i][j] > 0 && i != j){
                cont++;
            }
        }
        if(cont == 1){
            quant_vertice_folha++;
        }
        cont = 0;
    }
    return quant_vertice_folha;
}

bool planar(int quant_vertices,int quant_arestas){
    char resp;
    do{
        cout << "grafo e bipartido? [s] ou [n]";
        cin >> resp;
    }
    while(resp != 's' && resp != 'n');
    //consertar para incluir na condição se a quantidade de vertices for menor ou igual a 2!!!!!
    if(resp == 'n'){
        if(quant_arestas <= 3 * quant_vertices - 6 || quant_vertices <= 2){
            return true;
        }else{
            return false;
        }
    }else{
        if(quant_arestas <= 2 * quant_vertices - 4){
            return true;
        }else{
            return false;
        }
    }
}

void menu(int** grafo,int quant_vertices,int quant_arestas){
    int opc;
    bool fim = false;
    do{
        cout << "verificar se e completo[1] \n Verificar se e um multigrafo[2] \n Quantos lacos existem[3] \n Quantos vertices folhas existem[4] \n Verificar se existe vertice isolado[5] \n Verificar se e possivel ser planar[6] \n Sair[7]: ";
        cin >> opc;
        switch (opc){
            case 1:
                if(grafo_completo(grafo,quant_vertices)){
                    cout << "e completo" << endl;
                }else{
                    cout << "nao e completo" << endl;
                }
                break;
            case 2:
                if(multigrafo(grafo,quant_vertices)){
                    cout << "e multigrafo" << endl;
                }else{
                    cout << "nao e multigrafo" << endl;
                }
                break;
            case 3:
                if(quant_lacos(grafo,quant_vertices) >= 1){
                    cout<< "tem laco(s): " << quant_lacos(grafo,quant_vertices) << endl;
                }else{
                    cout << "nao tem laco" << endl;
                }
                break;
            case 4:
                if(vertice_folha(grafo,quant_vertices) >= 1){
                    cout<< "tem vertice folha: " << vertice_folha(grafo,quant_vertices) << endl;
                }else{
                    cout << "nao tem vertice folha" << endl;
                }
                break;
            case 5:
                if(vertice_isolado(grafo,quant_vertices)){
                    cout << "tem vertice isolado" << endl;
                }else{
                    cout << " nao tem vertice isolado" << endl;
                }
                break;
            case 6:
                if(planar(quant_vertices,quant_arestas)){
                    cout << "pode ser planar" << endl;
                }else{
                    cout << "nao pode ser planar" << endl;
                }
                break;
            case 7:
                fim = true;
                break;
            default:
                cout << "opcao invalida" << endl;
                break;
            }
    }
    while(!fim);
}

int main(){
    bool direcional;
    char resp;

    do{
        cout << "grafo direcionado? [s] para sim [n] para nao: ";
        cin >> resp;
    }
    while(resp != 's' && resp != 'n');

    if(resp == 's'){
        direcional = true;
    }else{
        direcional = false;
    }

    int quant_vertices,quant_arestas;
    cout << "Quantos vertices tem o grafo? ";
    cin >> quant_vertices;

    //criação da matriz
    int** grafo = criar_matriz(quant_vertices,quant_vertices);
    preencher_matriz(grafo,quant_vertices,quant_vertices);
    quant_arestas = fazer_ligacoes(grafo,quant_vertices,direcional);
    cout<< endl << "------ MATRIZ FINAL ------" << endl;
    imprimir_matriz(grafo,quant_vertices,quant_vertices);
    cout << endl;

    menu(grafo,quant_vertices,quant_arestas);

    //fim do programa
    system ("pause");
    return 0;
}