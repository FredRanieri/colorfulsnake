#include <SDL.h>
#include "SDL_opengl.h"
#include "mapa_snake.h"
#include "atuador_snake.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include "SDL_mixer.h"
//MEDIDAS
#define tela_x 1100
#define tela_y 500
#define largura 5
//
//CORES
#define amarelo 255,215,0
#define azul 0,139,139
#define cinza 211,211,211
#define cinza_e 105,105,105
#define laranja 255,140,0
#define preto 0,0,0
#define verde 60,179,113
#define vermelho 178,34,34
//
using namespace std;
//HEADER FUNCOES
    //FUB합ES PARA CRIA플O NO JOGO
void abrir_arquivo(int& facil, int& medio, int& dificil);
void salvar_arquivo(int facil, int medio, int dificil);
void criar_snake(vector<atuador>&snake, atuador obj1, atuador obj2, atuador obj3, atuador obj4, atuador obj5);
void criar_parede(vector<atuador>&parede, atuador obj1, atuador obj2, atuador obj3, atuador obj4);
void cria_obj(vector<atuador>&objeto,int c_r, int c_g, int c_b,vector<atuador>&snake,vector<atuador>&parede,int num_comida);
    //
    //FUN합ES DE A플O NO JOGO
void controle(SDL_Event& eventos,int& tela);
void controle_start(int& menu_start,SDL_Event& eventos, int& tela);
void controle_dificuldade(int& menu_dificuldade,SDL_Event& eventos,int& select_dificuldade);
void controle(int& menu,bool& executando,SDL_Event& eventos, int& tela);
void controle(char& l_btn, SDL_Event& eventos, bool& executando, bool& left, bool& right, bool& up, bool& down, int& tela);
    void aciona(char a,bool& left, bool& right, bool& up, bool& down);

void movimento_snake(vector<atuador>&snake, char& l_btn, bool left, bool right, bool up, bool down);
void velocidade_snake(vector<atuador>snake, int& vel);
bool colisao_obj(atuador obj,vector<atuador>&snake,vector<atuador>&objeto);
    bool colisao(atuador obj, vector<atuador>&snake, vector<atuador>&parede);
    //
    //FUNC합ES PARA DESENHAR NA TELA
void desenhar(mapa mapa_snake,vector<atuador>parede,vector<atuador>snake,vector<atuador>obj1,vector<atuador>obj2,vector<atuador>obj3,vector<atuador>obj4,vector<atuador>obj5);
    void criar(vector<atuador>obj);
    //
//
int main(int argc, char* args[]){
//VARIAVEIS DE CRIACAO
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_Music *music_menu = NULL;//Poteiros para pegar o arquivo de son
    Mix_Music *music_game = NULL;
    Mix_Music *music_lose = NULL;
    Mix_Music *music_win = NULL;
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
    music_menu = Mix_LoadMUS( "menu_song.wav" );
    music_game = Mix_LoadMUS ("song_game.wav");
    music_lose = Mix_LoadMUS ("lose.wav");
    music_win = Mix_LoadMUS ("win.wav");
    ofstream fo;//Variavel para abrir e fechar arquivo .txt
    ifstream fi;//Variavel para abrir e fechar arquivo .txt
    string linha;
    int facil;//Variavel para selecionar a opção do menu onde usuario esta
    int medio;//Variavel para selecionar a opção do menu onde usuario esta
    int dificil;//Variavel para selecionar a opção do menu onde usuario esta
    int a = 11;//Tamanho onde vai andar a snake
    int vel;//Variavel que vai alterar a velocidade da snake
    int menu = 1;//Variavel para selecionar a opção do menu onde usuario esta
    int menu_start = 1;//Variavel para selecionar a opção do menu onde usuario esta
    int menu_dificuldade = 1;//Variavel para selecionar a opção do menu onde usuario esta
    int select_dificuldade = 0;//Variavel para selecionar a opção do menu onde usuario esta
    int num_comida = 0;//Variavel para delimitar quantas comidas vao ter no mapa
    int tela = 1;//Variavel para selecionar a opção do menu onde usuario esta
    int level = 0;//Variavel para delimitar dificuldade do jogo
    int score = 0;//Quanto pontos o usuario fez
    int M,C,D,U;//Variaveis para coverter o score para numeros entre 0 e 9
    pagina abertura;//Objeto que vai mostrar imagem na tela(futuros updates os objetos tambem teram cada um seu proprio menu e som)
    pagina menu_principal;
    pagina menu_nivel;
    pagina menu_continue;
    pagina win_lose;
    pagina ranking;
    mapa mapa_snake(tela_x,tela_y,cinza);//Objeto que vai criar a area onde vamos trabalhar com o jogo, por exemplo tamanho da janela e cor de fundo
    atuador janela(95,125,250,200,preto);//Objeto que vai gerar a snake e a comida do jogo
    atuador parede1(0,0,tela_x,largura,cinza_e);//parede superior
    atuador parede2(0,0,largura,tela_y,cinza_e);//parede esquerda
    atuador parede3(tela_x-largura,0,largura,tela_y,cinza_e);//parede direita
    atuador parede4(0,tela_y-largura,tela_x,largura,cinza_e);//parede baixo
    atuador obj1(100,100,10,10,azul);//Azul
    atuador obj2(100,100,10,10,laranja);//Laranja
    atuador obj3(100,100,10,10,verde);//Verde
    atuador obj4(100,100,10,10,amarelo);//Amarelo
    atuador obj5(100,100,10,10,vermelho);//Vermelho
    vector<atuador>parede;//Vetor onde vai conter todos os objetos parede para facilitar testes de colisao
    vector<atuador>snake;//Vetor onde vai conter todos os objetos snake para facilitar testes de colisao
    vector<atuador>objeto_azul;//Vetor onde vai conter todos os objetos comida para facilitar testes de colisao
    vector<atuador>objeto_laranja;
    vector<atuador>objeto_verde;
    vector<atuador>objeto_amarelo;
    vector<atuador>objeto_vermelho;
    SDL_Event eventos;//Variavel tipo Event da SDL que vai receber os botoes pressionados do teclado
    bool executando = true, left = false, right = true, up = false, down = false, teste_criar = true;////Variaveis para controlar loop do jogo e movimento da snake e do menu
    bool musica = true;//Variavel para controlar repetição da musica
    bool lose = true;
    bool win = true;
    char l_btn = 'R';//Variavel para controlar ultimo botao apertado
    abrir_arquivo(facil,medio,dificil);//função para abrir um arquivo .txt com score passado
//
//COMEÇA O LOOP DO JOGO
    while(executando){
        if(tela == 1){
            abertura.imagem_list("abertura");//metodo do objeto para mostrar imagem na tela
            controle(eventos,tela);//Função de controle de menu
            SDL_Delay(100);
        }
        else if(tela == 2){
            if(musica){
                Mix_PlayMusic(music_menu,-1);//Iniciar musica, -1 significa que vai tocar até que outra musica tome seu lugar
                musica = false;
            }
            if(teste_criar){//Limpa todo o que aconteceu no jogo anterior
                parede.clear();
                snake.clear();
                objeto_azul.clear();
                objeto_laranja.clear();
                objeto_verde.clear();
                objeto_amarelo.clear();
                objeto_vermelho.clear();
                left = false;
                right = true;
                up = false;
                down = false;
                lose = true;
                win = true;
                menu_start = 1;
                select_dificuldade = 0;
                menu_dificuldade = 1;
                score = -30;
            }
            if(menu == 1)menu_principal.imagem_list("menu_jogar");//Mostrar imagem da onde o usuario esta
            else if(menu == 2)menu_principal.imagem_list("menu_rank");
            else if(menu == 3)menu_principal.imagem_list("menu_about");
            else if(menu == 4)menu_principal.imagem_list("menu_exit");
            controle(menu,executando,eventos,tela);//Controlar o menu para o usuario
            SDL_Delay(100);
        }
        else if(tela == 3){
            if(select_dificuldade == 0){//Selecionar menu de dificuldades
                if(menu_dificuldade == 1)menu_nivel.imagem_list("menu_jogar_facil");//Mostrar imagem da onde o usuario esta
                else if(menu_dificuldade == 2)menu_nivel.imagem_list("menu_jogar_medio");
                else if(menu_dificuldade == 3)menu_nivel.imagem_list("menu_jogar_dificil");
                controle_dificuldade(menu_dificuldade,eventos,select_dificuldade);
                SDL_Delay(100);
            }
            else if(select_dificuldade == 1){
                if(menu_dificuldade == 1){//Diferença entre os niveis de dificuldade
                    level = 15;
                    num_comida = 20;
                }
                else if(menu_dificuldade == 2){
                    level = 20;
                    num_comida = 25;
                }
                else if(menu_dificuldade == 3){
                    level = 28;
                    num_comida = 30;
                }
                controle(l_btn,eventos,executando,left,right,up,down,tela);//Controlar o menu para o usuario
                if(teste_criar){//Criar todo um jogo novo
                    Mix_PlayMusic(music_game,-1);
                    criar_parede(parede,parede1,parede2,parede3,parede4);
                    criar_snake(snake,obj1,obj2,obj3,obj4,obj5);
                    cria_obj(objeto_azul,azul,snake,parede,num_comida);
                    cria_obj(objeto_laranja,laranja,snake,parede,num_comida);
                    cria_obj(objeto_verde,verde,snake,parede,num_comida);
                    cria_obj(objeto_amarelo,amarelo,snake,parede,num_comida);
                    cria_obj(objeto_vermelho,vermelho,snake,parede,num_comida);
                    teste_criar = false;
                    musica = true;
                }
                velocidade_snake(snake,vel);//Calcular velocidade da snake baseado no seu tamanho
                movimento_snake(snake,l_btn,left,right,up,down);//Movimento da snake no mapa
                if(!colisao(snake[0],snake,parede)) tela = 5;//Teste de colisão com parede, retorna false se voce bateu em alguma coisa
                if(colisao_obj(snake[0],snake,objeto_azul)){//Testa colisão com algum objeto do tipo comida, se retornar true testa se a comida é ou nao igual ao inicio da snake
                    movimento_snake(snake,l_btn,left,right,up,down);
                    score++;//Soma um ponto no score cada vez que come um objeto
                }
                if(colisao_obj(snake[0],snake,objeto_laranja)){
                    movimento_snake(snake,l_btn,left,right,up,down);
                    score++;
                }
                if(colisao_obj(snake[0],snake,objeto_verde)){
                    movimento_snake(snake,l_btn,left,right,up,down);
                    score++;
                }
                if(colisao_obj(snake[0],snake,objeto_amarelo)){
                    movimento_snake(snake,l_btn,left,right,up,down);
                    score++;
                }
                if(colisao_obj(snake[0],snake,objeto_vermelho)){
                    movimento_snake(snake,l_btn,left,right,up,down);
                    score++;
                }
                if(objeto_azul.size() == level)cria_obj(objeto_azul,azul,snake,parede,num_comida);//Se o numero de objetos no mapa for menor que a variavel level, reinicia as comidas do mapa
                if(objeto_laranja.size() == level)cria_obj(objeto_laranja,laranja,snake,parede,num_comida);
                if(objeto_verde.size() == level)cria_obj(objeto_verde,verde,snake,parede,num_comida);
                if(objeto_amarelo.size() == level)cria_obj(objeto_amarelo,amarelo,snake,parede,num_comida);
                if(objeto_vermelho.size() == level)cria_obj(objeto_vermelho,vermelho,snake,parede,num_comida);
                if(snake.empty())tela = 4;//Se a snake ficar vazia, voce venceu o jogo.
                desenhar(mapa_snake,parede,snake,objeto_azul,objeto_laranja,objeto_verde,objeto_amarelo,objeto_vermelho);//Função para desenhar todos os objetos no mapa
                SDL_Delay(vel);
            }
        }
        else if(tela == 4){//Tela de vitoria, para mostrar que voce venceu e testar se você bateu o record
            if(win){
                Mix_PlayMusic(music_win,1);//Se 1 então o loop ocorre apenas uma vez
                win = false;
            }
            if(menu_dificuldade == 1){
                if(score<facil){
                    facil = score;
                    salvar_arquivo(facil,medio,dificil);
                }
                ranking.imagem_list("tela_wins","numero",score,facil,medio,dificil,'F');
            }
            else if(menu_dificuldade == 2){
                if(score<medio){
                    medio = score;
                    salvar_arquivo(facil,medio,dificil);
                }
                ranking.imagem_list("tela_wins","numero",score,facil,medio,dificil,'M');
            }
            else if(menu_dificuldade == 3){
                if(score<dificil){
                    dificil = score;
                    salvar_arquivo(facil,medio,dificil);
                }
                ranking.imagem_list("tela_wins","numero",score,facil,medio,dificil,'D');
            }
            controle(eventos,tela);
            SDL_Delay(100);
            teste_criar = true;
        }
        else if(tela == 5){//Tela de derrota
            if(lose){
                Mix_PlayMusic(music_lose,1);//Se 1 então o loop ocorre apenas uma vez
                lose = false;
            }
            win_lose.imagem_list("tela_lose");
            controle(eventos,tela);
            SDL_Delay(100);
            teste_criar = true;
        }
        else if(tela == 6){//Tela de pause do jogo
            if(menu_start == 1)menu_continue.imagem_list("menu_start_cont");
            else if(menu_start == 2)menu_continue.imagem_list("menu_start_sair.bmp");
            controle_start(menu_start,eventos,tela);
            SDL_Delay(100);
        }
        else if(tela == 7){//Tela do ranking
            ranking.imagem_list("tela_rank","numero",score,facil,medio,dificil,'X');
            controle(eventos,tela);
            SDL_Delay(100);
        }
    }
    glDisable(GL_BLEND);
    Mix_FreeMusic(music_menu);
    Mix_FreeMusic(music_game);
    Mix_FreeMusic(music_lose);
    Mix_CloseAudio();
    SDL_Quit();
return 0;
}
void abrir_arquivo(int& facil, int& medio, int& dificil){
    ofstream fo;
    ifstream fi;
    string linha;
    fi.open("pontuacao.txt");
    getline(fi, linha);
    facil = atoi(linha.c_str());
    getline(fi,linha);
    medio = atoi(linha.c_str());
    getline(fi,linha);
    dificil = atoi(linha.c_str());
    fi.close();
}
void salvar_arquivo(int facil, int medio, int dificil){
    ofstream fo;
    ifstream fi;
    fo.open("pontuacao.txt");
    fo<<facil<<endl;
    fo<<medio<<endl;
    fo<<dificil<<endl;
    fo.close();
}
void criar_snake(vector<atuador>&snake, atuador obj1, atuador obj2, atuador obj3, atuador obj4, atuador obj5){
    snake.push_back(obj1);
    snake.push_back(obj2);
    snake.push_back(obj3);
    snake.push_back(obj4);
    snake.push_back(obj5);
    snake.push_back(obj5);
    snake.push_back(obj4);
    snake.push_back(obj3);
    snake.push_back(obj2);
    snake.push_back(obj1);
    snake.push_back(obj1);
    snake.push_back(obj2);
    snake.push_back(obj3);
    snake.push_back(obj4);
    snake.push_back(obj5);
    snake.push_back(obj5);
    snake.push_back(obj4);
    snake.push_back(obj3);
    snake.push_back(obj2);
    snake.push_back(obj1);
    snake.push_back(obj1);
    snake.push_back(obj2);
    snake.push_back(obj3);
    snake.push_back(obj4);
    snake.push_back(obj5);
    snake.push_back(obj5);
    snake.push_back(obj4);
    snake.push_back(obj3);
    snake.push_back(obj2);
    snake.push_back(obj1);
}
void criar_parede(vector<atuador>&parede, atuador obj1, atuador obj2, atuador obj3, atuador obj4){
    parede.push_back(obj1);
    parede.push_back(obj2);
    parede.push_back(obj3);
    parede.push_back(obj4);
}
void cria_obj(vector<atuador>&objeto,int c_r, int c_g, int c_b,vector<atuador>&snake,vector<atuador>&parede,int num_comida){
    for(int i=0;i<num_comida;){
        int x = rand() % tela_x-10 + 10;
        int y = rand() % tela_y-10 + 10;
        if(x%10 == 0 && y%10 == 0){
                atuador obj(x-5,y-5,10,10,c_r,c_g,c_b);
                if(colisao(obj,snake,parede)){
                objeto.push_back(obj);
                i++;
            }
        }
    }
}
void controle(SDL_Event& eventos, int& tela){
    while(SDL_PollEvent(&eventos)){
        if(eventos.type == SDL_KEYDOWN){
            if(eventos.key.keysym.sym == SDLK_SPACE){
                tela = 2;
            }
            else if(eventos.key.keysym.sym == SDLK_ESCAPE){
                tela = 2;
            }
        }
    }
}
void controle_start(int& menu_start,SDL_Event& eventos, int& tela){
    while(SDL_PollEvent(&eventos)){
        if(eventos.type == SDL_KEYDOWN){
            if(eventos.key.keysym.sym == SDLK_SPACE){
                if(menu_start == 1)tela = 3;
                else if(menu_start == 2) tela = 5;
            }
            else if(eventos.key.keysym.sym == SDLK_UP){
                menu_start = 1;
            }
            else if(eventos.key.keysym.sym == SDLK_DOWN){
                menu_start = 2;
            }
        }
    }
}
void controle_dificuldade(int& menu_dificuldade,SDL_Event& eventos,int& select_dificuldade){
    while(SDL_PollEvent(&eventos)){
        if(eventos.type == SDL_KEYDOWN){
            if(eventos.key.keysym.sym == SDLK_SPACE){
                select_dificuldade = 1;
            }
            else if(eventos.key.keysym.sym == SDLK_UP){
                if(menu_dificuldade != 1){
                    menu_dificuldade--;
                }
            }
            else if(eventos.key.keysym.sym == SDLK_DOWN){

                if(menu_dificuldade != 3){
                    menu_dificuldade++;
                }
            }
        }
    }
}
void controle(int& menu,bool& executando,SDL_Event& eventos, int& tela){
    while(SDL_PollEvent(&eventos)){
        if(eventos.type == SDL_KEYDOWN){
            if(eventos.key.keysym.sym == SDLK_SPACE){
                if(menu == 1)tela = 3;
                else if(menu == 2) tela = 7;
                else if(menu == 3) tela = 1;
                else if(menu == 4) executando = false;
            }
            else if(eventos.key.keysym.sym == SDLK_UP){
                if(menu != 1)
                    menu--;
            }
            else if(eventos.key.keysym.sym == SDLK_DOWN){
                if(menu != 4)
                    menu++;
            }
        }
    }
}
void controle(char& l_btn, SDL_Event& eventos, bool& executando, bool& left, bool& right, bool& up, bool& down, int& tela){
    while(SDL_PollEvent(&eventos)){
        if(eventos.type == SDL_QUIT){
            executando = false;
        }
        if(eventos.type == SDL_KEYDOWN){
            if(eventos.key.keysym.sym == SDLK_ESCAPE){
                tela = 6;
            }
            else if(eventos.key.keysym.sym == SDLK_LEFT){
                if(l_btn != 'R')
                    aciona('L',left,right,up,down);
                }
            else if(eventos.key.keysym.sym == SDLK_RIGHT){
                if(l_btn != 'L')
                    aciona('R',left,right,up,down);
            }
            else if(eventos.key.keysym.sym == SDLK_UP){
                if(l_btn != 'D')
                    aciona('U',left,right,up,down);
            }
            else if(eventos.key.keysym.sym == SDLK_DOWN){
                if(l_btn != 'U')
                    aciona('D',left,right,up,down);
            }
        }
    }
}
void aciona(char a,bool& left, bool& right, bool& up, bool& down){
    left = false;
    right = false;
    up = false;
    down = false;
    if(a == 'L') left = true;
    else if(a == 'R') right = true;
    else if(a == 'U') up = true;
    else if(a == 'D') down = true;
}
void movimento_snake(vector<atuador>&snake, char& l_btn, bool left, bool right, bool up, bool down){
    if(left == true){
        for(int i=snake.size();i>0;i--){
            snake[i].andar(snake[i-1]);
        }
        snake[0].andar(11,'X');
        l_btn = 'L';
    }
    else if(right == true){
        for(int i=snake.size();i>0;i--){
            snake[i].andar(snake[i-1]);
        }
            snake[0].andar(-11,'X');
        l_btn = 'R';
    }
    else if(up == true){
        for(int i=snake.size();i>0;i--){
            snake[i].andar(snake[i-1]);
        }
        snake[0].andar(11,'Y');
        l_btn = 'U';
    }
    else if(down == true){
        for(int i=snake.size();i>0;i--){
            snake[i].andar(snake[i-1]);
        }
        snake[0].andar(-11,'Y');
        l_btn = 'D';
    }
}
void velocidade_snake(vector<atuador>snake, int& vel){
    if(snake.size() > 8)
        vel = snake.size()*4;
    else
        vel = 35;
}
bool colisao_obj(atuador obj,vector<atuador>&snake,vector<atuador>&objeto){
    for(int i=0;i<objeto.size();i++){
        if(obj.colisao(objeto[i])){
            if(obj.cor(objeto[i])){
                snake.erase(snake.begin());
                objeto.erase(objeto.begin()+i);
            }
            else{
                snake.push_back(objeto[i]);
                objeto.erase(objeto.begin()+i);
            }
            return true;
        }
    }
    return false;
}
bool colisao(atuador obj, vector<atuador>&snake, vector<atuador>&parede){
    for(int i=1;i<snake.size();i++){
        if(obj.colisao(snake[i]))
            return false;
    }
    for(int i=0;i<parede.size();i++){
        if(obj.colisao(parede[i]))
            return false;
    }
    return true;
}
void desenhar(mapa mapa_snake,vector<atuador>parede,vector<atuador>snake,vector<atuador>obj1,vector<atuador>obj2,vector<atuador>obj3,vector<atuador>obj4,vector<atuador>obj5){
    glClear(GL_COLOR_BUFFER_BIT);//Limpa o buffer
    glPushMatrix();
    glOrtho(0,tela_x,tela_y,0,-1,1);//dimensoes da matriz
        mapa_snake.criar_mapa();
        mapa_snake.cor_mapa();
        criar(parede);
        criar(snake);
        criar(obj1);
        criar(obj2);
        criar(obj3);
        criar(obj4);
        criar(obj5);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    SDL_GL_SwapBuffers();
}
void criar(vector<atuador>obj){
    for(int i=0;i<obj.size();i++){
        obj[i].criar();
    }
}
