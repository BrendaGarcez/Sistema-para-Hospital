# Sistema de Registro e Busca de Pacientes em um Hospital
Programado por: Brenda Amanda da Silva Garcez e Nicole Lousie Matias Jamuchewski
Este projeto é um sistema de registro de pacientes para um hospital, desenvolvido em C como parte da disciplina de Estrutura de Dados II do curso de Ciência da Computação na Universidade Tecnológica Federal do Paraná. O sistema visa resolver problemas de gerenciamento de dados de pacientes, proporcionando uma busca rápida e eficiente através de uma Árvore Binária de Pesquisa (ABP).

## Objetivo

O objetivo do projeto é informatizar o registro de pacientes de um hospital, facilitando a organização, inserção, busca, remoção e listagem de pacientes com persistência de dados em arquivos. O sistema permite a organização dos registros por ID ou nome dos pacientes, conforme escolha do usuário.

## Funcionalidades

- **Carregamento de Dados**: Importa os dados dos pacientes a partir de um arquivo de texto ao iniciar a aplicação.
- **Cadastro de Pacientes**: Insere novos pacientes com ID único, nome, idade e condição médica, garantindo a integridade dos dados (sem duplicidades).
- **Critério de Ordenação Personalizado**: Organiza a árvore binária de pesquisa por ID ou nome.
- **Busca de Pacientes**: Permite a busca por ID ou nome, dependendo do critério de ordenação.
- **Remoção de Pacientes**: Exclui um paciente com base no ID ou nome.
- **Listagem de Pacientes**: Exibe todos os pacientes em ordem crescente de acordo com o critério de ordenação.
- **Persistência dos Dados**: Salva todas as alterações em um arquivo de texto ao final da execução.
- **Contagem de Pacientes**: Exibe o total de pacientes cadastrados.
- **Gerenciamento de Memória**: Libera a memória alocada dinamicamente ao finalizar o programa.

## Estrutura de Dados

Cada paciente é representado como um nó na Árvore Binária de Pesquisa, onde a chave do nó pode ser o ID ou o nome do paciente, dependendo do critério escolhido. O sistema manipula os nós usando ponteiros para otimizar o uso de memória e garantir uma busca eficiente.

## Requisitos Técnicos

- **Linguagem**: C
- **Entrada de Dados**: Arquivo de texto
- **Persistência**: Arquivo de saída atualizado com os dados dos pacientes ao final da execução.

## Como Usar

1. Compile o código utilizando um compilador C.
2. Execute o programa e escolha o critério de ordenação.
3. Realize as operações de inserção, busca, remoção e listagem conforme desejado.
4. As alterações serão salvas automaticamente em um arquivo de texto ao final da execução.
