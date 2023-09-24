items = {"P58B23040509":{"Name" : "Barcode Scanner", "Price" : 100000}}

print("Scan your BarCode")
value = input()

for key in items.keys():
    if key==value:
        print('This is:',items[key])
        break
else:
    print("Item Not Found",value)