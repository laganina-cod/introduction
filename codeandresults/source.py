import subprocess
import csv
import os

def run_sp(n):
    try:
        result = subprocess.run(["./sp/sp.exe", str(n)], capture_output=True, text=True, check=True)
        return float(result.stdout.strip())
    except subprocess.CalledProcessError as e:
        print(f"Ошибка: {e}")
        return None
    except ValueError:
        print("Ошибка преобразования результата в число.")
        return None
        
def run_mxv(n):
    try:
        result = subprocess.run(["./mxv/mxv.exe", str(n)], capture_output=True, text=True, check=True)
        return float(result.stdout.strip())
    except subprocess.CalledProcessError as e:
        print(f"Ошибка: {e}")
        return None
    except ValueError:
        print("Ошибка преобразования результата в число.")
        return None
        

def run_mxm(n):
    try:
        result = subprocess.run(["./mxm/mxm.exe", str(n)], capture_output=True, text=True, check=True)
        return float(result.stdout.strip())
    except subprocess.CalledProcessError as e:
        print(f"Ошибка: {e}")
        return None
    except ValueError:
        print("Ошибка преобразования результата в число.")
        return None

if __name__ == "__main__":
    try:
        print("Введите метод (sp-1, mxv-2, mxm-3), размерность матрицы, количество запусков (через пробел):")
        # Ввод всех значений в одну строку
        input_data = input().strip().split()
        
        # Проверка, что введено ровно три значения
        if len(input_data) != 3:
            raise ValueError("Необходимо ввести ровно три числа.")
        
        # Преобразование введенных данных в целые числа
        method = int(input_data[0])
        n = int(input_data[1])  # Размер матрицы
        num_runs = int(input_data[2])  # Количество запусков
       
    except (ValueError, IndexError):
        print("Ошибка: Необходимо указать три целых числа (метод, размер матрицы, число запусков).")
        exit(1)

    time = 0
    if method==1:
        for i in range(num_runs):
            success = run_sp(n)
            if success is None:
                break
            time += success
        file_path = "./results/output_files/sp_result.csv"
        file_exists = os.path.exists(file_path)
        with open(file_path, 'a', newline='') as csvfile:  
            writer = csv.writer(csvfile) 
            if not file_exists:
                writer.writerow(['Размер матрицы','Количество запусков', 'Время выполнения'])
            writer.writerow([n, num_runs,time])
    elif method==2:
        for i in range(num_runs):
            success = run_mxv(n)
            if success is None:
                break
            time += success
        file_path = "./results/output_files/mxv_result.csv"
        file_exists = os.path.exists(file_path)
        with open(file_path, 'a', newline='') as csvfile:  
            writer = csv.writer(csvfile) 
            if not file_exists:
                writer.writerow(['Размер матрицы','Количество запусков', 'Время выполнения'])
            writer.writerow([n,num_runs,time])
    else:
        for i in range(num_runs):
            success = run_mxm(n)
            if success is None:
                break
            time += success
        file_path = "./results/output_files/mxm_result.csv"
        file_exists = os.path.exists(file_path)
        with open(file_path, 'a', newline='') as csvfile:  
            writer = csv.writer(csvfile) 
            if not file_exists:
                writer.writerow(['Размер матрицы','Количество запусков', 'Время выполнения'])
            writer.writerow([n,num_runs,time])
    
            
       
