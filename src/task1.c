#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ERROR(...) (fprintf(stderr,__VA_ARGS__))

double func(double x)
{
    return sin(x);
}

double CountRiemann(int n, double a, double b)
{
    double s = (func(a) + func(b)) / 2;
    double height = (b-a) / n;

    for (int i = 1; i <= n-1; i++)
        s += func(a + i * height);
    return height * s;
}

double CountSimpson(int n, double a, double b)
{
    double x = 0.0;
    double simpson_integral = 0.0;
    int m = 2 * n;

    x = (b - a) / m;
    simpson_integral = func(a) + func(b);

    for (int i = 1; i < m; i++)
    {
        a += x;
        if ((i % 2) == 0)
            simpson_integral += 2 * func(a);
        else
            simpson_integral += 4 * func(a);
    }
    return simpson_integral * x / 3;
}

void FreeArray(char **arr, unsigned int len)
{
    for (int i = 0; i < len; ++i)
    {
        free(arr[i]);
    }
    free(arr);
}

int ReadVals(double *a, double *b)
{
    if (printf("Enter left border\n") < 0)
    {
        ERROR("Can't write to stdout");
        return 0;
    }
    if (scanf("%lf", a) != 1)
    {
        ERROR("Can't read left border");
        return 0;
    }
    if (*a < 0)
    {
        ERROR("Left border is less than 0");
        return 0;
    }
    if (*a > M_PI)
    {
        ERROR("Left border is greater than PI");
        return 0;
    }
    if (printf("Enter right border\n") < 0)
    {
        ERROR("Cannot write to stdout");
        return 0;
    }
    if (scanf("%lf", b) != 1)
    {
        ERROR("Cannot read right border");
        return 0;
    }
    if (*b > M_PI)
    {
        ERROR("Right border is greater than PI");
        return 0;
    }
    if (*a > *b)
    {
        ERROR("Right border is less than the left border");
        return 0;
    }
    if (*a == *b)
    {
        ERROR("Left and right borders are equal");
        return 0;
    }
    return 1;
}

char **CountAllSquares(int arr[], double a, double b, const unsigned int LEN)
{
    char **out = (char **) malloc(sizeof(char *) * LEN);
    if (!out)
    {
        ERROR("Can't allocate memory for **out\n");
        return NULL;
    }
    for (int i = 0; i < LEN; i++)
    {
        out[i] = (char *) malloc(sizeof(char) * 32);
        if (!out[i])
        {
            FreeArray(out, i);
            ERROR("Can't allocate memory for out[%d]\n", i);
            return NULL;
        }
        if (!sprintf(out[i], "%d %.5f %.5f", arr[i], CountRiemann(arr[i], a, b), CountSimpson(arr[i], a, b)))
        {
            ERROR("Can't write string to out[%d]\n", i);
            return NULL;
        }
    }
    return out;
}

int main()
{
    int arr[] = {6, 10, 20, 100, 500, 1000};
    unsigned int LEN = (unsigned int)(sizeof(arr)/sizeof(arr[0]));
    double a, b;
    if (ReadVals(&a, &b) == 1)
    {
        char **out = CountAllSquares(arr, a, b, LEN);
        for(unsigned int i = 0; i < LEN; i++)
        {
            printf("%s\n", out[i]);
        }
    }
    else
    {
        return 1;
    }
    return 0;
}