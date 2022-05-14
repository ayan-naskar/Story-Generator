struct node
{
	char word[30];
	float probability;
	struct node* next;
};

struct hash_table
{
	int hash;
	char key[100];
	struct node* value;
};

struct hash_table *ar;