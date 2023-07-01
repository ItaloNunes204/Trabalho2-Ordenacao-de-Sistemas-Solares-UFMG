#include <stdio.h>
#include <stdlib.h>

//cria struct das luas com nome e o raio da lua
struct luas {
    char nome[101];
    int raio_lua;
};

//cria struct dos planetas com nome, raio,numero de luas e uma lista de luas
struct planetas {
    char nome[101];
    int raio_planeta;
    int n_luas;
    struct luas* lua;
};

//cria struct dos sistemas com tempo, nome,raio do sol, numero de planetas e uma lista de planetas
//para facilitar e criado o raio do maior planeta e o raio da maior lua
struct sistemas {
    int tempo;
    char nome[101];
    int raio_sol;
    int n_planetas;
    int raio_maior_planeta;
    int n_luas;
    int raio_maior_lua;
    struct planetas* planeta;
};

//coleta as informaçoes da lua
void Lelua(struct luas* lua){
    //coleta as informaçoes da lua
    scanf("\t\t %s %d", lua->nome, &lua->raio_lua);
}

//coleta as informaçoes do planeta
void LePlaneta(struct planetas* planeta) {

    int n_luas=0;
    //coleta as informaçoes do planeta
    scanf("\t %s %d %d", planeta->nome, &planeta->raio_planeta,&planeta->n_luas);

    //cria uma lista com as luas de um planeta
    planeta->lua = (struct luas*)malloc(planeta->n_luas * sizeof(struct luas));

    //chama a coleta de informaçoes para cada lua
    for (int i = 0; i < planeta->n_luas; i++) {
        Lelua(&planeta->lua[i]);
    }

}

//coleta informaçoes do sistema
void LeSistema(struct sistemas* sistema) {

    //coleta informaçoes do sistema
    int n_planetas;
    scanf("%d %s %d %d", &sistema->tempo, sistema->nome, &sistema->raio_sol, &n_planetas);

    sistema->n_planetas = n_planetas;

    //cria uma lista de planetas
    sistema->planeta = (struct planetas*)malloc(n_planetas * sizeof(struct planetas));

    //chama a coleta de informaçoes de cada planeta
    for (int i = 0; i < sistema->n_planetas; i++) {
        LePlaneta(&sistema->planeta[i]);
    }

}

//libera a memoria da lista de luas
void FreeLua(struct luas* lua) {
    //libera a memoria da lista de luas
    free(lua);
}

//libera a memoria de sistemas
void ResetSistema(struct sistemas* sistema) {

    //para cada sistemas e
    for (int i = 0; i < sistema->n_planetas; i++) {
        FreeLua(sistema->planeta[i].lua);
    }

    //libera a memoria da lista de planetas que a memoria da lista de luas ja foi liberada
    free(sistema->planeta);
}

//imprime o nome de cada sistema da lista de sistemas
void imprimirSistemas(struct sistemas* sistema, int n) {
    //imprime o nome de cada sistema da lista de sistemas

    for (int i = 0; i < n; i++) {
        printf("%s\n", sistema[i].nome);
    }

}

//coleta o maior planeta do sistema
void maior_planeta(struct sistemas* sistema){
    //coleta o maior planeta do sistema

    int maiorPlaneta=0;

    for(int i = 0;i < sistema->n_planetas;i++){

        if(sistema->planeta[i].raio_planeta > maiorPlaneta){
            maiorPlaneta = sistema->planeta[i].raio_planeta;
        }

    }

    //adiciona ao sistema a informaçao
    sistema->raio_maior_planeta = maiorPlaneta;

}

//coleta a maior lua e o numero de luas
void maior_lua_numero_lua(struct sistemas* sistema) {
    //coleta a maior lua e o numero de luas

    int maiorLua = 0;
    int n_lua = 0;

    for (int i = 0; i < sistema->n_planetas; i++) {

        n_lua += sistema->planeta[i].n_luas;

        for (int j = 0; j < sistema->planeta[i].n_luas; j++) {
            if(sistema->planeta[i].lua[j].raio_lua > maiorLua){
                maiorLua=sistema->planeta[i].lua[j].raio_lua;
            }
        }

    }

    //adiciona ao sistema as informaçoes
    sistema->n_luas = n_lua;
    sistema->raio_maior_lua = maiorLua;
}

//com a entrada de 2 sistemas e usado as informaçoes de preferencia para determinar qual e mais importante
// retorna 1 para o primeiro sistema e 2 para o segundo sistema
int melhor_de_2sistemas(struct sistemas* sistema1,struct sistemas* sistema2){
    if(sistema1->raio_sol != sistema2->raio_sol){
        //maior raio de sol
        if(sistema1->raio_sol > sistema2->raio_sol){
            return 1;
        }else{
            return 2;
        }
    }else if(sistema1->n_planetas != sistema2->n_planetas){
        //maior numero de planetas
        if(sistema1->n_planetas > sistema2->n_planetas){
            return 1;
        }else{
            return 2;
        }
    }else if(sistema1->raio_maior_planeta != sistema2->raio_maior_planeta){
        //maior raio do planeta
        if(sistema1->raio_maior_planeta > sistema2->raio_maior_planeta){
            return 1;
        }else{
            return 2;
        }
    }else if(sistema1->n_luas != sistema2->n_luas){
        //maior numero de luas
        if(sistema1->n_luas > sistema2->n_luas){
            return 1;
        }else{
            return 2;
        }
    }else if(sistema1->raio_maior_lua != sistema2->raio_maior_lua){
        //maior raio da lua
        if(sistema1->raio_maior_lua > sistema2->raio_maior_lua){
            return 1;
        }else{
            return 2;
        }
    }else{
        //menor tempo
        if(sistema1->tempo < sistema2->tempo){
            return 1;
        }else{
            return 2;
        }
    }
}

//uni as listas de sistemas
//e enviado a lista de sistemas,o inicio da primeira lista,fim da primeira lista,inicio da segunda lista e o fim da segunda lista
void ritacao(struct sistemas* sistema,int inicio_x,int fim_x,int inicio_y,int fim_y){

    //cria uma nova lista de sistemas
    struct sistemas* saida = (struct sistemas*) malloc((fim_y - inicio_x) * sizeof(struct sistemas));

    //acha o sistama mais importante e adiciona a lista criada
    for(int i=inicio_x,j=inicio_y,k=0; i < fim_x || j < fim_y;k++){
        if(i == fim_x){
            saida[k] = sistema[j];
            j++;
        }else if(j == fim_y){
            saida[k] = sistema[i];
            i++;
        }else if(melhor_de_2sistemas(&sistema[i],&sistema[j]) == 1){
            saida[k]=sistema[i];
            i++;
        }else{
            saida[k]=sistema[j];
            j++;
        }
    }

    //modifica a ordem de sistemas da lista original

    for(int i=inicio_x,k=0;i<fim_y;i++,k++){
        sistema[i]=saida[k];
    }

    free(saida);
}

//quebra a lista de sistemas
struct sistemas BromeroSort(struct sistemas*sistema,int esquerda,int direita){

    int operador = direita-esquerda;

    if(operador == 1){
        //retorna o sistema
        return *sistema;

    }else if(operador == 2){

        //quebra alista de 2 elementos
        BromeroSort(sistema,esquerda,direita-1);
        BromeroSort(sistema,direita-1,direita);

        //ordena os dois elementos
        ritacao(sistema,esquerda,direita-1,direita-1,direita);

        //retorna o sistema ordenado
        return *sistema;

    }else if(operador % 2 != 0){

        //para uma lista com um numero impar de elementos e retirado um elemento e o resto da lista e quebrada novamente
        BromeroSort(sistema,esquerda,direita-1);
        BromeroSort(sistema,direita-1,direita);

        //ordena as duas listas
        ritacao(sistema,esquerda,direita-1,direita-1,direita);

        //retorna a lista
        return *sistema;

    }else{

        //quebra a lista de n elementos
        int direitaF=direita-(operador/2);

        BromeroSort(sistema,esquerda,direitaF);
        BromeroSort(sistema,direitaF,direita);

        //ordena as duas listas
        ritacao(sistema,esquerda,direitaF,direitaF,direita);

        //retorna a lista de sistemas
        return *sistema;
    }
}

int main(){
    //coleta a quantidade de sistemas
    int quantidade=0;
    scanf("%d",&quantidade);

    //cria uma lista de sistemas
    struct sistemas* sistema = (struct sistemas*)malloc(quantidade * sizeof(struct sistemas));

    //coleta as informaçoes de cada sistema
    for(int i=0;i<quantidade;i++){
        LeSistema(&sistema[i]);
    }
    //coleta as informaçoes extras (maior planeta,maior lua,numero de luas)
    for(int i=0;i<quantidade;i++){
        maior_planeta(&sistema[i]);
        maior_lua_numero_lua(&sistema[i]);
    }
    //quebra a lista de sistemas
    BromeroSort(sistema,0,quantidade);
    //imprime a lista de sistemas ordenados
    imprimirSistemas(sistema,quantidade);

    //libera a memoria das luas, planetas e do sistema
    for(int i=0;i<quantidade;i++){
        ResetSistema(&sistema[i]);
    }
    free(sistema);
}
