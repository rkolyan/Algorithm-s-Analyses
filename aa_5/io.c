#include "io.h"

char *[CIRCLE_VARIANTS_COUNT] circles = {"Обычные круглые", "Круглые с шипами", "Треугольные гусеничные", "Гусеничные с изменяемой формой"};
char *[BODY_VARIANTS_COUNT] bodies = {"Грузовик", "Автобус", "Кроссовер", "Спортивный автомобиль", "Кабриолет", "Танк"};
char *[COLOR_VARIANTS_COUNT] colors = {"Черный", "Желтый", "Красный", "Зеленый", "Розовый", "Фиолетовый", "Белый"};

error_t print_automobile(automobile_t *automobile)
{
	if (!automobile)
		return ERROR_INPUT;
	puts("\nСоздан автомобиль со следующими характеристиками:");
	printf("Серия автомобиля:%u\n", automobile->number);
	printf("Тип автомобиля:%s\n", bodies[automobile->body]);
	printf("Тип колес автомобиля:%s\n", circles[automobile->circles]);
	printf("Цвет автомобиля:%s\n", colors[automobile->color]);
	return SUCCESS;
}
