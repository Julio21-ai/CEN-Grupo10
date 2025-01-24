/*
Julio Baltazar Colín | A01794476
Programación de una solución paralela
Computo en la Nube TC4031.10
*/
#include "SolucionSumaArreglosParalela.h"
using namespace std;

int main()
{
	SetLocale();

	int arraySize = 100;
	int numArrays = 2;
	int numThreadsUsed = 0;

	CheckOpenMP();
	//crear los arreglos
	auto arrays = CreateArrays(numArrays, arraySize);
	//mostar los arreglos a sumar
	PrintArrays(arrays, 13);
	
	cout << "Sumando en paralelo..." << endl;
	// Vector para almacenar la suma
	vector<int> result =  SumVectors(arrays); 
	cout << "Resultado de la suma" << endl;
	
	//mostrar el resultado
	PrintVectorTable(result, 13);
}

vector<int> SumVectors(vector<vector<int>>& arrays)
{
	int numArrays = arrays.size();
	int arraySize = 0;
	if (numArrays > 1)
	{
		arraySize = arrays[0].size();
	}

	vector<int> result(arraySize);

#pragma omp parallel for
	for (int i = 0; i < arraySize; ++i)
	{
		int sum = 0;
		// Imprimir una sola vez por cada hilo para verificar los IDs
#pragma omp critical
		{
			cout
				<< "Hilo #" << omp_get_thread_num()
				<< " de " << omp_get_num_threads()
				<< " está trabajando.\n";
		}

		for (int j = 0; j < numArrays; ++j)
		{
#pragma omp atomic
			result[i] += arrays[j][i];
		}
	}

	return result;

}

void CheckOpenMP()
{
	cout << "Verificando la ejecución de las directivas OMP!\n";

# ifdef _OPENMP
	cout << "OMP disponible" << endl;
# else
	cout << "OMP no está disponible en esta configuración.\n";
# endif
}

vector<vector<int>> CreateArrays(int numArrays, int arraySize)
{
	vector<vector<int>> arrays(numArrays);

	for (int i = 0; i < numArrays; ++i)
	{
		arrays[i] = InitArray(arraySize);
	}

	return arrays;
}

vector<int> InitArray( int arraySize)
{
	vector<int > result(arraySize);

	// Configurar el generador de números aleatorios
	random_device rd;                          // Generador de semilla
	mt19937 gen(rd());                         // Generador Mersenne Twister
	uniform_int_distribution<> dist(1, 100);   // Distribución uniforme entre 1 y 100

	#pragma omp parallel for
	for (int i = 0; i < arraySize; ++i) 
	{
		mt19937 localgen(rd() + omp_get_thread_num());
		result[i] = dist(localgen);
	}

	return result;
}

void PrintArrays(vector<vector<int>>& vectors, int columns)
{
	//mostrar los arreglos
	for (size_t i = 0; i < vectors.size(); i++)
	{
		cout << "Arreglo " << i << endl;
		auto &vect = vectors.at(i);

		PrintVectorTable(vect, columns);
	}
}

void PrintVectorTable(const vector<int>& vec, int columns) 
{
	for (size_t i = 0; i < vec.size(); ++i) 
	{
		cout << setw(4) << vec[i]; // Espacio para alinear columnas
		if ((i + 1) % columns == 0 || i == vec.size() - 1)
		{
			cout << "\n"; // Salto de línea al final de cada fila
		}
	}
}

void SetLocale()
{
	//ajustar los codigos de pagina para la salida
	locale::global(locale("")); // Configura el sistema a UTF-8
	cout.imbue(locale()); // Aplica el locale a la salida estándar
}