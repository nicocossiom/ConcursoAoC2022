folder = "./inputs"
ifile = "inputDia"
number_of_days = 25
for i in range(2, number_of_days+1):
    open(folder+"/"+ifile+str(i)+"A", "w").close()
    open(folder+"/"+ifile+str(i)+"B", "w").close()
