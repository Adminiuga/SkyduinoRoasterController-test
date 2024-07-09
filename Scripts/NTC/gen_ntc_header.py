#!/usr/bin/python3

# will use argparser next time, instead of hardcoding
# the CSV file is expected to contain the following columns
# Temp, Rmin, Rnom, Rmax, TCR, positive tolerance, negative tolerance
# this data is based on https://www.analogtechnologies.com/document/High_Presision_Thermistor_with_Stainless_Housing.pdf

NTC_FILE = "./100K-NTC.csv"
ADC_BITS = 12
# NTC is connected as a Resistive voltage divider
# 3V3 - R1 - ADC_Input - NTC - GND
R1 = 10000
# Output file
OUT_FILE = "./ntc-data.h"

ADC_MAX = (1 << ADC_BITS) - 1

def res2adc(resistance: float) -> int:
    adc_reading = (ADC_MAX * resistance) / (R1 + resistance)
    adc_reading = round(adc_reading)
    return adc_reading


import csv
is_first_output_line = True
line_count = 0;

with open(OUT_FILE, "w", encoding="utf-8") as out_file:
    out_file.write("#define NTC_DATA { \\\r\n")
    with open(NTC_FILE, newline='', encoding="utf-8-sig") as csvfile:
        rdr = csv.DictReader(csvfile, dialect='excel')
        for row in rdr:
            temp = int(row["Temp"])
            r = float(row["Rnom"].replace(',', ''))
            adc = res2adc(r)
            if is_first_output_line: 
                out_file.write(f"\t{{{temp}, {adc}}}")
                is_first_output_line = False
            else:
                out_file.write(f", \\\r\n\t{{{temp}, {adc}}}")
            line_count += 1
    out_file.write(" \\\r\n} // NTC_DATA\r\n")
    out_file.write(f"#define NTC_TABLE_SIZE {line_count}\r\n")
