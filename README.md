# 2020q3 Homework1 (quiz1)
contributed by < [huang-me](https://github.com/huang-me) > 
###### tags: `embedded_master`

[toc]

# 重新回答[第一周測驗題](https://hackmd.io/@sysprog/sysprog2020-quiz1)
## AA1
1. assert 在 debug 模式下才會執行，所以不應該將任何應該執行的步驟放入 assert() 
2. 在使用 malloc 配置記憶體之後應該要測試有沒有給予成功記憶體再繼續執行其他的動作，所以本題的位置選擇放 assert
## AA2
- 在找到整個 list 的 tail 之後才將新的 node 串接在 list 的後面
    - STEP 1
    ```graphviz
    digraph step1{
            node[shape=box]

            head[shape=plaintext,fontcolor=red]
            indirect[shape=plaintext,fontcolor=blue]
            rankdir=LR
            {
                rankdir = LR
                A[label=1]
                B[label=2]
                C[label=3]
                D[label=new_node]
                NULL1[label=NULL,shape=plaintext]
                NULL2[label=NULL,shape=plaintext]
            }

            {
                rank="same";
                indirect[shape=plaintext,fontcolor=blue]
                indirect->head->A      
            }

            A->B->C->NULL1
            D->NULL2
        }
    ```
    - STEP 2
        ```graphviz
        digraph step2{
                node[shape=box]

                head[shape=plaintext,fontcolor=red]
                indirect[shape=plaintext,fontcolor=blue]
                rankdir=LR
                {
                    rankdir = LR
                    A[label=1]
                    B[label=2]
                    C[label=3]
                    D[label=new_node]
                    NULL1[label=NULL,shape=plaintext]
                    NULL2[label=NULL,shape=plaintext]
                }

                {
                    rank="same";
                    tmp[label="Address of 3's next",shape=plaintext]
                    indirect->tmp->NULL1 
                }

                A->B->C->NULL1
                D->NULL2
            }
        ```
    - STEP 3
        ```graphviz
        digraph step3{
                node[shape=box]

                head[shape=plaintext,fontcolor=red]
                indirect[shape=plaintext,fontcolor=blue]
                rankdir=LR
                {
                    rankdir = LR
                    A[label=1]
                    B[label=2]
                    C[label=3]
                    D[label=new_node]
                    NULL1[label=NULL,shape=plaintext]
                }

                {
                    rank="same";
                    tmp[label="Address of 3's next",shape=plaintext]
                    indirect->tmp->D     
                }
                {
                    rank="same";
                    head->A;
                }

                A->B->C->D->NULL1
                
            }
        ```
## BB1
- 執行完之後要把 node 向後指兩個 node，不過同時不能更動到 head 的指向，所以必須要使用```node=&((*node)->next)->next```
1. ```node = &((*node)->next)->next```
    ```graphviz
    digraph graphname{
            node[shape=box]


            n[shape=plaintext,label="node"]
            m[shape=plaintext,label="head",fontcolor=red]
            rankdir=LR
            {
                rankdir = LR
                A[label=A]
                B[label=B]
                NULL1[label="...",shape=plaintext]
            }
            {
              rank="same";
              m->B
            }
            {
              rank="same";
              ptr[label="ptr to C",shape=plaintext];
              n->ptr->C
            }

            B->A->C->NULL1
        }
    ```
2. ```*node = (*node)->next->next```
    ```graphviz
    digraph graphname{
            node[shape=box]


            n[shape=plaintext,label="node"]
            m[shape=plaintext,label="head",fontcolor=red]
            rankdir=LR
            {
                rankdir = LR
                A[label=A]
                B[label=B]
                NULL1[label="...",shape=plaintext]
            }
            {
              rank="same";
              n->m->C
            }

            B->A->C->NULL1
        }
    ```
## BB2
- 因為在 BB2 的位置需要把 head 調換位置以指向 swap 完之後的 head  
    ==**BEFORE**==
    ```graphviz
    digraph graphname{
            node[shape=box]


            n[shape=plaintext,label="node"]
            m[shape=plaintext,label="head(tmp)"]
            rankdir=LR
            {
                rankdir = LR
                A[label=A]
                B[label=B]
                NULL1[label="...",shape=plaintext]
            }
            {
              rank="same";
              n->m->A
            }

            A->B->C->NULL1
        }
    ```
    ==**AFTER**==
    1. ```*node = (*node)->next```
    ```graphviz
    digraph graphname{
            node[shape=box]


            n[shape=plaintext,label="node"]
            m[shape=plaintext,label="head"]
            rankdir=LR
            {
                rankdir = LR
                A[label=A]
                B[label=B]
                NULL1[label="...",shape=plaintext]
                tmp[label="tmp",shape=plaintext]
            }
            {
              rank="same";
              n->m->B
            }
            {
            rank="same";
            tmp->A
            }

            A->B->C->NULL1
        }
    ```
    2. ```node = &(*node)->next```
    ```graphviz
    digraph graphname{
            node[shape=box]


            n[shape=plaintext,label="node"]
            rankdir=LR
            {
                rankdir = LR
                A[label=A]
                B[label=B]
                NULL1[label="...",shape=plaintext]
                tmp[label="head(tmp)",shape=plaintext]
            }
            {
              rank="same";
              baddr[label="Address of A's next",shape=plaintext]
              n->baddr->B
            }
            {
            rank="same";
            tmp->A
            }

            A->B->C->NULL1
        }
    ```

## CCC
- 將 head->next 接上 cursor 之後再將 cursor 更新到 head 上，再把 head 移動到舊的 list 的頭(next)
    - STEP 1
        ```graphviz
        digraph step1{
                node[shape=box]

                cursor[label="cursor"]
                NULL2[label="NULL",shape=plaintext]
                rankdir=LR
                {
                    rankdir = LR
                    A[label=1]
                    B[label=2]
                    NULL1[label="...",shape=plaintext]
                    tmp[label="head",shape=plaintext]
                }
                {
                rank="same";
                tmp->A
                }
                cursor->NULL2;
                A->B->3->NULL1
            }
        ```
    - STEP 2
        ```graphviz
        digraph step2{
            rankdir=LR;
            node [shape=box];
            NULL1[label="...", shape=plaintext]
            NULL2[label="NULL",shape=plaintext]
            head[label="cursor(head)",shape=plaintext]
            {
                rankdir=LR
                A[label="1"]
                B[label="2"]
                C[label="3"]
            }
            {
                  rank="same";
                  next[shape=plaintext]
                  next -> B
            }
            {
                rank="same"
                head->A
            }
            B->C->NULL1;
            A->NULL2;
        }
        ```
    - STEP 3
        ```graphviz
        digraph step3{
            rankdir=LR;
            node [shape=box];
            NULL1[label="...", shape=plaintext]
            cursor[label="cursor",shape=plaintext]
            {
                rankdir=LR
                A[label="1"]
                B[label="2"]
                C[label="3"]
            }
            {
                  rank="same";
                  next[shape=plaintext,label="head(next)"]
                  next -> B
            }
            {
                rank="same"
                cursor->A
            }
            B->C->NULL1;
            A->B;
        }
        ```

# 利用指標的指標實作某些 function
## swap_pair_ptrtoptr()
```lang=c
void swap_pair_ptrtoptr(node_t **head) {
    for (node_t **node = head; *node && (*node)->next;
        node = &((*node)->next)->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    return;
}
```
## reverse_ptrtoptr()
```lang=c
void reverse_ptrtoptr(node_t **head) {
    node_t *cursor = NULL;
    while (*head) {
        node_t *next = (*head)->next;
        (*head)->next = cursor;
        cursor = *head;
        *head = next;
    }
    *head = cursor;
    return;
}
```
- 不管是 swap_pair 或者 reverse，達成的方法都與前面沒有用 pointer to pointer 相同，改動的地方只有傳入的是 head 的指標的指標，並且處理資料的時候也要小心不要移動到 head 的位置，以免之後讀取資料發生錯誤

# 利用 recursive 方式實作 reverse
```lang=c
node_t *rev_recursive(node_t *head, node_t *pre)
{
    if (head->next)
        head = rev_recursive(head->next, head);

    node_t *tail = head;
    while (tail->next)
        tail = tail->next;

    if (pre) {
        tail->next = pre;
        pre->next = NULL;
    } else
        tail->next = NULL;

    return head;
}
``` 
- 在 main function 直接呼叫 rev_recursive，並且傳入 head 以及 NULL
- recursive 的做法就是先判斷目前的 head 是否為 list 的尾巴，如果不是的話就直接再呼叫自己，並且傳入 head->next 以及 head，最後就會得到新的 head，再從頭找新的 tail 並且將 tail 串接上 pre
:::warning
在寫開發檔案的時候發現更新的 tail 就是 head 自己，所以改寫 code 在進入 function 的時候就先存取好原本的 head，如此即使 list 長度很長就不會受 while 影響執行時間  
```lang=c
node_t *rev_recursive(node_t *head, node_t *pre)
{
    node_t *tail = head;

    if (head->next)
        head = rev_recursive(head->next, head);

    if (pre) {
        tail->next = pre;
        pre->next = NULL;
    } else
        tail->next = NULL;

    return head;
}
```
:::

# 實作 linked-list 版本的 Fisher Yates Shuffle
```lang=c
node_t *fisher_yates(node_t *head)
{
    node_t *tmp = head, *output = NULL;
    int num = 0;
    while (tmp) {
        tmp = tmp->next;
        num++;
    }

    srand(time(NULL));
    for (; num > 0; num--) {
        int randnum = (rand() % num) + 1;
        node_t *pre = NULL;

        tmp = head;
        if (randnum == 1)
            head = head->next;

        for (; randnum > 1; randnum--) {
            pre = tmp;
            tmp = tmp->next;
        }

        if (pre)
            pre->next = tmp->next;

        if (!output) {
            output = tmp;
            tmp->next = NULL;
        } else {
            node_t *tail = output;
            while (tail->next)
                tail = tail->next;
            tail->next = tmp;
            tmp->next = NULL;
        }
    }

    return output;
}
```
- 傳入的 list 因為沒有存取 list 的長度，所以只好先使用一個 while 測量 list 的長度，之後用 for 使得後面處理的程式執行的次數與 list 的長度相同。for 迴圈的內容則是先取一個隨機變數 randnum，再找到目前剩下 list 的第 randnum 個 node 並且將其放到 output list 的頭。

:::warning
- 之後為了不要一直使用 while 找尋 output list 的尾巴，決定多使用一個 pointer 存取 output tail，所以修改程式如下:

```lang=c
node_t *fisher_yates(node_t *head)
{
    node_t *tmp = head, *output = NULL, *tail = NULL;
    int num = 0;
    while (tmp) {
        tmp = tmp->next;
        num++;
    }

    srand(time(NULL));
    for (; num > 0; num--) {
        int randnum = (rand() % num) + 1;
        node_t *pre = NULL;

        tmp = head;
        if (randnum == 1)
            head = head->next;

        for (; randnum > 1; randnum--) {
            pre = tmp;
            tmp = tmp->next;
        }

        if (pre)
            pre->next = tmp->next;

        if (!output) {
            output = tmp;
            tmp->next = NULL;
            tail = output;
        } else {
            tail->next = tmp;
            tmp->next = NULL;
            tail = tail->next;
        }
    }

    return output;
}
```
- 在有一萬個數字的 list 情況下原本的程式需要約0.36秒的時間，不過修改完之後只需要0.13秒，有明顯的差距
:::
