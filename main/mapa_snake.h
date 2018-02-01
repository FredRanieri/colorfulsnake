#ifndef MAPA_SNAKE.h
#define MAPA_SNAKE.h
#include<string>
using namespace std;
class mapa{
    int eixox;
    int eixoy;
    int cor[3];
  public:
    mapa (int x, int y, int r, int g, int b);
    void criar_mapa();
    void cor_mapa();
};
class pagina{
    string fundo;
    string musica;
 public:
    void imagem_list(string fundo);
    void imagem_list(string fundo, string num, int score, int facil, int medio, int dificil, char nivel);
    void mostrar_imagem(SDL_Surface* imagem,SDL_Surface* screen);
    void mostrar_imagem(SDL_Surface* imagem, SDL_Surface* imagem2,SDL_Surface* screen,int y_p,int w_p,int h_p,int y_l,int w_l,int h_l,int x_p_1,int x_p_2,int x_p_3,int x_p_4,int x_l);
    void mostrar_imagem(SDL_Surface* imagem,SDL_Surface* screen,int y_p,int w_p,int h_p,int y_l,int w_l,int h_l,int x_p_1,int x_p_2,int x_p_3,int x_p_4,int x_l);
    void converte(int& M, int& C, int& D, int& U, int& score);
};
#endif // mapa
