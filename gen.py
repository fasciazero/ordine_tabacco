import pandas as pd
import numpy as np
import xlrd
import json

file = pd.read_excel(r'C:\Users\Secernato\Documents\Qt projects\ordine_tabacco\ORDINE TABACCO.xlsx', sheet_name = None)
file2 = open(r'C:\Users\Secernato\Documents\Qt projects\ordine_tabacco\database.json', "w")
obj = {"elenco" : []}
for row in range(0, 167):
    single_data = {
    "codice" : str(file["Foglio1"].iloc[row, 1]),
    "nome" : file["Foglio1"].iloc[row, 0],
    "quantita" : str(0),
    "totale" : "0"
}
    obj["elenco"].append(single_data)

file2.write(json.dumps(obj))
file2.close()
