#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
const int quantity = 5;

enum PRIORIRIES {
	LOWEST,
	LOW,
	MEDIUM,
	HIGH,
	HIGHEST
};

struct queue
{
	int priority;
	char message[255];
	struct queue *next;
};

struct queue_new
{
	struct queue *element;
	int size;
};

struct queue_new *queue_create()
{
	struct  queue_new *root;
	root = malloc(sizeof(*root));
	if (root != NULL)
	{
		root->size = 0;
		root->element = NULL;
	}
	return root;
}

int queue_size(struct queue_new *root)
{
	return root->size;
}

bool queue_empty(struct queue_new *root)
{
	if (root->size == 0) return true;
	else return false;
}

bool queue_full(struct queue_new *root)
{
	if (root->size == quantity) return true;
	else return false;
}

void dequeue(struct queue_new *root)
{
	if (root->size == 0) printf("dequeue: we have not root\n");
	else
	{
		struct queue *temp = root->element;
		root->element = temp->next;
		free(temp);
		root->size--;
	}
}

void enqueue(struct queue_new *root, char message[], int priority)
{
	struct queue *duplicate, *duplicate_past, *temp, *temp_add = NULL, *temp_del = NULL;
	int number = 0;
	bool check = false;
	if (root->size != 0)
	{
		if (root->size != quantity)
		{
			duplicate = root->element;
			duplicate_past = NULL;
			while (duplicate != NULL && duplicate->priority >= priority)
			{
				duplicate_past = duplicate;
				duplicate = duplicate->next;
			}
			temp = (struct queue*)malloc(sizeof(struct queue));
			temp->priority = priority;
			strncpy(temp->message, message, sizeof(temp->message) - 1);
			temp->message[sizeof(temp->message) - 1] = '\0';
			temp->next = duplicate;
			if (duplicate_past != NULL)
			{
				duplicate_past->next = temp;
			}
			else
			{
				root->element = temp;
			}
			root->size++;
		}
		else
		{
			duplicate = root->element;
			duplicate_past = NULL;
			while (duplicate != NULL)
			{
				if (duplicate->priority < priority && check == false)
				{
					temp_add = duplicate_past;
					check = true;
				}
				if (duplicate->next == NULL) temp_del = duplicate_past;
				duplicate_past = duplicate;
				duplicate = duplicate->next;
			}
			if (check == true)
			{
				temp = (struct queue*)malloc(sizeof(struct queue));
				temp->priority = priority;
				strncpy(temp->message, message, sizeof(temp->message) - 1);
				temp->message[sizeof(temp->message) - 1] = '\0';
				temp->next = NULL;
				if (temp_add == temp_del)
				{
					free(temp_del->next);
					temp_del->next = temp;
				}
				else
					if (temp_add == NULL)
					{
						free(temp_del->next);
						temp_del->next = NULL;
						temp->next = root->element;
						root->element = temp;
					}
					else
					{
						free(temp_del->next);
						temp_del->next = NULL;
						temp->next = temp_add->next;
						temp_add->next = temp;
					}
			}
		}
	}
	else
	{
		temp = (struct queue*)malloc(sizeof(struct queue));
		temp->priority = priority;
		strncpy(temp->message, message, sizeof(temp->message) - 1);
		temp->message[sizeof(temp->message) - 1] = '\0';
		temp->next = NULL;
		root->element = temp;
		root->size++;
	}
}

void queue_print(struct queue_new *root)
{
	struct queue *duplicate;
	duplicate = root->element;
	if (root->size == 0) printf("queue_print: we have not root\n");
	else
		do {
			printf("priority %d: %s\n", duplicate->priority, duplicate->message);
			duplicate = duplicate->next;
		} while (duplicate != NULL);
}

int main()
{
	struct queue_new *root = queue_create();
	enqueue(root, "message 1", LOW);
	enqueue(root, "message 2", HIGH);
	dequeue(root);
	enqueue(root, "message 3", LOWEST);
	enqueue(root, "message 4", HIGH);
	enqueue(root, "message 5", HIGH);
	enqueue(root, "message 6", HIGHEST);
	queue_print(root);
	if (queue_empty(root)) printf("Queue is empty\n");
	else printf("Queue is not empty\n");
	printf("Queue size = %d\n", queue_size(root));
	if (queue_full(root)) printf("Queue is full\n");
	else printf("Queue is not full\n");
	getchar();
	return 0;
}