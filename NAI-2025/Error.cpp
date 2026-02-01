#include "stdafx.h" 

namespace Error
{
    ERROR errors[ERROR_MAX_ENTRY] = {
        
        ERROR_ENTRY(0, "Недопустимый код ошибки"),
        ERROR_ENTRY(1, "Системный сбой"),
        ERROR_ENTRY(2, "Ошибочное выражение"),
        ERROR_ENTRY(3, "Неизвестная библиотека"),
        ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
        ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7),
        ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
        ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20),
        ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
        ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60),
        ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80),
        ERROR_ENTRY_NODEF10(90),

        
        ERROR_ENTRY(100, "Параметр -in должен быть задан"),
        ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102),
        ERROR_ENTRY_NODEF(103),
        ERROR_ENTRY(104, "Превышена длина входного параметра"),
        ERROR_ENTRY(105, "Ошибка при создании выходного файла .out"),
        ERROR_ENTRY(106, "Недопустимый размер таблицы лексем"),
        ERROR_ENTRY(107, "Превышен размер таблицы лексем"),
        ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
        ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
        ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
        ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),

        ERROR_ENTRY(113, "Недопустимый идентификатор"),
        ERROR_ENTRY(114, "Дублирование идентификатора"),
        ERROR_ENTRY(115, "Идентификатор не определён"),
        ERROR_ENTRY(116, "Дублирование функции Main"),
        ERROR_ENTRY(117, "Недопустимый размер таблицы идентификаторов"),
        ERROR_ENTRY(118, "Превышен размер таблицы идентификаторов"),
        ERROR_ENTRY(119, "Превышена длина идентификатора (max 30 символов)"),

        
        ERROR_ENTRY(120, "Функция не может быть типа char"),
        ERROR_ENTRY(121, "Использование запрещенного символа"),
        ERROR_ENTRY(122, "Кавычки не были закрыты"),
        ERROR_ENTRY(123, "Литерал типа char должен содержать только 1 символ"),
        ERROR_ENTRY(124, "Превышен максимальный размер для литерала str (255)"),
        ERROR_ENTRY(125, "Пустой строковый литерал"),
        ERROR_ENTRY(126, "Пустой символьный литерал"),
        ERROR_ENTRY(127, "Превышен диапазон числового литерала int8 (-128..127)"),
        ERROR_ENTRY(128, "Числовой литерал с недопустимым форматом"),
        ERROR_ENTRY(129, "Управляющий символ вне допустимого набора"),

        
        ERROR_ENTRY(130, "Функция Main не может иметь параметры"),
        ERROR_ENTRY(131, "Функция Main должна быть объявлена"),
        ERROR_ENTRY(132, "Дублирование функции"),
        ERROR_ENTRY(133, "Идентификатор совпадает с ключевым словом"),
        ERROR_ENTRY(134, "Идентификатор начинается с цифры"),
        ERROR_ENTRY(135, "Идентификатор содержит запрещённые символы"),
        ERROR_ENTRY(136, "Невозможность распознать лексему"),
        ERROR_ENTRY(137, "Неправильное разделение токенов"),
        ERROR_ENTRY_NODEF(138),
        ERROR_ENTRY(139, "Недопустимое использование ключевого слова"),

        ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
        ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170),
        ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),

        
        ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300),
        ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),

        

        
        ERROR_ENTRY(600, "Неверная структура программы"),
        ERROR_ENTRY(601, "Ошибочный оператор"),
        ERROR_ENTRY(602, "Ошибка в выражении"),
        ERROR_ENTRY(603, "Ошибка в параметрах функции при вызове"),
        ERROR_ENTRY(604, "Ошибка в параметрах объявляемой функции"),
        ERROR_ENTRY_NODEF(605), ERROR_ENTRY_NODEF(606),
        ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(608),
        ERROR_ENTRY_NODEF(609),
        ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620),
        ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
        ERROR_ENTRY_NODEF10(650), ERROR_ENTRY_NODEF10(660),
        ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680),
        ERROR_ENTRY_NODEF10(690),
        
         ERROR_ENTRY(700, "Тип возвращаемого значения не соответствует объявлению"),
         ERROR_ENTRY(701, "Не совпадает количество параметров при вызове функции"),
         ERROR_ENTRY(702, "Не совпадают типы параметров при вызове функции"),
         ERROR_ENTRY(703, "Вызов несуществующей функции"),
         ERROR_ENTRY(704, "Функция с типом возврата не возвращает значение"),
         ERROR_ENTRY_NODEF(705), ERROR_ENTRY_NODEF(706),
         ERROR_ENTRY_NODEF(707), ERROR_ENTRY_NODEF(708),
         ERROR_ENTRY_NODEF(709),

         
         ERROR_ENTRY(710, "Использование необъявленной переменной"),
         ERROR_ENTRY(711, "Повторное объявление переменной в той же области видимости"),
         ERROR_ENTRY(712, "Попытка изменить константу"),
         ERROR_ENTRY(713, "Конфликт имени с функцией стандартной библиотеки"),
         ERROR_ENTRY(714, "Использование переменной вне области видимости"),
         ERROR_ENTRY_NODEF(715), ERROR_ENTRY_NODEF(716),
         ERROR_ENTRY_NODEF(717), ERROR_ENTRY_NODEF(718),
         ERROR_ENTRY_NODEF(719),

         
         ERROR_ENTRY(720, "Несоответствие типов при присваивании"),
         ERROR_ENTRY(721, "Несовместимость типов в арифметическом выражении"),
         ERROR_ENTRY(722, "Несовместимость типов в логическом выражении"),
         ERROR_ENTRY(723, "Использование строк в арифметических операциях"),
         ERROR_ENTRY(724, "Неверный тип в условном выражении цикла"),
         ERROR_ENTRY(725, "Превышение диапазона типа int8 (-128..127)"),
         ERROR_ENTRY(726, "Побитовые операции допустимы только для типа int"),
         ERROR_ENTRY(727, "Операции сравнения требуют одинаковых типов операндов"),
         ERROR_ENTRY(728, "Недопустимая операция для данного типа"),
         ERROR_ENTRY(729, "Попытка выполнить арифметическую операцию над char"),
         ERROR_ENTRY(730, "Попытка выполнить арифметическую операцию над string"),
         ERROR_ENTRY(731, "Попытка выполнить арифметическую операцию над bool"),
         ERROR_ENTRY_NODEF(732),
         ERROR_ENTRY_NODEF(733),
        ERROR_ENTRY_NODEF(734), ERROR_ENTRY_NODEF(735),
        ERROR_ENTRY_NODEF(736), ERROR_ENTRY_NODEF(737),
        ERROR_ENTRY_NODEF(738), ERROR_ENTRY_NODEF(739),

        ERROR_ENTRY_NODEF10(740), ERROR_ENTRY_NODEF10(750),
        ERROR_ENTRY_NODEF10(760), ERROR_ENTRY_NODEF10(770),
        ERROR_ENTRY_NODEF10(780), ERROR_ENTRY_NODEF10(790),

        
        ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
    };

    ERROR geterror(int id) {
        if (id < 0 || id >= ERROR_MAX_ENTRY) {
            return errors[0];
        }
        if (errors[id].id == 0 && id != 0) {
            return errors[0];
        }
        return errors[id];
    }

    ERROR geterrorin(int id, int line = -1, int col = -1) {
        if (id < 0 || id >= ERROR_MAX_ENTRY) {
            return errors[0];
        }
        errors[id].inext.line = line;
        errors[id].inext.col = col;
        return errors[id];
    }
}