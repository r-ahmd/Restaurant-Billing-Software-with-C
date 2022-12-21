#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items
{
    char item[30];
    float price;
    int qty;
};
struct orders
{
    char customer[50];
    char date[50];
    int numOfitems;
    struct items itm[50];
};

///Function To generate Bills
void generateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\tTrattoria di Famiglia Resturant");
    printf("\n\t\t ---------------------");
    printf("\n Date: %s", date);
    printf("\n Invoice To: %s", name);
    printf("\n");
    printf("----------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n----------------------------");
    printf("\n\n");
}
void generateBillBody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}
void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float vat = 0.15*netTotal, grandTotal = netTotal + 2*vat;
    printf("----------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t\t--------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nVat @15%s\t\t\t%.2f", "%", vat);
    printf("\n----------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n----------------------------\n");
}

///The Main body for the sytem
int main()
{
    int opt, n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', continueflag = 'y';
    char name[50];
    FILE *file; ////for saving data in a file
    ///first print the dashboard to the User
    while(continueflag == 'y')
    {
        system("clear");
        int invfound = 0;
        float total = 0;
        
        printf("\t========== Trattoria di Famiglia Resturant ==========");
        printf("\n\nPlease select your prefered operation\n");
        printf("\n1. Generate Invoice");
        printf("\n2. Show all Invoice");
        printf("\n3. Search Invoice");
        printf("\n4. Exit");
        
        printf("\n\nYour Choice:\t");
        scanf("%d", &opt);
        fgetc(stdin); ////use if you want to save the data in a file
        switch(opt)
        {
            case 1:
                system("clear");
                printf("\nEnter The Name Of The Customer:\t");
                //gets(ord.customer);
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer)-1] = 0;
                printf("\nEnter Date:\t");
                fgets(ord.date, 50, stdin);
                printf("\nEnter the number of Items:\t");
                scanf("%d", &n);
                ord.numOfitems = n;
                for(int i=0; i<n; i++)
                {
                    fgetc(stdin);
                    printf("\n\n");
                    printf("Enter The item %d:\t", i+1);
                    //gets(ord.itm[i].item);
                    fgets(ord.itm[i].item, 50, stdin);
                    ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
                    printf("Enter the quantity:\t");
                    scanf("%d", &ord.itm[i].qty);
                    printf("Enter the unit price:\t");
                    scanf("%f", &ord.itm[i].price);
                    total += ord.itm[i].qty * ord.itm[i].price;
                }
                generateBillHeader(ord.customer, ord.date);
                for(int i=0; i<ord.numOfitems; i++)
                {
                    generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                }
                generateBillFooter(total);
                printf("\nDo you want to save the invoice[y/n]:\t");
                scanf("%s", &saveBill);
                
                if(saveBill == 'y')
                {
                    file = fopen("ResturantBill.dat", "a+");
                    fwrite(&ord, sizeof(struct orders), 1, file);
                    
                    if(fwrite != 0)
                        printf("\nSuccessfully Saved.");
                    else
                        printf("\nError Saving.");
                    fclose(file);
                }
                break;
                    
            case 2:
                system("clear");
                file = fopen("ResturantBill.dat", "r");
                printf("\n ****** Your Previous Invoices ******");
                while(fread(&order, sizeof(struct orders), 1, file))
                {
                    float ttl = 0;
                    generateBillHeader(order.customer, order.date);
                    for(int i=0; i<order.numOfitems; i++)
                    {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        ttl += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(ttl);
                    fclose(file);
                    break;
                }
            case 3:
                system("clear");
                printf("\nEnter the name of the customer:\t");
                //fgetc(stdin);
                fgets(name, 50, stdin);
                name[strlen(name)-1] = 0;
                file = fopen("ResturantBill.dat", "r");
                printf("\t****** Invoice Of %s ******", name);
                while(fread(&order, sizeof(struct orders), 1, file))
                {
                    float ttl = 0;
                    if(!strcmp(order.customer, name))
                    {
                        generateBillHeader(order.customer, order.date);
                        for(int i=0; i<order.numOfitems; i++)
                        {
                            generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                            ttl += order.itm[i].qty * order.itm[i].price;
                        }
                        generateBillFooter(ttl);
                        invfound = 1;
                    }
                    if(!invfound)
                        printf("\nSorry the invoice for %s doesn't exist\n", name);
                    fclose(file);
                    break;
                }
            case 4:
                printf("\n\t\t BYE BYE!!!");
                exit(0);
                break;
            default:
                printf("\n\t\tSorry invalid option!!");
                break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s", &continueflag);
    }
    printf("\n\t\t BYE BYE !");
    
    printf("\n\n");
    
    
    return 0;
}




//////Welcome to trattoria di famiglia resturant where you can dine with your family and enjoy the weekend....thankyou (by r_ahmd)




