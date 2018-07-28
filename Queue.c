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

int queue_size(struct queue *root)
{
	struct queue *duplicate = root;
	int number = 0;
	while (duplicate != NULL)
	{
		number++;
		duplicate = duplicate->next;
	}
	return number;
}

bool queue_empty(struct queue *root)
{
	if (root == NULL) return true;
	else return false;
}

bool queue_full(struct queue *root)
{
	if (queue_size(root) == quantity) return true;
	else return false;
}

void dequeue(struct queue **root)
{
	if (*root == NULL) printf("delete_root: we have not root\n");
	else
	{
		struct queue *temp = *root;
		*root = (*root)->next;
		free(temp);
	}
}

void enqueue(struct queue **root, char message[], int priority)
{
	struct queue *duplicate, *duplicate_past, *temp, *temp_add_past = NULL, *temp_add_now = NULL, *temp_del = NULL;
	int number = 0;
	bool check = false;
	duplicate = *root;
	duplicate_past = NULL;
	if (!queue_empty(*root))
	{
		while (duplicate != NULL)
		{
			number++;
			if (duplicate->priority < priority && check == false)
			{
				temp_add_past = duplicate_past;
				temp_add_now = duplicate;
				check = true;
			}
			if (number == quantity) temp_del = duplicate_past;
			duplicate_past = duplicate;
			duplicate = duplicate->next;
		}
		if (number == quantity && check == true)
		{
			if (temp_del->next == temp_add_now) temp_add_now = NULL;
			temp = temp_del->next;
			temp_del->next = NULL;
			free(temp);
		}
		else if (number != quantity && check == false)
		{
			temp_add_past = duplicate_past;
			temp_add_now = duplicate;
			check = true;
		}
		if (check == true)
		{
			temp = (struct queue*)malloc(sizeof(struct queue));
			temp->priority = priority;
			strcpy(temp->message, message);
			temp->next = NULL;
			temp->next = temp_add_now;
			if (temp_add_past != NULL) temp_add_past->next = temp;
			else *root = temp;
		}
	}
	else
	{
		temp = (struct queue*)malloc(sizeof(struct queue));
		temp->priority = priority;
		strcpy(temp->message, message);
		temp->next = NULL;
		*root = temp;
	}
}

void queue_print(struct queue *root)
{
	struct queue *duplicate;
	duplicate = root;
	if (root == NULL) printf("turn_print: we have not root");
	else
		do {
			printf("priority %d: %s\n", duplicate->priority, duplicate->message);
			duplicate = duplicate->next;
		} while (duplicate != NULL);
}

int main()
{
	struct queue *root = NULL;
	enqueue(&root, "message 1", LOW);
	enqueue(&root, "message 2", HIGH);
	dequeue(&root);
	enqueue(&root, "message 3", HIGH);
	enqueue(&root, "message 4", HIGHEST);
	enqueue(&root, "message 5", LOWEST);
	enqueue(&root, "message 6", LOW);
	enqueue(&root, "message 8", LOW);
	queue_print(root);
	if (queue_empty(root)) printf("Queue is empty\n");
	else printf("Queue is not empty\n");
	printf("Queue size = %d\n", queue_size(root));
	if (queue_full(root)) printf("Queue is full\n");
	else printf("Queue is not full\n");
	getchar();
	return 0;
}