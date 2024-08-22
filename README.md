![mygif](https://media1.tenor.com/m/Ky6v0lFLVXwAAAAd/arch-linux-i-use-arch.gif)
___
# :bird: Матрицы :bird: :heavy_minus_sign::heavy_minus_sign::heavy_minus_sign:
### Проект в котором я постарался показать все свои знания в c++
#### Features:
* Оптимизация для L1 кэша, для квадратных матриц.
* Поддержка кастомного аллокатора.
* ~~Динамический полиморфизм~~.
* Статический полиморфизм.
* Использование атрибутов.
* Поддержка move семантики.
* SFINAE.
* Beautiful templates.

___

# :deciduous_tree: Детерминизация конечного автомата. :deciduous_tree:
### Проект в котором я постарался показать все свои знания в c++
#### Input data:
> (1,a,3) (1,a,4) (4,a,4) (4,b,3) (4,b,5) (5,a,3)
### Output data:
> (1,a,34) (34,b,35) (34,a,4) (4,b,35) (4,a,4) (35,a,3)
### Determinization case:
![gallery](preview_image/de-termination.png)

___

# :vhs: Лексический анализатор. :vhs:
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

___

# :children_crossing: Польская нотация. :children_crossing:
### Input data:
> 123*(1222-12354)*93
### Output data:
1. > 123 1222 12354 - * 93 *
2. > -127338948

___
