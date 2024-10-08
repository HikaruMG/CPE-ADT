#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int price;
    int weight;
    double value;
    int index;
} dish_t ;

int bs(dish_t **dish, int *g_dish, int l, int h, int idx ){
    while(l<h){
        int m = l + (h-l)/2;
        if(dish[g_dish[m]]->value > dish[idx]->value){
            h = m;
        }
        else{
            l = m+1;
        }
    }
    return l;
}

void cal_value(dish_t **dish,int n_dish){
    double tmp;
    for(int i = 0; i < n_dish; i++){
        tmp = (double)dish[i]->weight / dish[i]->price;
        
        dish[i] -> value = tmp;
    }
}

dish_t **choose_dish(dish_t **dish, int *g_dish, int *prev, int m_length){
    dish_t **selected_dish = (dish_t **)malloc(m_length * sizeof(dish_t *));
    int last_dish_idx = g_dish[m_length];
    for(int j = m_length -1; j >= 0; j--){
        selected_dish[j] = dish[last_dish_idx];
        last_dish_idx = prev[last_dish_idx];
    }
    return selected_dish;
}

void best_dish(int *g_dish, int *prev, int n_length, int idx){
    prev[idx] = g_dish[n_length-1];
    g_dish[n_length] = idx;
}



void show(dish_t **selected_dish, int m_length, dish_t **dish, int n_dish){
    char *c = (char *)malloc((n_dish+1)* sizeof(char));
    for (int i = 0; i < n_dish; i++){
        c[i] = '0';
    }
    int sum = 0;
    for(int i = 0; i < m_length; i++){
        c[selected_dish[i]->index] = '1';
        sum += selected_dish[i]->price;
    }
    for(int i = 0; i < n_dish; i++){
        putchar(c[i]);
        putchar(' ');
    }
    putchar('\n');
    printf("%d\n",sum);
    free(c);
}

void LIS(dish_t **dish, const int n_dish){
    int *prev = (int *)malloc(n_dish*sizeof(int));
    int *g_dish = (int *)malloc((n_dish+1)*sizeof(int));
    g_dish[0] = -1;
    int m_length = 0;
    for(int i = 0; i < n_dish; i++){
        int n_length = bs(dish, g_dish,1,m_length+1,i);
        best_dish(g_dish,prev,n_length,i);
        if(n_length>m_length){
            m_length = n_length;
        }
    }

    dish_t **selected_dish = choose_dish(dish,g_dish,prev,m_length);
    show(selected_dish,m_length,dish,n_dish);
}

int main(){
    int n_dish;
    scanf("%d",&n_dish);

    dish_t **arr = (dish_t **)malloc(n_dish*sizeof(dish_t *));
    for(int i = 0; i < n_dish; i++){
        arr[i] = (dish_t *)malloc(sizeof(dish_t));
        scanf("%d %d", &arr[i]->price, &arr[i]->weight);
        arr[i]->index = i;
    }
    cal_value(arr,n_dish);
    LIS(arr,n_dish);
    return 0;
}