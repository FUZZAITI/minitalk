*Este projeto foi criado como parte do curriculo da 42 por sdelmond*

## Descricao
O `fractol` e um pequeno explorador de fractais usando a MiniLibX. Ele renderiza os conjuntos de Mandelbrot e Julia, permitindo aproximar/afastar com a roda do mouse e testar diferentes parametros para o Julia via linha de comando.

## 1. A Matemática

Assim como Mandelbrot, o conjunto de Julia também é um conjunto de **números complexos** gerado por uma fórmula de iteração. A fórmula é idêntica:

- `Z_{n+1} = Z_n^2 + C`

A diferença crucial está em como `Z` e `C` são definidos:

- **Para Mandelbrot**:
    - `Z` sempre começa em `0` (`Z_0 = 0`).
    - `C` é o número complexo correspondente à coordenada `(x, y)` de **cada pixel**.

- **Para Julia**:
    - `C` é um **número complexo constante** para a imagem inteira. Ele não muda de pixel para pixel. Esse `C` é o que define "qual" conjunto de Julia estamos vendo.
    - `Z` começa com o valor do número complexo correspondente à coordenada `(x, y)` de **cada pixel**.

Em resumo:
- No Mandelbrot, você testa muitos `C`s e começa `Z` do zero.
- No Julia, você escolhe **um** `C` e testa muitos `Z`s iniciais.

**A condição de escape** é a mesma: se em algum momento o módulo de `Z` (`|Z|`) exceder 2, o ponto é considerado fora do conjunto.

# Teste de Mesa Visual: Fractal de Julia

Este documento demonstra o algoritmo do "tempo de escape" do Julia em ação. Usaremos uma constante `C` e dois pontos `Z` iniciais diferentes para ver como a sequência se comporta.

-   **Constante `C` escolhida:** `C = -0.8 (cr) + 0.156 (ci)`
-   **`max_iter` (máximo de iterações):** `10` para simplificar.

A fórmula-chave é a mesma do Mandelbrot: `Z_{n+1} = Z_n^2 + C`. A diferença é que `C` é fixo e `Z` começa no ponto do pixel.

**Condição de escape:** `zr^2 + zi^2 > 4`

---

## Exemplo 1: Um Ponto DENTRO do Conjunto (Provavelmente)

Vamos testar um ponto `Z` inicial que está próximo da origem.
- **`Z_0 = 0.2 (zr) + 0.1 (zi)`**

**Objetivo:** Ver se o valor de `Z` permanece pequeno e não "escapa".

**Tabela de Iterações:** (`cr` = -0.8, `ci` = 0.156)

| Iteração (i) | `zr` (inicial) | `zi` (inicial) | `zr_new = zr²-zi²+cr` | `zi_new = 2*zr*zi+ci` | `zr²+zi² > 4`? | `Z` (final) |
|:------------:|:--------------:|:--------------:|:-------------------------:|:-----------------------:|:---------------:|:----------------------:|
| **0** | `0.2` | `0.1` | 0.2²-0.1²-0.8 = **-0.77** | 2*(0.2*0.1)+0.156 = **0.196** | `0.2²+0.1²=0.05`. Não. | `(-0.77, 0.196)` |
| **1** | `-0.77` | `0.196` | (-0.77)²-0.196²-0.8 = **-0.245** | 2*(-0.77)*0.196+0.156 = **-0.146**| `(-0.77)²+0.196²=0.63`. Não.| `(-0.245, -0.146)`|
| **2** | `-0.245`| `-0.146`| (-0.245)²-(-0.146)²-0.8 = **-0.761**| 2*(-0.245)*(-0.146)+0.156 = **0.227**| `(-0.245)²+(-0.146)²=0.08`.Não| `(-0.761, 0.227)`|
| **...** | ... | ... | ... | ... | ... | ... |
| **9** | ... | ... | (continua pequeno) | (continua pequeno) | Não. | ... |
| **10**| ... | ... | (loop termina) | (loop termina) | Não. | ... |

**Conclusão para o Ponto 1:**
A condição de escape nunca foi atingida. O loop completou as `10` iterações. A função `julia_iters` retornaria `10`. O programa colore este pixel com a cor "interior" (geralmente preto).

---

## Exemplo 2: Um Ponto FORA do Conjunto

Agora, vamos testar um ponto `Z` inicial mais distante.
- **`Z_0 = 1.5 (zr) + 1.5 (zi)`**

**Objetivo:** Ver como e quando o valor de `Z` "escapa" (cresce rapidamente).

**Tabela de Iterações:** (`cr` = -0.8, `ci` = 0.156)

| Iteração (i) | `zr` (inicial) | `zi` (inicial) | `zr_new = zr²-zi²+cr` | `zi_new = 2*zr*zi+ci` | `zr²+zi² > 4`? | `Z` (final) |
|:------------:|:--------------:|:--------------:|:-------------------------:|:-----------------------:|:----------------:|:--------------------:|
| **0** | `1.5` | `1.5` | 1.5²-1.5²-0.8 = **-0.8** | 2*(1.5*1.5)+0.156 = **4.656** | `1.5²+1.5²=4.5`. **SIM!**| `(-0.8, 4.656)` |

**Conclusão para o Ponto 2:**
Já na **primeira verificação** (iteração `i = 0`), o valor de `|Z|^2` era `4.5`, que é maior que `4`. A condição de escape foi atingida imediatamente. O loop é interrompido (`break`).

A função `julia_iters` retornaria o valor atual de `i`, que é `0`. O programa usa esse valor para escolher uma cor, indicando que o ponto está fora do conjunto e escapou muito rapidamente.

---
## Instrucoes
### Compilar
- `make`

### Executar
- Mandelbrot: `./fractol mandelbrot`
- Julia (padrao): `./fractol julia`
- Julia com parametros: `./fractol julia <re> <im>`
  - Exemplo: `./fractol julia -0.7 0.2701`

### Limpar
- `make clean` (objetos)
- `make fclean` (objetos + binario)
- `make re` (recompila tudo)

## Recursos
- Wikipedia: Fractal - https://en.wikipedia.org/wiki/Fractal
- Wikipedia: Mandelbrot set - https://en.wikipedia.org/wiki/Mandelbrot_set
- Wikipedia: Julia set - https://en.wikipedia.org/wiki/Julia_set
- Documentacao MiniLibX (Linux): [minilibx-linux/README.md](minilibx-linux/README.md)

### Uso de IA
- Foi usada IA (GitHub Copilot/Chat) para: revisar requisitos do subject, apontar itens de conformidade (README/nome do binario/hooks) e sugerir ajustes pontuais (expose hook, cleanup no Linux).
