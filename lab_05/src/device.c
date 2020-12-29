#include "../inc/device.h"

double get_time(const int left_limit, const int right_limit)
{    
    double rnd = (double)rand() / (double)RAND_MAX;

    return (right_limit - left_limit) * rnd + left_limit;
}

void vector_model(vector_q *queue,
                const int t1_in, const int t1_out,
                const int t2_in, const int t2_out)
{
    vector_init(queue);

    int in_tasks = 0;
    int out_tasks = 0;
    int calls = 0;
    int calls_1 = 1;
    int c1_counter = 0;

    double arrival_time = 0;
    double service_time = 0;
    double hold_time = 0;
 
    double time_in = get_time(t1_in, t1_out);
    double time_out = -1;
 
    int overall_len = 0;
 
    while (out_tasks != 1000)
    {
        if (time_out < 0 || time_in < time_out)
        {
            if (time_out < 0)
                hold_time += time_in;
 
            time_out -= time_in;
            time_in = get_time(t1_in, t1_out);
            arrival_time += time_in;
 
            vpush(queue, 1);
 
            in_tasks++;
 
            if (time_out < 0 && VECTOR_SIZE)
            {
                vpop(queue);
                time_out = get_time(t2_in, t2_out);
                service_time += time_out;
            }
        }
        else
        {
            time_in -= time_out;
            time_out = 0;

            calls++;
 
            calls_1++;
            if (VECTOR_SIZE > 1)
                c1_counter++;

    
            overall_len += VECTOR_SIZE;
            out_tasks++;
            
            if (out_tasks % 100 == 0)
            {
                printf(
                        "\n_____\n"
                        "Обработано %d заявок\n"
                        "Длина очереди: %zu\n"
                        "Средняя длина очереди: %d\n"
                        "_____\n",
                        out_tasks, VECTOR_SIZE, overall_len / out_tasks
                        );
            }
            if (vempty(queue) == QUEUE_EMPTY)
            {
                time_out = -1;
            }
            else
            {
                vpop(queue);
                time_out = get_time(t2_in, t2_out);
                service_time += time_out;
            }
        }
    }

    double expected_arr_time = (t1_in + t1_out) / 2.0 * calls;
    double expected_serv_time = (t2_in + t2_out) / 2.0 * calls;

    double delta_arr = fabs(arrival_time - expected_arr_time) / expected_arr_time * 100;
    double delta_serv = fabs(service_time - expected_serv_time) / expected_serv_time * 100;

    printf(
           "Время прихода: %lf (ожидаемое время прихода: %lf, погрешность: %lf%%)\n"
           "Время работы автомата: %lf (ожидаемое время работы автомата: %lf, погрешность: %lf%%)\n"
           "Число вошедших заявок: %d\n"
           "Число вышедших заявок: %d\n"
           "Число срабатываний автомата: %d\n"
           "Время простоя автомата: %lf\n"
           "Количество обращений заявок второго типа: %d\n",
           arrival_time, expected_arr_time, delta_arr, 
           service_time, expected_serv_time, delta_serv,
           in_tasks, out_tasks,
           calls, hold_time,
           calls_1 - c1_counter
           );
}
