#include "error_codes.h"
#include "io.h"

char *circles[CIRCLE_VARIANTS_COUNT] = {"Обычные круглые", "Круглые с шипами", "Треугольные гусеничные", "Гусеничные с изменяемой формой"};
char *bodies[BODY_VARIANTS_COUNT] = {"Грузовик", "Автобус", "Кроссовер", "Спортивный автомобиль", "Кабриолет", "Танк"};
char *colors[COLOR_VARIANTS_COUNT] = {"Черный", "Желтый", "Красный", "Зеленый", "Розовый", "Фиолетовый", "Белый"};

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
