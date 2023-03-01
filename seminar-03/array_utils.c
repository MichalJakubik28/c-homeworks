#include "array_utils.h"

int find_max_in_array(int array[ARRAY_LENGTH])
{
    int max = array[0];
    for (int i = 1; i < ARRAY_LENGTH; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

int find_min_in_array(int array[ARRAY_LENGTH])
{
    int min = array[0];
    for (int i = 1; i < ARRAY_LENGTH; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}

int find_sum_in_array(int array[ARRAY_LENGTH])
{
    {
        int sum = 0;
        for (int i = 0; i < ARRAY_LENGTH; i++)
        {
            sum += array[i];
        }
        return sum;
    }
}
