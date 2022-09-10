// Lucas Pereira Pacheco nºusp: 12543930

#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <limits.h>

#define INVALID return -1;

int contaSprinklers(int numInputs);
int contaRetangulos(std::vector<std::pair<int, int>> sprinklers, int larguraCampo);
std::vector<std::pair<int, int>> calculaRetangulos(int alturaCampo, int numInputs);

int main()
{
    int numInputs;
    while ((scanf("%i", &numInputs) != EOF))
    {
        printf("%i\n", contaSprinklers(numInputs));
    }
}

int contaSprinklers(int numInputs)
{
    int largura, altura;
    scanf("%i %i", &largura, &altura);

    std::vector<std::pair<int, int>> sprinklers = calculaRetangulos(altura, numInputs);

    if (!sprinklers.size()) INVALID

    return contaRetangulos(sprinklers, largura);
}

std::vector<std::pair<int, int>> calculaRetangulos(int alturaCampo, int numInputs)
{

    std::vector<std::pair<int, int>> sprinklers;

    for (int i = 0; i < numInputs; i++)
    {
        int position, radius;

        scanf("%i %i", &position, &radius);

        if (radius * 2 <= alturaCampo || radius > 1000) continue;

        double areaCoberta = sqrt(fabs(pow(alturaCampo, 2) / 4 - pow(radius, 2)));
    
        std::pair<int, int> novoSprinkler{position - areaCoberta, position + areaCoberta};

        sprinklers.push_back(novoSprinkler);
    }

    return sprinklers;
}

int contaRetangulos(std::vector<std::pair<int, int>> sprinklers, int larguraCampo)
{
    std::sort(sprinklers.begin(), sprinklers.end());

    int rightestPoint = 0, contagemSprinklers = 0;

    for (int i = 0; i < (int)sprinklers.size(); i++)
    {
        if (sprinklers[i].first > rightestPoint) INVALID

        int newRight = rightestPoint;

        while (i < (int)sprinklers.size() && sprinklers[i].first <= rightestPoint)
        {
            if (sprinklers[i].second > newRight)
                newRight = sprinklers[i].second;

            i++;
        }

        i--;

        if (newRight > rightestPoint)
        {
            contagemSprinklers++;
            rightestPoint = newRight;
            if (rightestPoint >= larguraCampo) break;
            
            continue;
        }

        INVALID
    }
    return contagemSprinklers;
}