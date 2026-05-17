#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    int arr_time;
    int type; // 业务所需周期：1, 2, 3
} Customer;

int finish_times[10000]; // 正在接受服务的客户完成时间
int num_serving = 0;     // 正在接受服务的客户数量

int main()
{
    int T;
    if (scanf("%d", &T) != 1)
        return 0;

    int *arr_counts = (int *)malloc(T * sizeof(int));
    int total_cust = 0;
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &arr_counts[i]);
        total_cust += arr_counts[i];
    }

    Customer *q = (Customer *)malloc(total_cust * sizeof(Customer));
    int q_head = 0, q_tail = 0;

    int idx = 0;
    Customer *input_custs = (Customer *)malloc(total_cust * sizeof(Customer));
    for (int i = 0; i < T; i++)
    {
        for (int j = 0; j < arr_counts[i]; j++)
        {
            input_custs[idx].id = idx + 1;
            input_custs[idx].arr_time = i + 1;
            scanf("%d", &input_custs[idx].type);
            idx++;
        }
    }

    int current_t = 1;
    int input_idx = 0;
    int w_max = 3; // 初始对私窗口数量为3
    int finished_total = 0;

    while (finished_total < total_cust)
    {
        // 1. 周期开始时，检查并处理已完成服务的客户
        int new_num_serving = 0;
        for (int i = 0; i < num_serving; i++)
        {
            if (finish_times[i] > current_t)
            {
                finish_times[new_num_serving++] = finish_times[i];
            }
            else
            {
                finished_total++; // 在当前周期（含之前）已完成
            }
        }
        num_serving = new_num_serving;

        // 2. 将新到达的客户加入等待队列
        if (current_t <= T)
        {
            int arr = arr_counts[current_t - 1];
            for (int i = 0; i < arr; i++)
            {
                q[q_tail++] = input_custs[input_idx++];
            }
        }

        int queue_length = q_tail - q_head;

        // 3. 判断是否需要增加服务窗口（仅在有客户到达的周期内进行策略调整）
        if (current_t <= T)
        {
            // 如果增加一个窗口就能使平均小于7，则增加；继续直到 < 7 或达到上限5
            while (w_max < 5 && queue_length >= 7 * w_max)
            {
                w_max++;
            }
        }

        // 4. 计算当前空闲窗口数量
        int free_win = w_max - num_serving;
        if (free_win < 0)
            free_win = 0;

        // 5. 将等待队列客户分配至空闲窗口
        while (free_win > 0 && q_head < q_tail)
        {
            Customer c = q[q_head++];

            // 记录该客户的完成时间
            finish_times[num_serving++] = current_t + c.type;
            free_win--;
            queue_length = q_tail - q_head; // 更新排队人数

            // 客户开始接受服务，输出等待周期数
            printf("%d : %d\n", c.id, current_t - c.arr_time);

            // 每当有客户去接受服务（等待排队人数减少），马上判断是否可以减少增加的窗口
            if (w_max > 3 && queue_length < 7 * w_max)
            {
                w_max--;
            }
        }

        current_t++; // 进入下一个时间周期
    }

    free(arr_counts);
    free(q);
    free(input_custs);
    return 0;
}
