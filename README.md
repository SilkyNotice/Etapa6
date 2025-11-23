# Sistema de Caixa em C

Este projeto é um sistema simples de **caixa de mercado/loja**, feito em C, com menu interativo no terminal.  
Ele permite cadastrar produtos, calcular o total da compra e emitir uma “nota fiscal” com opção de desconto.

---

## 🧾 O que o sistema faz

- Exibe um **menu interativo** usando as setas ↑ e ↓ do teclado.
- Permite **adicionar produtos** com:
  - Nome
  - Preço
  - Quantidade
- Calcula o **total da compra** somando todos os produtos registrados.
- Emite uma **nota fiscal** listando:
  - Número do item
  - Nome do produto
  - Quantidade
  - Preço unitário
  - Subtotal de cada produto
- Dá opção de **aplicar um desconto percentual** sobre o total (0% a 100%).

---

## 🧱 Estrutura do código

- `struct Produto`  
  Guarda as informações de cada produto:
  ```c
  struct Produto {
      char nome[50];
      float preco;
      int quantidade;
  };

