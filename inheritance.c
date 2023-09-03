#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_GENERATIONS 3
#define NUM_ALLELES 3

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

char random_allele()
{
    char alleles[NUM_ALLELES] = {'A', 'B', 'O'};
    int index = rand() % NUM_ALLELES;
    return alleles[index];
}

person *create_family(int generations)
{
    person *p = malloc(sizeof(person));

    if (generations > 1)
    {
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        p->parents[0] = parent0;
        p->parents[1] = parent1;

        p->alleles[0] = parent0->alleles[rand() % 2];
        p->alleles[1] = parent1->alleles[rand() % 2];
    }
    else
    {
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    return p;
}

void print_family(person *p, int depth)
{
    if (p == NULL)
    {
        return;
    }

    for (int i = 0; i < depth; i++)
    {
        printf("  ");
    }

    printf("Person (Generation %d): blood type %c%c\n", depth, p->alleles[0], p->alleles[1]);

    print_family(p->parents[0], depth + 1);
    print_family(p->parents[1], depth + 1);
}

void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }

    free_family(p->parents[0]);
    free_family(p->parents[1]);

    free(p);
}

int main(void)
{
    srand(time(NULL));

    person *family = create_family(MAX_GENERATIONS);
    print_family(family, 0);
    free_family(family);

    return 0;
}
