# SWAMI KARUPPASWAMI THUNNAI

import nltk

dataset = input("Dataset Path: ")
dataset_path = dataset+"/frequency.txt"
frequency_table = []

with open(dataset_path, "r") as file:
    imports = file.readlines()
    for _import in imports:
        _import = _import.strip()
        if "@" in _import:
            pass
        else:
            frequency_table.append(_import)
if "ransom" in dataset:
    dataset += "ware"
nltk.FreqDist(frequency_table).plot(50, title=dataset)
