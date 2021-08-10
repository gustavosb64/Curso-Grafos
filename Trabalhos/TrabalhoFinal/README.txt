DESCRIÇÃO DO PROJETO

Uma genealogia pode ser representada por meio de um DAG. Esses DAGS possuem vários vértices fontes e vértices sorvedouros. O número total de vértices é igual ao número de indivíduos na genealogia. Todos os vértices possuem grau de entrada 2 (dois pais) ou zero (pais desconhecidos). Os vértices sorvedouros são aqueles indivíduos sem filhos. Se indivíduo Y é um descendente de indivíduo X , o vértice Y é alcançável por meio de uma busca em profundidade a partir do vértice X . Z é um dos pais do W se e somente se existe uma aresta Z →W .

(i) Quantos vértices são vértices fontes (pais desconhecidos)?
(ii) Quantos vértices são vertices sorvedouros?
(iii) Quais são os vértices sorvedouros tais que ambos pais são descendentes de vértice 1? (DFS)
(iv) Seja d o vetor de distâncias de cada vértice em relação ao vértice 1. Seja X e Y os pais de um dado vértice obtido na parte c. Quais são os vértices na parte (c) tais que a soma d [X] + d [Y] é o mínimo? Caso o vértice 1 seja portador de uma mutação associada com uma doença genética, esses indivíduos na parte (c) possuem um risco maior de serem afetados.
