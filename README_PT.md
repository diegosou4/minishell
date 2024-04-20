# Minishell 2024

Bem-vindo ao fascinante mundo do Bash! Nosso projeto é bastante complexo por si só, mas hoje vamos explicar um pouco sobre o que fizemos, o que nos ajudou a alcançar o resultado e, é claro, o caminho que percorremos para chegar lá. Desde já, vale ressaltar que nosso minishell está longe de ser o melhor que você verá, mas o que realmente importa é o aprendizado adquirido ao longo desse processo desafiador.

A comunicação com seu parceiro será fundamental, já que o executor precisa criar uma estrutura que o parser possa entender e trabalhar em paralelo para fornecer a estrutura solicitada. Essa etapa é crucial no projeto: separar as responsabilidades de cada um.

## Execução

Após a conclusão do parse e entrega das estruturas necessárias, o primeiro passo é lidar com o heredoc. Executamos todos os heredocs antes de iniciar a execução, já que os utilizamos com pipes. Em seguida, temos nossa rotina de execução que sempre verifica se é um builtin ou um executável. Vale ressaltar um caso específico: quando temos apenas um comando e ele é um builtin. Porém, vamos focar na rotina de execução geral.

Dentro dessa rotina, verificamos se é necessário criar pipes, ou seja, se há mais de um comando. Criamos um processo filho e, dentro dele, tratamos as estruturas de redirecionamento e seus comandos. É crucial entender que esses passos devem ser realizados dentro do processo filho. Após isso, determinamos de onde leremos e onde escreveremos e então executamos nosso comando. Devemos ter cuidado com os vazamentos de descritores de arquivo ou com o fechamento incorreto de descritores de arquivo em momentos inadequados.

## Builtins

Acredito que o builtin mais complexo de implementar seja o `export`, já que é utilizado em diversos cenários. Optamos por criar uma cópia do ambiente, junto com uma estrutura contendo três tokens diferentes. Isso nos ajuda a exibir o ambiente de forma diferente, mesmo consumindo a mesma estrutura. A parte mais desafiadora foi criar a rotina que verifica se a chave existe e, dependendo do caso, se adicionamos um valor ou apenas concatenamos. Confesso que, devido à complexidade de diversos casos específicos, alguns não foram tratados corretamente. Os outros builtins são mais simples, pois contam com a ajuda de funções externas. Por exemplo, o `cd` já possui uma função para redirecionar para outro local de acordo com o caminho fornecido, o `pwd` é uma função que retorna o diretório atual, e o `exit` requer apenas uma conversão do número fornecido, pois os status de saída variam de 0 a 255.

## Considerações Finais

Na minha opinião, a execução do nosso projeto foi muito boa. Apesar de algumas falhas, conseguimos cumprir o mais importante: comprometimento com o projeto, cumprimento dos prazos definidos e organização. Esses foram os elementos-chave que nos permitiram concluir o projeto com a sensação de missão cumprida.


## Resultado 

![RESULTADO](https://i.imgur.com/0twltqs.png)

### LINKS UTEIS

https://youtu.be/yHDzFRWmLGA?si=WkXmLU5iD3UsIq9r
https://github.com/zstenger93/minishell/blob/master/mindmap.png


Obrigamos a todos, desejamos uma boa sorte :)

diegmore e juan-pma
42 Lisboa
