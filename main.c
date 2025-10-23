#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30

void cityManagement();
void addCity(char cities[MAX_CITIES][50], int cityCount);
void renameCity(char cities[MAX_CITIES][50]);
void removeCity(char cities[MAX_CITIES][50], int cityCount);

char cities[MAX_CITIES][50];
int cityCount=0;

int main()
{
    cityManagement();
    return 0;
}

void cityManagement()
{
    int choice;
        printf("\n --- City Management ---\n");
        printf("1. Add City\n2. Rename City\n3. Remove City\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addCity(cities, cityCount);
                break;
            case 2:
                renameCity(cities);
                break;
            case 3:
                removeCity(cities,cityCount);
                break;
            default:
                printf("Invalid choice!\n");
        }

}

void addCity(char cities[MAX_CITIES][50], int cityCount)
{
    if(cityCount>=MAX_CITIES)
    {
        printf("Maximum city limit reached!\n");
        return;
    }

    int n;
    printf("Number of cities to add: (max=%d)",MAX_CITIES-cityCount);
    scanf("%d",&n);

    if(n>MAX_CITIES-cityCount){
        printf("Invalid number!\n");
        return;
    }
    for(int i=0; i<n; i++)
    {
        printf("Enter the city %d name: ",i+1);
        scanf("%s", cities[cityCount]);
        cityCount++;
    }

    printf("Cities added successfully!\n");
}

void renameCity(char cities[MAX_CITIES][50])
{
    int index;
    printf("Enter city number to rename: ");
    scanf("%d", &index);

    printf("Enter new name: ");
    scanf("%s", &cities[index-1]);

    printf("City renamed successfully");
}

void removeCity(char cities[MAX_CITIES][50], int cityCount)
{
    int index;
    printf("Enter city index remove");
    scanf("%d", &index);

    for(int i = index; i < cityCount - 1; i++)
    {
        strcpy(cities[i], cities[i+1]);
    }
    cityCount--;
    printf("City removed.\n");

}
