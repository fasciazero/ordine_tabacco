import pandas as pd
import xlwt
from xlwt import Workbook
import json

# Workbook is created
wb = Workbook()

# add_sheet is used to create sheet.
sheet1 = wb.add_sheet('Foglio1')

#file = open(r'C:\Users\Secernato\Documents\Qt projects\ordine_tabacco\database.json')
with open(r'C:\Users\Secernato\Documents\Qt projects\ordine_tabacco\database.json') as json_data:
    d = json.loads(json_data.read())
    json_data.close()

for row in range(1, 165):
    if((d["elenco"][row-1]["codice"] != "CODICE AAMS") or (d["elenco"][row-1]["codice"] != "CODICE AAMS")):
        if(d["elenco"][row-1]["totale"] != "0"):
            sheet1.write(row, 0, d["elenco"][row-1]["codice"])
            sheet1.write(row, 1, d["elenco"][row-1]["totale"])


wb.save(r'C:\Users\Secernato\Desktop\Excel_per_INVIO_ORDINE.xls')
