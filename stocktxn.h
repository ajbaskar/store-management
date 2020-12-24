
typedef struct stocktxn
{
	int itemcode;
	char txn;
	float qty;	  
} STOCK;
void ReceiptEntry();
void stocktransaction();
void IssueEntry();
void PrintStockList();
float ClosingStock(int itemcode);
void PrintTransactions(int itemcode);
void PrintTransactionsInput();

