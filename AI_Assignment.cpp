/* ................................................... 8 QUEENS...................................................................*/

#include<bits/stdc++.h>
using namespace std;

typedef struct     // This structure stores arrangement of queens and the cost (fitness) of corresponding arrangement.
{
    string arrangement;
    int cost;
} individual;

typedef vector<individual*> population_type;    // This vector stores the arrangement and fitness value of population.

population_type population;
int chessBoardSize;
int initialPopulationCount = 4;      // Initially we have 4 in the population.
individual * sampleArrangement;

int fitnessValue(string arrangement)       // This function calculates the cost/fitness value of the arrangement.
{
    int fitness=(chessBoardSize*(chessBoardSize-1))/2;          // for a 8*8 chessboard max fitness value possible is 28

    /*......................removing pairs that lie on the same row and on the same diagonal....................*/

    for(int i=0; i<chessBoardSize; i++)
    {
        for(int j=i+1; j<chessBoardSize; j++)
        {
            if((arrangement[i] == arrangement[j]) ||  (i-arrangement[i] == j-arrangement[j]) || (i+arrangement[i] == j+arrangement[j]))
            {
                fitness--;
            }
        }
    }

    return fitness;
}

individual* createNode()     // This function creates a new node for a new entry in the population
{
    individual *newNode  = new individual;
    return newNode;
}

void generatePopulation()              // This function inserts new entry in the population list.
{
    individual *temp;

    //adds entries to population list
    cout<<"Initially the first 4 members in the population list are : "<<endl;
    cout<<endl;
    cout<<"ARRANGEMENT : "<<sampleArrangement->arrangement<<" "<<"FITNESS VALUE : "<<fitnessValue(sampleArrangement->arrangement)<<endl;
    for(int i=0; i<4; i++)
    {
        random_shuffle( sampleArrangement->arrangement.begin(), sampleArrangement->arrangement.end());   //  we randomly shuffle the given arrangement to get 4 different entries in the population.
        temp   = createNode();
        temp->arrangement = sampleArrangement->arrangement;
        temp->cost = fitnessValue(sampleArrangement->arrangement);
        cout<<"ARRANGEMENT : "<<temp->arrangement<<" "<<"FITNESS VALUE : "<<fitnessValue(sampleArrangement->arrangement)<<endl;

        population.push_back(temp);     // here push back the node in the population vector.
    }
    cout<<endl;
    cout<<endl;

}

individual* reproduce(individual *x, individual *y)   // This function is used to reproduce a new child from two parent arrangements.
{
    individual *child = createNode();
    int n = chessBoardSize;
    int c = rand()%n;
    child->arrangement = (x->arrangement).substr(0,c) + (y->arrangement).substr(c,n-c+1);   // Random arrangement generation
    child->cost = fitnessValue(child->arrangement);    // calculating fitness value associated with it
    return child;
}

individual* mutate(individual *child)     // This function is used for mutating the child
{
    int randomQueen = rand()%(chessBoardSize)+1;
    int randomPosition= rand()%(chessBoardSize)+1;
    child->arrangement[randomQueen] = randomPosition+48;
    child->cost=fitnessValue(child->arrangement);
    return child;
}

int randomSelection()    // This function is used to randomly select two parents from the population list
{
    int randomPos = rand()%population.size() %2;
    return randomPos;
}

bool isFit(individual *test)   // This function checks if the child is fit or not
{
    if(fitnessValue(test->arrangement)==((chessBoardSize*(chessBoardSize-1))/2))
        return true;
    return false;
}

bool comp(individual *a, individual*b)     // This function compares the fitness values for sorting the population list according to fitness values.
{
    return(a->cost > b->cost);
}

individual* GA()      // This is the genetic algorithm
{
    int randomNum1,randomNum2;
    individual *individualX,*individualY,*child;
    bool found =0;
    while(!found)
    {
        population_type new_population;
        for(unsigned int i=0; i<population.size(); i++)
        {
            sort(population.begin(),population.end(),comp);

            randomNum1 = randomSelection();
            individualX = population[randomNum1];

            cout<<"Parent 1: "<<individualX->arrangement<<" "<<"Fitness: "<<individualX->cost<<endl;
            randomNum2 =randomSelection();
            individualY = population[randomNum2];
            cout<<"Parent 2: "<<individualY->arrangement<<" "<<"Fitness: "<<individualY->cost<<endl;

            child = reproduce(individualX,individualY);

            if(rand()%2==0)     //random probability
                child = mutate(child);
            cout<<"Child after Crossware and Mutation: "<<child->arrangement<<" "<<"Fitness: "<<child->cost<<endl;

            if(isFit(child))
            {
                found=1;
                return child;
            }
            new_population.push_back(child);
        }
        population = new_population;
    }
    return child;
}

void initialize()
{
    srand(time(0));
    string s;
    cin>>s;
    sampleArrangement= createNode();
    sampleArrangement->arrangement=s;
    sampleArrangement->cost=fitnessValue(s);
    population.push_back(sampleArrangement);
    chessBoardSize=8;
}

int main()
{
    initialize();
    map<string,int> solutionsFound;
    int maxSolutions = 92,numFound=0;       //already known that 92 solutions exist for 8 Queen Problem!
    cout<<"*Returns the column number corresponding to the row at the index*"<<endl<<endl;
    // while(numFound!=maxSolutions)
    // {
        generatePopulation();
        individual *solution = GA();
        if(!solutionsFound[solution->arrangement])
        {
            solutionsFound[solution->arrangement]=1;
            cout<<"Possible Solution #"<<(++numFound)<<":\t"<<solution->arrangement<<endl;
             string s=solution->arrangement;
             for(int i=0;i<s.length();i++)
             {
                     for(int j=0;j<s.length();j++)
                     {
                             if(s[j]==i+49)
                             {
                                     cout<<1<<" ";
                             }
                                     else
                                             cout<<0<<" ";

                     }
                     cout<<endl;

             }

        }

   // }

    return 0;
}
