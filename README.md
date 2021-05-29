# Лабораторная работа

## Задание
В компании недавно был релиз новой версии продукта. За несколько часов до релиза один разработчик
выпонил блокирующую задачу и спас релиз (не спрашивайте как), но качество этого кода оставляет желать лучшего.

Чтобы закрыть техдолг, необходимо кардинально улучшить качество кода.

В файле [sources/source.cpp](sources/histogram.cpp) лежит код, который необходимо улучшить.
*Не обращайте внимание на бессмысленность кода*.

#### Требуется:
1. Реализуйте юнит-тестирование класса `PageContainer`:
  * удостоверьтесь, что в случае исключения, члены класса не модифицируются
  * удостоверьтесь, что метод `AsyncSend` будет вызывается всегда, когда изменяются данные при загрузке
  * удостоверьтесь, что метод `AsyncSend` будет вызывается всегда, при пропуске элемента
  * удостоверьтесь, что в случае некорректных данных в `istream` процесс загрузки `Load` будет работать корректно (пропускать данные)
1. Реализуйте юнит-тестирование класса `UsedMemory`:
  * удостоверьтесь, что класс `UsedMemory` корректно подсчитывает используемую память
1. Произведите рефакторинг существующего кода, без изменения логики программы
1. Перейдите на использование `boost::program_options`
1. Добавьте возможность задавать параметр `threshold` из командной строки
1. Добавьте класс `Histogram`:
  * который сохраняет в память среднее значение `score` всех загруженных объектов в методах `Load` и `Reload`
  * который сохраняет в память сколько было отброшено элементов по параметру `threshold` за каждый вызов методов `Load` и `Reload` (каждый новый вызов метода `Load`/`Reload` создает новое значение)
1. Нельзя использовать сторонние библиотеки кроме `boost::program_options`


#### Рекомендации
1. Подойдите критично к существующему коду
1. Используйте [gtest::mock](https://github.com/google/googletest/blob/master/googlemock/docs/cook_book.md)
1. Не пугайтесь, если придется использовать динамический полиморфизм при рефакторинге или при тестировании
1. Ниже есть некоторые мысли что можно улучшить, но хорошему студенту сначала рекомендуется выпонить работу самостоятельно, а затем свериться с подсказками.


<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>

#### Что можно улучшить
Список может быть не полным! Скорее всего вам придет в голову лучшие решения, чем ниже приведенные.

* Класс `Log` сделайте через синглтон
* Используйте шаблон "Наблюдатель":
  * `PageContainer` - уведовляет о событиях: `OnDataLoaded`, `OnRawDataLoaded`, `OnSkipped`
  * Классы `UsedMemory`, `StatSender` - наблюдателями
* метод `AsyncSend` стоит сделать виртуальным, чтобы проверить что он вызывается в нужных местах
* Класс `Histogram` так же следует реализовать как наблюдателя класса `PageContainer`
* проверьте в юнит-тестировании случаи когда `istream` закрыт на чтение, когда пустые данные, когда не поддерживаемые данные