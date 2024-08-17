//
// Created by karol on 17.08.24.
//

#include <iostream>

using namespace std;


class Teacher
{
    int if_can_delete_block(int tall, int space, int next_space)
    {
        if (tall > space + next_space)
        {
            return 1;
        }

        return 0;
    }

    int sum(int n, int *arr)
    {
        int arrsum = 0;
        for (int i = 0; i < n; i++)
        {
            arrsum += arr[i];
        }

        return arrsum;
    }

    int load_n()
    {
        int n;
        cin >> n;
        return n;
    }

    void load_wx(int n, int *w, int *x)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> w[i];
        }

        for (int i = 0; i < n - 1; i++)
        {
            cin >> x[i];
        }
    }

    void calculate_how_much_replaces(int n, int *w, int *x, int *num_replaces)
    {
        int len_of = 0;
        int num_of_blocks = 0;
        for (int i = 0; i < n - 1; i++)
        {
            len_of = w[i] - x[i];
            num_of_blocks = 1;
            while(true)
            {
                if (len_of > x[i + num_of_blocks] && i + num_of_blocks < n - 2)
                {
                    num_of_blocks++;
                    len_of -= x[i + num_of_blocks + 1];
                }else if(i == n - 2) // Można pominąć warunek!!!
                {
                    num_of_blocks = 1;
                    break;
                }else
                {
                    break;
                }
            }
            num_replaces[i] = num_of_blocks;

        }
    }

    int find_max_index(int n, int *num_replaces)
    {
        int arr_max = 1;
        int index = -1;
        for (int i = 0; i < n - 1; i++)
        {
            if (num_replaces[i] >= arr_max)
            {
                index = i;
                arr_max = num_replaces[i];
            }
        }
        if (arr_max == 1)
        {
            return -1;
        }
        return index;
    }

    static int rnd_int(int min, int max)
    {
        return rand()%(max-min+1)+min;
    }

public:

    int machen(int n, int *a, int *b)
    {
        int w[n];
        int x[n];
        int total_replacements = 0;

        for (int i = 0; i<n; i++)
        {
            w[i] = a[i];
        }
        for (int i = 0; i < n-1; i++)
        {
            x[i] = b[i];
        }

        int index = 0;
        int num_of_replacements = 0;
        while(true)
        {
            int num_which_replaces[n-1];
            calculate_how_much_replaces(n, w, x, num_which_replaces);
            index = find_max_index(n, num_which_replaces);

            // cout << "NEW ITERATION" << endl;
            // print_domino(n,w,x);
            // for (int i = 0; i < n - 1; i++)
            // {
            //     cout << "N[" << i << "] = " << num_which_replaces[i] << endl;
            // }

            if (index == -1)
            {
                break;
            }

            num_of_replacements = num_which_replaces[index];

            total_replacements += num_of_replacements;

            int new_array_w[n - num_of_replacements];
            int a = 0;
            for (int i = 0; i < n; i++)
            {
                if (!(i > index && i <= index + num_of_replacements))
                {
                    new_array_w[a] = w[i];
                    a++;
                }
            }

            int new_array_x[n - num_of_replacements - 1];
            int b = 0;
            for (int i = 0; i < n-1; i++)
            {
                if (!(i > index && i <= index + num_of_replacements))
                {
                    new_array_x[b] = x[i];
                    b++;
                }else
                {
                    new_array_x[b-1] += x[i];
                }
            }

            n = n - num_of_replacements;

            for (int i = 0; i<n; i++)
            {
                w[i] = new_array_w[i];
            }
            for (int i = 0; i < n-1; i++)
            {
                x[i] = new_array_x[i];
            }
        }

        return total_replacements;
    }

    void create_domino(int n, int *w, int *x)
    {
        for(int i = 0; i < n-1; i++)
        {
            w[i] = rnd_int(2,10);
            x[i] = rnd_int(1,w[i]-1);
        }
        w[n-1] = 1;
    }
};
