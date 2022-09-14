#include <stdio.h>
#include <vector>

#define MTRX std::vector<std::vector<char>>

MTRX readMatrix(int matHeight, int matWidth);
void printMatrix(MTRX matrix);
std::vector<char> readWord();

int main()
{

    // recbeer input
    int matHeight, matWidth;
    scanf("%i %i \n", &matHeight, &matWidth);

    // montar matriz
    MTRX maze = readMatrix(matHeight, matWidth);
    printMatrix(maze);

    // percorrer com histórico
}

int runMatrixAux(MTRX maze, std::vector<char> word){}


int runMatrix(MTRX maze, std::vector<char> word)
{
    for (int i = 0; i < (int)maze.size(); i++)
    {
        for (int j = 0; j < (int)maze[i].size(); j++)
        {
            if(maze[i][j] == word[0]){

            }

        }
    }
}

void printMatrix(MTRX matrix)
{
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[i].size(); j++)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

std::vector<char> readWord()
{
    int wordSize;
    std::vector<char> word;
    for (int i = 0; i < wordSize; i++)
    {
        char tmp;
        scanf("%c", &tmp);
        word.push_back(tmp);
    }

    return word;
}

MTRX readMatrix(int matHeight, int matWidth)
{
    MTRX maze;
    for (int i = 0; i < matHeight; i++)
    {
        std::vector<char> vec;
        for (int j = 0; j < matWidth; j++)
        {
            char tmp;
            scanf("%c", &tmp);
            vec.push_back(tmp);
        }
        scanf("%*c"); // Engolindo \n
        maze.push_back(vec);
    }
    return maze;
}