import subprocess
import csv

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
        print("Введите метод(sp-1,mxv-2,mxm-3),размерность матрицы,количество запусков")
        method=int(input())
        n = int(input())  # Размер матрицы
        num_runs = int(input())
       
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

        with open("./results/csv_files/sp_result.csv", 'a', newline='') as csvfile:  
            writer = csv.writer(csvfile) 
            writer.writerow([n, time])
    elif method==2:
        for i in range(num_runs):
            success = run_mxv(n)
            if success is None:
                break
            time += success

        with open("./results/csv_files/mxv_result.csv", 'a', newline='') as csvfile:  
            writer = csv.writer(csvfile) 
            writer.writerow([n, time])
    else:
        for i in range(num_runs):
            success = run_mxm(n)
            if success is None:
                break
            time += success

        with open("./results/csv_files/mxm_result.csv", 'a', newline='') as csvfile:  
            writer = csv.writer(csvfile) 
            writer.writerow([n, time])
       
