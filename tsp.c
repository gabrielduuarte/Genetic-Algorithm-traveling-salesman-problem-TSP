/* Given a list of cities and the distances between each pair of cities, 
 * what is the shortest possible route that visits each city and returns 
 * to the origin city?
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CITIES 8
#define GENES CITIES+1
#define POP 10
#define GENERATIONS 200

void cities_distances(int dist[CITIES][CITIES]);
void init_pop(int pop[POP][GENES]);
void fitness(float fit[POP], int pop[POP][GENES], int distances[CITIES][CITIES]);
void sort_pop(int pop[POP][GENES], float fit[POP]);

int main(void)
{
    int distances[CITIES][CITIES]={};
    int pop[POP][GENES]={};
    float fit[POP] = {};
    int i, j;

    srand(time(NULL));

    cities_distances(distances);

    for(i=0; i<CITIES; i++)
        for(j=0; j<CITIES; j++)
            printf("dist[%d][%d]: %d\n", i, j, distances[i][j]);
    
    init_pop(pop);

    fitness(fit, pop, distances);

    sort_pop(pop, fit);
    
    for(i=0; i<POP; i++)
    {
        printf("pop[%d]: ", i);
        for(j=0; j<GENES; j++)
            printf("%d, ", pop[i][j]);
        printf("\n");
    }

    return 0;
}

void sort_pop(int pop[POP][GENES], float fit[POP])
{
    int i, j, a, aup[GENES];
    float aux;

    for(i=0; i<POP-1; i++)
        for(j=i+1; j<POP; j++)
            if(fit[j] > fit[i])
            {
                aux = fit[i];
                fit[i] = fit[j];
                fit[j] = aux;
                for(a=0; a<GENES; a++)
                {
                    aup[a] = pop[i][a];
                    pop[i][a] = pop[j][a];
                    pop[j][a] = aup[a];
                }
            }
}


void fitness(float fit[POP], int pop[POP][GENES], int distances[CITIES][CITIES])
{
    int i ,j, sum;

    for(i=0; i<POP; i++)
    {
        sum = 0;
        for(j=0; j<GENES-1; j++)
            sum += distances[pop[i][j]][pop[i][j+1]];
        printf("sum[%d]: %d\n", i, sum);
        fit[i] = 1 / (float) sum;
        printf("fit: %f\n", fit[i]);
    }
}

void init_pop(int pop[POP][GENES])
{
    int i, j, flag;

    for(i=0; i<POP; i++)
    {
        for(j=0; j<GENES-1; j++)
        {
            flag=0;
            pop[i][j] = rand()%8;
            while(flag < 8)
            {
                if(flag == j)
                    break;

                if(pop[i][flag] != pop[i][j])
                {
                    flag++;
                    continue;
                }
                pop[i][j] = rand()%8;
                flag = 0;
            }
        }
        pop[i][j] = pop[i][0];
    }

    for(i=0; i<POP; i++)
    {
        printf("pop[%d]: ", i);
        for(j=0; j<GENES; j++)
            printf("%d, ", pop[i][j]);
        printf("\n");
    }

}

void cities_distances(int dist[CITIES][CITIES])
{
    int i, j;

    for(i=0; i<CITIES; i++)
        for(j=0; j<CITIES; j++)
        {
            if(dist[j][i] != 0)
            {
                dist[i][j] = dist[j][i];
                continue;
            }

            dist[i][j] = rand()%100+1;
            if(i==j)
                dist[i][j] = 0;
        }
}
