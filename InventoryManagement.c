#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product
{
    int id;
    char name[20];
    int price, quantity;
};

int main()
{
    int n;
    printf("Enter the number of products: ");
    scanf("%d", &n);

    struct product *ptr;
    ptr = (struct product *)malloc(n * sizeof(struct product));

    for (int i = 0; i < n; i++)
    {
        printf("Enter id: ");
        scanf("%d", &ptr[i].id);

        printf("Enter name: ");
        scanf("%s", ptr[i].name);

        printf("Enter price: ");
        scanf("%d", &ptr[i].price);

        printf("Enter quantity: ");
        scanf("%d", &ptr[i].quantity);
    }

    for (int i = 0; i < 2; i++)
    {
        printf("\nproduct %d\n", i + 1);

        printf("ID: %d\n", ptr[i].id);
        printf("Name: %s\n", ptr[i].name);
        printf("price: %d\n", ptr[i].price);
        printf("quantity: %d\n", ptr[i].quantity);
    }
    char line[128];

    for (;;)
    {
        printf("\nSearch by (i)id, (t)title or (q)quit: ");
        if (!fgets(line, sizeof line, stdin))
            break;
        if (line[0] == 'q' || line[0] == 'Q')
            break;

        if (line[0] == 'i' || line[0] == 'I')
        {
            printf("Enter product id: ");
            if (!fgets(line, sizeof line, stdin))
                break;
            size_t len = strlen(line);
            if (len && line[len - 1] == '\n')
                line[len - 1] = '\0';
            int id = atoi(line);
            int found = -1;
            for (int i = 0; i < n; ++i)
            {
                if (ptr[i].id == id)
                {
                    found = i;
                    break;
                }
            }
            if (found >= 0)
            {
                printf("Found: [%d]_ %s _ %d_%d\n", ptr[found].id, ptr[found].name, ptr[found].price, ptr[found].quantity);
            }
            else
            {
                printf("Product with id %d not found.\n", id);
            }
        }
        else if (line[0] == 't' || line[0] == 'T')
        {
            printf("Enter name (substring match, case-sensitive): ");
            if (!fgets(line, sizeof line, stdin))
                break;
            size_t len = strlen(line);
            if (len && line[len - 1] == '\n')
                line[len - 1] = '\0';

            int foundAny = 0;
            for (int i = 0; i < n; ++i)
            {
                if (strstr(ptr[i].name, line) != NULL)
                {
                    printf("Found: [%d] %s — %d\n", ptr[i].id, ptr[i].name, ptr[i].price);
                    foundAny = 1;
                }
            }
            if (!foundAny)
                printf("No product matched \"%s\".\n", line);
        }
        else
        {
            printf("Unknown option. Please enter i, t, or q.\n");
        }
    }
    int updateid;
    printf("\nProduct id to update: ");
    scanf("%d", &updateid);

    int found = -1;
    for (int i = 0; i < n; i++)
    {
        if (ptr[i].id == updateid)
        {
            found = i;
            break;
        }
    }

    if (found >= 0)
    {
        printf("Current Data: [%d] %s — %d — %d\n", ptr[found].id, ptr[found].name, ptr[found].price, ptr[found].quantity);

        printf("\nEnter new name: ");
        scanf("%s", ptr[found].name);

        printf("Enter new price: ");
        scanf("%d", &ptr[found].price);

        printf("Enter new quantity: ");
        scanf("%d", &ptr[found].quantity);

        printf("Product Updated Successfully!\n");
    }
    else
    {
        printf("Product not found.\n");
    }

    free(ptr);
    return 0;
}