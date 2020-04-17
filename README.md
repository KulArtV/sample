### Занятие 1. Базовые понятия. Сортировки. Деревья поиска.

В этом занятии мы с вами рассмотрим классификацию задач, из алгоритмов поговорим про сортировки, а также посмотрим, как устроены ассоциативные контейнеры STL.

## Базовые понятия

В общем задачи можно разбить на несколько типов. Для начала разобьем их на задачи с предподсчетом и без него. Таким образом, асимптотически время решение задачи почти всегда разбивается на такую формулу: *O(g(n_1, ..., n_m) + k * f(n_1, ..., n_m))*, где *n_1, ..., n_m* - параметры задачи,  функция *g* отвечает за предподсчет, а *f* за время ответа на один запрос.

В общем, основные асимтотики вам более чем знакомы: *O(logN), O(N)* и их степени, произведения и линейные комбинации. Но тут важно понимать, что в таком определении точного понимания времени работы алгоритма нет. Всего лишь гарантируется, что функция решения растет не быстрее какой-то _константы_ (а она может быть очень большой), умноженной на функцию внутри *O*-большого. И когда вы искренне уверены, что алгоритм асимптотически корректен, но вердикт *TL*, нужно задуматься о том, как уменьшить эту самую _константу_. Об этом мы будем говорить редко, так как это вопрос больше к спортивным программистам.

Сказанное выше в общем корректно для статических систем. То есть состояние системы, однажды рассчитанное на фазе предподсчета, меняться не будет. Иначе задача динамическая и стоит также подумать, как быстро перестраивать систему.

Для примера, рассмотрим задачу *RMQ* (Range Min Query) или поиск минимума на подотрезке. Решать мы ее сейчас не будем, но просто посмотрим разные вариации и определимся с понятиями. Собственно задача: есть массив целых чисел, нужно уметь находить минимум на подотрезке массива. Задача будет статической, если нет запросов изменения элементов исходного массива, иначе она уже динамическая. Предлагаю вам подумать, за сколько бы хотелось отвечать на запрос минимума и какой по времени  предподсчет нас бы устроил.

Способов у решения задачи *RMQ* очень много, для которой было придумано множество структур данных, про которые вы будете говорить в третьем семестре.

Сразу же заметим, что как правило, если в задаче дано ограничение на величину порядка 3 * 10^5, то ее решение должно быть не более, чем за *O(NlogN)*. В случае если ограничение до 7-8 тысяч, то  сложность решения квадратическая. Также можно оценить вклад логарифма в асимптотике степенью ограничения. Это достаточно тривиальное знание позволяет вам осознать временную сложность алгоритма решения и отсечь достаточно быстро из множества известных вам алгоритмов те, что работают долго. Таким образом, по ограничениям, как правило, понятно, какую сложность от вас хотят на стадиях предподсчета и ответа на запрос.

## Сортировки

Задача сортировки на самом деле может быть решена двумя способами: с использованием оператора сравнения и без него. Есть теорема, которая заключается в том, что если сортировка использует оператор сравнения, то ее асимптотическая сложность не менее *O(NlogN * G)*, где N - размер  массива, который надо отсортировать, а *G* - функция, которая отвечает за время одной операции  сравнения. Например, сравнивать массив строк дольше, чем массив чисел того же размера.

Еще сортировки могут быть стабильными или нет. Сортировка стабильна, если она не будет менять  местами равные величины (предлагаю вам придумать простой способ проверки сортировки на стабильность). Сразу отметим, что все рассматриваемые в курсе ранее сортировки нестабильны, хотя это классное свойство. Предлагаю быстро вспомнить известные вам сортировки и действительно убедиться в их нестабильности, а также вспомнить, какие у них худшие случаи работы по времени.

* Быстрая сортировка - нестабильна, в худшем случае квадратична, но имеет малую константу и не требует дополнительной памяти.
* Heap Sort - нестабильна, не имеет худшего случая, имеет среднюю константу и не требует дополнительной памяти.

Теперь рассмотрим сортировку слиянием. Для этого нужно в принципе ознакомиться с идеей *Divide and  Conquer* или *Разделяй и властвуй*. Суть в том, что вы рекурсивно разбиваете задачу на малые подзадачи, а потом сливаете решения меньших подзадач в решение исходной задачи.

В сортировке слиянием используется процедура `Merge`, суть которой слить два отсортированных массива в один отсортированный. Подробнее про саму сортировку можно [прочесть тут](https://neerc.ifmo.ru/wiki/index.php?title=Сортировка_слиянием). Я же хочу предложить вам несколько забавных задач на процедуру слияния:

1. Вам дано *K* отсортированных списков длины *N*. Ваша задача - слить их все в один большой отсортирванный список за *O(N * K * logK)* времени и памяти.
2. Вам дан огромный массив, который не влезает целиком в память. Ваша цель - вывести *K* первых по возрастанию элементов массива.
3. Данная задача к теме не очень относится, но позволит применить идею первой задачи.
Есть три массива чисел, нам надо выбрать из каждого из них по одному числу *x, y, z* таким образом, чтобы *(x - y)^2 + (y - z)^2 + (z - x)^2* было минимальным.

Далее рекомендую прочитать про [поразрядные сортировки](https://neerc.ifmo.ru/wiki/index.php?title=Цифровая_сортировка) (это необязательно, но знать полезно)

## Деревья поиска

Дерево поиска - структура данных, которая умеет:
* `void Delete(T key)` - удалить элемент с ключом `key`
* `void Insert(T key)` - вставить элемент с ключом `key`
* `bool Exists(T key)` - проверить, есть ли элемент с ключом `key` в дереве

Рассмотрим с вами бинарное дерево поиска (дерево бинарное, если у каждой вершины не более двух детей). Для удобства работы с такими деревьями будем по умолчанию считать, что если в узле записан ключ `key`, то во всех узлах левого поддерева элементы строго меньше `key`, а во всех узлах правого - не меньше. Тогда нетрудно догадаться, как устроены вставка, удаление и поиск в таком дереве. Заметим, что тогда все операции работают за *O(h)*, где *h* - высота дерева.

Придумайте алгоритм, который выведет в таком дереве элементы в отсортированном порядке.

Заметим, что если вставлять и удалять элементы _наивно_, то оно может выродиться в список, что в общем делает стоимость всех операций линейной от числа элементов, что может привести к мысли "А зачем мы вообще придумываем деревья поиска". И тут мы приходим к понятию сбалансированности дерева. Существует много определений сбалансированности, но я приведу такое: дерево *T* сбалансировано, если для поддеревьев верно, что отношение большей высоты к меньшей не превосходит заранее фиксированной константы (которая не зависит от входных данных и их размера).

Есть огромное множество сбалансированных деревьев: *AVL-дерево*, *декартово дерево* и *красно-черное дерево* - наиболее часто встречающиеся реализации. Для общего ознакомления можно также прочитать про *BTree*, *2-3 дерево* и огромное множество других. 

Теперь поговорим про ассоциативные контейнеры STL. Они бывают упорядоченные и неупорядоченные, а также позволяют хранить несколько одинаковых элементов или нет.

1. `std::set` - одна из реализаций множества. Его суть в том, чтобы упорядоченно хранить элементы, при этом каждый из них хранится ровно один раз. Все операции делаются за логарифм. Реализовано как *красно-черное* дерево внутри.

2. `std::multiset` - как `std::set`, только позволяет повторы элементов внутри себя. Все операции делаются за логарифм. Реализовано как *красно-черное* дерево внутри.

3. `std::map` - позволяет хранить отображение из множества ключей в множество значений, то есть как массив, но индексы не чиселки, а произвольные объекты. Опять же все ключи уникальны, так как иначе подумайте, что произойдет.

4. `std::multimap` - как `std::map`, но при этом позволяет неуникальные ключи:)

Как можно догадаться, `std::set` реализует функциональность дерева поиска. 

Ваши вопросы, пожелания, предложения.



