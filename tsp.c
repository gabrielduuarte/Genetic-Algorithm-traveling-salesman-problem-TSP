/* Given a list of cities and the distances between each pair of cities, 
 * what is the shortest possible route that visits each city and returns 
 * to the origin city?
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CITIES 30
#define GENES CITIES+1
#define POP 10
#define GENERATIONS 300

void cities_distances(int dist[CITIES][CITIES]);
void init_pop(int pop[POP][GENES]);
void fitness(float fit[POP], int pop[POP][GENES], int distances[CITIES][CITIES]);
void sort_pop(int pop[POP][GENES], float fit[POP]);
int pool(void);
void crossover(int p1[], int p2[], int filho[]);
void mutacao(int filhos[POP][GENES]);
int contem(int v[GENES], int ng);
int sameIndex(int v[GENES], int ng);

int main(void)
{
    int distances[CITIES][CITIES]={};
    int pop[POP][GENES]={};
    int filhos[POP][GENES]={};
    float fit[POP] = {};
    float best[GENERATIONS] = {};
    int i, j, f, c1, c2, g;

    srand(time(NULL));

    cities_distances(distances);
    
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
    best[0] = fit[0];


    for(g=1; g<GENERATIONS; g++)
    {
        f=0;
        while(f < POP)
        {
            c1 = pool();
            while((c2 = pool()) == c1);
            crossover(pop[c1], pop[c2], filhos[f]);
            f++;
            crossover(pop[c2], pop[c1], filhos[f]);
            f++;
        }

        mutacao(filhos);
        fitness(fit, filhos, distances);
        sort_pop(filhos, fit);

        for(i=0; i<POP; i++)
            for(j=0; j<GENES; j++)
            {
                pop[i][j] = filhos[i][j];
                filhos[i][j] = 0;
            }

        
        printf("Geracao: %d---------\n", g);
        for(i=0; i<POP; i++)
        {
            printf("pop[%d]: ", i);
            for(j=0; j<GENES; j++)
                printf("%d, ", pop[i][j]);
            printf("\n");
        }
        best[g] = fit[0];
    }

    for(g=0; g<GENERATIONS; g++)
        printf("best[%d]: %f\n", g, best[g]);
    
    /* for(i=0; i<CITIES; i++) */
    /*     for(j=0; j<CITIES; j++) */
    /*         printf("dist[%d][%d]: %d\n", i, j, distances[i][j]); */

    printf("Best Route: ");
    for(i=0; i<GENES; i++)
        printf("%d, ", pop[0][i]);
    printf("\n");
    
    return 0;
}

int sameIndex(int v[GENES], int ng)
{
    int i;
    
    for(i=0; i<GENES; i++)
        if(v[i] == ng)
            return i;

    return 0;
}

void mutacao(int filhos[POP][GENES])
{
    int f, sorteio, go, ng, co, swp;

    for(f=0; f<POP; f++)
    {
        sorteio = rand()%100+1;
        if(sorteio >= 1 && sorteio <=3)
        {
            go = rand()%CITIES;
            ng = rand()%CITIES;
            /* swp = sameIndex(filhos[f], ng); */
            swp = sameIndex(filhos[f], ng);
            /* while(contem(filhos[f], ng)) */
            /*     ng = rand()%CITIES; */
            /* while((ng=rand()%GENES) == filhos[f][go]); */
            co = filhos[f][go];
            filhos[f][go] = ng;
            filhos[f][swp] = co;
        }
    }

}

int contem(int v[GENES], int ng)
{
    int i;

    for(i=0; i<GENES; i++)
    {
        if(v[i] == ng)
            return 1;
    }

    return 0;
}

void crossover(int p1[], int p2[], int filho[])
{
    int i, n, f=CITIES/2;

    for(i=0; i<GENES; i++)
        filho[i] = -1;

    for(i=0; i<CITIES/2; i++)
        filho[i] = p1[i];

    for(i=0; i<CITIES; i++)
    {
        n = p2[i];
        if(contem(filho, n))
            continue;
        filho[f] = n;
        f++;
    }

    filho[i] = filho[0];

}

int pool(void)
{
    float r = 0.6;
    float rol[POP];
    int s, i;

    for(i=0; i<POP; i++)
    {
        rol[i] = r * 100;
        r -= r*0.6;
    }
    
    s = rand()%100+1;
    for(i=0; i<POP; i++)
        if(s >= rol[i])
            return i;

    return -1;
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
        fit[i] = 1 / (float) sum;
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
            pop[i][j] = rand()%CITIES;
            while(flag < CITIES)
            {
                if(flag == j)
                    break;

                if(pop[i][flag] != pop[i][j])
                {
                    flag++;
                    continue;
                }
                pop[i][j] = rand()%CITIES;
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
