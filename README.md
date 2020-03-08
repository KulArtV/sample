В этой задаче вам нужно реализовать класс динамического массива. Проблема стековых и выделяемых в куче массивов заключается в том, что они имеют фиксированный размер и не умеют автоматически расширяться при необходимости (в отличие, например, от `list` в Python). Кроме того, при выделении памяти в динамической области возникает потребность в ручном отслеживании возможных утечек памяти, что накладывает дополнительные сложности на процесс разработки.

Эти проблемы можно обойти, используя ООП функционал C++. В частности, механизм инкапсуляции позволяет реализовать методы добавления элементов, при вызове которых массив будет автоматически расширяться, создавая иллюзию неограниченного контейнера. А механизмы работы с ресурсами гарантируют своевременное выделение и очищение памяти. 

Здесь естественным образом возникает разделение понятий "размера" массива (size) и его "вместимости" (capacity). С++ в каждый момент времени позволяет поддерживать массивы конечной вместимости, при этом фактический размер (количество добавленных элементов) может быть меньше этого значения. *Почему бы постоянно не поддерживать равенство между этими величинами?* - это не эффективно. Допустим, мы добавляем элементы по одному. Тогда при каждом обновлении будет происходить перевыделение исходной памяти с последующим копированием всех старых элементов в новый буфер. Легко видеть, что в этом случае общее число копирований будет квадратичным образом зависеть от числа добавленных элементов. Оказыватся, что, если при каждом переполнении массива увеличивать его вместимость в константное число раз, то можно добиться линейной зависимости числа операций над массивом от числа добавляемых элементов (https://en.wikipedia.org/wiki/Dynamic_array#Geometric_expansion_and_amortized_cost). В вашем решении будет проверяться корректность работы данной схемы при множителе равном 2 (то есть, если фактический размер изменяется так: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> ..., то вместимость меняется следующим образом: 0 -> 1 -> 2 -> 4 -> 4 -> 8 -> ...).

От вас требуется реализовать шаблонный класс `Vector` с единственным шаблонным параметром - типом хранящихся элементов. Класс должен поддерживать следующий функционал:
* Конструктор по умолчанию - создает пустой массив
* Явный конструктор от числа - создает массив заданного размера
* Конструктор, принимющий `size` и `value` (именно в этом порядке) - содает массив длины `size`, заполненный элементами `value`
* Правило "трех"
* метод `Clear()` - устанавливает размер в 0, деаллокации выделенной памяти при этом НЕ происходит
* метод `PushBack(value)` - добавляет элемент value в конец массива
* метод `PopBack()` - удаляет последний элемент
* метод `Resize(new_size)` - изменяет размер на `new_size`. Если вместимость не позволяет хранить столько элементов, то выделяется новый буфер с вместимостью `new_size`.
* метод `Resize(new_size, value)` - то же, что и `Resize(new_size)`, но в случае `new_size > size` заполняет недостающие элементы значением `value`.
* метод `Reserve(new_cap)` - изменяет вместимость на `max(cap, текущая вместимость)`. Размер при этом не изменяется.
* метод `ShrinkToFit()` - уменьшает `capacity` до `size`
* метод `Swap(other)` - обменивает содержимое с другим массивом (`other` имеет тип `Vector`)
* Константный и неконстантный оператор доступа по индексу []. Неконстантный должен позволять изменять полученный элемент (`a[1] = 5`);
* Методы `Front() и Back()` - доступ к первому и последнему элементам (тоже по две версии).
* метод `Empty()` - `true`, если массив пуст (размер 0)
* метод `Size()` - возвращает размер
* метод `Capacity()` - возвращает вместимость
* Операторы сравнения (`<`, `>`, `<=`, `>=`, `==`, `!=`), задающие лексикографический порядок

**Замечания.** 

1) В этой задаче запрещается использование стандартной библиотеки C++. Если нужны какие-либо служебные классы или функции, реализуйте их самостоятельно.

2) Проверка устроена таким образом, что требует от вас жесткого следования принятым (выше) сигнатурам и именованиям сущностей (то есть никакие `MyVector`, `__vector_`, `push_back`, `superSolver3000` не пройдут). Если вы реализовали требуемый функционал не полностью или интерфейс отличается от заявленного, в ответ вы получите ошибку компиляции

3) В тесты включены проверки функциональности (методы работают так как требует условие), проверка эффективности реализации (что значит эффективно описано выше), проверка корректности работы с памятью (утечки памяти, обращения к памяти не принадлежащей процессу будут приводить к провалу)
