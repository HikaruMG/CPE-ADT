#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int price;
    int weight;
    double value;
    int idx;
} dish_t;

// Function to calculate values for the dish
void cal_value(dish_t **dish, int n_dish)
{
    for(int i = 0; i < n_dish; i++){
        double tmp;
        tmp = (double)dish[i]->weight / dish[i]->price;
        dish[i] -> value = tmp;
    }
}
// Function to perform binary search to find the position of a plate in the g_dish array
int bs(dish_t **dish, int *g_dish, int l, int h, int idx)
{
    while(l<h){
        int m = l + (h-l)/2;
        if (dish[g_dish[m]]->value > dish[idx]->value){
            h = m;
        }
        else{
            l = m + 1;
        }
    }
    return l;
}

// Function to update the g_dish and prev arrays
void best_dish(int *g_dish, int *prev, int n_length, int idx){
    prev[idx] = g_dish[n_length-1];
    g_dish[n_length] = idx;
}

// Function to build the selected dish based on the optimal indices
dish_t **choose_dish(dish_t **dish, int *g_dish, int *prev, int m_length){
    dish_t **selected_dish = (dish_t **)malloc(m_length * sizeof(dish_t *));
    int last_dish_idx = g_dish[m_length];
    for(int j = m_length -1; j >= 0; j--){
        selected_dish[j] = dish[last_dish_idx];
        last_dish_idx = prev[last_dish_idx];
    }
    return selected_dish;
}

// Function to output the c and calculate total price
void show(dish_t **selected_dish, int m_length, dish_t **dish, int n_dish)
{
    char *c = (char *)malloc((n_dish+1)* sizeof(char));
    for (int i = 0; i < n_dish; i++){
        c[i] = '0';
    }
    int sum = 0;
    for(int i = 0; i < m_length; i++){
        c[selected_dish[i]->idx] = '1';
        sum += selected_dish[i]->price;
    }

    for(int i = 0; i < n_dish; i++){
        putchar(c[i]);
        putchar(' ');
    }
    putchar('\n');
    printf("%d\n", sum);

    free(c);
}

// Function to find the optimal dish based on values
void find_optimal_dish(dish_t **dish, const int n_dish)
{
    int *prev = (int *)malloc(n_dish * sizeof(int));
    int *g_dish = (int *)malloc((n_dish + 1) * sizeof(int));
    g_dish[0] = -1;

    int m_length = 0;

    for (int i = 0; i < n_dish; i++)
    {
        int n_length = bs(dish, g_dish, 1, m_length + 1, i);
        best_dish(g_dish, prev, n_length, i);

        if (n_length > m_length)
        {
            m_length = n_length;
        }
    }

    // Build selected dish and output results
    dish_t **selected_dish = choose_dish(dish, g_dish, prev, m_length);
    show(selected_dish, m_length, dish, n_dish);
}

int main()
{
    int n_dish;
    scanf("%d", &n_dish);

    dish_t **dish_array = (dish_t **)malloc(n_dish * sizeof(dish_t *));
    for (int i = 0; i < n_dish; i++)
    {
        dish_array[i] = (dish_t *)malloc(sizeof(dish_t));
        scanf("%d %d", &dish_array[i]->price, &dish_array[i]->weight);
        dish_array[i]->idx = i;
    }

    cal_value(dish_array, n_dish);
    find_optimal_dish(dish_array, n_dish);
    return 0;
}