#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct Stock{
    int product_id;
    char product_name[50];
    int quantity;
    float price;
    char date[12];
}stock_item;

FILE *file_pointer;

void add_item(){

    char current_date[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(current_date, "%02d/%02d/%d", tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900);
    strcpy(stock_item.date, current_date);

    file_pointer = fopen("product.txt", "ab");
    printf("Enter product ID: ");
    scanf("%d", &stock_item.product_id);
    printf("Enter the product name: ");
    fflush(stdin);
    scanf("%s", &stock_item.product_name);
    printf("Enter product quantity: ");
    fflush(stdin);
    scanf("%d", &stock_item.quantity);
    printf("Enter the product price: ");
    fflush(stdin);
    scanf("%f", &stock_item.price);

    printf("\nProduct added successfully...\n");
    fwrite(&stock_item, sizeof(stock_item), 1, file_pointer);
    fclose(file_pointer);
}

void display_items(){
    system("cls");
    printf("<=== Product List ===>\n\n");
    printf("%-10s %-30s %-30s %-20s %s\n", "ID", "Product Name",
           "Quantity", "Price", "Date");
    printf("\n---------------------------------------------------------------------------------------\n");
    file_pointer = fopen("product.txt", "rb");
    while(fread(&stock_item, sizeof(stock_item), 1, file_pointer) == 1){
        printf("%-10d %-30s %-30d %-20f %s\n", stock_item.product_id, stock_item.product_name,
               stock_item.quantity, stock_item.price, stock_item.date);
    }
    fclose(file_pointer);
}

void update_inventory(){
    int id, found;
    printf("<== Update products ==>\n\n");
    printf("Enter the product ID to update: ");
    scanf("%d", &id);

    FILE *temp_file_pointer;
    file_pointer = fopen("product.txt", "rb+");
    while(fread(&stock_item, sizeof(stock_item), 1, file_pointer) == 1){
        if(id == stock_item.product_id){
            found = 1;
            printf("Select the operation to be performed\n");
            printf("1. Update the product name\n");
            printf("2. Update the quantity\n");
            printf("3. Update the product price\n");

            int choice;
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch(choice){
                case 1: printf("Enter the new product name: ");
                        fflush(stdin);
                        scanf("%s", &stock_item.product_name);
                        break;
                case 2: printf("Enter new product quantity: ");
                        fflush(stdin);
                        scanf("%d", &stock_item.quantity);
                        break;
                case 3: printf("Enter new product price: ");
                        fflush(stdin);
                        scanf("%f", &stock_item.price);
                        break;
                default: printf("Invalid input\n");
            }

            fseek(file_pointer, -sizeof(stock_item), 1);
            fwrite(&stock_item, sizeof(stock_item), 1, file_pointer);
            fclose(file_pointer);
            break;
        }
    }

    if(found == 1){
        printf("\nProduct updated successfully...\n");
    }
    else{
        printf("\nProduct not found\n");
    }
}

void delete_item(int id){
    int found = 0;

    FILE *temp_file_pointer;
    file_pointer = fopen("product.txt", "rb");
    temp_file_pointer = fopen("temp.txt", "wb");
    while(fread(&stock_item, sizeof(stock_item), 1, file_pointer) == 1){
        if(id == stock_item.product_id){
            found = 1;
        }
        else{
            fwrite(&stock_item, sizeof(stock_item), 1, temp_file_pointer);
        }
    }

    fclose(file_pointer);
    fclose(temp_file_pointer);
    remove("product.txt");
    rename("temp.txt", "product.txt");
}

void delete_item_prompt(){
    int id, found = 0;
    printf("<== Delete Products ==>\n\n");

    printf("Enter the product ID to delete: ");
    scanf("%d", &id);

    file_pointer = fopen("product.txt", "rb");
    while(fread(&stock_item, sizeof(stock_item), 1, file_pointer) == 1){
        if(id == stock_item.product_id){
            found = 1;
            break;
        }
    }

    if(found == 1){
        printf("Product deleted successfully...\n");
        delete_item(id);
    }
    else{
        printf("\nProduct not found\n");
    }
}

void admin_interface(){

    int choice;
    printf("\n");
    printf("1. Add product\n");
    printf("2. Update inventory\n");
    printf("3. Delete product\n");
    printf("4. Display products\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){
        case 1: add_item();
                break;
        case 2: update_inventory();
                break;
        case 3: delete_item_prompt();
                break;
        case 4: display_items();
                break;
        default: printf("Invalid input\n");
    }
}

void buy_item(){
    int id, found = 0, quantity;
    printf("<== Buy products ==>\n\n");
    printf("Enter the product ID to buy: ");
    scanf("%d", &id);
    printf("Enter the quantity of the product: ");
    scanf("%d", &quantity);

    FILE *temp_file_pointer;
    float price;
    file_pointer = fopen("product.txt", "rb+");
    while(fread(&stock_item, sizeof(stock_item), 1, file_pointer) == 1){
        if(id == stock_item.product_id){
            found = 1;
            price = stock_item.price;
            if(stock_item.quantity - quantity < 0){
                printf("Insufficient quantity available\n");
                return;
            }
            else if(stock_item.quantity - quantity >= 0){
                stock_item.quantity = stock_item.quantity - quantity;
                fseek(file_pointer, -sizeof(stock_item), 1);
                fwrite(&stock_item, sizeof(stock_item), 1, file_pointer);
                fclose(file_pointer);
                if(stock_item.quantity == 0){
                    delete_item(stock_item.product_id);
                }
                break;
            }
        }
    }

    if(found == 1){
        printf("<===== Here is the invoice =====>\n");
        printf("Total amount payable: %.2f\n", price * quantity);
        printf("Product bought successfully...\n");
    }
    else{
        printf("Product not found\n");
    }
}

void customer_interface(){
    int choice;
    printf("1. Buy product\n");
    printf("2. View product inventory\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch(choice){
        case 1: buy_item();
                break;
        case 2: display_items();
                break;
        default: printf("Invalid input\n");
    }
}

int main(){
    int choice;
    while(1){
        printf("1. Administrator\n");
        printf("2. Customer\n");
        printf("0. Exit\n");
        printf("--> Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: admin_interface();
                    break;
            case 2: customer_interface();
                    break;
            case 0: exit(0);
            default: printf("Invalid input\n");
        }
    }
    return 0;
}
