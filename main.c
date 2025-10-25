#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50

void cityManagement();
void addCity(char cities[MAX_CITIES][50], int *cityCount);
void renameCity(char cities[MAX_CITIES][50], int *cityCount);
void removeCity(char cities[MAX_CITIES][50], int *cityCount);
void displayCities(char cities[MAX_CITIES][50], int *cityCount);

void distanceManagement();
void inputDistance(char cities[MAX_CITIES][50], int distance[MAX_CITIES][MAX_CITIES], int *cityCount);
void displayDistanceTable(char cities[MAX_CITIES][50], int distance[MAX_CITIES][MAX_CITIES], int *cityCount);

char cities[MAX_CITIES][50];
int distance[MAX_CITIES][MAX_CITIES];
int cityCount=0;

char vehicleTypes[3][10] = {"Van", "Truck", "Lorry"};
float vCapacity[3] = {1000, 5000, 10000};
float vRate[3] = {30.0, 40.0, 80.0};
float vSpeed[3] = {60.0, 50.0, 45.0};
float vFuelEfficiency[3] = {12.0, 6.0, 4.0};

int main()
{
    cityManagement();
    return 0;
}

//City management menu and functions
void cityManagement()
{
    int choice;
    do{
        printf("\n --- City Management ---\n");
        printf("1. Add City\n2. Rename City\n3. Remove City\n4. Display Cities\n5. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);


        switch(choice) {
            case 1:
                addCity(cities, &cityCount);
                break;
            case 2:
                renameCity(cities, &cityCount);
                break;
            case 3:
                removeCity(cities, &cityCount);
                break;
            case 4:
                displayCities(cities, &cityCount);
            default:
                printf("Invalid choice!\n");
        }
    }
        while(choice!=5);

}

void addCity(char cities[MAX_CITIES][50], int *cityCount)
{
    if(*cityCount>=MAX_CITIES)
    {
        printf("Maximum city limit reached!\n");
        return;
    }

    int n;
    printf("Number of cities to add (max=%d) : ",MAX_CITIES-*cityCount);
    scanf("%d",&n);

    if(n>MAX_CITIES-*cityCount){
        printf("Invalid number!\n");
        return;
    }
    for(int i=0; i<n; i++)
    {
        printf("Enter the city %d name: ",i+1);
        scanf("%s", cities[*cityCount]);
        (*cityCount)++;
    }

    printf("Cities added successfully!\n");
}

void renameCity(char cities[MAX_CITIES][50], int *cityCount)
{
    if(*cityCount == 0)
    {
        printf("No cities added yet to rename!\n");
        return;
    }

    displayCities(cities, cityCount);

    int index;
    printf("Enter city number to rename: ");
    scanf("%d", &index);

    printf("Enter new name: ");
    scanf("%s", &cities[index-1]);

    printf("City renamed successfully");
}

void removeCity(char cities[MAX_CITIES][50], int *cityCount)
{
    if(*cityCount == 0)
    {
        printf("No cities added yet to remove!\n");
        return;
    }

    displayCities(cities, cityCount);

    int index;
    printf("Enter city index remove");
    scanf("%d", &index);

    if(index <= 0 || index > *cityCount) {
        printf("Invalid index!\n");
        return;
    }

    for(int i = index-1; i < *cityCount - 1; i++)
    {
        strcpy(cities[i], cities[i+1]);
    }
    (*cityCount)--;
    printf("City removed.\n");

}

void displayCities(char cities[MAX_CITIES][50], int *cityCount)
{
    if(cityCount == 0) {
        printf("No cities added yet!\n");
        return;
    }
    printf("\nList of Cities:\n");
    for(int i = 0; i < *cityCount; i++) {
        printf("%d. %s\n", i+1, cities[i]);
    }
}

//Distance management menu and functions
void distanceManagement()
{
    int choice;
        printf("\n --- Distance Management ---\n");
        printf("1. Input or Edit Distance\n2. Display Distance Table\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                inputDistance(cities,distance,&cityCount);
                break;
            case 2:
                displayDistanceTable(cities, distance, &cityCount);
                break;
            case 3:

                break;
            default:
                printf("Invalid choice!\n");
        }

}

void inputDistance(char cities[MAX_CITIES][50], int distance[MAX_CITIES][MAX_CITIES], int *cityCount)
{
     if(*cityCount < 2)
    {
        printf("No enough cities added yet!\n");
        return;
    }

    char from[50], to[50];
    int fromIndex = -1, toIndex = -1;

    printf("\nEnter From City name: ");
    scanf("%s", from);
    printf("Enter To City name: ");
    scanf("%s", to);

     for (int i = 0; i < *cityCount; i++)
    {
        if (strcmp(cities[i], from) == 0)
            fromIndex = i;
        if (strcmp(cities[i], to) == 0)
            toIndex = i;
    }
    if (fromIndex == -1 || toIndex == -1) {
        printf("Invalid city(s)!\n");
        return;
    }

    if (fromIndex == toIndex) {
        distance[fromIndex][toIndex] = 0;
        return;
    }

    int dist;
    printf("Enter the distance(km) between %s and %s: ", from, to);
    scanf("%d", &dist);

    distance[fromIndex][toIndex] = dist;
    distance[toIndex][fromIndex] = dist;

    printf("Distance between %s and %s is set to %d km.\n", from, to, dist);

}

void displayDistanceTable(char cities[MAX_CITIES][50], int distance[MAX_CITIES][MAX_CITIES], int *cityCount)
{
    if(*cityCount == 0) {
        printf("No cities available!\n");
        return;
    }

    printf("\n          Distance Table (km)\n");

    printf("%12s", " ");
    for (int i = 0; i < *cityCount; i++) {
        printf("%12s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < *cityCount; i++) {
        printf("%12s", cities[i]);
        for (int j = 0; j < *cityCount; j++) {
            if (i == j) {
                printf("%12d", 0);
            } else if (distance[i][j] == 0) {
                printf("%12s", "--");
            } else {
                printf("%12d", distance[i][j]);
            }
        }
        printf("\n");
    }
}

//delivery
void deliveryRequest(float vCapacity[3])
{
    int src, dest, vType;
    float weight;

    printf("Enter source city index: ");
    scanf("%d", &src);
    printf("Enter destination city index: ");
    scanf("%d", &dest);

    if(src == dest) {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    printf("Enter weight (kg): ");
    scanf("%f", &weight);
    printf("Select vehicle (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vType);

    if(weight > vCapacity[vType-1]) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }
}
