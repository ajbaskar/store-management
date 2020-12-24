#include "stocktxn.h"
#include "StoreItem.h"
#include<stdio.h>

char stkfilename[]="./stock.bin";
/*1.Receipt Entry function*/
void ReceiptEntry()
{
	FILE *f;
	STOCK stk;
	int itemfound;
	char itemname[31];
	char opt;
	f=fopen(stkfilename,"ab");
	printf("\nEnter the item code : ");
	scanf("%d",&stk.itemcode);
	
	fflush(stdin);
	
	itemfound=ReadItemName(stk.itemcode,itemname);
	if(itemfound==0)
	{
		printf("\nInvalid Item code");
		return;
	}
	printf("\nItem name : %s",itemname);
	printf("\nThis is the correct (Y/N) :");
	scanf("%c",&opt);
	if(opt=='n' || opt=='N')
	return;
	printf("\nEnter Qty : ");
	scanf("%f",&stk.qty);
	fflush(stdin);
	stk.txn='R';
	fwrite(&stk,sizeof(STOCK),1,f);
	
	fclose(f);
	
}
/*2.Issue Entry function*/
void IssueEntry()
{
	FILE *f;
	STOCK stk;
	int itemfound;
	char itemname[31];
	char opt;
	f=fopen(stkfilename,"ab");
	printf("\nEnter the item code : ");
	scanf("%d",&stk.itemcode);
	
	fflush(stdin);
	
	itemfound=ReadItemName(stk.itemcode,itemname);
	if(itemfound==0)
	{
		printf("\nInvalid Item code");
		return;
	}
	printf("\nItem name : %s",itemname);
	printf("\nThis is the correct (Y/N) :");
	scanf("%c",&opt);
	if(opt=='n' || opt=='N')
	return;
	printf("\nEnter Qty : ");
	scanf("%f",&stk.qty);
	fflush(stdin);
	stk.txn='I';
	fwrite(&stk,sizeof(STOCK),1,f);
	
	fclose(f);
		   
}
/*4.Stock Transaction REport function*/
void stocktransaction()
{
	int itemcode,itemfound;
	char itemname[31];
	
	STOCK item;
	FILE *f;
	printf("\nEnter the item code : ");
	scanf("%d",&itemcode);
	
	fflush(stdin);
	
	itemfound=ReadItemName(itemcode,itemname);
	if(itemfound==0)
	{
		printf("\nInvalid Item code");
		return;
	}
	printf("\nItem name : %s",itemname);
	
	f=fopen(stkfilename,"rb");
	while(fread(&item,sizeof(STOCK),1,f))
	{
		if(item.itemcode==itemcode)
		printf("\n%c  %10.2f",item.txn,item.qty);
	}
	fclose(f);

}

/*3.Stock List function*/
void PrintStockList()
{
	STOREITEM *items=GetStoreItems();
	STOREITEM item;
	int i,itemscount;
	float closingstock;
	itemscount=GetItemsCount();
	
	for(i=0;i<itemscount;i++)
	{
		item=items[i];
		
		closingstock=ClosingStock(item.itemcode);
		
		printf("\n%d  %-20s  %10.2f",item.itemcode, item.itemname,closingstock);
	}
	
	
}

float ClosingStock(int itemcode)
{
	STOCK txn;
	FILE *f;
	float stk=0;
	f=fopen(stkfilename,"rb");
	
	while(fread(&txn,sizeof(STOCK),1,f))
	{
		if(txn.itemcode==itemcode)
		{
			if(txn.txn=='R')
				stk+=txn.qty;
				
			else
				stk-=txn.qty;	 	 
		}
	}
	fclose(f);
	return stk;	   	    
}

void PrintTransactionsInput()
{
	int itemcode;
	char itemname[30];
	int itemfound;
	
	printf("\nEnter the Item code : ");
	scanf("%d",&itemcode);
	fflush(stdin);
	
	itemfound=ReadItemName(itemcode,itemname);
	
	if(itemfound==0)
	{
		printf("\nInvalid Item code");
		return;
	}
	
	printf("\nItem name : %-s",itemname);
	PrintTransactions(itemcode);	
}

void PrintTransactions(int itemcode)
{
	FILE *f;
	STOCK txn;
	float Itotal,Rtotal,i,r;
	
	Itotal=Rtotal=0;
	
	f=fopen(stkfilename,"rb");
	
	while(fread(&txn,sizeof(STOCK),1,f))
	{
		if(txn.itemcode==itemcode)
		{
			r=0;
			i=0;
			
			if(txn.txn=='R')
				r=txn.qty;
			else
				i=txn.txn;
				
			/*Print the receipt or issues text */	 	 	 	 
			if(txn.txn=='R')
				printf("\n%-10s ","Receipt");
			else
				printf("\n%-10s ","Isues");
				
			/*Print the receipt or issues value */	  
			if(r!=0)
				printf("%10.3f",r);
			else
				printf("%10s %10.3f","",i);	   	   	   	   
				
			Rtotal+=r;
			Itotal+=i;	  	  
			
		}
		
		
	}
	/*Print the total*/
		printf("\n--------------------------------");
		printf("\n%-10s %10.3f %10.3f","Total",Rtotal,Itotal);	
		
	/*Print the closing stock*/
	
	if((Rtotal-Itotal)!=0)
	{
		if(Rtotal>Itotal)
			printf("\n%-10s %10.3f","Cl.stock",Rtotal-Itotal);
		else
			printf("\n%-10s %10.3f","Cl.stock",Itotal-Rtotal);
	}
	
	else
		printf("\nNo of Transaction Found");
	fclose(f);	  	      
}

