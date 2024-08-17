#include <iostream>
#include <cstdlib>
#include <ctime>

#include "environment.cpp"

using namespace std;

int main()
{
    // srand(time(NULL));

    Environment env(10);

    int rounds = 0;
    while(rounds < 1000)
    {
        rounds++;
        env.round();
        cout << "R: " << rounds << " ,N: " << env.get_number_of_chromosomes() << " ,BS: " << env.get_best_score() << " ,MS: " << env.get_mean_score() << endl;
    }

    return 0;
}
