#include <stdio.h>
#include <string.h>
#include "StoreItem.h"

STOREITEM items[50];
int itemcount;
char filename[]="./store.bin";

int ReadItemName(int itemcode, char *itemname)
{
	int itemfound,i;
	itemfound=0;
	for(i=0;i<itemcount;i++)
	{
		if(itemcode==items[i].itemcode)
		{
			strcpy(itemname,items[i].itemname);
			itemfound=1;
			break;
		}
	}
	return itemfound;
}

void InitializeItems()
{
	FILE *f;
	
	STOREITEM item;
	itemcount=0;
	f=fopen(filename,"rb");
	while(fread(&item,sizeof(STOREITEM),1,f))
	{
		items[itemcount].itemcode=item.itemcode;
		strcpy(items[itemcount].itemname,item.itemname);
		itemcount++;	
	}
	fclose(f);	  
}

void ListItems()
{
	FILE *f;
	int i;
	STOREITEM item;
	printf("\nList of items ");
	for(i=0;i<itemcount;i++)
	{
		item=items[i];
		printf("\n%d  %-30s",item.itemcode,item.itemname);
	}
		
}

STOREITEM *GetStoreItems()
{
	return items;
}

int GetItemsCount()
{
	return itemcount;
}

