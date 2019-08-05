/**Grafos: G = (V, A) -- conjunto de vertices (nao vazio) e arestas.**/
#include <stdio.h>
#include <stdlib.h>

/**Definição do tipo Grafo**/
typedef struct grafo { //lista de adjacencia
    int eh_ponderado;
    int nro_vertices; //simplificação
    int grau_max;
    int** arestas; //conecçoes
    float** pesos; //caso queira trabalhar com grafico ponderado
    int* grau; //vetor de grau (quantas ele ja possui)
} Grafo;

/**Definição das funcoes**/
Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);
void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont);
void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado);
void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado);
int procuraMenorDistancia(float *dist, int *visitado, int NV);
void menorCaminho_Grafo(Grafo *gr, int ini, int *antecessor, float *distancia);
void imprime_Grafo(Grafo *gr);

//----Arvore geradora minima:
void algPRIM(Grafo *gr, int orig, int *pai);
void algKruskal(Grafo *gr, int orig, int *pai);


/**Rodando o projeto (Exemplo)**/
int main(){
    int i;
    int eh_digrafo = 1; //digrafo ->, se nao for digrafo --
    Grafo* gr = cria_Grafo(5, 5, 0); //cria grafo com no max 5 vertices e grau 5

    //inserção
    insereAresta(gr, 0, 1, eh_digrafo, 0);
    insereAresta(gr, 1, 3, eh_digrafo, 0);
    insereAresta(gr, 1, 2, eh_digrafo, 0);
    insereAresta(gr, 2, 4, eh_digrafo, 0);
    insereAresta(gr, 3, 0, eh_digrafo, 0);
    insereAresta(gr, 3, 4, eh_digrafo, 0);
    insereAresta(gr, 4, 1, eh_digrafo, 0);
    imprime_Grafo(gr);

    //remoção
    /*printf("\nRemovido a aresta 4-1 \n\n");
    removeAresta(gr, 4, 1, eh_digrafo);
    imprime_Grafo(gr);*/

    //realização de busca
    int vis[5];
    printf("\nBusca em Grafo");
    printf("\n\nBusca em Profundidade \n");
    buscaProfundidade_Grafo(gr, 0, vis);
    printf("\n\nBusca em largura\n");
    buscaLargura_Grafo(gr, 0, vis);

    //Apresentacao do menor caminho
    printf("\n\nMenor Caminho: \n");
    int ant[5];
    float dist[5];
    menorCaminho_Grafo(gr, 0, ant, dist);
    for(i = 0; i < 5; i++)
        printf("%d: %d -> %.2f\n",i,ant[i],dist[i]);

    libera_Grafo(gr); //libera grafo


    printf("\n--------------------------------------------------\n");
    eh_digrafo = 0; //nao eh direcionado
    gr = cria_Grafo(6, 6, 1); //cria grafo ponderado com no max 6 vertices e grau 6

    insereAresta(gr, 0, 1, eh_digrafo, 6);
    insereAresta(gr, 0, 2, eh_digrafo, 1);
    insereAresta(gr, 0, 3, eh_digrafo, 5);
    insereAresta(gr, 1, 2, eh_digrafo, 2);
    insereAresta(gr, 1, 4, eh_digrafo, 5);
    insereAresta(gr, 2, 3, eh_digrafo, 2);
    insereAresta(gr, 2, 4, eh_digrafo, 6);
    insereAresta(gr, 2, 5, eh_digrafo, 4);
    insereAresta(gr, 3, 5, eh_digrafo, 4);
    insereAresta(gr, 4, 5, eh_digrafo, 3);

    int pai1[6], pai2[6];
    printf("\n\nAlgoritmo de PRIM:\n");
    algPRIM(gr, 0, pai1);
    for(i = 0; i < 6; i++)
        printf("%d: %d\n", pai1[i], i);


    printf("\n\nAlgoritmo de Kruskal:\n");
    algKruskal(gr, 0, pai2);
    for(i = 0; i < 6; i++)
        printf("%d: %d\n", pai2[i], i);

    libera_Grafo(gr); //libera grafo

    printf("\n--------------------------------------------------\n");
    system("pause");
    return 0;
}


/**funcoes**/
Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado){
    Grafo *gr = (Grafo*) malloc(sizeof(struct grafo)); //alocação
    if(gr != NULL){ //caso eu consegui alocar
        int i;
        gr->nro_vertices = nro_vertices; //guarda os dados
        gr->grau_max = grau_max; //guarda dados
        gr->eh_ponderado = (eh_ponderado != 0)?1:0; //guarda se e ponderado(1) ou nao(0)
        gr->grau = (int*) calloc(nro_vertices,sizeof(int)); //aloca zerado pq no inicio cada vertice tem grau zero

        //criacao da matriz de arestas (olhar verificação)
        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*)); //aloca numero de vertices
        for(i=0; i<nro_vertices; i++) //pra cada vertice eu crio o grau maximo
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

        //cria matriz de peso, semelhante a lista de adjacencia anterior
        if(gr->eh_ponderado){ //somente se tiver peso
            gr->pesos = (float**) malloc(nro_vertices * sizeof(float*)); //aloca por vertice
            for(i=0; i<nro_vertices; i++)
                gr->pesos[i] = (float*) malloc(grau_max * sizeof(float)); //para cada vertice e grau max por peso
        }
    }
    return gr; //ok
}

void libera_Grafo(Grafo* gr){
    if(gr != NULL){ //basicamente libera tdo que aloquei
        int i;

        //libera matriz de arestas
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas); //libera vertices

        //libera matriz de pesos
        if(gr->eh_ponderado){
            for(i=0; i<gr->nro_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }

        free(gr->grau);
        free(gr); //elimina primeira alocacao
    }
}

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){ //liga origem ao destino
    if(gr == NULL) //grafico valido ou nao
        return 0; //se nao for valido retorna zero

    //verifica se os vertices orig e dest existem
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    //grafo existe
    // insere no final da linha
    gr->arestas[orig][gr->grau[orig]] = dest; //arestas de origem(vertice original), acrescento o destino no grau max dele
    if(gr->eh_ponderado) //se for ponderado, faco a mesma coisa no peso
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++; //almento o vertice de origem (grau comeca de zero)

    if(eh_digrafo == 0) //se nao for digrafo eu tenho q inserir outra aresta (troca origem e destino) -- recursivo
        insereAresta(gr,dest,orig,1,peso); //tenho q botar digrado como 1 pra evitar loop infinito
    return 1; //ok
}

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo){
    if(gr == NULL) //verifica se o grafo existe
        return 0;

    //verifica validade dos vertices orig e dest
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    int i = 0; //procurar aresta
    while(i<gr->grau[orig] && gr->arestas[orig][i] != dest) //procuro quem vai ser removido
        i++;

    if(i == gr->grau[orig])//elemento nao encontrado
        return 0;

    gr->grau[orig]--; //diminuo graus (eliminando aresta)
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]]; //a ultima aresta vai pra posicao i, nao precisa deslocar os elemnetos
    if(gr->eh_ponderado) //se for ponderado faz a mesma coisa
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];

    if(eh_digrafo == 0) //verificacao de digrafo, pq tem q remover a outra aresta se nao for digrafo
        removeAresta(gr,dest,orig,1);

    return 1; //ok
}

/**Buscas**/
/*Função auxiliar: realiza o calculo*/
void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont){
    int i;
    visitado[ini] = cont; //marca o vertice como visitado
    for(i=0; i<gr->grau[ini]; i++){ //visita os vizinhos ainda nao visitados
        if(!visitado[gr->arestas[ini][i]]) //verifico se o visinho foi visitado ou nao
            buscaProfundidade(gr,gr->arestas[ini][i],visitado,cont+1);
    }
}
/*função principal: faz a interface com o usuario*/
void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado){
    int i, cont = 1;

    for(i=0; i<gr->nro_vertices; i++) //marca todos sos vertices como nao vizitados
        visitado[i] = 0;
    buscaProfundidade(gr,ini,visitado,cont);

    for(i=0; i < gr->nro_vertices; i++)
        printf("%d -> %d\n",i,visitado[i]);
}

void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado){
    int i, vert, NV, cont = 1;
    int *fila, IF = 0, FF = 0;

    for(i=0; i<gr->nro_vertices; i++) //marca vertices como nao visitados
        visitado[i] = 0;

    //preciso de uma fila pra exibir a ordem
    NV = gr->nro_vertices;
    fila = (int*) malloc(NV * sizeof(int)); //cria fila
    FF++; //incremneta final da fila
    fila[FF] = ini; //coloca o vertice inicial no final da fila
    visitado[ini] = cont; //marca o vertice inicial como visitado

    while(IF != FF){ //enquanto a fila nao estiver vazia
        IF = (IF + 1) % NV; //pega primeiro da fila
        vert = fila[IF];
        cont++; //incremento o contador
        for(i=0; i<gr->grau[vert]; i++){ //visita vizinhos
            if(!visitado[gr->arestas[vert][i]]){ //pega os ainda nao visitados e coloca na fila, caso nao foi, faz:
                FF = (FF + 1) % NV; //coloco ele na fila
                fila[FF] = gr->arestas[vert][i];
                visitado[gr->arestas[vert][i]] = cont; //marco ele como visitado
            }
        }
    }
    free(fila); //ao fim do processo libera o vetor auxiliar

    for(i=0; i < gr->nro_vertices; i++) //apresenta os visitados
        printf("%d -> %d\n",i,visitado[i]);

//OUTRA VERSÃO
/**void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado){
    int i, vert, NV, cont = 1;
    int *pilha, IP = 0, FP = 0;
    for(i=0; i<gr->nro_vertices; i++)
        visitado[i] = 0;

    NV = gr->nro_vertices;
    pilha = (int*) malloc(NV * sizeof(int));
    FP++;
    pilha[FP] = ini;
    while(IP != FP){
        IP = (IP + 1) % NV;
        vert = pilha[IP];
        if(!visitado[vert]){
            visitado[vert] = cont;
            cont++;
            for(i=0; i<gr->grau[vert]; i++){
                if(!visitado[gr->arestas[vert][i]]){
                    FP = (FP + 1) % NV;
                    pilha[FP] = gr->arestas[vert][i];
                }
            }
        }
    }
    free(pilha);
    for(i=0; i < gr->nro_vertices; i++)
        printf("%d -> %d\n",i,visitado[i]);
}
**/
}

int procuraMenorDistancia(float *dist, int *visitado, int NV){
    int i, menor = -1, primeiro = 1;
    //procura vertice com menor distancia e que nao tenha sido visitado ainda
    for(i = 0; i < NV; i++){ //percorro todos os vertices
        //se o vertice ainda nao foi visitado: dist = -1.
        if(dist[i] >= 0 && visitado[i] == 0){ //verifica a distancia e se foi visitado
            if(primeiro){ //se é a primeira vez
                menor = i;
                primeiro = 0;
            }else{ //se nao for
                if(dist[menor] > dist[i]) //faz a comparacao para se eu souber se quero trocar o menor.
                    menor = i;
            }
        }
    }
    return menor; //indice do vertice com a menor distancia que nao foi visitado ainda
}

void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist){ //metodo dijkstra, diste eh a distancia e ant diz o anterior ao vertice (ordem)
    int i, cont, NV, ind, *visitado, vert;
    cont = NV = gr->nro_vertices; //inicialiso NV e contador, esse contador é pra garantir q visitou tds os verticies

    visitado = (int*) malloc(NV * sizeof(int)); //cria vetor auziliar
    for(i=0; i < NV; i++){ //inicializa distancias e anteriores (-1)
        ant[i] = -1; //ngm tem anterior
        dist[i] = -1;
        visitado[i] = 0;
    }
    dist[ini] = 0; //a distancia do inicial pra ele mesmo eh zero

    while(cont > 0){ //enquanto eu tiver vertices ainda para serem visitados no meu grafo
        //procura vertice com menor distancia e marca como visitado
        vert = procuraMenorDistancia(dist, visitado, NV);

        if(vert == -1) //tesste de erro, caso se nao tem vertices que conectem todos (desconexo)
            break;

        visitado[vert] = 1; //marca o cara do vert como visitado
        cont--; //decremento cont

        for(i = 0; i < gr->grau[vert]; i++){ //pra cada vertice vizinho  a vert
            ind = gr->arestas[vert][i]; //indicador
            //atualiza distancias dos vizinhos
            if(dist[ind] < 0){ //significa q ngm chegou nele ainda (distancia invalida)
               dist[ind] = dist[vert] + 1;
               //ou peso da aresta
               // dist[ind] = dist[vert] + gr->pesos[vert][i];
               ant[ind] = vert;
            }else{
                if(dist[ind] > dist[vert] + 1){ //se for mair significa q existe um caminho pra u com custo menor, por isso tenho q mudar o antecessor
                    dist[ind] = dist[vert] + 1;
                    //ou peso da aresta
                    //dist[ind] = dist[vert] + gr->pesos[vert][i];
                    ant[ind] = vert;
                }
            }
        }
    }
    free(visitado); //depois do while ja posso liberar visitado
}

/**Imprime**/
void imprime_Grafo(Grafo *gr){
    if(gr == NULL) //grafo valido?
        return; //se nao, retorna
    //caso for valido:
    int i, j;
    for(i=0; i < gr->nro_vertices; i++){ //percorre colunas
        printf("%d: ", i);
        for(j=0; j < gr->grau[i]; j++){ //percorre linha
            if(gr->eh_ponderado) //imprime diferente a depender se eh ou nao ponderado
                printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]); //printa o valor e e peso
            else
                printf("%d, ", gr->arestas[i][j]); //printa o valor
        }
        printf("\n");
    }
}

void algPRIM(Grafo *gr, int orig, int *pai){ //1 arvore ao lomgo do processo O(v^3)
    int i, j, dest, primeiro, NV = gr->nro_vertices;
    double menorPeso;
    for (i = 0; i < NV; i++) //todos sos vertices sao sem pai
        pai[i] = -1;
    pai[orig] = orig; //o pai da origem eh ele mesmo
    while(1){ //pocesso ate quando puder
        primeiro = 1; //controlar caso encontro arestas com msm peso
        for (i = 0; i < NV; i++){ //percorre todos os vertices
            if (pai[i] != -1){  //achou vertices ja visitado
                for (j = 0; j < gr->grau[i]; j++) { //percorre os vizinhos do vertices visitados
                    //procurar  menor peso
                    if (pai[gr->arestas[i][j]] == -1){ //achou vertice vizinho nao visitado, indices de outro vertices (colocar cara na arvore)
                        if (primeiro){ //procuro aresta de menor custo
                            menorPeso = gr->pesos[i][j]; //por ser o primeiro, ele recebe direto
                            orig = i;
                            dest = gr->arestas[i][j];
                            primeiro = 0; //ja encontrei o vertice, logo encontrei ele
                        }else{ //encontro outro que nao eh o primeiro
                            if (menorPeso > gr->pesos[i][j]){ //se essa aresta for menor, efetuo a troca
                                menorPeso = gr->pesos[i][j];
                                orig = i;
                                dest = gr->arestas[i][j];
                            }
                        }
                    }
                }
            }
        }
        if (primeiro == 1) //nao consigo encontrar mais ninguem
            break;

        pai[dest] = orig; //o cara do menor peso pasa a ser orig, pq ja encontrei ele
    }
}

void algKruskal(Grafo *gr, int orig, int *pai){
    int i, j, dest, primeiro, NV = gr->nro_vertices;
    double menorPeso;
    int *arv = (int*) malloc(NV * sizeof(int)); //cria vetor auxiliar com mesmo numero de vertices
    for (i = 0; i < NV; i++){
        arv[i] = i; //arv de i recebe o indices, identificador (as arvores)
        pai[i] = -1; //sem pai
    }
    pai[orig] = orig; //o pai da origem eh ele mesmo
    while(1){ //pocesso ate quando puder
        primeiro = 1; //controlar caso encontro arestas com msm peso
        for (i = 0; i < NV; i++){ //percorre os vertices
            for (j = 0; j < gr->grau[i]; j++) { //arestas do vertices i
                //procura vertice menor peso (aresta menor custo)
                if (arv[i] != arv[gr->arestas[i][j]]){ //verifica se as arvores sao diferentes, se forem, conecto na mesma arvore
                    if (primeiro){ //ja tentei conectar alguem antes? se nao:
                        menorPeso = gr->pesos[i][j]; //por ser o primeiro, ele recebe direto
                        orig = i;
                        dest = gr->arestas[i][j];
                        primeiro = 0; //ja encontrei o vertice, logo encontrei ele
                    }else{ //encontro outro que nao eh o primeiro
                        if (menorPeso > gr->pesos[i][j]){ //se essa aresta for menor, efetuo a troca
                            menorPeso = gr->pesos[i][j];
                            orig = i;
                            dest = gr->arestas[i][j];
                        }
                    }
                }
            }
        }

        if (primeiro == 1) //se nao encontrei ninguem
            break;

        //ajuste, tratamento pra saber quem vai ser pai de quem
        if(pai[orig] == -1)
            pai[orig] = dest;
        else
            pai[dest] = orig;

        for (i = 0; i < NV; i++) //processo pra todos fazerem parte da mesma arvore
            if (arv[i] == arv[dest]) //para cada arvore i, se ela fizer parte da dest, ela vai passar a fazer parte da orig
                arv[i] = arv[orig]; //conecta as arvores para o mesmo identificador
    }
    free(arv);
}
