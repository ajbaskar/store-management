#include <stdio.h>
#include "StoreItem.h"
#include "stocktxn.h"
void Menu();

int main()
{
	InitializeItems();
	Menu();
}

void Menu()
{
	int opt;
	while(1)
	{
		/* Clear Screen */
		system("cls");
		printf("XYZ Corportation");
		printf("\nStock Management\n");
		printf("\n1. Receipt Entry");
		printf("\n2. Issue Entry");
		printf("\n3. Stock List");
		printf("\n4. Stock Transactions Report");
		printf("\n5. View Store Items");
		printf("\n6. Exit");
		printf("\n\nEnter your choice (1-6): ");
		scanf("%d", &opt);
		fflush(stdin);

		switch(opt)
		{
			case 1:
				ReceiptEntry();
				break;
			case 2:
				IssueEntry();
				break;
			case 3:
				PrintStockList();
				break;
			case 4:
				PrintTransactionsInput();
				break;
			case 5:
				ListItems();
				break;
			case 6:
				return;
				break;
			default:
				printf("\nInvalid choice. Please try again (1-6)");	   	   	   
		}	 	 	 	 
		
		printf("\n\nPress a key to proceed...");
		getch();
	}
}

