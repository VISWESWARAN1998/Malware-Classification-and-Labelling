# SWAMI KARUPPASWAMI THUNNAI

import glob
import csv

def initialize():
    with open("header.txt", "r") as file:
        headers = file.readlines()
        headers = [header.strip() for header in headers]
        headers = list(filter(None, headers))
        headers.append("RESULT")
        return headers

def add_row(row):
    with open("dataset.csv", "a", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(row)

def add_directory(dir_location, result, header):
    global compiled_files, omitted_files
    files = glob.glob(dir_location+"/*.txt")
    for file in files:
        if "packed.txt" in file:
            print("Omitted Packed")
        elif "frequency.txt" in file:
            print("Omitted Frequency")
        elif "scanned_hash.txt" in file:
            print("Omitted Scanned Hash")
        else:
            row = [0 for i in range(len(header))]
            row[len(header)-1] = result
            with open(file, "r") as func_file:
                print("[*] COMPILING: ", file)
                functions = func_file.readlines()
                functions = [function.strip() for function in functions]
                functions = list(filter(None, functions))
                if len(functions) > 5:
                    for function in functions:
                        if function[len(function)-1] == "W":
                            print("Stemming ", function, " To: ", function[:-1])
                            function = function[:-1]
                        if function[len(function)-1] == "A":
                            print("Stemming ", function, " To: ", function[:-1])
                            function = function[:-1]
                        try:
                            row[header.index(function)] = 1
                        except ValueError:
                            print(function, " is omitted!")
                    compiled_files += 1
                    add_row(row)
                else:
                    print(file, " is omitted!")
                    omitted_files += 1
            print(compiled_files, omitted_files)
                    
                    


if __name__ == "__main__":
    header = initialize()
    add_row(header)
    compiled_files = 0
    omitted_files = 0
    add_directory("backdoor", 0, header)
    add_directory("downloader", 1, header)
    add_directory("keylogger", 2, header)
    add_directory("miner", 3, header)
    add_directory("ransom", 4, header)
    add_directory("rouge", 5, header)
    add_directory("trojan", 6, header)
    add_directory("worm", 7, header)
    
    
