#pragma once
/*
Julio Baltazar Colín | A01794476
Programación de una solución paralela
Computo en la Nube TC4031.10
*/

#ifndef id18AE01D7_FCD3_45B6_91CE252D0A9B58F0
#define id18AE01D7_FCD3_45B6_91CE252D0A9B58F0

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <omp.h>
#include <iomanip>
#include <locale>

void CheckOpenMP();
std::vector<std::vector<int>> CreateArrays(int numArrays, int arraySize);
std::vector<int> InitArray(int arraySize);
void PrintArrays(std::vector<std::vector<int>>& vectors, int columns);
void PrintVectorTable(const std::vector<int>& vec, int columns);
void SetLocale();
std::vector<int> SumVectors(std::vector<std::vector<int>>& vectors);
#endif 