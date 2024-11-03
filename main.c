

#include "code.h"

int size;

int main()
{
    int doAgain = 0, option = 0;
    unsigned key;
    NODE *tree = NULL;
    int keysize = 0;

    printf("inputs assumed as binary strings.\n i.e. (10000, 10001, 0000)\n");

    printf("Digite o tamanho das chaves binárias: ");
    scanf("%d", &keysize);
    getchar();

    start(&tree);

    do
    {
        printf("Operações:\n1. Inserção\n2. Busca\n3. Remoção\n4. Impressão\nSelecione: ");
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 1:
            printf("Digite a chave: ");
            scanf("%u", &key);

            if ((keysize * keysize) - 1 <= key);
            {
                printf("key is too big, sorry\n");
                getchar();
                break;
            }

            insert(&tree, key);

            printf("valor inserido: %d\n", key);
            break;
        case 2:
            printf("Digite a chave: ");
            scanf("%u", &key);

            NODE *found = search(tree, key);

            if (found != NULL)
            {
                printf("Chave encontrada: %s\n", found->key);
            } else
            {
                printf("Chave não encontrada.\n");
            }
        break;
        case 3:
            printf("Digite a chave: ");
            scanf("%u", &key);
            getchar();

            delete(&tree, key);
            break;
        case 4:
            print(&tree, keysize);
        break;

        default:
            printf("Opção inválida.\n");
            break;
        }

        printf("\nDeseja continuar?\n1. Sim\n 0. Não\nDigite: ");
        scanf("%d", &doAgain);
        getchar();
    } while (doAgain);

    freeTree(tree);

    return 0;
}