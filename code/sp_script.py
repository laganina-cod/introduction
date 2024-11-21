import subprocess
import csv
import sys

def run_sp(n):
    try:
        result = subprocess.run(["./sp.exe", str(n)], capture_output=True, text=True, check=True)
        return float(result.stdout.strip())
    except subprocess.CalledProcessError as e:
        print(f"Ошибка: {e}")
        return None
    except ValueError:
        print("Ошибка преобразования результата в число.")
        return None

if __name__ == "__main__":
    try:
        num_runs = int(sys.argv[1])
        n = int(sys.argv[2])  # Размер матрицы
    except (ValueError, IndexError):
        print("Ошибка: Необходимо указать два целых числа (число запусков и размер матрицы).")
        exit(1)

    time = 0
    for i in range(num_runs):
        success = run_sp(n)
        if success is None:
            break
        time += success

    with open("sp_result.csv", 'a', newline='') as csvfile: 
        writer = csv.writer(csvfile,delimiter=";")
        writer.writerow((n, time))
   
