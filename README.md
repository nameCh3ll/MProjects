
<p align="center">
  <img src="preview-image/preview.gif">
</p>

___

<h1 align="center"> :bird: Матрицы :bird: </h1>

### Проект в котором я постарался показать большинство своиx знаний в c++
#### :wrench: Features:
* Оптимизация для L1 кэша, для квадратных матриц.
* Поддержка кастомного аллокатора.
* ~~Динамический полиморфизм~~.
* Статический полиморфизм.
* Атрибуты.
* Использование атрибутов.
* Поддержка move семантики.
* SFINAE.
* Beautiful templates.


<h1 align="center"> :deciduous_tree: Детерминизация конечного автомата. :deciduous_tree: </h1>

### Проект в котором я постарался показать все свои знания в c++
#### Input data:
> (1,a,3) (1,a,4) (4,a,4) (4,b,3) (4,b,5) (5,a,3)
### Output data:
> (1,a,34) (34,b,35) (34,a,4) (4,b,35) (4,a,4) (35,a,3)
### Determinization case:
![gallery](preview_image/de-termination.png)


<h1 align="center">  :vhs: Лексический анализатор. :vhs: </h1>

### Input data:
> for(a:=+10.e212;_value)
### Output data(таблица лексем и его идентификатора):
|       Lexem       |       Lexeme type     |
|-------------------|:----------------------|
| for               | ID                    |
| (                 | DLM                   |
| a                 | ID                    |
| :=                | ASGH                  |
| +10.e212          | NM                    |
| ;                 | DLM                   |
| _value            | ID                    |
| )                 | DLM                   |

<h1 align="center"> :children_crossing: Польская нотация. :children_crossing: </h1>

### Input data:
> 123*(1222-12354)*93
### Output data:
1. > 123 1222 12354 - * 93 *
2. > -127338948

___
