#include <SDL.h>
#include "SDL_opengl.h"
#include "mapa_snake.h"
using namespace std;
mapa::mapa(int x, int y, int r, int g, int b){
        eixox = x;
        eixoy = y;
        cor[0] = r;
        cor[1] = g;
        cor[2] = b;
}
void mapa::criar_mapa(){
        SDL_Init(SDL_INIT_VIDEO);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        //nome do jogo
        SDL_SetVideoMode(eixox, eixoy, 32, SDL_OPENGL);//inserir valores dos eixos
        glClearColor(1,1,1,1);//cor de fundo, preta ou branca
        glViewport(0,0,eixox,eixoy);
        glShadeModel(GL_SMOOTH);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);
}
void mapa::cor_mapa(){
    glOrtho(0,eixox,eixoy,0,-1,1);//dimensoes da matriz
//CRIANDO FUNDO
    glBegin(GL_QUADS);//Quadrado
    glColor4ub(cor[0],cor[1],cor[2],255);//cor de fundo
    glVertex2f(0,0);
    glVertex2f(0,eixoy);
    glVertex2f(eixox,eixoy);
    glVertex2f(eixox,0);
    glEnd();
//
}

void pagina::imagem_list(string fundo){
    SDL_Surface* screen = NULL;
    SDL_Surface* imagem = NULL;
    if(fundo == "abertura")imagem = SDL_LoadBMP("abertura.bmp");
    else if(fundo == "menu_jogar")imagem = SDL_LoadBMP("menu_jogar.bmp");
    else if(fundo == "menu_rank")imagem = SDL_LoadBMP("menu_rank.bmp");
    else if(fundo == "menu_about")imagem = SDL_LoadBMP("menu_about.bmp");
    else if(fundo == "menu_exit")imagem = SDL_LoadBMP("menu_exit.bmp");
    else if(fundo == "menu_jogar_facil")imagem = SDL_LoadBMP("menu_jogar_facil.bmp");
    else if(fundo == "menu_jogar_medio")imagem = SDL_LoadBMP("menu_jogar_medio.bmp");
    else if(fundo == "menu_jogar_dificil")imagem = SDL_LoadBMP("menu_jogar_dificil.bmp");
    else if(fundo == "tela_lose")imagem = SDL_LoadBMP("tela_lose.bmp");
    else if(fundo == "menu_start_cont")imagem = SDL_LoadBMP("menu_start_cont.bmp");
    else if(fundo == "menu_start_sair")imagem = SDL_LoadBMP("menu_start_sair.bmp");
    else if(fundo == "tela_lose")imagem = SDL_LoadBMP("tela_lose.bmp");
    mostrar_imagem(imagem,screen);
}
void pagina::mostrar_imagem(SDL_Surface* imagem,SDL_Surface* screen){
    screen = SDL_SetVideoMode(1100, 500, 32, SDL_SWSURFACE);
    SDL_BlitSurface(imagem,NULL,screen,NULL);
    SDL_Flip(screen);
    SDL_WM_SetCaption("Colorful Snake", NULL);
}
void pagina::imagem_list(string fundo, string num, int score, int facil, int medio, int dificil, char nivel){
    int M,C,D,U;
    SDL_Surface* screen = NULL;
    SDL_Surface* imagem = NULL;
    SDL_Surface* imagem_num = NULL;
    if(fundo == "tela_wins")imagem = SDL_LoadBMP("tela_wins.bmp");
    else if(fundo == "tela_rank")imagem = SDL_LoadBMP("tela_rank.bmp");
    imagem_num = SDL_LoadBMP("numeros.bmp");
    screen = SDL_SetVideoMode(1100, 500, 32, SDL_SWSURFACE);
    if(fundo == "tela_wins"){
        converte(M,C,D,U,score);
        mostrar_imagem(imagem_num,imagem,screen,0,25,58,255,50,58,M*25,C*25,D*25,U*25,290);
        if(nivel == 'F')converte(M,C,D,U,facil);
        else if(nivel == 'M')converte(M,C,D,U,medio);
        else if(nivel == 'D')converte(M,C,D,U,dificil);
        mostrar_imagem(imagem_num,screen,0,25,58,255,50,58,M*25,C*25,D*25,U*25,915);
        SDL_Flip(screen);
    }
    else if(fundo == "tela_rank"){
        converte(M,C,D,U,facil);
        mostrar_imagem(imagem_num,imagem,screen,0,25,58,232,50,58,M*25,C*25,D*25,U*25,550);
        converte(M,C,D,U,medio);
        mostrar_imagem(imagem_num,screen,0,25,58,298,50,58,M*25,C*25,D*25,U*25,565);
        converte(M,C,D,U,dificil);
        mostrar_imagem(imagem_num,screen,0,25,58,360,50,58,M*25,C*25,D*25,U*25,570);
        SDL_Flip(screen);
    }
}
void pagina::converte(int& M, int& C, int& D, int& U, int& score){
    M = score/1000;
    C = score%1000/100;
    D = score%1000%100/10;
    U = score%1000%100%10;
}
void pagina::mostrar_imagem(SDL_Surface* imagem, SDL_Surface* imagem2,SDL_Surface* screen,int y_p,int w_p,int h_p,int y_l,int w_l,int h_l,int x_p_1,int x_p_2,int x_p_3,int x_p_4,int x_l){
    SDL_Rect pos;
    SDL_Rect local;
    SDL_Rect pos_2;
    SDL_Rect local_2;
    SDL_Rect pos_3;
    SDL_Rect local_3;
    SDL_Rect pos_4;
    SDL_Rect local_4;
    pos.x = x_p_1;
    pos.y = y_p;
    pos.w = w_p;
    pos.h = h_p;
    local.x = x_l;
    local.y = y_l;
    local.w = w_l;
    local.h = h_l;
    pos_2.x = x_p_2;
    pos_2.y = y_p;
    pos_2.w = w_p;
    pos_2.h = h_p;
    local_2.x = x_l+25;
    local_2.y = y_l;
    local_2.w = w_l;
    local_2.h = h_l;
    pos_3.x = x_p_3;
    pos_3.y = y_p;
    pos_3.w = w_p;
    pos_3.h = h_p;
    local_3.x = x_l+50;
    local_3.y = y_l;
    local_3.w = w_l;
    local_3.h = h_l;
    pos_4.x = x_p_4;
    pos_4.y = y_p;
    pos_4.w = w_p;
    pos_4.h = h_p;
    local_4.x = x_l+75;
    local_4.y = y_l;
    local_4.w = w_l;
    local_4.h = h_l;
    SDL_BlitSurface(imagem2,NULL,screen,NULL);
    SDL_BlitSurface(imagem,&pos,screen,&local);
    SDL_BlitSurface(imagem,&pos_2,screen,&local_2);
    SDL_BlitSurface(imagem,&pos_3,screen,&local_3);
    SDL_BlitSurface(imagem,&pos_4,screen,&local_4);
}
void pagina::mostrar_imagem(SDL_Surface* imagem,SDL_Surface* screen,int y_p,int w_p,int h_p,int y_l,int w_l,int h_l,int x_p_1,int x_p_2,int x_p_3,int x_p_4,int x_l){
    SDL_Rect pos;
    SDL_Rect local;
    SDL_Rect pos_2;
    SDL_Rect local_2;
    SDL_Rect pos_3;
    SDL_Rect local_3;
    SDL_Rect pos_4;
    SDL_Rect local_4;
    pos.x = x_p_1;
    pos.y = y_p;
    pos.w = w_p;
    pos.h = h_p;
    local.x = x_l;
    local.y = y_l;
    local.w = w_l;
    local.h = h_l;
    pos_2.x = x_p_2;
    pos_2.y = y_p;
    pos_2.w = w_p;
    pos_2.h = h_p;
    local_2.x = x_l+25;
    local_2.y = y_l;
    local_2.w = w_l;
    local_2.h = h_l;
    pos_3.x = x_p_3;
    pos_3.y = y_p;
    pos_3.w = w_p;
    pos_3.h = h_p;
    local_3.x = x_l+50;
    local_3.y = y_l;
    local_3.w = w_l;
    local_3.h = h_l;
    pos_4.x = x_p_4;
    pos_4.y = y_p;
    pos_4.w = w_p;
    pos_4.h = h_p;
    local_4.x = x_l+75;
    local_4.y = y_l;
    local_4.w = w_l;
    local_4.h = h_l;
    SDL_BlitSurface(imagem,&pos,screen,&local);
    SDL_BlitSurface(imagem,&pos_2,screen,&local_2);
    SDL_BlitSurface(imagem,&pos_3,screen,&local_3);
    SDL_BlitSurface(imagem,&pos_4,screen,&local_4);
}

