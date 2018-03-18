#include<stdio.h>
#include<stdlib.h>
struct stack_t
{
	size_t size;
	size_t capacity;
	int *elements;
};
void stack_init(struct stack_t *);
void stack_destroy(struct stack_t*);
int stack_empty(struct stack_t*);
void stack_push(struct stack_t*,int);
void stack_pop(struct stack_t*);
void stack_state(struct stack_t*);
int stack_top (struct stack_t *ptr);
int main()
{
	struct stack_t stack;
	struct stack_t *pointer=&stack;
	stack_init(pointer);
	stack_state(pointer);
	//printf("Empty? -> %d",stack_empty(pointer));
	stack_push(pointer,5);
	stack_push(pointer,5);
	stack_push(pointer,2);
	stack_push(pointer,3);
	stack_push(pointer,8);
	stack_state(pointer);
	stack_pop(pointer);
	stack_state(pointer);
	return 0;
}
void stack_init(struct stack_t *ptr)
{
	ptr->size=0;
	ptr->elements=malloc(ptr->capacity*sizeof(int));	
}
void stack_destroy(struct stack_t *ptr)
{
	ptr->size=0;
	ptr->capacity=0;
	free(ptr->elements);
}
int stack_empty(struct stack_t *ptr)
{
	if(ptr->size>0)return 0;
	return -1;//empty=true
}
void stack_push(struct stack_t *ptr,int value)
{
	/*if(ptr->size==ptr->capacity)
	{
		//printf("Error stack is full");
		return;
	}*/
	ptr->elements[ptr->size++]=value;
}
int stack_top (struct stack_t *ptr)
{
	if(stack_empty(ptr)==-1)return -1;
	return ptr->elements[ptr->size-1];
}
void stack_pop(struct stack_t *ptr)
{
	if(stack_empty(ptr)==-1)return;
	ptr->size--;
}
void stack_state(struct stack_t *ptr)
{
	printf("\nStack:");
        printf("\nSize: %ld",ptr->size);
        printf("\nCapacity: %ld\n",ptr->capacity);
	printf("Elements: ");
	for(int i=0;i<ptr->size;i++)printf("%d ",*(ptr->elements+i));
}
