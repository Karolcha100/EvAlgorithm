//
// Created by karol on 16.08.24.
//
#include <iostream>
#include <cstdlib>


using namespace std;

class Gen
{
    int possible_next[2] = {-1, -1};
    int coefs[6][7] = {{0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}}; // (dir_w, dir_x, change_w, change_x, next)(n, k, bias)
    int coef_num = 6;
    int coef_size = 7;
    int mutatity = 5;
    int selfnum;

    static int rnd_int(int min, int max)
    {
        return rand()%(max-min+1)+min;
    }

    public:

    Gen(int next1 = -1, int next2 = -1, int mutt = 5, int num = -1)
    {
        possible_next[0] = next1;
        possible_next[1] = next2;
        mutatity = mutt;
        selfnum = num;
    }

    Gen(const Gen &other)
    {
        mutatity = other.mutatity;
        coef_num = other.coef_num;
        coef_size = other.coef_size;

        for (int i = 0; i < 2; i++)
        {
            possible_next[i] = other.possible_next[i];
        }
        for (int i = 0; i < coef_num; i++)
        {
            for (int j = 0; j < coef_size; j++)
            {
                coefs[i][j] = other.coefs[i][j];
            }
        }
    }

    void set_next(int next1, int next2)
    {
        possible_next[0] = next1;
        possible_next[1] = next2;
    }

    void set_num(int num)
    {
        selfnum = num;
    }

    void mutate_coef()
    {
        int num = rnd_int(0, coef_num-1);
        int size_num = rnd_int(0, coef_size-1);

        coefs[num][size_num] += rnd_int(-mutatity, mutatity);
    }

    void mutate_next_gen(int next)
    {
        possible_next[rnd_int(0,1)] = next;
    }

    int get_direction_w(int n, int kw, int kx, int w, int x, int answ)
    {
        return coefs[0][0] * n + coefs[0][1] * kw + coefs[0][2]*kx + coefs[0][3]*w + coefs[0][4]*x + coefs[0][5] * answ + coefs[0][6];
    }

    int get_direction_x(int n, int kw, int kx, int w, int x, int answ)
    {
        return coefs[1][0] * n + coefs[1][1] * kw + coefs[1][2]*kx + coefs[1][3]*w + coefs[1][4]*x + coefs[1][5] * answ + coefs[1][6];
    }

    int get_change_w(int n, int kw, int kx, int w, int x, int answ)
    {
        return coefs[2][0] * n + coefs[2][1] * kw + coefs[2][2]*kx + coefs[2][3]*w + coefs[2][4]*x + coefs[2][5] * answ + coefs[2][6];
    }

    int get_change_x(int n, int kw, int kx, int w, int x, int answ)
    {
        return coefs[3][0] * n + coefs[3][1] * kw + coefs[3][2]*kx + coefs[3][3]*w + coefs[3][4]*x + coefs[3][5] * answ + coefs[3][6];
    }

    int get_next(int n, int kw, int kx, int w, int x, int answ)
    {
        int val = coefs[4][0] * n + coefs[4][1] * kw + coefs[4][2]*kx + coefs[4][3]*w + coefs[4][4]*x + coefs[4][5] * answ + coefs[4][6];

        if (val < 0)
        {
            return possible_next[0];
        }
        if (val > 0)
        {
            return possible_next[1];
        }

        return selfnum;
    }

    int get_answer_parts(int n, int kw, int kx, int w, int x, int answ)
    {
        return coefs[5][0] * n + coefs[5][1] * kw + coefs[5][2]*kx + coefs[5][3]*w + coefs[5][4]*x + coefs[5][5] * answ + coefs[5][6];
    }


};
