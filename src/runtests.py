import subprocess
from itertools import product


METHODS = {
    1: {
        'name': 'sp',
        'valid_data_methods': [1, 2, 3, 4], 
        'valid_storage': [0],
        'sizes': [40000000, 41000000, 42000000, 43000000, 44000000, 45000000, 
                 46000000, 47000000, 48000000, 49000000, 50000000, 51000000,
                 52000000, 53000000, 54000000, 55000000],
        'runs': 50
    },
    2: {
        'name': 'mxv',
        'valid_data_methods': [1, 2, 3, 4],  
        'valid_storage': [0, 1],
        'sizes': [500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 
                 600, 610, 620, 630, 640, 650],
        'runs': 50
    },
    3: {
        'name': 'mxm',
        'valid_data_methods': [1, 2, 3, 4],
        'valid_storage': [0, 1],
        'sizes': [180, 190, 200, 210, 220, 230, 240, 250, 260, 270,
                 280, 290, 300, 310, 320, 330],
        'runs': 50
    }
}


DATA_METHODS = {
    1: 'zeros',
    2: 'random',
    3: 'twos',
    4: 'custom_pattern' 
}

def is_valid_combination(method, data_method, storage):
    """Проверяет допустимость комбинации параметров"""
    return (data_method in METHODS[method]['valid_data_methods'] and
            storage in METHODS[method]['valid_storage'])

def run_benchmark(method, size, runs, data_method, storage):
    """Запускает тест с указанными параметрами"""
    command = [
        "python", "benchmark.py",
        str(method), str(size), str(runs), str(data_method), str(storage)
    ]
    try:
        subprocess.run(command, check=True)
        data_desc = DATA_METHODS.get(data_method, f'unknown({data_method})')
        print(f"Успешно: {METHODS[method]['name']}, size={size}, runs={runs}, "
              f"data={data_desc}, storage={'2D' if storage else '1D'}")
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при запуске {command}: {e}")

if __name__ == "__main__":
    print("Начало тестирования с индивидуальными параметрами\n")
    print("Доступные data_methods:")
    for num, desc in DATA_METHODS.items():
        print(f"{num}: {desc}")
    
    for method in METHODS:
        cfg = METHODS[method]
        print(f"\nМетод: {cfg['name'].upper()}")
        print(f"Допустимые data_methods: {cfg['valid_data_methods']}")
        print(f"Размеры: {cfg['sizes']}")
        print(f"Запусков: {cfg['runs']}")
        print("-" * 60)
        
        for size, data_method, storage in product(cfg['sizes'], 
                                               cfg['valid_data_methods'],
                                               cfg['valid_storage']):
            if is_valid_combination(method, data_method, storage):
                run_benchmark(method, size, cfg['runs'], data_method, storage)
            else:
                print(f"Пропуск: {cfg['name']}, data={data_method}, storage={storage} - недопустимая комбинация")
    
    print("\nТестирование завершено")