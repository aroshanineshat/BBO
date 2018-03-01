#include <algorithm>
#include <iostream>
#include <random>

int main (int argc, char* argv[])
{

    int GenerationLimit=40;
    int PopulationSize=20;
    int PopulationDimention=10;
    float MutationProbability=0.04;
    int NumberOfElites=2;

    std::vector<float> Minimum_Range;
    std::vector<float> Maximum_Range;

    Minimum_Range.push_back(-2.048);
    Maximum_Range.push_back(+2.048);

    std::random_device rd;
    std::mt19937 gen(rd());
//std::uniform_int_distribution<> dis(1,6);

    std::vector<std::vector<float>> x;

    for (int i =0; i< PopulationSize; i++)
    {
        std::vector<float> temp_row;
        for (int j=0; j< PopulationDimention; j++)
        {
            float value;

        }
    }
    
}
