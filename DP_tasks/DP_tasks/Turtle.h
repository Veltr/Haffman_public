#ifndef TURTLE_H
#define TURTLE_H

// Формат входного файла:
// 1) размер поля (количество вершин) (size) - int
// 2) длина вертикальных путей - матрица (size, size - 1)
// 3) длина горизонтальных путей - матрица (size, size - 1)
// В пунктах 2-3 точкой (0, 0) считается точка старта черепашки

#include <iostream>
#include <fstream>

size_t goTurtle(const std::string& inPath){
    std::ifstream file; file.open(inPath);
    if(!file){ std::cerr << "Can't open file\n"; return 0; }
    int size; file >> size;

    size_t** vert = new size_t*[size];
    for(int i = 0; i < size; i++){
        vert[i] = new size_t[size - 1];
        for(int ii = 0, t; ii < size - 1; ii++){
            file >> t;
            vert[i][ii] = t;
        }
    }

    size_t** hor = new size_t*[size];
    for(int i = 0; i < size; i++){
        hor[i] = new size_t[size - 1];
        for(int ii = 0, t; ii < size - 1; ii++){
            file >> t;
            hor[i][ii] = t;
        }
    }

    size_t** dp = new size_t*[size];
    dp[0] = new size_t[size]; dp[0][0] = 0;
    for(int i = 1; i < size; i++)
        dp[0][i] = dp[0][i - 1] + hor[0][i - 1];


    for(int i = 1; i < size; i++){
        dp[i] = new size_t[size]; dp[i][0] = dp[i - 1][0] + vert[0][i - 1];
        for(int ii = 1; ii < size; ii++)
            dp[i][ii] = std::min(dp[i][ii - 1] + hor[i][ii - 1], dp[i - 1][ii] + vert[ii][i - 1]);
    }

    for(int i = 0; i < size; i++){
        for(int ii = 0; ii < size; ii++)
            std::cout << dp[i][ii] << ' ';
        std::cout << '\n';
    }
    return dp[size - 1][size - 1];
}

#endif // TURTLE_H
