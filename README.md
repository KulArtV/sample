### Deque (часть 1)

*Дек - структура данных, которая представляет собой последовательность элементов и позволяет осуществлять добавление/удаление элементов с обоих концов.*
В C++ дек включен в стандартную библиотеку в виде шаблонного класса `std::deque`. Особенностями его реализации являются следующие характеристики: 

* Амортизированная сложность операций `push_front`, `pop_front`, `push_back` и `pop_back` составляет O(1)
* Поддержана возможность обращения к элементам по индексу за O(1)
* Вместимость дека увеличивается динамически по мере необходимости.
* В отличие от вектора (`std::vector`) ссылки и указатели на объекты не инвалидируются.

Особого внимания заслуживает последний пункт. Инвалидация ссылок и указателей довольно распространенная проблема при работе с вектором. Она заключается в следующем. Допустим, мы сохранили ссылку/указатель на один из элементов вектора (`int& ref = v[1];`), а затем проводили некоторые манипуляции над вектором (в самом простом случае - добавляли новые элементы в конец). Изменится ли значение элемента `v[1]`? Естественно, нет - мы добавляли новые элементы, это не должно повлиять на уже существующие объекты. А что произойдет c `ref`? Добавление нового элемента потенциально может вызвать расширение буфера, которое заключается в копировании элементов в новый буфер и **удалении** старого. Таким образом, теперь `ref` ссылается на удаленный участок памяти более не принадлежащий нашей программе ("висячая/битая" ссылка), работа с `ref` потенциально опасна и приводит к UB. Шаблон `std::deque` этой проблемой не обладает и гарантирует валидность всех ссылок и указателей даже после расширения вместимости.

### Page

Первым шагом для реализации требуемого функционала является 
написание класса `Page`. `Page` представляет собой буфер 
фиксированной вместимости и позволяет производить работу над собой
в двух режимах: режим добавления элементов в начало и режим 
добавления в конец (гарантируется, что, если в начало были
добавлены элементы, то добавления элементов в конец не будет до тех
пор пока буфер снова не станет пустым).

Формально: требуется реализовать шаблонный класс Page,
параметризованный типом хранимых элементов и максимальной
вместимостью (см. например `std::array`). 
Также требуется поддержать, следующие методы (все кроме копирования должно работать за O(1)):

* Конструктор по умолчанию (создает пустую страницу)
* Конструктор копирования, присваивание и деструктор должны работать корректно
* Константную и неконстантную версии оператора []. 
(Неконстантная версия должна позволять изменять полученный элемент)

* Константные и неконстантные версии методов `Front()` и `Back()`
* Метод `Empty()`, возвращающий true, если число добавленных элементов = 0
* Метод `Full()`, возвращающий true, если число добавленных 
элементов совпадает с максимальной вместимостью страницы
* Метод `Size()`, возвращающий число добавленных элементов
* Метод `PushBack(value)`, добавляющий элемент value в конец
страницы (гарантируется, что до вызова этого метода `Size() == 0`,
либо все предыдущие добавления тоже были `PushBack`)
* Аналогичный метод `PushFront(value)` (с аналогичными гарантиями)
* Метод `PopBack()`, удаляет элемент с конца (гарантируется, 
что до вызова этого метода `Size() > 0`, и все предыдущие
 добавления были `PushBack`). Если в результате вызова этого метода
 размер становится равным 0, становится возможным добавление в начало
 * Аналогичный метод `PopFront()`
 * Метод `Clear()`, приводящий страницу в начальное ("чистое") состояние
 
 **Пример.**
 
 `Page<int, 10> page; // создается страница с максимальной вместимостью 10`
 
 `page.PushBack(1); page.PushBack(2); page.PushBack(3); // page == [1, 2, 3]`
 
 `page.Size() // == 3`
 
 `// page.PushFront(4) - так нельзя!`
 
 `page.Clear() // page.Size() == 0`
 
 `page.PushFront(4); page.PushFront(5); page.PushFront(6) // а теперь можно, page == [6, 5, 4]`
 
 **Замечания.**
 
 1) В этой задаче запрещается использование стандартной библиотеки C++. Если нужны какие-либо служебные классы или функции, реализуйте их самостоятельно.
 
 2) Проверка устроена таким образом, что требует от вас жесткого следования принятым (выше) сигнатурам и именованиям сущностей. Если вы реализовали требуемый функционал не полностью или интерфейс отличается от заявленного, в ответ вы получите ошибку компиляции
 
 3) В тесты включены проверки функциональности (методы работают так как требует условие), проверка эффективности реализации (что значит эффективно описано выше), проверка корректности работы с памятью (утечки памяти, обращения к памяти не принадлежащей процессу будут приводить к провалу)
 
 4) Вы можете вдохновляться классом `std::array` из стандартной библиотеки, но заметьте, что он не позволяет добавлять/удалять элементы, так как считает, что в любой момент времени `Size() == Capacity (N)`