#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 30


char cities[MAX_CITIES][50];

int main()
{

    return 0;
}

void cityManagement()
{
    int choice;
        printf("/n --- City Management ---\n");
        printf("1. Add City\n2. Rename City\n3. Remove City\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                printf("Invalid choice!\n");
        }

}

void addCity(char cities[MAX_CITIES], int cityCount)
{
    if(cityCount>=MAX_CITIES)
    {
        printf("Maximum city limit reached!\n");
        return;
    }

    int n;
    printf("Number of cities to add: (max=%d)",MAX_CITIES-cityCount);
    scanf("%d",&n);
    for(int i=0; i<n; n++)
    {
        printf("Enter the city name");
    }
}
