#include <stdio.h>
#include <math.h>


#define PI 3.14159265 


int main()
{
    double alpha = 0;
    double res;
    int size = 1000000;
    int len;
    for (int i = 0; i < size; i++)
    {
        res = 0;
        for (int j = 0; j < size; j++)
        {
            res += cos(i * PI / 180) + sin(j * PI / 180);
        }
        printf("%f", res);
    }
    printf("\n ok \n");
}