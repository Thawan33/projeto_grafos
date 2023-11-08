#include <iostream>
using namespace std;

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
        cout << i << " ";
    }
    cout << endl;
    for(int i=0; i<lin; i++){
        cout << i << " ";
        for(int j=0; j<col; j++){
            cout<<mat[i][j]<<" ";
        }
        cout << endl;
    }
}

void fazer_ligacoes(int** grafo,int quant_vertices,bool direcional){
    char resp;
    int quant_arestas,vert_inicial,vert_final;
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
                        grafo[vert_inicial][vert_final] = quant_arestas;
                        cout << endl << "------ MATRIZ ATUAL ------" << endl;
                        imprimir_matriz(grafo,quant_vertices,quant_vertices);
                        cout << endl;
                    }else{
                        grafo[vert_inicial][vert_final] = quant_arestas;
                        grafo[vert_final][vert_inicial] = quant_arestas;
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

int vertice_isolado(int** grafo,int quant_vertices){
    int cont, vertices_isolados = 0;
    for(int i = 0;i<quant_vertices;i++){
        cont = 0;
        for(int j = 0;j<quant_vertices;j++){
            if(grafo[i][j] > 0 && i != j){
                cont++;
            }
        }
        if(cont == 0){
            vertices_isolados++;
        }
    }
    return vertices_isolados;
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

void menu(int** grafo,int quant_vertices){
    char resp;
    int opc;
    do{
        cout << "verificar se e completo[1] \n Verificar se e um multigrafo[2] \n Quantos laços existem[3] \n Quantos vertices folhas existem[4] \n Verificar se existe vertice isolado[5] \n Verificar se e possível ser planar[6] \n Sair[7]: ";
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
                if(vertice_isolado(grafo,quant_vertices) > 0){
                    cout << "tem vertice isolado" << endl;
                }else{
                    cout << " nao tem vertice isolado" << endl;
                }
                break;
            case 6:
                /* verificar se é possível ser planar*/
                break;
            default:
                cout << "opcao invalida" << endl;
                break;
            }
        cout << "deseja fazer outra verificao?[s]: ";
        cin >> resp;
    }
    while(resp == 's');
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

    int quant_vertices;
    cout << "Quantos vertices tem o grafo? ";
    cin >> quant_vertices;

    //criação da matriz
    int** grafo = criar_matriz(quant_vertices,quant_vertices);
    preencher_matriz(grafo,quant_vertices,quant_vertices);
    fazer_ligacoes(grafo,quant_vertices,direcional);
    cout<< endl << "------ MATRIZ FINAL ------" << endl;
    imprimir_matriz(grafo,quant_vertices,quant_vertices);
    cout << endl;




    menu(grafo,quant_vertices);

    //fim do programa
    system ("pause");
    return 0;
}