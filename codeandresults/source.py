import subprocess
import sys
import os
import csv

def run_sp(n, data_method):
    try:
        result = subprocess.run(["./sp/sp.exe", str(n), str(data_method)], capture_output=True, text=True, check=True)
        return float(result.stdout.strip())
    except subprocess.CalledProcessError as e:
        print(f"Ошибка: {e}")
        return None
    except ValueError:
        print("Ошибка преобразования результата в число.")
        return None

def run_mxv(n, data_method,matrix_storage):
    try:
        if matrix_storage == 0:
            result = subprocess.run(["./mxv/1d_array/mxv_1d.exe", str(n), str(data_method)], capture_output=True, text=True, check=True)
        else:
            result = subprocess.run(["./mxv/2d_array/mxv_2d.exe", str(n), str(data_method)], capture_output=True, text=True, check=True)
        return float(result.stdout.strip())
    except subprocess.CalledProcessError as e:
        print(f"Ошибка: {e}")
        return None
    except ValueError:
        print("Ошибка преобразования результата в число.")
        return None

def run_mxm(n, data_method,matrix_storage):
    try:
        if matrix_storage == 0:
            result = subprocess.run(["./mxm/1d_array/mxm_1d.exe", str(n), str(data_method)], capture_output=True, text=True, check=True)
        else:
            result = subprocess.run(["./mxm/2d_array/mxm_2d.exe", str(n), str(data_method)], capture_output=True, text=True, check=True)
        return float(result.stdout.strip())
    except subprocess.CalledProcessError as e:
        print(f"Ошибка: {e}")
        return None
    except ValueError:
        print("Ошибка преобразования результата в число.")
        return None

def validate_input(method, data_method,matrix_storage):
    """Проверка, что method и data_method находятся в допустимых пределах."""
    if method not in {1, 2, 3}:
        raise ValueError("Недопустимое значение method. Допустимые значения: 1, 2, 3.")
    if data_method not in {1, 2, 3}:
        raise ValueError("Недопустимое значение data_method. Допустимые значения: 1, 2, 3.")
    if matrix_storage not in {0,1}:
        raise ValueError("Недопустимое значение matrix_storage. Допустимые значения: 0,1.")

if __name__ == "__main__":
    try:
        args = sys.argv
        script_name = args[0]
        method = int(args[1])  # Метод
        n = int(args[2])  # Размер матрицы
        num_runs = int(args[3])  # Количество запусков
        data_method = int(args[4])# Метод генерации данных
        matrix_storage=int(args[5])

        # Проверка допустимости значений method и data_method
        validate_input(method, data_method,matrix_storage)

    except (ValueError, IndexError) as e:
        print(f"Ошибка при считывании аргументов командной строки: {e}")
        exit(1)

    time = 0
    try:
        if method == 1:
            for i in range(num_runs):
                success = run_sp(n, data_method)
                if success is None:
                    break
                time += success
            if data_method == 1:
                file_path = "./results/output_files/sp_result_zeros.csv"
            elif data_method == 2:
                file_path = "./results/output_files/sp_result_random.csv"
            elif data_method == 3:
                file_path = "./results/output_files/sp_result_twos.csv"

        elif method == 2:
            for i in range(num_runs):
                success = run_mxv(n, data_method,matrix_storage)
                if success is None:
                    break
                time += success
            if data_method == 1:
                if matrix_storage==0:
                    file_path = "./results/output_files/mxv_1d_result_zeros.csv"
                else:
                    file_path = "./results/output_files/mxv_2d_result_zeros.csv"
            elif data_method == 2:
                if matrix_storage ==0:
                    file_path = "./results/output_files/mxv_1d_result_random.csv"
                else:
                    file_path = "./results/output_files/mxv_2d_result_random.csv"
            elif data_method == 3:
                if matrix_storage==0:
                    file_path = "./results/output_files/mxv_1d_result_twos.csv"
                else:
                    file_path = "./results/output_files/mxv_2d_result_twos.csv"

        elif method == 3:
            for i in range(num_runs):
                success = run_mxm(n, data_method)
                if success is None:
                    break
                time += success
            if data_method == 1:
                if matrix_storage==0:
                    file_path = "./results/output_files/mxm_1d_result_zeros.csv"
                else:
                    file_path = "./results/output_files/mxm_2d_result_zeros.csv"
            elif data_method == 2:
                if matrix_storage==0:
                    file_path = "./results/output_files/mxm_1d_result_random.csv"
                else:
                    file_path = "./results/output_files/mxm_2d_result_random.csv"
            elif data_method == 3:
                if matrix_storage==0:
                    file_path = "./results/output_files/mxm_1d_result_twos.csv"
                else:
                    file_path = "./results/output_files/mxm_2d_result_twos.csv"

        # Запись результатов в файл
        file_exists = os.path.exists(file_path)
        with open(file_path, 'a', newline='') as csvfile:
            writer = csv.writer(csvfile)
            if not file_exists:
                writer.writerow(['Размер матрицы', 'Количество запусков', 'Время выполнения'])
            writer.writerow([n, num_runs, time])

    except Exception as e:
        print(f"Ошибка во время выполнения программы: {e}")
        exit(1)