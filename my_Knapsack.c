#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Include ctype.h for isalpha function

#define MAX_ITEMS 5
#define MAX_WEIGHT 20

int knapSack(int weights[], int values[], int selected_bool[]) {
    int dp[MAX_ITEMS + 1][MAX_WEIGHT + 1];
    int i, w;

    for (i = 0; i <= MAX_ITEMS; i++) {
        for (w = 0; w <= MAX_WEIGHT; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]]) > dp[i - 1][w] ? (values[i - 1] + dp[i - 1][w - weights[i - 1]]) : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int maxProfit = dp[MAX_ITEMS][MAX_WEIGHT];
    int currentWeight = MAX_WEIGHT;

    for (i = MAX_ITEMS; i > 0 && maxProfit > 0; i--) {
        if (maxProfit == dp[i - 1][currentWeight])
            continue;
        else {
            selected_bool[i - 1] = 1;
            maxProfit = maxProfit - values[i - 1];
            currentWeight = currentWeight - weights[i - 1];
        }
    }

    return dp[MAX_ITEMS][MAX_WEIGHT];
}

int main() {
    int weights[MAX_ITEMS];
    int values[MAX_ITEMS];
    int selected_bool[MAX_ITEMS] = {0};

    char item;
    int value, weight;
    int count = 0; // Counter to keep track of items entered

    while (count < MAX_ITEMS * 3) {
        scanf(" %c", &item); // Read the item character


        scanf("%d %d", &value, &weight); // Read the value and weight for the item

        // Convert the item character to an index (0 for 'a', 1 for 'b', and so on)
        int index = item - 'a';

        // Store the value and weight in the respective arrays
        values[index] = value;
        weights[index] = weight;

        count += 3; // Move to the next set of inputs
    }
    int maxProfit = knapSack(weights, values, selected_bool);

    printf("Maximum profit: %d\n", maxProfit);
    printf("Selected items:");
    for (int i = 0 ; i < MAX_ITEMS ; i++) {
        if (selected_bool[i] == 1) {
            printf(" %c", 'a' + i);
        }
    }
    printf("\n");

    return 0;
}
