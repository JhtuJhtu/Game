# Game

Небольшая игра, созданная для проверки моих умений писать код.

## Описание

Игра написана на C++ с применением библиотеки SFML. Для разработки была использована IDE Microsoft Visual Studio. Тайлсет был взят из <https://github.com/I-am-Erk/CDDA-Tilesets>

Цель - пройти 3 этажа. Каждый этаж сосотоит из 6 комнат: стартовая, финальная и 4 обычных. Расположение комнат и их наполнение (частично) генерируется с помощью генератора псевдослучайных чисел. Здоровье полностью востанавливается после перехода на следующий этаж.

![preview1](Game/images/preview1)

![preview2](Game/images/preview2)

## Управление

Стрелки - передвижение;

"1", "2" - прицеливание оружием;

"Esc" - выход из режима прицеливания;

"Enter" - В режиме прицеливания - использование оружия, в режиме движения - конец хода.
