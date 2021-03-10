
#include <stdlib.h>

#define FALSE -1
#define TRUE 1

/**
 * Названия функций близки к подобным для List для C++ STL 11,
 */

// указатель на данные, хранящиеся в связанном списке
typedef void* DataPointer;

//структура, представляющая узел в списке
typedef struct ListNode {
    DataPointer data;
    struct ListNode *next;
} ListNode;

// структура, представляющая единый список
typedef struct LinkedList {
    ListNode *head;
} LinkedList;

LinkedList* createList()
{
    // выделяем память для списка
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    // если нет ошибки при выделении, инициализируем..
    if (list)
        list->head = NULL;
    return list;
}


int pushFront(LinkedList *list, DataPointer data)
{
    ListNode *top;

    if(!list)
        return FALSE;
    // выделяем память для узла
    top = (ListNode *) malloc(sizeof(ListNode));
    // если память выделить не удалось, возвращаем FALSE
    if(!top)
        return FALSE;

    // помещаем значение
    top->data = data;
    // добавляем узел в начало
    top->next = list->head;
    list->head = top;

    return TRUE;
}


int pushBack(LinkedList *list, DataPointer data)
{
    if(list)
    {
        // выделяем память для узла
        ListNode *new = (ListNode *) malloc(sizeof(ListNode));
        // если память выделить не удалось, возвращаем FALSE
        if(!new)
            return FALSE;

        new->data = data;
        new->next = NULL;

        // если список не пустой, то
        if(list->head)
        {
            ListNode *tail = list->head;

            // повторяем до конца
            while(tail && tail->next)
                tail = tail->next;

            tail->next = new;

            return TRUE;
        }
        else
        {
            list->head = new;
            return TRUE;
        }
    }

    return FALSE;
}

void popFront(LinkedList *list)
{
    // если список не =NULL или пустой
    if (list && list->head)
    {
        // переупорядочиваем список
        ListNode *top = list->head;
        list->head = top->next;
        // очищаем данные, которые были спереди списка
        free(top->data);
        // очищаем узел
        free(top);
    }
}


void deleteList(LinkedList *list)
{
	// если список не =NULL или пустой
    if (list)
    {
        if (list->head)
        {
            // проходим список, каждый раз удаляя последний элемент
            do
                popFront(list);
            while (list->head);
        }
        // освобождаем память от списка
        free(list);
    }
}


void popBack(LinkedList *list)
{
	// если список не =NULL или пустой
    if (list && list->head)
    {
        ListNode *tail = list->head;
        ListNode *previous = tail;
        // если в списке один узел, то..
        if (list->head->next)
        {
            // проходим до конца
            while(tail && tail->next)
            {
                previous = tail;
                tail = tail->next;
            }
            previous->next = NULL;
            free(tail->data);
            free(tail);
        }
        else // если размер > 1
        {
            free(list->head->data);
            free(list->head);
            list->head = NULL;
        }
    }
}


unsigned long getSize(LinkedList *list)
{
	// если список не =NULL или пустой
    if(list && list->head)
    {
        unsigned long size = 1;
        ListNode *current = list->head;
        while (current->next)
        {
            // увеличиваем счетчик размера при переходе к след. узлу
            current = current->next;
            size++;
        }
        return size;
    }

    return 0;
}


DataPointer getFront(LinkedList *list)
{
	// если список не =NULL или пустой
    if(list && list->head)
        return list->head->data;
    return NULL;
}


DataPointer getBack(LinkedList *list)
{
	// если список не =NULL или пустой
    if(list && list->head)
    {
        ListNode *tail = list->head;
        // проходим до конца
        while(tail && tail->next)
            tail = tail->next;
        return tail->data;
    }
    return NULL;
}

int main () {
	// создаем список
    LinkedList *list = createList();
    //заполняем с начала значениями от 1 до 10
    int *a;
    for (unsigned int i=0; i<10; i++)
    {
		a=(int*)malloc(sizeof(int));
		*a=i+1;
		pushFront(list,a);
    }
    int *b=(int*)malloc(sizeof(int));
    b = getBack(list);
    printf("Значение в конце = %d\n",*b);
    b = getFront(list);
    printf("Значение в начале = %d\n",*b);
    popBack(list); //удаляем элемент с конца
    b = getBack(list);
    printf("Размер списка = %d\n", getSize(list));
    printf("Значение в начале = %d\n",*b);
    popFront(list); //удаляем с начала
    b = getFront(list);
    printf("Размер списка = %d\n", getSize(list));
    printf("Значение в конце = %d\n",*b);
    deleteList(list);
    free(a);
    free(b);
	return 0;
}
