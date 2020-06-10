# asw

Ассоциативная система - настраиваемый чат-бот с *поддержкой скриптов Python* (в процессе), базами данных SQLite и интерфейсом Qt.

## Сборка и установка

Процесс сборки состоит из двух команд:

```
$ qmake asw.pro
$ make
```

Чтобы установить asw, выполните:

`# make install`

## Описание

### Встроенный поиск выражений-триггеров

asw предоставляет встроенный поиск триггеров в введённых выражениях пользователя. Для ответа на них используются базы данных *.asw.db (SQLite).

Чтобы создать базу данных, откройте `asw > Файл > Менеджер источников` или напишите сообщение `/sm`. В ответном сообщении нажмите `Добавить контейнер |> Создать`, введите любое название источника, выберите файл для сохранения и нажмите `Сохранить`. Для сохранения изменений нажмите `Сохранить и закрыть`.

Содержимое базы данных включает в себя таблицу `sources` с определёнными свойствами, никнеймом источника (в одной базе данных может быть несколько источников) и его UUID, а также сами таблицы источников.

Источник представляет из себя таблицу с тремя столбцами: адрес выражения, само выражение и ссылки от данного выражения на другие. Таким образом, использование баз данных может заключаться в подобном примере:

```
1  |  Привет!      |  1,2
2  |  Здравствуй!  |  1,2
```

Выражения могут ссылаться сами на себя. Выбор между вариантами происходит случайным образом.

Ядро поиска триггеров находится в классе `NLPmodule`. Ядро собирает со всех источников выражения, освобождает от знаков препинания, делает регистронезависимыми, затем ищет их вхождения в пользовательском вводе. Если выражение было найдено, то случайным образом выбирается ответное выражение и добавляется в строку ответа, после чего выводится на экран.

`#TODO: подробно описать механизм NLPmodule`  
`#TODO: реализовать необходимые функции NLPmodule`
