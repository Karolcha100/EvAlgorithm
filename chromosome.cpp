//
// Created by karol on 16.08.24.
//
#include <iostream>
#include <cstdlib>

#include "gen.cpp"

using namespace std;

class Chromosome
{
    int genome_len = 10;
    Gen genome[10];

    float energy = 20;
    float gen_dir_mut_chance = 0.1;
    int ending_gen = 9;

    static float rnd_float(float min, float max)
    {
        return (rand() / (float)RAND_MAX) * (max - min) + min;
    }

    static int rnd_int(int min, int max)
    {
        return rand()%(max-min+1)+min;
    }

    public:

    Chromosome()
    {
        for(int i = 0; i < genome_len; i++)
        {
            genome[i].set_num(i+1);
            if (i < genome_len - 2)
            {
                genome[i].set_next(i+1,i+1);
            }else
            {
                genome[i].set_next(-1,-1);
            }
        }
    }

    Chromosome(const Chromosome &other)
    {
        genome_len = other.genome_len;
        for(int i = 0; i < genome_len; i++)
        {
            genome[i] = other.genome[i];
        }
        energy = 20;
        gen_dir_mut_chance = other.gen_dir_mut_chance;
        ending_gen = other.ending_gen;
    }

    void mutate()
    {
        int gen_num = rnd_int(0,genome_len-1);
        genome[gen_num].mutate_coef();
        if (rnd_float(0,1) < gen_dir_mut_chance)
        {
            int new_next = rnd_int(0,genome_len-1);
            genome[gen_num].mutate_next_gen(new_next);
        }
    }

    int get_answer(int n, int *w, int *x)
    {
        int answer = 0;
        int kw = 0;
        int kx = 0;
        int curent_gen = 0;
        while(true)
        {
            energy -= 1;

            kw += genome[curent_gen].get_direction_w(n, kw, kx, w[kw], x[kx], answer);

            if (kw >= n or kw < 0)
            {
                break;
            }

            kx += genome[curent_gen].get_direction_x(n, kw, kx, w[kw], x[kx], answer);

            if (kx >= n-1 or kx < 0)
            {
                break;
            }

            w[kw] += genome[curent_gen].get_change_w(n, kw, kx, w[kw], x[kx], answer);
            x[kx] += genome[curent_gen].get_change_x(n, kw, kx, w[kw], x[kx], answer);
            answer += genome[curent_gen].get_answer_parts(n, kw, kx, w[kw], x[kx], answer);
            curent_gen = genome[curent_gen].get_next(n, kw, kx, w[kw], x[kx], answer);

            if (curent_gen == ending_gen or energy < 0)
            {
                break;
            }
        }

        return answer;
    }

    void add_energy(float en)
    {
        energy += en;
    }

    void set_energy(float en)
    {
        energy = en;
    }

    float get_energy()
    {
        return energy;
    }
};

