#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <cmath>
#include <vector>

//Dengging

std::vector<float> Cost_Function(std::vector<std::vector<float>>, int, int);
void Data_Sort(std::vector<std::vector<float>>&, std::vector<float>&, int);

int main ()
{

    const int GenerationLimit=2500;
    const int PopulationSize=20;
    const int PopulationDimention=50;
    const float MutationProbability=0.04;
    const int NumberOfElites=2;
    std::cout.flush();
    std::vector<float> Minimum_Range;
    std::vector<float> Maximum_Range;
    std::vector<float> Minimum_Cost;

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
    Data_Sort(x, Cost, PopulationSize);
    Minimum_Cost.push_back(Cost[0]);
    std::cout<<"Generation 0 minimum cost: " << Minimum_Cost[0] << std::endl;

    std::vector<std::vector<float>> z;
    std::array<float, PopulationSize> mu;
    std::array<float, PopulationSize> lambda;
    float mu_sum =0;
    std::vector<std::vector<float>> EliteSolutions;
    std::vector<float> EliteCosts;
    for (int i=0; i < PopulationSize; i++)
    {
        mu[i]=(PopulationSize-i)/(PopulationSize+1);
        mu_sum=mu_sum+mu[i];
        lambda[i]=1-mu[i];
    }

    for (int crnt_generation=1; crnt_generation<GenerationLimit; crnt_generation++)
    {
        EliteSolutions.clear();
        EliteCosts.clear();
        for (int i =0; i< NumberOfElites;i++)
        {
            EliteSolutions.push_back(x[i]);
            EliteCosts.push_back(Cost[i]);
        }
        for (int k=0; k< PopulationSize; k++)
        {
            std::vector<float> z_temp;
            for (int j=0; j<PopulationDimention; j++)
            {
                std::uniform_real_distribution<> migration_rate (0,1);
                if (migration_rate(gen) < lambda[k])
                {
                    std::uniform_real_distribution<> randomnm(0,1);
                    float random_a = randomnm(gen) * mu_sum;
                    float select = mu[0];
                    int select_ind=0;
                    while((random_a > select) && (select_ind < PopulationSize))
                    {
                        select_ind++;
                        select = select + mu[select_ind];
                    }
                    z_temp.push_back(x[select_ind][j]);
                }else{
                    z_temp.push_back(x[k][j]);
                }
            }
            z.push_back(z_temp);
        }
        
        for (int k =0; k < PopulationSize; k++)
        {
            for (int p=0;p< PopulationDimention; p++)
            {
                std::uniform_real_distribution<> l(0,1);
                if (l(gen) < MutationProbability)
                {
                    float value2;
                    std::uniform_real_distribution<> m_temp(Minimum_Range[0], Maximum_Range[0]);
                    value2 = m_temp(gen);
                    z[k][p] = value2; 
                }
            }
        }
        x.clear();
        for (int i=0; i< PopulationSize; i++)
        {
            x.push_back(z[i]);
        }

        Cost=Cost_Function(x, PopulationSize, PopulationDimention);
        Data_Sort(x, Cost, PopulationSize);

        for (int l =0; l < NumberOfElites; l++)
        {
            x[PopulationSize-l+1] = EliteSolutions[l];
            Cost[PopulationSize-l+1] = EliteCosts[l];
        }

        Data_Sort(x, Cost, PopulationSize);
        Minimum_Range.push_back(Cost[0]);
        std::cout << "Generation " << crnt_generation << " min cost= "<< Cost[0] << std::endl;
    }
    return 0;
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

bool comparator ( const std::pair<float,int>& l, const std::pair<float,int>& r)
       { return l.first < r.first; }

void Data_Sort(std::vector<std::vector<float>> &matrix, std::vector<float> (&Cost), int Population_Size)
{
    std::vector<std::pair<float,int>> New_vector;
    std::vector<std::vector<float>> New_matrix;
    for (int i = 0; i < Population_Size; i++)
    {
        New_vector.push_back(std::make_pair(Cost[i], i));
        New_matrix.push_back(matrix[i]);
    }
    std::sort(New_vector.begin(), New_vector.end(), comparator);
    
    matrix.clear();
    Cost.clear();
    for (int i=0; i< Population_Size;i++)
    {
        matrix.push_back(New_matrix[New_vector[i].second]);
        Cost.push_back(New_vector[i].first);
    }
    

}
