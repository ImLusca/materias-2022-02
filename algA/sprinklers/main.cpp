#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

void calculaSprinklers(int numInputs)
{
    int largura, altura;
    scanf("%i %i", &largura, &altura);

    std::vector<std::pair<int, int>> sprinklers;

    for (int i = 0; i < numInputs; i++)
    {
        int position, radius;

        scanf("%i %i", &position, &radius);

        if (radius <= altura)
            continue;

        double areaCoberta = sqrt(fabs(pow(altura, 2) / 4 - pow(radius, 2)));

        std::pair<int, int> novoSprinkler{position - areaCoberta, position + areaCoberta};

        sprinklers.push_back(novoSprinkler);
    }

    std::sort(sprinklers.begin(), sprinklers.end());

    int rightestPoint = 0, left = sprinklers[0].first;
    int contagemSprinklers = 0;

    for (int i = 0; i < sprinklers.size(); i++)
    {
        if (sprinklers[i].first > rightestPoint)
        {
            printf("-1");
            return;
        }

        int newRight = rightestPoint;

        while (i < sprinklers.size() && sprinklers[i].first <= rightestPoint)
        {
            if (sprinklers[i].second > newRight)
            {
                newRight = sprinklers[i].second;
            }
            i++;
        } 

        i--;

        if (newRight > rightestPoint)
        {
            contagemSprinklers++;
            rightestPoint = newRight;
            if (rightestPoint >= largura)
                break;

            continue;
        }

        printf("-1");
        return;
    }
}

int main()
{

    // l -> largura
    // w -> altura
    // n -> num of sprinklers

    // pos and radius
    int numInputs;
    while ((scanf("%i", &numInputs) != EOF))
    {
        calculaSprinklers(numInputs);
    }
}