import pandas as pd
import os

def csv_to_xls(csv_file, xls_file):
    try:
        # Проверка существования CSV-файла
        if not os.path.exists(csv_file):
            raise FileNotFoundError(f"Файл '{csv_file}' не найден.")
        
        # Чтение CSV-файла с указанием типов данных и кодировки
        df = pd.read_csv(
            csv_file,
            dtype={"Размер матрицы": int, "Количество запусков": int, "Время выполнения": float},
            encoding='windows-1251',
            decimal="."
        )
        
        # Запись данных в XLS-файл
        df.to_excel(xls_file, index=False, engine='openpyxl')
        
        print(f"Файл '{csv_file}' успешно преобразован в '{xls_file}'.")
    except Exception as e:
        print(f"Ошибка при преобразовании файла: {e}")
        print(f"Тип ошибки: {type(e).__name__}")

if __name__ == "__main__":
    # Укажите пути к CSV и XLS файлам
    csv_file = "./mxm_1d_result_twos.csv"  # Замените на путь к вашему CSV-файлу
    xls_file = "./mxm_1d_result_twos.xlsx"  # Используйте .xlsx вместо .xls

    # Вызов функции для преобразования
    csv_to_xls(csv_file, xls_file)
    input()