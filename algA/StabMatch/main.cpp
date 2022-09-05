#include <stdio.h>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#define MATINT std::vector<std::vector<int>>

MATINT leListaPreferencias(int numPessoas, char tipoLeitura)
{
    MATINT preferencias(numPessoas);
    for (int i = 0; i < numPessoas; i++)
    {
        preferencias[i] = std::vector<int>(numPessoas);
        scanf("%*i");
        for (int j = 0; j < numPessoas; j++)
        {
            if (tipoLeitura == 'M')
            {
                scanf("%i", &preferencias[i][j]);
                preferencias[i][j]--;
            }
            else if (tipoLeitura == 'W')
            {
                // A lista de preferencias das mulheres é indexada ao inverso
                // com o funcionamento semelhante ao hashmap. Pois assim conseguimos descobrir a preferencia
                // que a mulher tem por um homem sem percorrer toda lista
                int pessoa;
                scanf("%i", &pessoa);
                preferencias[i][pessoa - 1] = j;
            }
        }
    }

    return preferencias;
}

void formaCasais(MATINT listaPrefsH, MATINT listaPrefsM)
{

    std::queue<int> solteirosH;
    std::unordered_set<int> solteirosM;
    std::unordered_map<int, int> casais;
    std::vector<int> rejeicoes(listaPrefsH.size(), 0);

    for (int i = 0; i < (int)listaPrefsH.size(); i++)
    {
        solteirosH.push(i);
        solteirosM.insert(i);
    }

    while (!solteirosH.empty())
    {

        int homem = solteirosH.front();
        int numRejeicoes = rejeicoes[homem];
        solteirosH.pop();

        for (int i = numRejeicoes; i < (int)listaPrefsH.size(); i++, rejeicoes[homem]++)
        {

            int preferencia = listaPrefsH[homem][i];

            // Verificar se a mulher está solteira
            if (solteirosM.find(preferencia) != solteirosM.end())
            {
                // Se sim, engaja os dois
                casais[preferencia] = homem;
                solteirosM.erase(preferencia);
                break;
            }

            // Se não, compara preferencia da mulher com casal atual
            int atual = casais[preferencia];

            if (listaPrefsM[preferencia][atual] > listaPrefsM[preferencia][homem])
            {
                // Se trocar de par, volta o homem de menor preferencia para o final da queue
                solteirosH.push(atual);
                casais[preferencia] = homem;
                break;
            }
        }
    }

    for (int i = 0; i < (int)listaPrefsH.size(); i++)
    {
        for (int j = 0; j < (int)listaPrefsH.size(); j++)
        {
            if (casais[j] == i)
            {
                printf("%i %i \n", casais[j] + 1, j + 1);
            }
        }
    }
}

void printaMatriz(MATINT mtrx)
{

    for (int i = 0; i < (int)mtrx.size(); i++)
    {
        for (int j = 0; j < (int)mtrx.size(); j++)
        {
            printf("%i ", mtrx[i][j]);
        }
        printf("\n");
    }
}

int main()
{

    // Leitura do num de casos
    int numCasosTeste;
    scanf("%i", &numCasosTeste);

    for (int i = 0; i < numCasosTeste; i++)
    {
        int numPessoas;
        scanf("%i", &numPessoas);

        MATINT preferenciasM = leListaPreferencias(numPessoas, 'W');
        MATINT preferenciasH = leListaPreferencias(numPessoas, 'M');

        formaCasais(preferenciasH, preferenciasM);
    }

    return 0;
}