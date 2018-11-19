'''
this make a graph plotting in matplotlib a matrix like :

    |---------------------------------------------------|
    |                                                   |
    |   |-------------------------------------------|   |
    |   |                                           |   |
    |   |   |-----------------------------------|   |   |
    |   |   |  number of the generation         |   |   |
    |   |   |-----------------------------------|   |   |
    |   |                                           |   |
    |   |-------------------------------------------|   |
    |                                                   |
    |                                                   |
    |   |-------------------------------------------|   |
    |   |  population 1                             |   |
    |   |   |-----------------------------------|   |   |
    |   |   |   allele 1                        |   |   |
    |   |   |-----------------------------------|   |   |
    |   |                                           |   |
    |   |   |-----------------------------------|   |   |
    |   |   |  allele 2                         |   |   |
    |   |   |-----------------------------------|   |   |
    |   |                                           |   |
    |   |-------------------------------------------|   |
    |                                                   |
    |                                                   |
    |   |-------------------------------------------|   |
    |   |  population 2                             |   |
    |   |   |-----------------------------------|   |   |
    |   |   |   allele 1                        |   |   |
    |   |   |-----------------------------------|   |   |
    |   |                                           |   |
    |   |-------------------------------------------|   |
    |                                                   |
    |---------------------------------------------------|

it load from a file writen sush as :

0\t0.1|0.9\t0.5|0.5
1\t0.2|0.4|0.4\t0.5|0.5
etc...

'''



import matplotlib.pyplot as plt

#plt.ion()
#matplotlib.interactive(True)

fig = plt.figure()
fig.canvas.set_window_title('Frequenza delle Allele')
ax1 = fig.add_subplot(1,1,1)

pullData = open("Output.txt","r").read()
dataArray = pullData.split('\n')


lineSansT = []
for l in dataArray:
    lineSansT.append(l.split('\t'))


vari = []
matrix = []
for l in lineSansT[:(len(lineSansT)-1)]:
    for e in l[:(len(l)-1)]:
        y = e.split('|')
        vari.append(y)

    if(matrix == []):
        for el in vari:
            matrix.append([])

            
    #si pas de nouvelle population c est ajoute		
    if(len(matrix) == len(vari)):
        cnt = 0 #population indice
        
        for el in vari:
            cnt2 = 0 #allele type indice
            for ele in el:
                if(len(matrix[cnt]) < len(el)):
                    for nbrCasesManquantes in range(0,len(el)-len(matrix[cnt])):
                        matrix[cnt].append([])
                        
                matrix[cnt][cnt2].append(float(ele))
                
                if(len(matrix[0][0]) > len(matrix[cnt][cnt2])):
                    zeros = []
                    a = len(matrix[0][0])-len(matrix[cnt][cnt2])
		    #print a

                    for additionalZero in range(0,a):
                        zeros.append(float(0.0))
                    matrix[cnt][cnt2] += zeros
                    matrix[cnt][cnt2].reverse()
                
                cnt2 = 1+cnt2
                
                
            cnt = 1+cnt
           
    vari = []
	

#print matrix

ax1.clear()
ax1.set_ylim([0, 1])
ax1.set_xlabel("generation")

	
cnt3 = 0

for caselle in matrix[1:]:
    for caselline in caselle:
        ax1.plot(matrix[0][0],caselline)

bamboo = False
		
for casellinette_ in range(0,len(matrix[0][0])):
    for caselle_ in matrix[1:]:
        for caselline_ in caselle_:
            if(caselline_[casellinette_] == 0 or caselline_[casellinette_] == 1):	
                cnt3 = 1+cnt3

    if(cnt3 == 4 and bamboo == False):
        bamboo = True
        #ax1.set_xlim([0,casellinette_+10])
    cnt3 = 0

			
		

plt.show()
