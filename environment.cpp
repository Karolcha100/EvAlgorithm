//
// Created by karol on 17.08.24.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

#include "chromosome.cpp"
#include "teacher.cpp"

using namespace std;

class Environment
{
    int rounds = 0;

    vector<Chromosome> chromosomes;
    vector<float> scores;
    float energy_to_redistribute = 10000;

    Teacher teacher;

    vector<int> to_death;

    float fitness_function(int answer, int correct)
    {
        return exp(-pow((answer - correct),2));
    }

    static int rnd_int(int min, int max)
    {
        return rand()%(max-min+1)+min;
    }

    void calculate_scores()
    {
        int n = rnd_int(0, 20);
        int w[n];
        int x[n-1];

        teacher.create_domino(n,w,x);
        int cor_answer =  teacher.machen(n,w,x);

        for (int i = 0; i < chromosomes.size(); i++)
        {
            scores[i] = fitness_function(chromosomes[i].get_answer(n,w,x),cor_answer);
        }
    }

    float sum_scores()
    {
        float sum = 0;
        for (int i = 0; i < scores.size(); i++)
        {
            sum += scores[i];
        }
        return sum;
    }

    void calculate_energy_redistribution()
    {
        float score_sum = sum_scores();
        for (int i = 0; i < scores.size(); i++)
        {
            chromosomes[i].add_energy(energy_to_redistribute * scores[i]/score_sum);
        }
    }

    void calculate_to_death()
    {
        for (int i = 0; i < chromosomes.size(); i++)
        {
            if (chromosomes[i].get_energy() <= 0)
            {
                chromosomes.erase(chromosomes.begin() + i);
                scores.erase(scores.begin() + i);
                i--;
            }
        }
    }

    void calculate_to_reproduce()
    {
        float score_sum = sum_scores();

        int count_of_reproduce = 0;
        for (int i = 0; i < scores.size(); i++)
        {
            for (int j = 0; j < int(200 * scores[i]/score_sum); j++)
            {
                count_of_reproduce++;
                Chromosome newborn = chromosomes[i];
                newborn.mutate();
                chromosomes.push_back(newborn);
                scores.push_back(0);
            }
        }
        std::cout << "Count of reproduce: " << count_of_reproduce << std::endl;
    }

public:

    void round()
    {
        std::cout << "Scores size before " << rounds+1 << " rounds:" << scores.size() << std::endl;
        rounds++;
        calculate_scores();
        calculate_energy_redistribution();
        calculate_to_death();
        calculate_to_reproduce();
    }

    int get_number_of_chromosomes()
    {
        return chromosomes.size();
    }

    float get_best_score()
    {
        float best = 0;
        for (int i = 0; i < scores.size(); i++)
        {
            if (scores[i] > best)
            {
            best = scores[i];
            }
        }

        return best;
    }

    float get_mean_score()
    {
        float mean = 0;
        for (int i = 0; i < scores.size(); i++)
        {
            mean += scores[i];
        }

        return mean/float(scores.size());
    }

    Environment(float en)
    {
        energy_to_redistribute = en;
        chromosomes.push_back(Chromosome());
        scores.push_back(0);
    }
};
