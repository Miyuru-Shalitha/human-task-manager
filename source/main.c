#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint32_t year;
    uint8_t day;
    uint8_t month;
} Date;

typedef struct {
    uint8_t minutes;
    uint8_t hours;
} Time;

typedef struct {
    const char* name;
    Date* starting_date;
    Date* ending_date;
    Time* starting_time;
    Time* ending_time;
    bool status;
} Task;

typedef struct {
    Task* buffer;
    size_t capacity;
    size_t size;
} Task_List;

static Task_List task_create(size_t capacity)
{
    void* buffer = malloc(sizeof(Task) * capacity);

    if (!buffer)
    {
        fprintf(stderr, "malloc failed!\n");
        exit(EXIT_FAILURE);
    }

    return (Task_List) {
        .buffer = buffer,
        .capacity = capacity,
        .size = 0
    };
}

static void task_push(Task_List* self, Task task)
{
    if (self->size == self->capacity)
    {
        self->capacity *= 2;
        void* new_buffer = realloc(self->buffer, self->capacity);

        if (!new_buffer)
        {
            fprintf(stderr, "realloc failed!\n");
            exit(EXIT_FAILURE);
        }

        self->buffer = new_buffer;
    }

    self->buffer[self->size++] = task;
}

static void task_free(Task_List* self)
{
    free(self->buffer);
    self->buffer = nullptr;
    self->capacity = 0;
    self->size = 0;
}

int main()
{
    Date starting_date = (Date) {
        .year = 2025,
        .month = 5,
        .day = 16
    };

    Time starting_time = (Time) {
        .hours = 12,
        .minutes = 0
    };

    Date end_date = (Date) {
        .year = 2025,
        .month = 5,
        .day = 20
    };

    Time ending_time = (Time) {
        .hours = 12,
        .minutes = 0
    };

    Task_List task_list = task_create(4);

    task_push(&task_list, (Task) {
        .name = "Task 1",
        .starting_date = &starting_date,
        .ending_date = &end_date,
        .starting_time = &starting_time,
        .ending_time = &ending_time,
        .status = false
    });

    task_push(&task_list, (Task) {
        .name = "Task 1",
        .starting_date = &starting_date,
        .ending_date = &end_date,
        .starting_time = &starting_time,
        .ending_time = &ending_time,
        .status = false
    });

    for (size_t i = 0; i < task_list.size; i++)
    {
        printf("| %s | %d | (%d/%d/%d | %d:%d) | (%d/%d | %d:%d:%d) | \n",
                task_list.buffer[i].name,
                task_list.buffer[i].status,
                task_list.buffer[i].starting_date->day, task_list.buffer[i].starting_date->month, task_list.buffer[i].starting_date->year,
                task_list.buffer[i].starting_time->hours, task_list.buffer[i].starting_time->minutes,
                task_list.buffer[i].ending_date->day, task_list.buffer[i].ending_date->month, task_list.buffer[i].ending_date->year,
                task_list.buffer[i].ending_time->hours, task_list.buffer[i].ending_time->minutes);
    }

    return 0;
}
