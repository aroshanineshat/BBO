#include <algorithm>
#include <iostream>
#include <random>
#include <cmath>

std::vector<float> Cost_Function(std::vector<std::vector<float>>, int, int);
void Data_Sort(std::vector<std::vector<float>>*, std::vector<float>*);

int main (int argc, char* argv[])
{

    int GenerationLimit=40;
    int PopulationSize=20;
    int PopulationDimention=50;
    float MutationProbability=0.04;
    int NumberOfElites=2;

    std::vector<float> Minimum_Range;
    std::vector<float> Maximum_Range;

    Minimum_Range.push_back(-2.048);
    Maximum_Range.push_back(+2.048);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::vector<float>> x;

    for (int i =0; i< PopulationSize; i++)
    {
        std::vector<float> temp_row;
        for (int j=0; j< PopulationDimention; j++)
        {
           float value;
           std::uniform_real_distribution<> disp(Minimum_Range[0], Maximum_Range[0]);
           value = disp(gen);
           temp_row.push_back(value);
        }
        x.push_back(temp_row);
    }

    std::vector<float> Cost=Cost_Function(x, PopulationSize, PopulationDimention);
    

}

std::vector<float> Cost_Function(std::vector<std::vector<float>> initial_m, int Population_Size, int Population_Dimention){

    std::vector<float> Cost_temp;

    for (int current_pop=0; current_pop<Population_Size; current_pop++){
        float Cost_eachpop=0;
        for (int current_dimention=0; current_dimention<Population_Dimention-1; current_dimention++)
        {
            float temp1 = initial_m[current_pop][current_dimention];
            float temp2 = initial_m[current_pop][current_dimention+1];
            Cost_eachpop=Cost_eachpop + 100*pow(temp2-pow(temp1,2),2) + pow(temp1-1,2);
        }
        Cost_temp.push_back(Cost_eachpop);
    }
    return Cost_temp;
}
