#include "io.h"
#include <stdio.h>

char *circles[CIRCLE_VARIANTS_COUNT] = {"Обычные круглые", "Круглые с шипами", "Треугольные гусеничные", "Гусеничные с изменяемой формой"};
char *bodies[BODY_VARIANTS_COUNT] = {"Грузовик", "Автобус", "Кроссовер", "Спортивный автомобиль", "Кабриолет", "Танк"};
char *colors[COLOR_VARIANTS_COUNT] = {"Черный", "Желтый", "Красный", "Зеленый", "Розовый", "Фиолетовый", "Белый"};

FILE *file = NULL;

void open_output(void)
{
	if (!file)
		file = fopen("result.txt", "w");
}

error_t print_automobile(automobile_t *automobile)
{
	if (!automobile)
		return ERROR_INPUT;
	fprintf(file, "Создан автомобиль со следующими характеристиками:\n");
	fprintf(file, "Серия автомобиля:%u\n", automobile->number);
	fprintf(file, "Тип автомобиля:%s\n", bodies[automobile->body]);
	fprintf(file, "Тип колес автомобиля:%s\n", circles[automobile->circles]);
	fprintf(file, "Цвет автомобиля:%s\n\n", colors[automobile->color]);
	return SUCCESS;
}

void close_output(void)
{
	if (file)
		fclose(file);
	file = NULL;
}
