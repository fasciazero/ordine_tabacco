import pandas as pd
import xlwt
from xlwt import Workbook

# Workbook is created
wb = Workbook()

# add_sheet is used to create sheet.
sheet1 = wb.add_sheet('Foglio1')

for row in range(1, 165):
    sheet1.write(row, 0, '338')
    sheet1.write(row, 1, '2')


wb.save(r'C:\Users\Oscar\Desktop\Excel_per_INVIO_ORDINE.xls')
