#include <iostream>
using namespace std;

/*
1 - Verificar se o grafo é completo
2 - Verificar se é um multigrafo //
3 - Quantos laços existem //
4 - Quantos vértices folhas existem
5 - Verificar se existe vértice isolado
6 - Verificar se é possível ser planar
7 - Sair
*/

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

int quant_lacos(int** grafo,int quant_vertices){
    int lacos = 0;
    for(int i = 0;i<quant_vertices;i++){
        if(grafo[i][i] >= 1){
            lacos++;
        }
    }
    return lacos;
}

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

void menu(int** grafo,int quant_vertices){
    char opc,resp;
    do{
        cout << "opcoes do menu";
        cin >> opc;
        switch (opc){
            case 1:
                /* grafo completo */
                break;
            
            case 2:
                if(multigrafo(grafo,quant_vertices)){
                    cout << "e multigrafo";
                }else{
                    cout << "nao e multigrafo";
                }
                break;
            case 3:
                if(quant_lacos(grafo,quant_vertices) >= 1){
                    cout<< "tem laco(s): " << quant_lacos(grafo,quant_vertices) << endl;
                }else{
                    cout << "nao tem laco" << endl;
                }   
            }
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

    int quant_vertices,quant_arestas,vert_inicial,vert_final;
    cout << "Quantos vertices tem o grafo? ";
    cin >> quant_vertices;

    //criação da matriz
    int** grafo = criar_matriz(quant_vertices,quant_vertices);
    preencher_matriz(grafo,quant_vertices,quant_vertices);
    fazer_ligacoes(grafo,quant_vertices,direcional);
    cout<< endl << "------ MATRIZ FINAL ------" << endl;
    imprimir_matriz(grafo,quant_vertices,quant_vertices);




    if(quant_lacos(grafo,quant_vertices) >= 1){
        cout<< "tem laco(s): " << quant_lacos(grafo,quant_vertices) << endl;
    }else{
        cout << "nao tem laco" << endl;
    }
    if(multigrafo(grafo,quant_vertices)){
        cout << "e multigrafo" << endl;
    }else{
        cout << "nao e multigrafo" << endl;
    }




    system ("pause");
    return 0;
}