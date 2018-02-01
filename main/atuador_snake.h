#ifndef ATUADOR_SNAKE.h
#define ATUADOR_SNAKE.h
class atuador{
    int posx;
    int posy;
    int comp;
    int alt;
    int cor_red;
    int cor_green;
    int cor_blue;
  public:
    atuador(int p_x, int p_y, int comp, int alt, int r, int g, int b);
    void criar();
    void criar(int vis);
    void andar(int a, char x_y);
    void andar(atuador obj);
    bool colisao(atuador obj);
    bool cor(atuador obj);
};
#endif // atuador

