#include <stdio.h>
#include <stdlib.h>

typedef struct plate
{
    int cost;
    int weight;
    int order;
    double ratio;
} plate_t;

// Function to calculate ratios for the plates
void calculate_ratios(plate_t **plates, int num_plates)
{
    for (int i = 0; i < num_plates; i++)
    {
        plates[i]->ratio = (double)plates[i]->weight / plates[i]->cost;
    }
}

// Function to perform binary search to find the position of a plate in the best_plate array
int binary_search(plate_t **plates, int *best_plate, int low, int high, int current_index)
{
    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (plates[best_plate[mid]]->ratio > plates[current_index]->ratio)
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }
    return low;
}

// Function to update the best_plate and prev_plate arrays
void update_best_plates(int *best_plate, int *prev_plate, int new_length, int current_index)
{
    prev_plate[current_index] = best_plate[new_length - 1];
    best_plate[new_length] = current_index;
}

// Function to build the selected plates based on the optimal indices
plate_t **build_selected_plates(plate_t **plates, int *best_plate, int *prev_plate, int max_length)
{
    plate_t **selected_plates = (plate_t **)malloc(max_length * sizeof(plate_t *));
    int last_plate_index = best_plate[max_length];

    for (int j = max_length - 1; j >= 0; j--)
    {
        selected_plates[j] = plates[last_plate_index];
        last_plate_index = prev_plate[last_plate_index];
    }
    return selected_plates;
}

// Function to output the choices and calculate total cost
void printer(plate_t **selected_plates, int max_length, plate_t **plates, int num_plates)
{
    char *choices = (char *)malloc((num_plates + 1) * sizeof(char));
    for (int i = 0; i < num_plates; i++)
    {
        choices[i] = '0'; // Initialize choices to '0'
    }

    int total_cost = 0;
    for (int i = 0; i < max_length; i++)
    {
        choices[selected_plates[i]->order] = '1';
        total_cost += selected_plates[i]->cost;
    }

    for (int i = 0; i < num_plates; i++)
    {
        putchar(choices[i]);
        putchar(' ');
    }
    putchar('\n');
    printf("%d\n", total_cost);

    free(choices);
}

// Function to find the optimal plates based on ratios
void find_optimal_plates(plate_t **plates, const int num_plates)
{
    int *prev_plate = (int *)malloc(num_plates * sizeof(int));
    int *best_plate = (int *)malloc((num_plates + 1) * sizeof(int));
    best_plate[0] = -1;

    int max_length = 0;

    for (int i = 0; i < num_plates; i++)
    {
        int new_length = binary_search(plates, best_plate, 1, max_length + 1, i);
        update_best_plates(best_plate, prev_plate, new_length, i);

        if (new_length > max_length)
        {
            max_length = new_length;
        }
    }

    // Build selected plates and output results
    plate_t **selected_plates = build_selected_plates(plates, best_plate, prev_plate, max_length);
    printer(selected_plates, max_length, plates, num_plates);
}

int main()
{
    int num_plates;
    scanf("%d", &num_plates);

    plate_t **plates_array = (plate_t **)malloc(num_plates * sizeof(plate_t *));
    for (int i = 0; i < num_plates; i++)
    {
        plates_array[i] = (plate_t *)malloc(sizeof(plate_t));
        scanf("%d %d", &plates_array[i]->cost, &plates_array[i]->weight);
        plates_array[i]->order = i;
    }

    calculate_ratios(plates_array, num_plates);
    find_optimal_plates(plates_array, num_plates);
    return 0;
}