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

void cities_distances(int dist[CITIES][CITIES]);
void init_pop(int pop[POP][GENES]);

int main(void)
{
    int distances[CITIES][CITIES]={};
    int pop[POP][GENES]={};
    int fit[POP] = {};
    int i, j;

    srand(time(NULL));

    cities_distances(distances);

    for(i=0; i<CITIES; i++)
        for(j=0; j<CITIES; j++)
            printf("dist[%d][%d]: %d\n", i, j, distances[i][j]);
    
    init_pop(pop);

    fit = fitness(pop);

    return 0;
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
