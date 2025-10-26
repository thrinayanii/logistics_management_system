#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0

void cityManagement();
void addCity(char cities[MAX_CITIES][50], int *cityCount);
void renameCity(char cities[MAX_CITIES][50], int *cityCount);
void removeCity(char cities[MAX_CITIES][50], int *cityCount, int distance[MAX_CITIES][MAX_CITIES]);
void displayCities(char cities[MAX_CITIES][50], int *cityCount);

void distanceManagement();
void inputDistance(char cities[MAX_CITIES][50], int distance[MAX_CITIES][MAX_CITIES], int *cityCount);
void displayDistanceTable(char cities[MAX_CITIES][50], int distance[MAX_CITIES][MAX_CITIES], int *cityCount);

void deliveryRequest(float vCapacity[3], char vehicleTypes[3][10], float vRate[3]);

float calculateDeliveryCost(float D, float R, float weight);
float calculateDeliveryTime(float D, float S);
float calculateFuelUsed(float D, float E);
float calculateFuelCost(float fuelUsed);
float calculateProfit(float cost);
float calculateCustomerCharge(float totalCost, float profit);

void findMinDistance(int distance[MAX_CITIES][MAX_CITIES], int src, int dest, int *minDist, int path[4], int *pathLen, int cityCount);
void generateReports(int deliveryCount);

char cities[MAX_CITIES][50];
int distance[MAX_CITIES][MAX_CITIES];
int cityCount=0;

char vehicleTypes[3][10] = {"Van", "Truck", "Lorry"};
float vCapacity[3] = {1000, 5000, 10000};
float vRate[3] = {30.0, 40.0, 80.0};
float vSpeed[3] = {60.0, 50.0, 45.0};
float vFuelEfficiency[3] = {12.0, 6.0, 4.0};

int deliveryDistance[MAX_DELIVERIES];
float deliveryCharge[MAX_DELIVERIES];
float deliveryProfit[MAX_DELIVERIES];
float deliveryTime[MAX_DELIVERIES];
int deliveryCount = 0;

int main()
{
    int choice;
    do{
        printf("\n\n===== LOGISTICS MANAGEMENT SYSTEM ======\n\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. New Delivery Request\n");
        printf("4. Performance Reports\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
                case 1:
                    cityManagement();
                    break;
                case 2:
                    distanceManagement();
                    break;
                case 3:
                    deliveryRequest(vCapacity, vehicleTypes, vRate);
                    break;
                case 4:
                    generateReports(deliveryCount);
                    break;
                case 5:
                    printf("\nExiting the Logistics Management System...\n");
                    break;
                default:
                    printf("Invalid choice! Please try again.\n");
            }
        } while(choice != 5);

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
                removeCity(cities, &cityCount, distance);
                break;
            case 4:
                displayCities(cities, &cityCount);
                break;
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

    if(n>MAX_CITIES-*cityCount || n<=0){
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

void removeCity(char cities[MAX_CITIES][50], int *cityCount, int distance[MAX_CITIES][MAX_CITIES] )
{
    if(*cityCount == 0)
    {
        printf("No cities added yet to remove!\n");
        return;
    }

    displayCities(cities, cityCount);

    int index;
    printf("Enter city index remove: ");
    scanf("%d", &index);

    if(index <= 0 || index > *cityCount) {
        printf("Invalid index!\n");
        return;
    }

    for(int i = index-1; i < *cityCount - 1; i++)
    {
        strcpy(cities[i], cities[i+1]);
        for(int j = 0; j < *cityCount; j++)
        {
            distance[i][j] = distance[i + 1][j];
            distance[j][i] = distance[j][i + 1];
        }
    }
    (*cityCount)--;
    printf("City removed.\n");

}

void displayCities(char cities[MAX_CITIES][50], int *cityCount)
{
    if(*cityCount == 0) {
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
    do{
        printf("\n --- Distance Management ---\n");
        printf("1. Input or Edit Distance\n2. Display Distance Table\n3. Back\n");
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
    while (choice != 3);

}

void inputDistance(char cities[MAX_CITIES][50], int distance[MAX_CITIES][MAX_CITIES], int *cityCount)
{
    displayCities(cities, cityCount);
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

    printf("\nDistance Table (km)\n");

    printf("\n%-15s", " ");
    for (int i = 0; i < *cityCount; i++) {
        printf("%-12s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < *cityCount; i++) {
        printf("%-15s", cities[i]);
        for (int j = 0; j < *cityCount; j++) {
            if (i == j) {
                printf("%-12d", 0);
            } else if (distance[i][j] == 0) {
                printf("%-12s", "--");
            } else {
                printf("%-12d", distance[i][j]);
            }
        }
        printf("\n");
    }
}

//delivery
void deliveryRequest(float vCapacity[3], char vehicleTypes[3][10], float vRate[3])
{
    if(cityCount < 2) {
        printf("Need at least 2 cities to process delivery.\n");
        return;
    }

    displayCities(cities, &cityCount);

    int src, dest, vType;
    float weight;

    printf("Enter source city index: ");
    scanf("%d", &src);
    printf("Enter destination city index: ");
    scanf("%d", &dest);

    src--;
    dest--;

    if(src == dest) {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    printf("Enter weight (kg): ");
    scanf("%f", &weight);

    printf("\nVehicle Types:\n");
    for(int i = 0; i < 3; i++) {
        printf("%d. %s (Capacity: %d kg, Rate: %.2f LKR/km)\n",
               i + 1, vehicleTypes[i], vCapacity[i], vRate[i]);
    }

    printf("Select vehicle (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vType);

    vType--;

    if(weight >vCapacity[vType]) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }

    int minDist;
    int path[4];
    int pathLen;

    findMinDistance(distance,src,dest,&minDist, path,&pathLen, cityCount);

    if(minDist == 0 || minDist >= 99999) {
        printf("\nError: Invalid Routes!\n");
        return;
    }

    float baseCost = calculateDeliveryCost(minDist,vRate[vType],weight);
    float deliveryTimeCalc = calculateDeliveryTime(minDist,vSpeed[vType]);
    float fuelUsed = calculateFuelUsed(minDist, vFuelEfficiency[vType]);
    float fuelCost = calculateFuelCost(fuelUsed);
    float totalCost = baseCost + fuelCost;
    float profit = calculateProfit(baseCost);
    float customerCharge = calculateCustomerCharge(totalCost, profit);

    printf("\nDELIVERY COST ESTIMATION\n");
    printf("----------------------------------------------\n\n");
    printf("From: %s\n", cities[src]);
    printf("To: %s\n", cities[dest]);
    printf("Minimum Distance: %d km\n",minDist);
    printf("Vehicle: %s\n", vehicleTypes[vType]);
    printf("Weight: %.2f kg\n",weight);
    printf("-----------------------------------------------\n");
    printf("Base Cost:%d x %.0f x (1+%.0f/10000) = %.2f LKR\n",minDist,vRate[vType],weight, baseCost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n",fuelCost);
    printf("Operational Cost: %.2f LKR\n",totalCost);
    printf("Profit: %.2f LKR\n",profit);
    printf("Customer Charge: %.2f LKR\n",customerCharge);
    printf("Estimated Time: %.2f hours\n",deliveryTimeCalc);

    deliveryDistance[deliveryCount] = minDist;
    deliveryCharge[deliveryCount] = customerCharge;
    deliveryProfit[deliveryCount] = profit;
    deliveryTime[deliveryCount] = deliveryTimeCalc;
    deliveryCount++;
}

float calculateDeliveryCost(float D, float R, float weight)
{
    return D*R*(1.0+(weight/10000.0));
}

float calculateDeliveryTime(float D, float S)
{
    return D/S;
}

float calculateFuelUsed(float D, float E)
{
    return D/E;
}

float calculateFuelCost(float fuelUsed)
{
    return fuelUsed*FUEL_PRICE;
}

float calculateProfit(float cost)
{
    return cost*0.25;
}

float calculateCustomerCharge(float totalCost, float profit)
{
    return totalCost+profit;
}

void findMinDistance(int distance[MAX_CITIES][MAX_CITIES], int src, int dest, int *minDist, int path[4], int *pathLen, int cityCount)
{
    if(distance[src][dest]>0)
    {
        *minDist = distance[src][dest];
        path[0] = src;
        path [1] = dest;
        *pathLen = 2;
    }
    else
    {
        *minDist=99999;
        *pathLen=0;
    }

    for(int i=0; i< cityCount; i++)
    {
        if(i !=src && i!=dest)
        {
            int dist1=distance[src][i];
            int dist2=distance[i][dest];

            if(dist1>0 && dist2>0)
            {
                int totalDist = dist1+dist2;

                if(totalDist<*minDist)
                {
                    *minDist=totalDist;
                    path[0]=src;
                    path[1]=i;
                    path[2]=dest;
                    *pathLen=3;
                }
            }
        }
    }
}

void generateReports(int deliveryCount)
{
    if(deliveryCount == 0) {
        printf("No delivery data available.\n");
        printf("Please complete at least one delivery first.\n");
        return;
    }

    float totDistance = 0;
    float AvgTime = 0;
    float totRevenue = 0;
    float profit = 0;
    float longestRoute = 0;
    float shortestRoute = 99999;

    for(int i = 0; i < deliveryCount; i++)
    {
        totDistance += deliveryDistance[i];
        AvgTime += deliveryTime[i];
        totRevenue += deliveryCharge[i];
        profit += deliveryProfit[i];

        if(deliveryDistance[i] > longestRoute) {
            longestRoute = deliveryDistance[i];
        }
        if(deliveryDistance[i] < shortestRoute) {
            shortestRoute = deliveryDistance[i];
        }
    }

    printf("\nPerformance Report\n");
    printf("Total Deliveries Completed: %d\n", deliveryCount);
    printf("Total Distance Covered: %.2f km\n", totDistance);
    printf("Average Delivery Time: %.2f hours\n", AvgTime / deliveryCount);
    printf("Total Revenue: %.2f LKR\n", totRevenue);
    printf("Total Profit: %.2f LKR\n", profit);
    printf("Longest Route: %.2f km\n", longestRoute);
    printf("Shortest Route: %.2f km\n", shortestRoute);
}
