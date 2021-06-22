#include <stdio.h>
#include <math.h>


#define PI 3.14159265 


int main()
{
    double alpha = 0;
    double res;
    int tmp;
    char buf[20];
    int size = 10000000;
    int len;
    while(1)
    {
        scanf("%d", &tmp);
        res = 0;
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
                res += cos(k * PI / 180) + sin(j * PI / 180);
        }
        printf("%f ", res);
    }
    printf("\n ok \n");
}