// Lucas Pereira Pacheco nºusp: 12543930
// Gul2

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h>
#include <math.h>

void funcao(int numCapsulas, int numAmostras);

int main()
{
    int numSet = 1;
    int numCapsulas, numAmostras;
    while ((scanf("%i %i", &numCapsulas, &numAmostras) != EOF))
    {
        printf("Set #%i\n", numSet++);
        funcao(numCapsulas, numAmostras);
    }
}

void funcao(int numCapsulas, int numAmostras)
{

    std::vector<int> amostras(numAmostras);
    int capsulas[3][numCapsulas];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < numCapsulas; j++)
        {
            capsulas[i][j] = 0;
        }
    }

    // Receber inputs

    for (int i = 0; i < numAmostras; i++)
    {
        scanf("%i", &amostras[i]);
    }

    // ordenar
    std::sort(amostras.rbegin(), amostras.rend());

    // distribuir
    for (int i = 0; i < numAmostras; i++)
    {
        int menorPeso = INT_MAX;
        int capsulaMaisLeve;
        for (int j = 0; j < numCapsulas; j++)
        {
            if (capsulas[0][j] <= menorPeso)
            {
                capsulaMaisLeve = j;
                menorPeso = capsulas[0][j];
            }
        }

        for (int j = 1; j < 3; j++)
        {
            if (capsulas[j][capsulaMaisLeve] != 0)
            {
                continue;
            }

            capsulas[j][capsulaMaisLeve] = amostras[i];
            capsulas[0][capsulaMaisLeve] += amostras[i];
            if (j == 2)
            {
                capsulas[0][capsulaMaisLeve] = INT_MAX;
            }
            break;
        }
    }

    // calcular balanço
    double imbalance = 0, media = 0;

    for (int i = 0; i < numCapsulas; i++)
    {
        int capsula = 0;
        for (int j = 1; j < 3; j++)
        {
            capsula += capsulas[j][i];
        }
        capsulas[0][i] = capsula;
        media += capsula;
    }
    media /= numCapsulas;

    for (int i = 0; i < numCapsulas; i++)
    {
        imbalance += fabs(capsulas[0][i] - media);
    }

    for (int i = 0; i < numCapsulas; i++)
    {
        printf(" %i: ", i);

        for (int j = 1; j < 3; j++)
        {
            if (capsulas[j][i] != 0)
            {
                printf("%i ", capsulas[j][i]);
            }
        }
        printf("\n");
    }

    printf("IMBALANCE = %.5f\n\n", imbalance);
}
