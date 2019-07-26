/**
 * 数组实现栈
 */

#include <stdio.h>
#include <malloc.h>

static int count = 0;

// 创建大小为 size 的栈
int *create_array_stack(int size)
{
    int *stack = (int *)malloc(sizeof(int)*size);

    if (stack)
    {
        return stack;
    }

    return NULL;
}

void destroy_array_stack(int *stack)
{
    if (stack)
    {
        free(stack);
        stack = NULL;
    }
}

void push_stack(int *stack, int value)
{
    if (NULL == stack)
    {
        return;
    }

    stack[count++] = value;
}
// 出栈，并删除栈顶元素
int pop_stack(int *stack)
{
    if (NULL == stack)
    {
        -1;
    }

    int ret = stack[count-1];
    count--;
    return ret;
}

// 返回栈顶元素的值，不删除栈顶元素
int peek_stack(int *stack)
{
    if (NULL == stack)
    {
        -1;
    }

    return stack[count-1];
}

int size_stack()
{
    return count;
}

int stack_is_empty()
{
    return size_stack() == 0;
}

void printf_stack(int *stack)
{
    if (stack_is_empty())
    {
        printf("stack is empty.\n");
        return;
    }

    int i = 0;
    for (i; i < size_stack(); ++i)
    {
        printf("[%d]-->%d\n", i, stack[i]);
    }
}

int main(int argc, char const *argv[])
{
    int *stack = create_array_stack(32);

    int i = 0;
    for (i; i < 10; ++i)
    {
        push_stack(stack, i*5);
    }

    printf_stack(stack);

    int top = 0;
    top = peek_stack(stack);
    printf_stack(stack);


    for (i = 0; i < 5; ++i)
    {
        pop_stack(stack);
    }
    printf_stack(stack);

    return 0;
}